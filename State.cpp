//
// Created by Арлан on 21.04.2023.
//

#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states) {
  this->window = window;
  this->supported_keys = supported_keys;
  this->states = states;
  this->quit = false;
  this->pause = false;
  this->KeyTime = 0.f;
  this->KeyTimeMax = 10.f;
}

State::~State() {

}

const bool& State::GetQuit() const {
  return this->quit;
}

const bool State::GetKeyTime() {
  if (this->KeyTime >= this->KeyTimeMax) {
    this->KeyTime = 0.f;
    return true;
  }
  return false;
}

void State::EndState() {
  this->quit = true;
}

void State::PauseState() {
  this->pause = true;
}

void State::unPauseState() {
  this->pause = false;
}

void State::UpdateMousePosition() {
  this->mouse_pos_screen = sf::Mouse::getPosition();
  this->mouse_pos_window = sf::Mouse::getPosition(*this->window);
  this->mouse_pos_view = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::UpdateKeyTime(const float& dt) {
  if (this->KeyTime < this->KeyTimeMax) {
    this->KeyTime += 100.f * dt;
  }
}
