#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include <thread>
#include <chrono>
#include <cstdlib>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

Direction Controller::CalculateComputerMove(Snake &snake, SDL_Point* const food) const {
  int grid_width, grid_height, head_x, head_y, left, right, up, down;
  grid_width = snake.GetGridWidth();
  grid_height = snake.GetGridHeight();

  head_x = static_cast<int>(snake.head_x);
  left = head_x - food->x + ((head_x > food->x) ? 0 : grid_width);
  right = food->x - head_x + ((food->x > head_x) ? 0 : grid_width);
  if(left < right) {
    return COM_LEFT;
  } else if (right < left) {
    return COM_RIGHT;
  }
  head_y = static_cast<int>(snake.head_y);
  up = head_y - food->y + ((head_y > food->y) ? 0 : grid_height);
  down = food->y - head_y + ((food->y > head_y) ? 0 : grid_height);
  if(down < up) {
    return COM_DOWN;
  } else {
    return COM_UP;
  }
}

void Controller::HandleInput(Snake &snake, int dir) const {
  switch (dir) {
    //SDLK_UP
    case 1073741906:
    case 0:
      ChangeDirection(snake, Snake::Direction::kUp,
                      Snake::Direction::kDown);
      break;
    //SDLK_DOWN
    case 1073741905:
    case 1:
      ChangeDirection(snake, Snake::Direction::kDown,
                      Snake::Direction::kUp);
      break;
    //SDLK_LEFT
    case 1073741904:
    case 2:
      ChangeDirection(snake, Snake::Direction::kLeft,
                      Snake::Direction::kRight);
      break;
    //SDLK_RIGHT
    case 1073741903:
    case 3:
      ChangeDirection(snake, Snake::Direction::kRight,
                      Snake::Direction::kLeft);
      break;
  }
}

void Controller::HandleUserInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      HandleInput(snake, (int) e.key.keysym.sym);
    }
  }
}

void Controller::HandleComputerInput(Snake &snake, SDL_Point* const food) const {
    Direction dir = CalculateComputerMove(snake, food);
    HandleInput(snake, (int) dir);
}