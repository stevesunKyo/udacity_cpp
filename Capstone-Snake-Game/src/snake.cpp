#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void AISnake::set_target(SDL_Point target_food){// set the target of food
   _target = target_food;
} 

SDL_Point AISnake::get_target(){ // get the current target of food;
	return _target;
}


void AISnake::set_direction(vector<SDL_Point> food_list, Snake snake, AISnake ai01, AISnake ai02){
// set the direction of AI snake
  
  //initiate a new Asearch class by constructor Asearch()
  Asearch search01(get_width(), get_height());
  
  //enter the location of snake body by setObstacle()
  search01.setObstacle(snake.body);
  search01.setObstacle(ai01.body);
  search01.setObstacle(ai02.body);
  SDL_Point target = food_list[0];
  SDL_Point nullpoint;
  nullpoint.x = 99999;
  nullpoint.y = 99999;
  // if there is a target in ai and this target in the foodlist, there is no need to find a new target
  if ((get_target()).x != nullpoint.x || (get_target()).y != nullpoint.y){
  		bool flag = false;
    for (int i = 0; i < food_list.size(); i++){
    if((get_target()).x == (food_list[i]).x || (get_target()).y != nullpoint.y){
      flag = true;
      break;}
     } // check if target in the foodlist
    if (flag == false){
		 srand(unsigned(time(NULL)));
      random_shuffle(food_list.begin(), food_list.end());
      // random shuffle the foodlist and use the first item to get a item from foodlist randomly.
      SDL_Point target = food_list[0];
      if (target.x != (get_target()).x || target.y != (get_target()).y){
         set_target(target);}
   } // if target is not in the foodlist, set a new one.
  } 
  else{  // there are no target
  // find a target inside food list randomlly.
		 srand(unsigned(time(NULL)));
      random_shuffle(food_list.begin(), food_list.end());
  // random shuffle the foodlist and use the first item to get a item from foodlist randomly.
  SDL_Point target = food_list[0];
  set_target(target);
  }
  
  // conduct A*search by search()
  SDL_Point head;
  head.x = head_x;
  head.y = head_y;
  search01.search(head, target);
  
  //Analyse the solution by analysis()
  search01.analysis();
  
  //output the solution of directions in Asearch.solution_dir()
  Direction result = (search01.solution_dir)[0];
  
  // set result to direction.
  direction = result;
}


Asearch::Asearch(int row_size, int col_size){
  // initialize the state map variable at first
  for(int i=0; i<row_size; i++){
  vector<State> temp;
  for(int j=0; j<col_size; j++){
  temp.push_back(State::kEmpty);}
  Statemap.push_back(temp);}}

void Asearch::search(SDL_Point start, SDL_Point goal){
  vector<vector<int>> open_list;
  int x, y, g, h;
  x = start.x;
  y = start.y;
  g = 0;
  h = hValue(start, goal);
  open_list.push_back(vector<int> {x, y, g, h});
  Statemap[x][y] = State::kEmpty;
  // initialize the starting point;
  while(open_list.size() > 0){
  	auto compare = [](vector<int> vec1, vector<int>vec2){return vec1[2]+vec1[3] > vec2[2] + vec2[3];};
   std::sort(open_list.begin(), open_list.end(), compare);
  	vector<int> back = open_list.back();
  	open_list.pop_back(); // take the point should be added in the open list
  	Statemap[back[0]][back[1]] = State::kClosed;
      
  	SDL_Point this_point; // the target point should be added to the solution vector
   this_point.x = back[0];
   this_point.y = back[1]; 
    
  	solution.push_back(this_point);
   if (back[0] == goal.x || back[1] == goal.y){
    	return; // goal reached, end of searching
   }
   expand(back, goal, open_list);
  }
  // if nothing found, we do not conduct any movement. So the "solution" only consist of starting point.
  solution.push_back(start);
  return; //end this function
}

void Asearch::setObstacle(vector<SDL_Point> snake_body){
  for(auto item:snake_body){
    Statemap[item.x][item.y] = State::kObstacle;
  }
}

int Asearch::hValue(SDL_Point p1, SDL_Point p2){
  // calculate the manhattan distance of two points p1(x1,y1), p2(x2,y2)
  return abs(p1.x-p2.x) + abs(p1.y-p2.y);}

bool Asearch::able_to_use(int x, int y){
  int _col = Statemap.size();
  int _row = Statemap[0].size();
  
  if (x < 0 || x >= _col){return false;}
  else if (y < 0 || y >= _row){return false;}
  else if (Statemap[x][y] != State::kEmpty){return false;}
  return true;
}
 

void Asearch::expand(vector<int> loc_now, SDL_Point goal, vector<vector<int>> &open_list){
  int x = loc_now[0], y = loc_now[1], g = loc_now[2];
  for (int i=0; i<4; i++){
  int x1 = x + delta[i][0];
  int y1 = y + delta[i][1];
  bool able_ = able_to_use(x1, y1);
  if (able_ == true){
  	int g1 = g + 1;
  	SDL_Point p1;
   p1.x = x1;
   p1.y = y1;
  	int h1 = hValue(p1, goal);
   open_list.push_back(vector<int>{x1, y1, g1, h1});
   Statemap[x1][y1] = State::kClosed;
   }
  }
}
  
void Asearch::analysis(){
  // transfer the "solution" of search path, to directions.
  int len_solution = solution.size();
  if(len_solution==1){return;}
  // size of solution == 1 means that search failed.
  for (int i = 0; i < len_solution - 1; i++){
   // path in vector "solution" saved in an order from starting point to goal.
   int diff_x = solution[i+1].x - solution[i].x;
   int diff_y = solution[i+1].y - solution[i].y;
   Direction result; // direction of movement from point solution[i] to solution[i+1]
   if (diff_x == 1){result = Direction::kRight;}
   else if (diff_x == -1){result = Direction::kLeft;} 
   else if (diff_y == 1){result = Direction::kUp;}
   else{result = Direction::kDown;}
   solution_dir.push_back(result);
  }

}


