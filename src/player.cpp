#include "player.hpp"
#include <glad\glad.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

Player::Player() {
	_texture = std::make_shared<Texture>("assets/textures/environment_block.png");
	_vertices = {
		Vertex{glm::vec2(-1, -1), glm::vec3(0.3,0.5,0.3), glm::vec2(0, 0)	},
		Vertex{glm::vec2(-1, 1), glm::vec3(0.63,0.32,0.07), glm::vec2(1, 0)	},
		Vertex{glm::vec2(1, 1), glm::vec3(0.3,0.5,0.3), glm::vec2(0, 1)	},
		Vertex{glm::vec2(1, -1), glm::vec3(0.3,0.5,0.3), glm::vec2(1, 1)	}
	};
	_indices = { 0, 1, 2, 0, 2, 3};

	_model = glm::translate(glm::vec3(-14, 0, 0)) * glm::scale(glm::vec3(1));

	_fixBuffers();
	_fixVertAttributes();
}

void Player::update() {

}

glm::mat4 Player::getModel() const{
	return _model;
}

void Player::_fixBuffers() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);
}

void Player::_fixVertAttributes() {
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