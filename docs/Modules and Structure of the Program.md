# Overview 
To improve readability and ease of testing, I decided to split the programs to different modules based on their functionalities. Modules are implemented by using header files. The modules I designed are as follows: 
* `player.h` which is responsible for functions involving the players
* `space.h` which is responsible for functions involving the space (or more specifically properties).
* `transaction.h` which is responsible for functions involving players and spaces (e.g. buying and selling properties).
* `game.h` which combines the functions of Transaction, and the structures of Player and Space to form the game logic
* `display.h` which is responsible for displaying screen elements
* `engine.h` which combines both Game and Display modules to make the functional program

The main file only uses the functions of the `engine.h`. The module `engine.h` depends on `display.h` and `game.h` while `game.h` depends on `player.h` and `space.h`.

# The modules
## `Player.h` 
### Structures 
The main structure in this module is the Player which stores the following: 
* `char name[MAX_NAME_CHAR]`
* `int index`
* `float cash`
* `int position`
* `int canPlay`
