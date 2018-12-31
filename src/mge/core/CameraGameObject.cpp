#include "glm.hpp"
#include "mge/core/CameraGameObject.hpp"

CameraGameObject::CameraGameObject( std::string pName, glm::vec3 pPosition, glm::mat4 pProjectionMatrix )
:	GameObject(pName, pPosition), _projection(pProjectionMatrix)
{
}

CameraGameObject::~CameraGameObject()
{
	//dtor
}

glm::mat4& CameraGameObject::getProjection() {
    return _projection;
}

