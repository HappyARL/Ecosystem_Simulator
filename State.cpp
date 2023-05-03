//
// Created by Арлан on 21.04.2023.
//

#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states) {
  this->window = window;
  this->supported_keys = supported_keys;
  this->states = states;
  this->quit = false;
}

State::~State() {

}

const bool& State::GetQuit() const {
  return this->quit;
}

void State::EndState() {
  this->quit = true;
}

void State::UpdateMousePosition() {
  this->mouse_pos_screen = sf::Mouse::getPosition();
  this->mouse_pos_window = sf::Mouse::getPosition(*this->window);
  this->mouse_pos_view = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
