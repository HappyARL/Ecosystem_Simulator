//
// Created by Арлан on 28.04.2023.
//

#include "Player.h"

void Player::Init_Variables() {

}

void Player::Init_Components() {

}

Player::Player(float x, float y, sf::Texture* texture) {
  this->Init_Variables();
  this->Init_Components();
  this->CreateSprite(texture);
  this->SetPosition(x, y);
  this->SetCameraPosition(x, y);
}

std::pair<float, float> Player::GetCoords() {
  std::pair<float, float> coords = std::make_pair(this->sprite->getPosition().x,
                                                  this->sprite->getPosition().y);
  return coords;
}

Player::~Player() noexcept {

}

void Player::Update(const float& dt) {

}

void Player::Render(sf::RenderTarget* target) {
  if (this->sprite) {
    target->draw(*this->sprite);
    target->setView(this->camera_view);
  }
}
