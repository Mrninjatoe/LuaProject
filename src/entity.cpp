#include "entity.hpp"


Entity::Entity() {
	
}

Entity::~Entity() {

}

void Entity::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, source, destination);
}