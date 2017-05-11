#include "entity.hpp"


Entity::Entity() {
	
}

Entity::~Entity() {
	delete[] source;
	delete[] destination;
}

void Entity::move(float x, float y) {
	posX += x;
	posY += y;
	destination->x = posX;
	destination->y = posY;
}

void Entity::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, source, destination);
}