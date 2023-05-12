//
// Created by Арлан on 04.05.2023.
//

#include "Pig.h"
#include "Wolf.h"
#include "aStarAlgoritm.h"
#include <utility>
#include <float.h>

void Pig::Init_Fonts() {
  if (!this->font.loadFromFile("Fonts/Futura.ttc")) {
    throw("ERROR::MAINMENUSTATE::Could not load font!");
  }
}

void Pig::Init_Variables(float x, float y, bool adult, bool sex, std::vector<std::vector<int> > map,
                         sf::Texture* texture_dead) {
  this->view_side = 500.0;
  this->sex_visor = 1500.f;
  this->is_male = sex;
  this->is_adult = adult;
  this->hunger = 100.0;
  this->health = 100.0;
  this->reproduce = 100.0;
  this->map_for_pig = std::move(map);
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
         std::vector<std::vector<int> > map) {
  this->Init_Fonts();
  this->Init_Variables(x, y, adult, sex, map, texture_dead);
  this->Init_Components();
  this->CreateSprite(texture_alive);
  this->SetPosition(x, y);
}

Pig::~Pig() noexcept {

}

// Condition of Pig

bool Pig::InDanger() {
  const float x = this->sprite->getPosition().x / 100;
  const float y = this->sprite->getPosition().y / 100;
  for (auto& curr_wolf : this->wolf_vector_for_pig) {
    float curr_distance = CountDistance(x, y,
                                        curr_wolf->GetPosition().first / 100,
                                        curr_wolf->GetPosition().second / 100);
    if (this->view_side > curr_distance) {
      this->src_fo_danger = curr_wolf;
      return true;
    }
  }
  return false;
}

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
    float curr_distance = CountDistance(x, y,
                                        (float)curr_carrot.first,
                                        (float)curr_carrot.second);
    if (shortest_distance > curr_distance) {
      shortest_distance = curr_distance;
      closest_carrot = &curr_carrot;
    }
  }
  if (shortest_distance <= this->view_side) {
    aStarAlgoritm star(this->map_for_pig);
    if (shortest_distance == 0) {
      this->hunger += 45;
      this->map_for_pig[closest_carrot->first][closest_carrot->second] = 0;
    } else {
      if (closest_carrot) {
        this->path = star.got_to_position((int)x, (int)y,
                                          closest_carrot->first,
                                          closest_carrot->second);
        this->sprite->setPosition((float)this->path.back().first, (float)this->path.back().second);
      } else {
        this->FindFood(x, y);
      }
    }
  }
}

void Pig::FindPartner(const float x, const float y) {
  float shortest_distance = FLT_MAX;
  Pig* closest_partner = nullptr;
  for (auto& curr_pig : this->pig_vector_for_pig) {
    if (curr_pig->isAlive() &&
        this->isMale() != curr_pig->isMale() && curr_pig->isAdult()) {
      float curr_distance = CountDistance(x, y,
                                          curr_pig->sprite->getPosition().x / 100,
                                          curr_pig->sprite->getPosition().y) / 100;
      if (shortest_distance > curr_distance) {
        shortest_distance = curr_distance;
        closest_partner = curr_pig;
      }
    }
  }
  if (shortest_distance <= this->sex_visor) {
    aStarAlgoritm star(this->map_for_pig);
    if (this->GetPosition() == closest_partner->GetPosition()) {
      float curr_reproduce = this->reproduce;
      this->reproduce += 100.f - curr_reproduce;
      this->newborn += GetRandomNumber(1, 3);
    } else {
      if (closest_partner) {
        this->path = star.got_to_position((int) x, (int) y,
                                          (int)closest_partner->sprite->getPosition().x / 100,
                                          (int)closest_partner->sprite->getPosition().y / 100);
        this->sprite->setPosition((float)this->path.back().first, (float)this->path.back().second);
      } else {
        this->FindPartner(x, y);
      }
    }
  }
}

void Pig::Run(const float x, const float y) {
  int gen_x = GetRandomNumber(-8, 8);
  int gen_y = GetRandomNumber(-8, 8);
  while ((int)x + gen_x < 0 || (int)x + gen_x >= 50 ||
         (int)y + gen_y < 0 || (int)y + gen_y >= 50 ||
         (int)x + (int)src_fo_danger->GetPosition().first / 100 < 0 ||
         (int)x + (int)src_fo_danger->GetPosition().first / 100 >= 50 ||
         (int)y + (int)src_fo_danger->GetPosition().second < 0 ||
         (int)y + (int)src_fo_danger->GetPosition().second >= 50 ||
         this->map_for_pig[(int)x + gen_x][(int)y + gen_y] != 0) {
    gen_x = GetRandomNumber(-8, 8);
    gen_y = GetRandomNumber(-8, 8);
  }
  aStarAlgoritm star(this->map_for_pig);
  this->path = star.got_to_position((int) x, (int) y,
                                    (int)src_fo_danger->GetPosition().first / 100 + gen_x,
                                    (int)src_fo_danger->GetPosition().second / 100 + gen_y);
  if (!this->path.empty()) {
    this->sprite->setPosition((float)this->path.back().first, (float)this->path.back().second);
  }
}

void Pig::Dying() {
  this->health -= 100.f;
}

void Pig::Wandering(const float x, const float y) {
  int gen_x = GetRandomNumber(-5, 5);
  int gen_y = GetRandomNumber(-5, 5);
  while ((int)x + gen_x < 0 || (int)x + gen_x >= 50 ||
         (int)y + gen_y < 0 || (int)y + gen_y >= 50 ||
         this->map_for_pig[(int)x + gen_x][(int)y + gen_y] != 0) {
    gen_x = GetRandomNumber(-5, 5);
    gen_y = GetRandomNumber(-5, 5);
  }
  aStarAlgoritm star(this->map_for_pig);
  this->path = star.got_to_position((int)x, (int)y,
                                    (int)x + gen_x, (int)y + gen_y);
  if (!this->path.empty()) {
    this->sprite->setPosition((float)this->path.back().first, (float)this->path.back().second);
  }
}

void Pig::Movement(const float& dt) {
  // Is pig alive
  if (isAlive()) {
    // Conditions that depend on time / timer
    if (this->KeyTime < this->KeyTimeMax) {
      this->KeyTime += 30.f * dt;
    } else {
      // Check hunger bar
      if (this->hunger > 0) {
        this->hunger -= 15.f;
      } else {
        this->health -= 20.f;
      }

      // Check reproduce urge bar
      if (this->isAdult()) {
        if (this->reproduce > 0) {
          this->reproduce -= 0.f;
        } else {
          this->health -= 10.f;
        }
      }

      // restart timer
      this->KeyTime = 0.f;
    }

    Priority priority = SAFE;

    if (InDanger()) {
      priority = UNDER_CHASE;
    }
    if (isHungry()) {
      priority = STARVING;
    }
    if (isHorny()) {
      priority = LONELY;
    }

    switch (priority) {
      case UNDER_CHASE:
        this->Run(this->sprite->getPosition().x / 100,
                  this->sprite->getPosition().y / 100);
        break;
      case STARVING:
        this->FindFood(this->sprite->getPosition().x / 100,
                       this->sprite->getPosition().y / 100);
        break;
      case LONELY:
        this->FindPartner(this->sprite->getPosition().x / 100,
                          this->sprite->getPosition().y / 100);
        break;
      case SAFE:
        this->Wandering(this->sprite->getPosition().x / 100,
                        this->sprite->getPosition().y / 100);
        break;
    }
  }
}

// Updates and Render

void Pig::UpdateCarrotPositions(std::vector<std::pair<int, int>> carrot_vector) {
  this->carrot_vector_for_pig = carrot_vector;
}

void Pig::UpdatePigPositions(std::vector<Pig *> pig_vector) {
  this->pig_vector_for_pig = pig_vector;
}

void Pig::UpdateWolfPositions(std::vector<Wolf *> wolf_vector) {
 this->wolf_vector_for_pig = wolf_vector;
}

std::vector<std::vector<int> > Pig::UpdateGlobalMap() {
  return this->map_for_pig;
}

int Pig::GetBabyCount() {
  return this->newborn;
}

std::pair<float, float> Pig::GetPosition() {
  return std::make_pair(this->sprite->getPosition().x,
                        this->sprite->getPosition().x);
}

void Pig::Update(const float& dt) {

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
