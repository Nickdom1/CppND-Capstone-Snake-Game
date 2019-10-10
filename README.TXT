BUILD INSTRUCTIONS:

Change Directory to build folder.
Compile: cmake .. && make
Run: ./SnakeGame
(No additional libraries required)

CHOSEN PROJECT:

I chose to add on to the existing Snake Game repo (see Example.png - it's a good capture of what the game has become).

The main feature I've added is competing with computer snake players.
Every 3 food your snake eats will add another computer snake to the game that you will compete with.
When they eat food, they will speed up and get longer, similar to your snake.
If your snake hits the other snakes, your snake's length and speed will reduce.
For added difficulty, the food will be regenerated if it hasn't been reached in time.
The secondary feature I added was configuring the game via the config.txt file, OR user input at the beginning.

To accomplish this, similar file and class structure were used. The main changes were:
- A config.txt file was added, where default config data is stored.
- The main file now checks the config file OR user input, and stores config data into a hashmap
- The controller files were altered and refactored into multiple functions to differentiate computer/player movement.
- The game files now maintain a vector of computer snake objects, and an additional function was added to detect collisions with snakes in that vector (this function utilizes find_if to run a lambda function across the vector, and returns a pointer to the collided snake)
- The renderer files now render multiple snakes, and can display when your snake collides with them.
- The snake files now have shrinking functionality for when your snake hits another one.


RUPRIC POINTS ADDRESSED:
- The project demonstrates an understanding of C++ functions and control structures. For example:
  * I refactored the "HandleInput" function in controller.cpp to have dynamic functions that differentiate between computer and user input.
  * I split the control functions that are called externally between "HandleUserInput" (line 67) and "HandleComputerInput" (line 78).
  * I made a "CalculateComputerMove" function to calculate which direction the computer snakes should go each turn (line 15), "HandleInput" (line 38) now takes an integer so that computer and user input can both command their respective snakes.
  * Any time the computer snakes are controlled, I use a for loop on the vector of snakes.
- The project reads data from a file and process the data:
  * See main.cpp. I have added a function, "getConfigMap()" (line 9) that reads and stores config.txt data.
- The project accepts input and processes the input:
  * See main.cpp. I have added a function "getConfigMap(std::string userInput)" (line 30) that allows the user to configure the game.
- Classes use appropriate access specifiers for class members:
  * Added following private members to game.h: std::vector<Snake> snakes; int initial_width; int initial_height;
  * Added public member to snake.h: bool is_bot;
- Overloaded functions allow the same function to operate on different parameters:
  * See main.cpp, the function "getConfigMap" is overloaded. It's defined on line 9 and line 30.