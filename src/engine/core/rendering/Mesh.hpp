#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <GL/glew.h>
#include "glm.hpp"

#include "ResourceLoader.h"

/**
 * A mesh represents an .OBJ file. It knows how it is constructed, how its data should be buffered to OpenGL
 * and how it should be streamed to OpenGL
 */
class Mesh final {

public:

	/**
	 * Loads a mesh from an .obj file. The file has to have:
	 * vertexes, uvs, normals and face indexes. See load source
	 * for more format information.
	 */
	static Mesh* load(std::string pFilename);

	~Mesh();

	/**
	 * Streams the mesh to opengl using the given indexes for the different attributes
	 */
	void streamToOpenGL(GLint verticesAttrib = -1, GLint normalsAttrib = -1, GLint uvsAttrib = -1, GLint tangentAttrib = -1, GLint bitangentAttrib = -1);

	/**
	 * Draws debug info (normals) for the mesh using the given matrices)
	 */
	void drawDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix);

protected:
	Mesh() = default;

	// OpenGL id's for the different buffers created for this mesh
	GLuint m_indexBufferId     = 0;
	GLuint m_vertexBufferId    = 0;
	GLuint m_normalBufferId    = 0;
	GLuint m_uvBufferId        = 0;
	GLuint m_tangentBufferId   = 0;
	GLuint m_bitangentBufferId = 0;

	GLuint m_vao;

	// vertex data
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_tangents;
	std::vector<glm::vec3> m_bitangents;

	//references to the vertices/normals & uvs in previous vectors
	std::vector<unsigned> m_indices;

	//buffer vertices, normals, and uv's
	void buffer();

	//Please read the "load" function documentation on the .obj file format first.
	//FaceVertexTriplet  is a helper class for loading and converting to obj file to
	//indexed arrays.
	//If we list all the unique v/uv/vn triplets under the faces
	//section in an object file sequentially and assign them a number
	//it would be a map of FaceVertexTriplet. Each FaceVertexTriplet refers
	//to an index with the originally loaded vertex list, normal list and uv list
	//and is only used during conversion (unpacking) of the facevertextriplet list
	//to a format that OpenGL can handle.
	//So for a vertex index a FaceVertexTriplet contains the index for uv and n as well.
	struct FaceIndexTriplet {

		unsigned v;  //vertex
		unsigned uv; //uv
		unsigned n;  //normal

		FaceIndexTriplet(unsigned pV, unsigned pUV, unsigned pN)
			: v(pV), uv(pUV), n(pN) {}

		// needed for use as key in map
		bool operator < (const FaceIndexTriplet other) const {
			return memcmp((void*)this, (void*)&other, sizeof(FaceIndexTriplet)) > 0;
		}
	};
};

template<>
struct en::ResourceLoader<Mesh> {
    inline static std::shared_ptr<Mesh> load(const std::string& filename) {
        return std::shared_ptr<Mesh>(Mesh::load(filename));
    }
};

#endif // MESH_HPP
