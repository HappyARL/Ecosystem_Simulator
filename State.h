//
// Created by Арлан on 21.04.2023.
//

#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State {
 protected:
  std::stack<State*>* states;
  sf::RenderWindow* window;
  std::map<std::string, int>* supported_keys;
  std::map<std::string, int> key_binds;
  bool quit;

  sf::Vector2i mouse_pos_screen;
  sf::Vector2i mouse_pos_window;
  sf::Vector2f mouse_pos_view;

  // Resources
  std::map<std::string, sf::Texture> textures;
  std::map<int, sf::Sprite> sprites;

  // Functions
  virtual void Init_KeyBinds() = 0;

 public:
  State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
  virtual~State();

  const bool& GetQuit() const;
  void EndState();
  virtual void UpdateMousePosition();
  virtual void UpdateInput(const float& dt) = 0;
  virtual void Update(const float& dt) = 0;
  virtual void Render(sf::RenderTarget* target = nullptr) = 0;
};


#endif //GAME_STATE_H
