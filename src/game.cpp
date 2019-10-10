#include "game.h"
#include <iostream>
#include "SDL.h"
#include <algorithm>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      initial_width(grid_width),
      initial_height(grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::addSnake() {
  Snake new_snake = Snake(initial_width, initial_height);
  new_snake.is_bot = true;
  snakes.push_back(new_snake);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  int loop_count = 0;
  bool running = true;

  while (running) {
    loop_count++;
    if(loop_count % (initial_width * 10) == 0) {
      PlaceFood();
    }
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleUserInput(running, snake);
    for(Snake &comSnake : snakes) {
      controller.HandleComputerInput(comSnake, &food);
    }

    Update();
    renderer.Render(snake, snakes, food);

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
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !CheckForCompCollision(x, y)) {
      food.x = x;
      food.y = y;
      break;
    } else {
      continue;
    }
  }
}

Snake * Game::CheckForCompCollision(int x, int y) {
  auto compCollision = std::find_if(snakes.begin(), snakes.end(), [x,y](Snake snek) ->bool { return snek.SnakeCell(x, y); });
  if(compCollision != snakes.end()) {
    return &*compCollision;
  } else {
    return nullptr;
  }
}


void Game::Update() {
  if (!snake.alive) return;

  snake.Update();
  for (Snake &comSnake : snakes) {
    comSnake.Update();
  }

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    if(snake.size % 3 == 0) {
      addSnake();
    }
    // Check if computer found food
  }
  Snake * compFoundFood = CheckForCompCollision(food.x, food.y);
  if (compFoundFood) {
    PlaceFood();
    compFoundFood->GrowBody();
    compFoundFood->speed += 0.01;
  }
  // Check if player is running into a snake
  if (CheckForCompCollision(new_x, new_y)) {
    snake.ShrinkBody();
    if(snake.speed > 0.1) {
      snake.speed -= 0.015;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }