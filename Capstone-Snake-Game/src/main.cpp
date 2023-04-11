#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <string>
#include <fstream>
using std::string;
int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  
  string name;
  
  
  std::cout << "Please input your name" << std::endl;
  std::cin >> name;
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  
  std::ofstream outfile("../PlayerScore.txt", std::ios::app);
  if (outfile.is_open())
   {
    outfile << "PlayerName: " << name << std::endl;
    outfile << "Score: " << game.GetScore() << std::endl;
    outfile << "Size: " << game.GetSize() << std::endl;
    outfile << std::endl;
    outfile.close();
    }
  
  return 0;
}