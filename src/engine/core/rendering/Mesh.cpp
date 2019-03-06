#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <assimp/mesh.h>
#include <functional>

#include "Mesh.hpp"
#include "GLHelpers.h"
#include "Demangle.h"

using namespace en;

Mesh::~Mesh() {

	glDeleteBuffers(1, &m_indexBufferId);

	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteBuffers(1, &m_normalBufferId);
	glDeleteBuffers(1, &m_uvBufferId);
	glDeleteBuffers(1, &m_tangentBufferId);
	glDeleteBuffers(1, &m_bitangentBufferId);

	glDeleteVertexArrays(1, &m_vao);
}

Mesh::Mesh(const aiMesh* aiMesh) :
	m_indices   (aiMesh->mNumFaces * 3),
	m_vertices  (aiMesh->mNumVertices),
	m_uvs       (aiMesh->mNumVertices),
	m_normals   (aiMesh->mNumVertices),
	m_tangents  (aiMesh->mNumVertices),
	m_bitangents(aiMesh->mNumVertices)
{

	static const auto toGlmVec3D = [](const aiVector3D& vec) -> glm::vec3 {return {vec.x, vec.y, vec.z};};
	static const auto toGlmVec2D = [](const aiVector3D& vec) -> glm::vec2 {return {vec.x, vec.y};};

	unsigned int counter = 0;
	for (unsigned int i = 0; i < aiMesh->mNumFaces; ++i) {
		const aiFace& face = aiMesh->mFaces[i];
		assert(face.mNumIndices == 3 && "Detected non-triangular face in mesh.");

		for (unsigned int j = 0; j < face.mNumIndices; ++j) {
			m_indices[counter++] = face.mIndices[j];
		}
	}

	if (aiMesh->HasPositions())
		std::transform(aiMesh->mVertices, aiMesh->mVertices + aiMesh->mNumVertices, m_vertices.begin(), toGlmVec3D);

	if (aiMesh->HasNormals())
		std::transform(aiMesh->mNormals , aiMesh->mNormals + aiMesh->mNumVertices , m_normals.begin(), toGlmVec3D);

	if (aiMesh->HasTextureCoords(0))
		std::transform(aiMesh->mTextureCoords[0], aiMesh->mTextureCoords[0] + aiMesh->mNumVertices, m_uvs.begin(), toGlmVec2D);

	generateTangentsAndBitangents();
	buffer();
}

/**
 * Load reads the obj data into a new mesh using C++ combined with c style coding.
 * The result is an indexed mesh for use with glDrawElements.
 * Expects a obj file with following layout v/vt/vn/f eg
 *
 * For example the obj file for a simple plane describes two triangles, based on
 * four vertices, with 4 uv's all having the same vertex normals (NOT FACE NORMALS!)
 *
 * v 10.000000 0.000000 10.000000              //vertex 1
 * v -10.000000 0.000000 10.000000             //vertex 2
 * v 10.000000 0.000000 -10.000000             //vertex 3
 * v -10.000000 0.000000 -10.000000            //vertex 4
 * vt 0.000000 0.000000                        //uv 1
 * vt 1.000000 0.000000                        //uv 2
 * vt 1.000000 1.000000                        //uv 3
 * vt 0.000000 1.000000                        //uv 4
 * vn 0.000000 1.000000 -0.000000              //normal 1 (normal for each vertex is same)
 * s off
 *
 * Using these vertices, uvs and normals we can construct faces, made up of 3 triplets (vertex, uv, normal)
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * So although this is a good format for blender and other tools reading .obj files, this is
 * not an index mechanism that OpenGL supports out of the box.
 * The reason is that OpenGL supports only one indexbuffer, and the value at a certain point in the indexbuffer, eg 3
 * refers to all three other buffers (v, vt, vn) at once,
 * eg if index[0] = 5, opengl will stream vertexBuffer[5], uvBuffer[5], normalBuffer[5] into the shader.
 *
 * So what we have to do after reading the file with all vertices, is construct unique indexes for
 * all pairs that are described by the faces in the object file, eg if you have
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * v/vt/vn[0] will represent 2/1/1
 * v/vt/vn[1] will represent 1/2/1
 * v/vt/vn[2] will represent 3/3/1
 * v/vt/vn[3] will represent 4/4/1
 *
 * and that are all unique pairs, after which our index buffer can contain:
 *
 * 0,1,2,3,0,2
 *
 * So the basic process is, read ALL data into separate arrays, then use the faces to
 * create unique entries in a new set of arrays and create the indexbuffer to go along with it.
 *
 * Note that loading this mesh isn't cached like we do with texturing, this is an exercise left for the students.
 */
Mesh* Mesh::load(std::string pFilename) {

	std::cout << "Loading " << pFilename << "...";

	Mesh* mesh = new Mesh();

	std::ifstream file(pFilename, std::ios::in);
	if (!file.is_open()) {
		std::cout << "Could not read " << pFilename << std::endl;
		delete mesh;
		return nullptr;
	}

	//these three vectors will contains data as taken from the obj file
	//in the order it is encountered in the object file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	//in addition we create a map to store the triplets found under the f(aces) section in the
	//object file and map them to an index for our index buffer (just number them sequentially
	//as we encounter them and store references to the pack
	std::map<FaceIndexTriplet, unsigned> mappedTriplets;

	const auto addTriplet = [&](const FaceIndexTriplet triplet) {

		const auto found = mappedTriplets.find(triplet);
		if (found != mappedTriplets.end()) {

			const unsigned index = found->second;
			mesh->m_indices.push_back(index);
			return;
		}

		//so create a new index value, and map our triplet to it
		const auto index = static_cast<unsigned>(mappedTriplets.size());
		mappedTriplets[triplet] = index;

		//now record this index
		mesh->m_indices.push_back(index);
		//and store the corresponding vertex/normal/uv values into our own buffers
		//note the -1 is required since all values in the f triplets in the .obj file
		//are 1 based, but our vectors are 0 based
		mesh->m_vertices.push_back(vertices[triplet.v  - 1]);
		mesh->m_normals .push_back(normals [triplet.n  - 1]);
		mesh->m_uvs     .push_back(uvs     [triplet.uv - 1]);
	};

	std::string line; // to store each line in
	while (getline(file, line)) {

		// c-type string to store cmd read from obj file (cmd is v, vt, vn, f)
		char cmd[10];
		cmd[0] = 0;

		//get the first string in the line of max 10 chars (c-style)
		sscanf(line.c_str(), "%10s", cmd);

		//note that although the if statements below seem to imply that we can
		//read these different line types (eg vertex, normal, uv) in any order,
		//this is just convenience coding for us (instead of multiple while loops)
		//we assume the obj file to list ALL v lines first, then ALL vt lines,
		//then ALL vn lines and last but not least ALL f lines last

		//so... start processing lines
		//are we reading a vertex line? straightforward copy into local vertices vector
		if (strcmp(cmd, "v") == 0) {

			glm::vec3 vertex;
			sscanf(line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);

			//or are we reading a normal line? straightforward copy into local normal vector
		} else if (strcmp(cmd, "vn") == 0) {

			glm::vec3 normal;
			sscanf(line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);

			//or are we reading a uv line? straightforward copy into local uv vector
		} else if (strcmp(cmd, "vt") == 0) {

			glm::vec2 uv;
			sscanf(line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y);
			uvs.push_back(uv);

			//this is where it gets nasty. After having read all vertices, normals and uvs into
			//their own buffer
		} else if (strcmp(cmd, "f") == 0) {

			//an f lines looks like
			//f 2/1/1 1/2/1 3/3/1
			//in other words
			//f v1/u1/n1 v2/u2/n2 v3/u3/n3
			//for each triplet like that we need to check whether we already encountered it
			//and update our administration based on that
			glm::ivec4 vertexIndex;
			glm::ivec4 normalIndex;
			glm::ivec4 uvIndex;
			const int numRead = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

			switch (numRead) {

				// 3 vertices
				case 10:
					for (int i = 0; i < 3; ++i)
						addTriplet(FaceIndexTriplet(vertexIndex[i], uvIndex[i], normalIndex[i]));
					break;
				// 4 vertices
				case 13:
					for (int i = 0; i < 3; ++i)
						addTriplet(FaceIndexTriplet(vertexIndex[i], uvIndex[i], normalIndex[i]));

					addTriplet(FaceIndexTriplet(vertexIndex[0], uvIndex[0], normalIndex[0]));
					addTriplet(FaceIndexTriplet(vertexIndex[2], uvIndex[2], normalIndex[3]));
					addTriplet(FaceIndexTriplet(vertexIndex[3], uvIndex[3], normalIndex[3]));
					break;
				default:
					//If we read a different amount, something is wrong
					std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
					delete mesh;
					return nullptr;
			}
		}
	}
	file.close();

	mesh->generateTangentsAndBitangents();
	mesh->buffer();

	std::cout << "Mesh loaded and buffered:" << (mesh->m_indices.size() / 3.0f) << " triangles." << std::endl;
	return mesh;
}

void Mesh::render(GLint verticesAttrib, GLint normalsAttrib, GLint uvsAttrib, GLint tangentAttrib, GLint bitangentAttrib) const {

	glCheckError();
	glBindVertexArray(m_vao);
	glCheckError();

	if (verticesAttrib > -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		glCheckError();
		glEnableVertexAttribArray(static_cast<GLuint>(verticesAttrib));
		glCheckError();
		glVertexAttribPointer(static_cast<GLuint>(verticesAttrib), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glCheckError();
	}
	glCheckError();

	if (normalsAttrib > -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
		glEnableVertexAttribArray(static_cast<GLuint>(normalsAttrib));
		glVertexAttribPointer(static_cast<GLuint>(normalsAttrib), 3, GL_FLOAT, GL_TRUE, 0, nullptr);
	}
	glCheckError();

	if (uvsAttrib > -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
		glEnableVertexAttribArray(static_cast<GLuint>(uvsAttrib));
		glVertexAttribPointer(static_cast<GLuint>(uvsAttrib), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	}
	glCheckError();

	if (tangentAttrib > -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_tangentBufferId);
		glEnableVertexAttribArray(static_cast<GLuint>(tangentAttrib));
		glVertexAttribPointer(static_cast<GLuint>(tangentAttrib), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	}
	glCheckError();

	if (bitangentAttrib > -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_bitangentBufferId);
		glEnableVertexAttribArray(static_cast<GLuint>(bitangentAttrib));
		glVertexAttribPointer(static_cast<GLuint>(bitangentAttrib), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	}
	glCheckError();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);

	glCheckError();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
	glCheckError();

	if (bitangentAttrib > -1) glDisableVertexAttribArray(static_cast<GLuint>(bitangentAttrib));
	if (tangentAttrib   > -1) glDisableVertexAttribArray(static_cast<GLuint>(tangentAttrib));
	if (uvsAttrib       > -1) glDisableVertexAttribArray(static_cast<GLuint>(uvsAttrib));
	if (normalsAttrib   > -1) glDisableVertexAttribArray(static_cast<GLuint>(normalsAttrib));
	if (verticesAttrib  > -1) glDisableVertexAttribArray(static_cast<GLuint>(verticesAttrib));

	glBindVertexArray(0);
}

void Mesh::drawDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {

	//demo of how to render some debug info using the good ol' direct rendering mode...
	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(pProjectionMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(pViewMatrix * pModelMatrix));

	glBegin(GL_LINES);
	//for each index draw the normal starting at the corresponding vertex
	for (std::size_t index : m_indices) {

		//draw normal for vertex
		glm::vec3 normal = m_normals[index];
		glColor3fv(glm::value_ptr(normal));
		glm::vec3 normalStart = m_vertices[index];
		glVertex3fv(glm::value_ptr(normalStart));
		glm::vec3 normalEnd = normalStart + normal * 0.2f;
		glVertex3fv(glm::value_ptr(normalEnd));
	}
	glEnd();
}

void Mesh::generateTangentsAndBitangents() {

	const std::size_t numVertices  = m_vertices.size();
	const std::size_t numTriangles = m_indices.size() / 3;

	m_tangents.clear();
	m_tangents.resize(numVertices, glm::vec3(0));
	m_bitangents.clear();
	m_bitangents.resize(numVertices, glm::vec3(0));

	for (std::size_t i = 0; i < numTriangles; ++i) {

		const std::size_t index0 = m_indices[i * 3 + 0];
		const std::size_t index1 = m_indices[i * 3 + 1];
		const std::size_t index2 = m_indices[i * 3 + 2];
		const glm::vec3& v0 = m_vertices[index0];
		const glm::vec3& v1 = m_vertices[index1];
		const glm::vec3& v2 = m_vertices[index2];
		const glm::vec2& uv0 = m_uvs[index0];
		const glm::vec2& uv1 = m_uvs[index1];
		const glm::vec2& uv2 = m_uvs[index2];

		const glm::vec3 delta1 = v1 - v0;
		const glm::vec3 delta2 = v2 - v0;
		const glm::vec2 deltaUV1 = uv1 - uv0;
		const glm::vec2 deltaUV2 = uv2 - uv0;

		const float f = 1.f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		glm::vec3 tangent;
		tangent.x = f * (deltaUV2.y * delta1.x - deltaUV1.y * delta2.x);
		tangent.y = f * (deltaUV2.y * delta1.y - deltaUV1.y * delta2.y);
		tangent.z = f * (deltaUV2.y * delta1.z - deltaUV1.y * delta2.z);
		tangent = glm::normalize(tangent);

		glm::vec3 bitangent;
		bitangent.x = f * (-deltaUV2.x * delta1.x + deltaUV1.x * delta2.x);
		bitangent.y = f * (-deltaUV2.x * delta1.y + deltaUV1.x * delta2.y);
		bitangent.z = f * (-deltaUV2.x * delta1.z + deltaUV1.x * delta2.z);
		bitangent = glm::normalize(bitangent);

		m_tangents[index0] += tangent;
		m_tangents[index1] += tangent;
		m_tangents[index2] += tangent;
		m_bitangents[index0] += bitangent;
		m_bitangents[index1] += bitangent;
		m_bitangents[index2] += bitangent;
	}

	for (std::size_t index = 0; index < numVertices; ++index) {
		m_tangents  [index] = glm::normalize(m_tangents[index]);
		m_bitangents[index] = glm::normalize(m_bitangents[index]);
	}
}

void Mesh::buffer() {

	glGenBuffers(1, &m_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned), m_indices.data(), GL_STATIC_DRAW);
	glCheckError();

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_STATIC_DRAW);
	glCheckError();

	glGenBuffers(1, &m_normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW);
	glCheckError();

	glGenBuffers(1, &m_uvBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), m_uvs.data(), GL_STATIC_DRAW);
	glCheckError();

	glGenBuffers(1, &m_tangentBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_tangentBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_tangents.size() * sizeof(glm::vec3), m_tangents.data(), GL_STATIC_DRAW);
	glCheckError();

	glGenBuffers(1, &m_bitangentBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_bitangentBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_bitangents.size() * sizeof(glm::vec3), m_bitangents.data(), GL_STATIC_DRAW);
	glCheckError();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_vao);
	glCheckError();
}
