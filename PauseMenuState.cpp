//
// Created by Арлан on 05.05.2023.
//

#include "PauseMenuState.h"

PauseMenuState::PauseMenuState(sf::View camera_view, sf::Font& font) : fonts(font){
  this->camera = camera_view;

  // Text
  this->menu_text.setFont(fonts);
  this->menu_text.setFillColor(sf::Color::White);
  this->menu_text.setCharacterSize(180);
  this->menu_text.setString("--PAUSED--");
}

PauseMenuState::~PauseMenuState() {

}

// Functions

void PauseMenuState::Update(const sf::Vector2f& mousePos) {

}

void PauseMenuState::Render(sf::RenderTarget* target, const float x, const float y) {
  this->menu_text.setPosition(x - 400, y - 1800);
  target->draw(this->menu_text);
}