//
// Created by Арлан on 21.04.2023.
//

#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include "State.h"
#include "MapGenerator.h"

class GameState : public State {
 private:
  Player* player;
  MapGenerator* map_gen;
  std::vector<std::vector<int> > map;

  // Functions
  void Init_KeyBinds();
  void Init_Texture();
  void Init_Sprite();
  void Init_Players();
  void Init_Map();

 public:
  GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
  virtual ~GameState();

  // Functions
  void UpdateInput(const float& dt);
  void Update(const float& dt);
  void Render(sf::RenderTarget* target = nullptr);
};


#endif //GAME_GAMESTATE_H
