//
// Created by Арлан on 21.04.2023.
//

#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include "State.h"
#include "PauseMenuState.h"
#include "MapGenerator.h"
#include "Pig.h"
#include "Wolf.h"

class GameState : public State {
 private:
  sf::Font font;
  PauseMenuState* pause_menu;
  Player* player;
  MapGenerator* map_gen;
  std::vector<std::pair<int, int> > carrot_vector;

  float default_speed = 5.f;

  sf::RectangleShape background;

  size_t pig_amount = 6;
  size_t wolf_amount = 2;
  int baby_born = 0;
  std::vector<Pig*> pig_vector;
  std::vector<Wolf*> wolf_vector;
  //Pig* piggy;

  // Functions
  int GetRandomNumber(int min, int max);
  std::pair<float, float> GetRandomCoords(int min, int max);

  void Init_KeyBinds();
  void Init_Fonts();
  void Init_Texture();
  void Init_PauseMenu();
  void Init_Sprite();
  void Init_Players();
  void Init_Animals();
  void Init_Map();

 public:
  std::vector<std::vector<int> > map;
  GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
  virtual ~GameState();

  // Functions
  void UpdateInput(const float& dt);
  void UpdatePlayerInput(const float& dt);
  void UpdatePigBorn();
  void Update(const float& dt);
  void Render(sf::RenderTarget* target = nullptr);
};


#endif //GAME_GAMESTATE_H
