#pragma once
#include <string>
#include <glad\glad.h>
#include <vector>
#include <glm\glm.hpp>

class ShaderProgram {
public:
	ShaderProgram(const std::string &vertex,
		const std::string &fragment);
	virtual ~ShaderProgram();
	void _compileShaders(std::vector<std::string> &sourceCodes);
	void _linkProgram();
	ShaderProgram& bindShader();
	ShaderProgram& addUniform(const std::string& name, glm::mat4& matrix);
	ShaderProgram& addUniform(const std::string& name, float& inFloat);
private:
	GLuint _shaderProgram;
	std::vector<GLuint> _shaders;
	std::vector<GLint> _uniforms;
};