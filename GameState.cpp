//
// Created by Арлан on 21.04.2023.
//

#include "GameState.h"
#include "MapGenerator.h"

int GameState::GetRandomNumber(int min, int max) {
  //srand(time(NULL));
  int num = min + rand() % (max - min + 1);
  return num;
}

std::pair<float, float> GameState::GetRandomCoords(int min, int max) {
  int x = GetRandomNumber(min, max);
  int y = GetRandomNumber(min, max);
  while (map[x][y] == 1) {
    x = GetRandomNumber(++min, --max);
    y = GetRandomNumber(++min, --max);
  }
  std::cout << x << " " << y << '\n';
  std::pair<float, float> ans = std::make_pair(x * 100, y * 100);
  return ans;
}

void GameState::Init_KeyBinds() {
  std::ifstream ifs("Config/gamestate_keybinds.ini");

  if (ifs.is_open()) {
    std::string key = "";
    std::string key2 = "";
    while (ifs >> key >> key2) {
      this->key_binds[key] = this->supported_keys->at(key2);
    }
  }
  ifs.close();
}

void GameState::Init_Fonts() {
  if (!this->font.loadFromFile("Fonts/Futura.ttc")) {
    throw("ERROR::MAINMENUSTATE::Could not load font!");
  }
}

void GameState::Init_Texture() {
  if (!this->textures["PLAYER_IDLE"].loadFromFile("Rescources/Images/Sprites/Player/white_dot.png")) {
    throw "ERROR::GAMESTATE::Error while load Player texture!";
  }
  if (!this->textures["PIG_ALIVE"].loadFromFile("Rescources/Images/Animals/pig.png")) {
    throw "ERROR::GAMESTATE::Error while load PigAlive texture!";
  }
  if (!this->textures["PIG_DEAD"].loadFromFile("Rescources/Images/Animals/pig_dead.png")) {
    throw "ERROR::GAMESTATE::Error while load PigDead texture!";
  }
  if (!this->textures["WOLF_ALIVE"].loadFromFile("Rescources/Images/Animals/wolf.png")) {
    throw "ERROR::GAMESTATE::Error while load PigAlive texture!";
  }
  if (!this->textures["WOLF_DEAD"].loadFromFile("Rescources/Images/Animals/wolf_dead.png")) {
    throw "ERROR::GAMESTATE::Error while load PigAlive texture!";
  }
  if (!this->textures["GRASS"].loadFromFile("Rescources/Images/Texture/grass_2.png")) {
    throw "ERROR::GAMESTATE::Error while load grass texture!";
  }
  if (!this->textures["WATER"].loadFromFile("Rescources/Images/Texture/water_2.png")) {
    throw "ERROR::GAMESTATE::Error while load water texture!";
  }
  if (!this->textures["CARROT"].loadFromFile("Rescources/Images/Texture/carrot.png")) {
    throw "ERROR::GAMESTATE::Error while load carrot texture!";
  }
}

void GameState::Init_PauseMenu() {
  this->pause_menu = new PauseMenuState(this->player->camera_view, this->font);

}

void GameState::Init_Sprite() {
  this->sprites[0] = sf::Sprite(this->textures["GRASS"]);
  this->sprites[1] = sf::Sprite(this->textures["WATER"]);
  this->sprites[2] = sf::Sprite(this->textures["CARROT"]);
}

void GameState::Init_Players() {
  this->player = new Player(2500, 2500, &this->textures["PLAYER_IDLE"]);
}

void GameState::Init_Animals() {
  for (size_t i = 0; i < this->pig_amount; ++i) {
    std::pair<float, float> map_pos = GetRandomCoords(1, 49);
    int sex_num = GetRandomNumber(0, 1);
    bool sex = sex_num == 1; // true = male and false = female
    this->pig_vector.push_back(new Pig(map_pos.first, map_pos.second, &this->textures["PIG_ALIVE"],
                                       &this->textures["PIG_DEAD"], true, sex, this->map));
  }
  for (size_t i = 0; i < this->wolf_amount; ++i) {
    std::pair<float, float> map_pos = GetRandomCoords(1, 49);
    int sex_num = GetRandomNumber(0, 1);
    bool sex = sex_num == 1; // true = male and false = female
    this->wolf_vector.push_back(new Wolf(map_pos.first, map_pos.second, &this->textures["WOLF_ALIVE"],
                                       &this->textures["WOLF_DEAD"], true, sex, this->map));
  }
}

void GameState::Init_Map() {
  this->map_gen = new MapGenerator(map, carrot_vector);
  this->map = map_gen->TileGenerator(51, 51);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
  : State(window, supported_keys, states) {
  this->Init_KeyBinds();
  this->Init_Fonts();
  this->Init_Texture();
  this->Init_Sprite();
  this->Init_Map();
  this->Init_Players();
  this->Init_PauseMenu();
  this->Init_Animals();
}

GameState::~GameState() {
  delete this->player;
  delete this->pause_menu;
  for (size_t i = 0; i < this->pig_amount; ++i) {
    delete this->pig_vector[i];
  }
}

void GameState::UpdateInput(const float& dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("PAUSE"))) && this->GetKeyTime()) {
    if (!this->pause) {
      this->PauseState();
    } else {
      this->unPauseState();
    }
  }
}

void GameState::UpdatePlayerInput(const float& dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_LEFT")))) {
    this->player->Move(dt, -3.f, 0.f);
    this->player->MoveCamera(dt, -3.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_RIGHT")))) {
    this->player->Move(dt, 3.f, 0.f);
    this->player->MoveCamera(dt, 3.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_UP")))) {
    this->player->Move(dt, 0.f, -3.f);
    this->player->MoveCamera(dt, 0.f, -3.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_DOWN")))) {
    this->player->Move(dt, 0.f, 3.f);
    this->player->MoveCamera(dt, 0.f, 3.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("CLOSE")))) {
    this->EndState();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("ZOOM_IN")))) {
    this->player->Zoom(.97f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("ZOOM_OUT")))) {
    this->player->Zoom(1.03f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("SPEED_UP"))) && this->GetKeyTime()) {
    if (this->default_speed >= -10.f) {
      this->default_speed -= 2.f;
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("SLOW_DOWN"))) && this->GetKeyTime()) {
    if (this->default_speed <= 18.f) {
      this->default_speed += 2.f;
    }
  }
}

void GameState::UpdatePigBorn() {

}

void GameState::Update(const float& dt) {
  if (this->KeyTime < this->KeyTimeMax) {
    this->KeyTime += this->default_speed * dt;
    this->UpdateMousePosition();
    this->UpdateKeyTime(dt);
    this->UpdateInput(dt);

    this->UpdatePlayerInput(dt);
    this->player->Update(dt);

    this->map_gen->Update(dt);
    this->carrot_vector = map_gen->GetCarrot();
  } else {
    this->UpdateMousePosition();
    this->UpdateKeyTime(dt);
    this->UpdateInput(dt);

    this->UpdatePlayerInput(dt);
    this->player->Update(dt);

    if (!pause) {
      this->map_gen->Update(dt);
      this->carrot_vector = map_gen->GetCarrot();
      size_t curr_amount = 0;

      // Update pigs
      for (size_t i = 0; i < this->pig_amount; ++i) {
        this->pig_vector[i]->UpdateCarrotPositions(this->carrot_vector);
        this->pig_vector[i]->UpdatePigPositions(this->pig_vector);
        this->pig_vector[i]->Update(dt);
        if (this->pig_vector[i]->isAlive()) {
          ++curr_amount;
        }
        this->map = this->pig_vector[i]->UpdateGlobalMap();
        this->baby_born += this->pig_vector[i]->GetBabyCount();
        // Birth of pig
        if (this->baby_born != 0) {
          while (this->baby_born != 0) {
            int sex_num = GetRandomNumber(0, 1);
            bool sex = sex_num == 1; // true = male and false = female
            this->pig_vector.push_back(new Pig(this->pig_vector[i]->GetPosition().first,
                                               this->pig_vector[i]->GetPosition().second,
                                               &this->textures["PIG_ALIVE"],
                                               &this->textures["PIG_DEAD"],
                                               true, sex, this->map));
            ++curr_amount;
            --this->baby_born;
          }
        }
      }

      // Update wolves
      for (size_t i = 0; i < this->wolf_amount; ++i) {
        this->wolf_vector[i]->UpdateWolfPositions(this->wolf_vector);
        this->wolf_vector[i]->UpdatePigPositions(this->pig_vector);
        this->wolf_vector[i]->Update(dt);
        if (this->wolf_vector[i]->isAlive()) {
          ++curr_amount;
        }
        this->baby_born += this->wolf_vector[i]->GetBabyCount();
        // Birth of wolf
        if (this->baby_born != 0) {
          while (this->baby_born != 0) {
            int sex_num = GetRandomNumber(0, 1);
            bool sex = sex_num == 1; // true = male and false = female
            this->wolf_vector.push_back(new Wolf(this->wolf_vector[i]->GetPosition().first,
                                               this->wolf_vector[i]->GetPosition().second,
                                               &this->textures["WOLF_ALIVE"],
                                               &this->textures["WOLF_DEAD"],
                                               true, sex, this->map));
            ++curr_amount;
            --this->baby_born;
          }
        }
      }
      //this->wolf_amount = curr_amount;
    } else {
      this->pause_menu->Update(this->mouse_pos_view);
    }
    this->KeyTime = 0.f;
  }
}

void GameState::Render(sf::RenderTarget* target) {
  if (!target) {
    target = this->window;
  }

  target->clear(sf::Color(18,140,235, 255));
  this->map_gen->Render(this->window, sprites);
  this->player->Render(this->window);

  int alive_pigs = 0;
  int alive_wolfs = 0;

  // Render pigs
  for (size_t i = 0; i < this->pig_amount; ++i) {
    this->pig_vector[i]->Render(this->window);
    if (this->pig_vector[i]->isAlive()) {
      ++alive_pigs;
    }
  }

  // Render wolfs
  for (size_t i = 0; i < this->wolf_amount; ++i) {
    this->wolf_vector[i]->Render(this->window);
    if (this->wolf_vector[i]->isAlive()) {
      ++alive_wolfs;
    }
  }

  sf::Text info_text;
  info_text.setPosition(this->player->GetCoords().first - 3500,
                        this->player->GetCoords().second - 1900);

  info_text.setFont(this->font);
  info_text.setCharacterSize(100);
  std::stringstream ss;
  ss << "CURRENT SIMULATION SPEED: " << this->default_speed << "x" << '\n';
  if (alive_pigs <= 0) {
    ss << "They are in a better place ..." << '\n';
  } else {
    ss << "Pig count: " << alive_pigs << '\n';
  }
  if (alive_wolfs <= 0) {
    ss << "They are in a better place ..." << '\n';
  } else {
    ss << "Wolf count: " << alive_wolfs << '\n';
  }
  ss << "Carrot count: " << this->carrot_vector.size() << '\n';
  info_text.setString(ss.str());
  target->draw(info_text);

  if (this->pause) {
    this->pause_menu->Render(target, this->player->GetCoords().first, this->player->GetCoords().second);
  }

/*
  if (pause_update_pig) {
    sf::Text info_text;
    info_text.setPosition(this->player->GetCoords().first - 600,
                          this->player->GetCoords().second);
    info_text.setFont(this->font);
    info_text.setCharacterSize(400);
    std::stringstream ss;
    ss << "-PAUSE-"<< '\n';
    info_text.setString(ss.str());
    target->draw(info_text);
  }
*/
}
