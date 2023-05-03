//
// Created by Арлан on 26.04.2023.
//

#ifndef GAME_MAINMENUSTATE_H
#define GAME_MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State {
 private:
  sf::Texture bg_texture;
  sf::RectangleShape background;
  sf::Font font;
  sf::View main_camera;

  std::map<std::string, Button*> buttons;
  // Functions
  void Init_Variables();
  void Init_Background();
  void Init_Fonts();
  void Init_KeyBinds();
  void Init_Buttons();

 public:
  MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
  virtual ~MainMenuState();

  // Functions
  void UpdateInput(const float& dt);
  void UpdateButtons();
  void Update(const float& dt);
  void RenderButton(sf::RenderTarget* target = nullptr);
  void Render(sf::RenderTarget* target = nullptr);
};


#endif //GAME_MAINMENUSTATE_H
