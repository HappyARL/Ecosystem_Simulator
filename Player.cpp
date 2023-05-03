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
}

Player::~Player() noexcept {

}