//
// Created by Арлан on 22.04.2023.
//

#include "Entity.h"

void Entity::Init_Variables() {
  this->sprite = nullptr;
  this->texture = nullptr;
  this->movement_speed = 350.f;
}

Entity::Entity() {
  this->Init_Variables();
}

Entity::~Entity() {
  delete this->sprite;
}
// Component function
void Entity::CreateSprite(sf::Texture* texture) {
  this->texture = texture;
  this->sprite = new sf::Sprite(*this->texture);
}

// Functions

void Entity::SetPosition(const float x, const float y) {
  if (this->sprite) {
    this->sprite->setPosition(x, y);
  }
}

void Entity::SetCameraPosition(const float x, const float y) {
  if (this->sprite) {
    sf::View view(sf::Vector2f(x, y), sf::Vector2f(3*2560, 3*1440));
    this->camera_view = view;
  }
}

void Entity::Move(const float& dt, const float dir_x, const float dir_y) {
  if (this->sprite) {
    this->sprite->move(dir_x * this->movement_speed * dt,
                      dir_y * this->movement_speed * dt);
  }
}

void Entity::MoveCamera(const float &dt, const float dir_x, const float dir_y) {
  if (this->sprite) {
    this->camera_view.move(dir_x * this->movement_speed * dt,
                           dir_y * this->movement_speed * dt);
  }
}

void Entity::Zoom(const float power_zoom) {
  this->camera_view.zoom(power_zoom);
}
