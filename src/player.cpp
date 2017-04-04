#include "player.hpp"

// BUFFER_OFFSET is defined in entity.hpp

Player::Player(glm::vec3 pos) {
	_texture = std::make_shared<Texture>("assets/textures/environment_block.png");
	_vertices = {
		Vertex{glm::vec2(-1, -1), glm::vec3(0.3,0.5,0.3), glm::vec2(0, 0)	},
		Vertex{glm::vec2(-1, 1), glm::vec3(0.63,0.32,0.07), glm::vec2(1, 0)	},
		Vertex{glm::vec2(1, 1), glm::vec3(0.3,0.5,0.3), glm::vec2(0, 1)		},
		Vertex{glm::vec2(1, -1), glm::vec3(0.3,0.5,0.3), glm::vec2(1, 1)	}
	};
	_indices = { 0, 1, 2, 0, 2, 3};

	_pos = (pos * glm::vec3(2));
	_model = glm::translate(_pos) * glm::scale(glm::vec3(1));

	_fixBuffers();
	_fixVertAttributes();
}

void Player::update(float delta) {
	_model = glm::translate(_pos) * glm::scale(glm::vec3(1));
}

glm::mat4 Player::getModel() const{
	return _model;
}

void Player::move(glm::vec3 _dir) {
	_pos += _dir;
}