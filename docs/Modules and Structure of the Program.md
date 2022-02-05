# Overview
To improve readability and ease of testing, I decided to split the programs to different modules based on their functionalities. Modules are implemented by using header files. The modules I designed are as follows:
* `player.h` which is responsible for functions involving the players
* `transaction.h` which is responsible for functions involving players and spaces (e.g. buying and selling properties). The inventory also lives inside this module.
* `game.h` which combines the functions of Transaction, and the structures of Player to form the game logic
* `display.h` which is responsible for displaying screen elements
* `engine.h` which combines both Game and Display modules to make the functional program

The main file only uses the functions of the `engine.h`. The module `engine.h` depends on `display.h` and `game.h` while `game.h` depends on `player.h` and `space.h`. The module `helper.h` is also called numerous times by the aforementioned modules.

```
main.c
|
|-engine.h
    |
    |-game.h
    |   |
    |   |-player.h
    |   |
    |   |-transaction.h
    |
    |-display.h
```

# How the game works
