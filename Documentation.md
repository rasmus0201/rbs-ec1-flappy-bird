# Documentation

Author: Rasmus Bundsgaard Sørensen

Date: 03/08/2020

Short Description: This program is a game replica of the known "Flappy Bird" ([See it on Google](https://lmgtfy.com/?q=flappy+bird&t=i)). There is use of sensors and other peripherals to make the game more interesting.

---

## 1. Explanation of chosen solution
I've chosen to make this game since I thought it would be challenging, fun and creative. I have been VERY optimistic about making all this in the timeline of 5 days. I had set different goals all ready from the start:

1. Get the basic game up and running:
    - This was making the built-on LCD/touch screen to initialise and show a "bird" (square) and make a game-loop where on each frame the screen gets re-drawn. Adding the pipes and inserting them and making them translate/move towards the left.
2. Make the game more intelligent: 
    - Add collision detection for when the bird hits a pipe. Add random pipe-holes (generate a random hole between the top and bottom of the screen for the bird to go through)
3. Begin writing documentation.
    - Including: prerequisites, installation guide and the documentation of the program.
4. Game-over:
    - Make the game-over/restart screen
4. Bug-fixing & improvements:
    - It would be utopia if I got to this point without having any problems/bugs, so any bugs should be fixed ASAP, if possible. A long with bugs therew would probably also be some stuff which could be improved.
5. Extend functionality while continue to improve and bug-fix:
    - Adding more sensors/peripherals - button to make the bird fly, temperatur sensor to control "theme".
    - Score - should be attached to how long the user gets.

## 2. Game features


## 3. Map of input/output peripherals
- LCD/Touch screen:
   - It is Built-on
- Grove Button:
   - D2
- Grove Temperature Sensor:
   - A0

## 4. How the peripherals are used
- LCD/Touch screen:
   - Display used for showing:
      - Boot screen
      - Start screen (**upcoming**)
      - Game (moving bird and pipes)
      - Gameover screen (also restart game)
   - Touch:
      - If touching screen the the bird flies.
- Button (InterruptIn rise):
   - If pressed the bird flies once.
- Temperature sensor:
   - Changes theme based on temperature.

## 5. Compiler version
The program compiles with ARMC6, but it could probably also work with GCC_ARM

## 6. Serial communication
I use the `printf()` function to communicate to serial. I use Mbed Studio and the cli-version to connect to serial (command: `mbed sterm` to connect via the Terminal)

## 7. Scheduled changes
- Start screen
- Game-over screen
- Score functionality
- Bug fixes & improvements

## 8. Known problems / bugs
- Pipes disappear before they hit the left side of the screen
- Crazy screen: The pipes is all over the place and it there are small white boxes all over the place.

## 9. Future development/extension of the project
* Make theming:
    - Basically a temperature sensor to control which background and fill colors are used.
* High score:
    - Store a scoreboard on the board and make a screen for seeing this.
    - Could also be ethernet attached so the game can send it to a database-server/web-server for displaying it online.
* Dynamic game difficulty / Dynamic pipe speed:
    - Make the pipe-generation and speed of them more dynamic - i.e. when you play for longer the game gets harder
