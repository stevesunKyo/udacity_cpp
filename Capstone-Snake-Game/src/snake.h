#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include "SDL.h"
#include <math.h>
#include <algorithm>
using std::vector;
enum class State{kEmpty, kObstacle, kClosed};
enum class Direction { kUp, kDown, kLeft, kRight };

class Snake {
 public:
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  int get_width(){return grid_width;}
  int get_height(){return grid_height;}
  
 protected:
  int grid_width;
  int grid_height;
  
 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  bool growing{false};

};


class AISnake : public Snake{
  /* 
  This AI snake was controlled by A*search algorithm.
  its direction should be setted by the first item of vector solution_dir, result of a* star search.
  */
  
  public:
    AISnake(int grid_width, int grid_height):Snake(grid_width, grid_height){
    _target.x = 99999;
    _target.y = 99999; }
    void set_target(SDL_Point target_food); // set the target of food
    SDL_Point get_target(); // get the current target of food;
    float speed{0.2f}; // ai snake move at a constant speed.
    void set_direction(vector<SDL_Point> food_list, Snake snake, AISnake ai01); //get a food_list 
  private:
    SDL_Point _target; // current target of food.
};

class Asearch{
	public:
   Asearch(int row_size, int col_size);
   vector<vector<State>> Statemap;
   vector<SDL_Point> solution; // solution of the path that from start to goal.
   vector<Direction> solution_dir; // solution of directions that from start to goal;
  
   void search(SDL_Point start, SDL_Point goal);
   void create();
   void setObstacle(vector<SDL_Point> snake_body); // set snake body as obstacle.
   void analysis(); // analysis the solution written in paths.
  
   private:
   const int delta[4][2] = {{-1,0}, {0,-1}, {1,0}, {0,1}};
   int hValue(SDL_Point p1, SDL_Point p2);
   vector<vector<int>> Open_list; // open list that stores the values should be used
   void expand(vector<int> loc_now, SDL_Point goal, vector<vector<int>> &open_list);
   bool able_to_use(int x, int y);
   
};




#endif