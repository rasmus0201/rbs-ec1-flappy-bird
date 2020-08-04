# Documentation

Author: Rasmus Bundsgaard Sørensen

Date: 03/08/2020

Short Description: This program is a game replica of the known "Flappy Bird" ([See it on Google](https://lmgtfy.com/?q=flappy+bird&t=i)). There is use of sensors and other peripherals to make the game more interesting.

---

WIP = Work In Progress

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
    - Adding more sensors/peripherals - button to make the bird fly, temperatur sensor to control "theme", leds, buzzer, etc.
    - Score - should be attached to how long the user gets.

## 2. Game features
You can use touch or the button to make the bird fly (go up). If you don't do anything the bird will accelerate to the ground. The goal is to get between the top and bottom pipes without hitting them. You do this to everytime a pipe comes towards the flappy bird.

You die if you:
- Hit the bottom of the screen (the ground)
- Hit any pipe

Theme (background color and fill color) change when the room temperature rises (it is getting hotter) and when it falls (it is getting colder)

## 3. Map of input/output peripherals
- LCD/Touch screen:
   - It is Built-on
- Grove Button:
   - D2
- Grove LED (WIP):
   - D3
- Grove Buzzer (WIP):
   - D4
- Grove Temperature Sensor (WIP):
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
- LED:
   - Lights up when the bird got an upwards lift (user pressed button or touch screen)
- Buzzer (DigitalOut):
   - Buzzes when user dies
- Temperature sensor:
   - Changes theme based on temperature.

## 5. Compiler version
The program compiles with ARMC6, but it could probably also work with GCC_ARM

## 6. Serial communication
I use the `printf()` function to communicate to serial. I use Mbed Studio and the cli-version to connect to serial (command: `mbed sterm` to connect via the Terminal)

## 7. Scheduled changes
- Implement the LED functionality
- Implement the buzzer functionality
- Fix the screen craziness issues 

## 8. Known problems / bugs
- The screens is going crazy and you can't really see anything

## 9. Future development/extension of the project
* Make theming:
    - Basically a temperature sensor to control which background and fill colors are used.
* High score:
    - Store a scoreboard on the board and make a screen for seeing this.
    - Could also be ethernet attached so the game can send it to a database-server/web-server for displaying it online.
* Dynamic game difficulty / Dynamic pipe speed:
    - Make the pipe-generation and speed of them more dynamic - i.e. when you play for longer the game gets harder
