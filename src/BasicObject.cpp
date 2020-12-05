#include "BasicObject.h"
#include "OpenGLApp.h"

BasicObject::BasicObject(OpenGLApp* owner_, std::shared_ptr<Texture2D> texture_, const glm::vec3& position_, const glm::vec3& scale_, float rotX_, float rotY_, float rotZ_) :
	owner(owner_),
	texture(texture_),
	vao(0),
	position(position_),
	scale(scale_),
	rotX(rotX_),
	rotY(rotY_),
	rotZ(rotZ_)
{

}
