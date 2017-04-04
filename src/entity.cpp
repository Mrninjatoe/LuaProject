#include "entity.hpp"

Entity::Entity() {

}

void Entity::render() {
	glBindVertexArray(_vao);

	glDrawElements(
		GL_TRIANGLES,
		_indices.size(),
		GL_UNSIGNED_INT,
		0
	);
}

Entity::~Entity() {
	glDeleteBuffers(sizeof(_vbo), &_vao);
	glDeleteBuffers(sizeof(_vbo), &_vbo);
	glDeleteBuffers(sizeof(_vbo), &_ibo);
}

void Entity::_fixBuffers() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);
}

void Entity::_fixVertAttributes() {
	glBindVertexArray(_vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec2)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec2) + sizeof(glm::vec3)));

	glBindVertexArray(0);
}

