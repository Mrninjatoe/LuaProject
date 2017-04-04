#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <vector>

struct Vertex {
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 uv;
};

class Entity {
public:
	Entity();
	virtual ~Entity() {};
	virtual void update() = 0;
	virtual glm::mat4 getModel() const = 0;
	void render();

private:

protected:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;

	GLuint _vao;
	GLuint _vbo;
	GLuint _ibo;

	glm::mat4 _model;
};