#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

enum Direction { COM_UP, COM_DOWN, COM_LEFT, COM_RIGHT };

class Controller {
 public:
  void HandleInput(Snake &snake, int dir) const;
  void HandleUserInput(bool &running, Snake &snake) const;
  void HandleComputerInput(Snake &snake, SDL_Point* const food) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  Direction CalculateComputerMove(Snake &snake, SDL_Point* const food) const;
};

#endif