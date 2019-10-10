#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <map>
#include<fstream>
#include <sstream>

std::map<std::string, size_t> getConfigMap() {
  std::ifstream filein("config.txt");
  std::stringstream buffer;
  buffer << filein.rdbuf();

  std::map<std::string, size_t> config;
  std::string key;
  std::string value;
  int pos = 0;

  for (std::string line; std::getline(buffer, line); )
  {
    pos = line.find("=");
    key = line.substr(0, pos);
    value = line.substr(pos+1, line.length());
    std::stringstream sstream(value);
    sstream >> config[key];
  }
  return config;
}

std::map<std::string, size_t> getConfigMap(std::string userInput) {
  if(userInput.compare("Y") == 0 || userInput.compare("y") == 0) {
    std::map<std::string, size_t> config;
    std::cout << "Enter kFramesPerSecond:" << std::endl;
    std::cin >> config["kFramesPerSecond"];
    std::cout << "Enter kScreenWidth:" << std::endl;
    std::cin >> config["kScreenWidth"];
    std::cout << "Enter kScreenHeight:" << std::endl;
    std::cin >> config["kScreenHeight"];
    std::cout << "Enter kGridWidth:" << std::endl;
    std::cin >> config["kGridWidth"];
    std::cout << "Enter kGridHeight:" << std::endl;
    std::cin >> config["kGridHeight"];
    return config;
  } else {
    return getConfigMap();
  }
}

int main() {
  std::string input;
  std::cout << "Use User configuration? (Y/N):" << std::endl;
  std::cin >> input;
  std::map<std::string, size_t> config = getConfigMap(input);

  std::size_t kFramesPerSecond{config["kFramesPerSecond"]};
  std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  std::size_t kScreenWidth{config["kScreenWidth"]};
  std::size_t kScreenHeight{config["kScreenHeight"]};
  std::size_t kGridWidth{config["kGridWidth"]};
  std::size_t kGridHeight{config["kGridHeight"]};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}