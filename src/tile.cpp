#include "tile.hpp"

Tile::Tile(glm::vec3 pos, bool collision) {
	_texture = std::make_shared<Texture>("assets/textures/environment_block.png");
	_collision = collision;
	if (collision == true)
		_color = glm::vec3(0.2f);
	else
		_color = glm::vec3(0.3, 0.6, 0.3);

	_vertices = {
		Vertex{ glm::vec2(-1, -1),	_color, glm::vec2(0, 0) },
		Vertex{ glm::vec2(-1, 1),	_color, glm::vec2(1, 0) },
		Vertex{ glm::vec2(1, 1),	_color, glm::vec2(0, 1) },
		Vertex{ glm::vec2(1, -1),	_color, glm::vec2(1, 1) }
	};

	_indices = { 0, 1, 2, 0, 2, 3 };
	_pos = pos;
	_model = glm::translate(_pos) * glm::scale(glm::vec3(1));

	_fixBuffers();
	_fixVertAttributes();
}

void Tile::update(float delta) {
	_model = glm::translate(_pos) * glm::scale(glm::vec3(1));
}

glm::mat4 Tile::getModel() const {
	return _model;
}

void Tile::move(glm::vec3 _dir) {
	_pos += _dir;
}
