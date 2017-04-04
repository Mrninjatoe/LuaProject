#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <vector>
#include <memory>
#include "texture.hpp"
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

struct Vertex {
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 uv;
};

class Entity {
public:
	Entity();
	virtual ~Entity();
	virtual void update(float delta) = 0;
	virtual glm::mat4 getModel() const = 0;
	virtual void move(glm::vec3 dir) = 0;
	virtual void _fixBuffers();
	virtual void _fixVertAttributes();
	void render();
private:

protected:
	std::shared_ptr<Texture> _texture;
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;

	GLuint _vao;
	GLuint _vbo;
	GLuint _ibo;

	glm::mat4 _model;
};