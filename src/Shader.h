#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void use();

	// Uniform-setting functions
	void setInt(const std::string& uniformName, int value);
	void setBool(const std::string& uniformName, bool value);
	void setFloat(const std::string& uniformName, float value);
	void setVec2f(const std::string& uniformName, float v0, float v1);
	void setVec3f(const std::string& uniformName, float v0, float v1, float v2);
	void setVec4f(const std::string& uniformName, float v0, float v1, float v2, float v3);
	void setMat4f(const std::string& uniformName, const glm::mat4& mat);

private:
	enum Type {VERTEX, FRAGMENT};
	static unsigned int compileShader(Type type, const char* src);
	static std::string readFromFile(const std::string& filePath);

	unsigned int id;
};
