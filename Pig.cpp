//
// Created by Арлан on 04.05.2023.
//

#include "Pig.h"
#include "aStarAlgoritm.h"
#include <utility>
#include <float.h>

void Pig::Init_Fonts() {
  if (!this->font.loadFromFile("Fonts/Futura.ttc")) {
    throw("ERROR::MAINMENUSTATE::Could not load font!");
  }
}

void Pig::Init_Variables(float x, float y, bool adult, bool sex, std::vector<std::vector<int> > map,
                         std::vector<std::vector<int> > graph, sf::Texture* texture_dead) {
  this->view_side = 500.0;
  this->is_male = sex;
  this->is_adult = adult;
  this->have_plan = false;
  this->hunger = 100.0;
  this->health = 100.0;
  this->reproduce = 100.0;
  this->direction = std::make_pair(x, y);
  this->map_for_pig = std::move(map);
  this->graph_for_pig = std::move(graph);
  this->texture_dead = texture_dead;
  this->sprite_dead = new sf::Sprite(*this->texture_dead);
  this->KeyTime = 0.f;
  this->KeyTimeMax = 10.f;
}

void Pig::Init_Components() {

}

float Pig::CountDistance(const float pig_x, const float pig_y, const float carrot_x, const float carrot_y) {
  float distance = sqrt((carrot_x - pig_x)*(carrot_x - pig_x) + (carrot_y - pig_y)*(carrot_y - pig_y));
  return distance * 100;
}

// Constructor for Pig

Pig::Pig(float x, float y, sf::Texture* texture_alive, sf::Texture* texture_dead, bool adult, bool sex,
         std::vector<std::vector<int> > map, std::vector<std::vector<int> > graph) {
  this->Init_Fonts();
  this->Init_Variables(x, y, adult, sex, map, graph, texture_dead);
  this->Init_Components();
  this->CreateSprite(texture_alive);
  this->SetPosition(x, y);
}

Pig::~Pig() noexcept {

}

// Condition of Pig

bool Pig::isMale() {
  return this->is_male;
}

bool Pig::isAdult() {
  return this->is_adult;
}

bool Pig::isAlive() {
  return (this->health > 0);
}

bool Pig::isHungry() {
  return (this->hunger < 60.0);
}

bool Pig::isHorny() {
  return (this->reproduce < 50.0);
}

int GetRandomNumber(int min, int max) {
  //srand(time(NULL));
  int num = min + rand() % (max - min + 1);
  return num;
}

// Behaviour of Pig

void Pig::FindFood(const float x, const float y) {
  float shortest_distance = FLT_MAX;
  std::pair<int, int>* closest_carrot = nullptr;
  for (auto& curr_carrot : this->carrot_vector_for_pig) {
    float curr_distance = CountDistance(x, y, (float)curr_carrot.first, (float)curr_carrot.second);
    if (shortest_distance > curr_distance) {
      shortest_distance = curr_distance;
      closest_carrot = &curr_carrot;
    }
  }
  if (shortest_distance <= this->view_side) {
    aStarAlgoritm star(this->map_for_pig);
    if (shortest_distance == 0) {
      this->hunger += 30;
      this->map_for_pig[closest_carrot->first][closest_carrot->second] = 0;
    } else {
      if (closest_carrot) {
        this->path = star.got_to_position((int)x, (int)y, closest_carrot->first, closest_carrot->second);
        //std::cout << "PATH IS FOUND!" << '\n';
        this->have_plan = true;
      }
    }
  }
}

void Pig::FindPartner(const float x, const float y) {

}

bool Pig::InDanger(const float x, const float y) {
  // search for wolf
  return false;
}

void Pig::Run(const float x, const float y) {

}

void Pig::Wandering(const float x, const float y, bool access_to_change) {
  if (access_to_change) {
    int direction_to_go = GetRandomNumber(1, 8);
    if (direction_to_go == 1) {
      if (this->map_for_pig[(int)x - 1][(int)y - 1] != 1) {
        this->sprite->setPosition((x - 1) * 100, (y - 1) * 100);
        this->direction = std::make_pair(-1, -1);
      }
    }
    if (direction_to_go == 2) {
      if (this->map_for_pig[(int)x - 1][(int)y] != 1) {
        this->sprite->setPosition((x - 1) * 100, (y) * 100);
        this->direction = std::make_pair(-1, 0);
      }
    }
    if (direction_to_go == 3) {
      if (this->map_for_pig[(int)x - 1][(int)y + 1] != 1) {
        this->sprite->setPosition((x - 1) * 100, (y + 1) * 100);
        this->direction = std::make_pair(-1, 1);
      }
    }
    if (direction_to_go == 4) {
      if (this->map_for_pig[(int)x][(int)y - 1] != 1) {
        this->sprite->setPosition((x) * 100, (y - 1) * 100);
        this->direction = std::make_pair(0, -1);
      }
    }
    if (direction_to_go == 5) {
      if (this->map_for_pig[(int)x][(int)y + 1] != 1) {
        this->sprite->setPosition((x) * 100, (y + 1) * 100);
        this->direction = std::make_pair(0, 1);
      }
    }
    if (direction_to_go == 6) {
      if (this->map_for_pig[(int)x + 1][(int)y - 1] != 1) {
        this->sprite->setPosition((x + 1) * 100, (y - 1) * 100);
        this->direction = std::make_pair(1, -1);
      }
    }
    if (direction_to_go == 7) {
      if (this->map_for_pig[(int)x + 1][(int)y] != 1) {
        this->sprite->setPosition((x + 1) * 100, (y) * 100);
        this->direction = std::make_pair(1, 0);
      }
    }
    if (direction_to_go == 8) {
      if (this->map_for_pig[(int)x + 1][(int)y + 1] != 1) {
        this->sprite->setPosition((x + 1) * 100, (y + 1) * 100);
        this->direction = std::make_pair(1, 1);
      }
    }
  } else {
    if (this->map_for_pig[(int)x + direction.first][(int)y + direction.second] != 1) {
      this->sprite->setPosition((x + (float)direction.first) * 100, (y + (float)direction.second) * 100);
    }
  }
}

void Pig::UpdateCarrotPositions(std::vector<std::pair<int, int>> carrot_vector) {
  this->carrot_vector_for_pig = carrot_vector;
}

std::vector<std::vector<int> > Pig::UpdateGlobalMap() {
  return this->map_for_pig;
}

void Pig::Update(const float& dt) {
  // Is pig alive
  if (isAlive()) {
    // Conditions that depend on time / timer
    if (this->KeyTime < this->KeyTimeMax) {
      this->KeyTime += 2.f * dt;
    } else {
      // Check hunger bar
      if (this->hunger > 0) {
        this->hunger -= 40.f;
      } else {
        this->health -= 20.f;
      }

      // Check reproduce urge bar
      if (this->reproduce > 0) {
        this->reproduce -= 5.f;
      } else {
        this->health -= 10.f;
      }

      // restart timer
      this->KeyTime = 0.f;
    }

    // Check does pig have route to smt
    if (this->have_plan) {
      if (!this->path.empty()) {
        std::pair<int, int> where_to_go = this->path.back();
        this->path.pop_back();
        this->sprite->setPosition((float) where_to_go.first * 100,
                                  (float) where_to_go.second * 100);
      } else {
        this->have_plan = false;
      }
    }
    // if pig does not have route
    else {
      if (InDanger(this->sprite->getPosition().x / 100, this->sprite->getPosition().y / 100)) {
        this->Run(this->sprite->getPosition().x / 100,
                  this->sprite->getPosition().y / 100);
      }
      if (isHungry()) {
        this->FindFood(this->sprite->getPosition().x / 100,
                       this->sprite->getPosition().y / 100);
      }
      if (isHorny()) {
        this->FindPartner(this->sprite->getPosition().x / 100,
                          this->sprite->getPosition().y / 100);
      }
      int access_to_change = GetRandomNumber(1, 200);
      if (access_to_change >= 195) {
        this->Wandering(this->sprite->getPosition().x / 100,
                        this->sprite->getPosition().y / 100, access_to_change);
      }
    }
  }
}


void Pig::Render(sf::RenderTarget* target) {
  if (this->sprite) {
    sf::Text info_text;
    info_text.setPosition(this->sprite->getPosition().x - 120,
                          this->sprite->getPosition().y + 60);
    info_text.setFont(this->font);
    info_text.setCharacterSize(20);
    std::stringstream ss;
    ss << "sex: " << (this->is_male ? "Male" : "Female") << '\n';
    ss << "health: " << this->health << '\n';
    ss << "hunger: " << this->hunger << '\n';
    ss << "reproduce urge: " << this->reproduce << '\n';
    ss << "age: " << (this->isAdult() ? "MATURE" : "BABY") << '\n';
    if (!this->isAlive()) {
      ss << "~DEAD~" << '\n';
    }
    info_text.setString(ss.str());
    if (!this->isAlive()) {
      this->sprite_dead->setPosition(info_text.getPosition().x + 120,
                                     info_text.getPosition().y - 60);
      target->draw(*this->sprite_dead);
    } else {
      target->draw(*this->sprite);
    }
    target->draw(info_text);
  }
}
