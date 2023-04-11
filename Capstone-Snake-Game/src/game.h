#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <vector>

using std::vector;

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int food_number = 0;
  
 private:
  Snake snake;
  //SDL_Point food;
  vector<SDL_Point> food_list;
  SDL_Point redfood;
  SDL_Point greenfood;
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int maximum_food_number = 10;
  void PlaceFood();
  void PlaceGreenFood();
  void PlaceRedFood();
  void Update();
};

#endif