#pragma once
#include "shaderprogram.hpp"
#include <fstream>
#include <iostream>
#include <memory>

ShaderProgram::ShaderProgram(const std::string &vertex, const std::string &fragment) {

	_shaders.push_back(glCreateShader(GL_VERTEX_SHADER));
	_shaders.push_back(glCreateShader(GL_FRAGMENT_SHADER));

	std::string vertexCode;
	std::ifstream vertexFile(vertex, std::ios::in);
	if (vertexFile.is_open()) {
		std::string line = "";
		while (getline(vertexFile, line))
			vertexCode += "\n" + line;
		vertexFile.close();
	}else
		printf("Could not open vertex shader!\n");

	std::string fragmentCode;
	std::ifstream fragmentFile(fragment, std::ios::in);
	if (fragmentFile.is_open()) {
		std::string line = "";
		while (getline(fragmentFile, line)) 
			fragmentCode += "\n" + line;
		fragmentFile.close();
	}
	else
		printf("Could not open fragment shader!\n");

	std::vector<std::string> sourceCodes;
	sourceCodes.push_back(vertexCode);
	sourceCodes.push_back(fragmentCode);
	
	_compileShaders(sourceCodes);
}

ShaderProgram::~ShaderProgram(){
	glUseProgram(0);
	glDeleteProgram(_shaderProgram);
}

void ShaderProgram::_compileShaders(std::vector<std::string> &sourceCodes) {
	GLint result = GL_FALSE;
	int infoLogLength = 0;

	// Vertex
	char const * sourcePointer = sourceCodes[0].c_str();
	glShaderSource(_shaders[0], 1, &sourcePointer, NULL);
	glCompileShader(_shaders[0]);

	glGetShaderiv(_shaders[0], GL_COMPILE_STATUS, &result);
	glGetShaderiv(_shaders[0], GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> vertErrorMsg(infoLogLength + 1);
		glGetShaderInfoLog(_shaders[0], infoLogLength, NULL, &vertErrorMsg[0]);
		printf("%s\n", &vertErrorMsg[0]);
	}

	sourcePointer = sourceCodes[1].c_str();
	glShaderSource(_shaders[1], 1, &sourcePointer, NULL);
	glCompileShader(_shaders[1]);

	glGetShaderiv(_shaders[1], GL_COMPILE_STATUS, &result);
	glGetShaderiv(_shaders[1], GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> fragErrorMsg(infoLogLength + 1);
		glGetShaderInfoLog(_shaders[1], infoLogLength, NULL, &fragErrorMsg[0]);
		printf("%s\n", &fragErrorMsg[0]);
	}

	_linkProgram();
}

void ShaderProgram::_linkProgram() {
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _shaders[0]);
	glAttachShader(_shaderProgram, _shaders[1]);
	glLinkProgram(_shaderProgram);

	glDetachShader(_shaderProgram, _shaders[0]);
	glDetachShader(_shaderProgram, _shaders[1]);

	glDeleteShader(_shaders[0]);
	glDeleteShader(_shaders[1]);

	GLint result = GL_FALSE;
	int infoLogLength = 0;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &result);
	glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMsg(infoLogLength + 1);
		glGetProgramInfoLog(_shaderProgram, infoLogLength, NULL, &programErrorMsg[0]);
		printf("%s\n", &programErrorMsg[0]);
	}
}

ShaderProgram& ShaderProgram::bindShader() {
	glUseProgram(_shaderProgram);

	return *this;
}

ShaderProgram& ShaderProgram::addUniform(const std::string& name, glm::mat4& matrix) {
	GLint loc = glGetUniformLocation(_shaderProgram, name.c_str());
	glUniformMatrix4fv(loc, 1, false, &matrix[0][0]);
	return *this;
}

ShaderProgram& ShaderProgram::addUniform(const std::string& name, float& inFloat) {
	GLint loc = glGetUniformLocation(_shaderProgram, name.c_str());
	glUniform1f(loc, inFloat);
	return *this;
}
