#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  while (running) {
    frame_start = SDL_GetTicks();
    
    // in case of game crash when food_list is empty, add a food with random location when food_list is empty
    if (food_list.size() == 0){
    SDL_Point food00;
    food00.x = random_w(engine);
    food00.y = random_h(engine);
    food_number ++;
    }
    
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food_list);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
      
      // place one food after every seconds. However, if there are too much food, do not place it.
      PlaceFood();
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  // modified place food function.
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) ) {
      if (food_number < maximum_food_number){
      SDL_Point food1;
      food1.x = x;
      food1.y = y;
      food_number ++;
      food_list.push_back(food1);
      return;}
      
      else{return;} // do nothing if there are so many foods. 
    }
  }
}

void Game::Update() {
  
  
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  
  bool check_ = false;// variable to check whether a food in the list is crashed with a snake's head 
  int food_num = food_list.size();
  
  for (int i = 0; i < food_num; i++){
    if (food_list[i].x == new_x && food_list[i].y == new_y){
    score++;
    food_number --; // this food was eaten.
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    
    food_list[i] = food_list[food_num - 1];
    food_list.pop_back();  // use a faster method to delete "eaten" food. 
    break;}
  
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }