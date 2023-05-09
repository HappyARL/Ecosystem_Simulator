//
// Created by Арлан on 27.04.2023.
//

#include "Button.h"

Button::Button(float x, float y, float width, float height,
               std::string text, sf::Font* font,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color) {
  this->button_state = BTN_IDLE;
  this->shape.setPosition(sf::Vector2f(x, y));
  this->shape.setSize(sf::Vector2f(width, height));

  this->font = font;
  this->text.setFont(*this->font);
  this->text.setString(text);

  this->x = x;
  this->y = y;

  this->text.setFillColor(sf::Color::White);
  this->text.setCharacterSize(70);
  this->text.setPosition(
          this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
          this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
          );

  this->idle_color = idle_color;
  this->hover_color = hover_color;
  this->active_color = active_color;

  this->shape.setFillColor(this->idle_color);
}

Button::~Button() {

}

// Accessors
const bool Button::is_pressed() {
  if (this->button_state == BTN_ACTIVE) {
    return true;
  }
  return false;
}

// Functions

void Button::Update(const sf::Vector2f& mouse_pos) {
  // Idle button
  this->button_state = BTN_IDLE;
  // Hover button
  if (this->shape.getGlobalBounds().contains(mouse_pos)) {
    this->button_state = BTN_HOVER;
    // Pressed button
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      this->button_state = BTN_ACTIVE;
    }
  }

  switch (this->button_state) {
    case BTN_IDLE:
      this->shape.setFillColor(this->idle_color);
      break;
    case BTN_HOVER:
      this->shape.setFillColor(this->hover_color);
      break;
    case BTN_ACTIVE:
      this->shape.setFillColor(this->active_color);
      break;
    default:
      break;
  }
}

void Button::Render(sf::RenderTarget *target) {
  target->draw(this->shape);
  target->draw(this->text);
}
