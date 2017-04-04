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