/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"
#include "flyingObject.h"
#define CLOSE_ENOUGH 16


class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);

private:
   Point topLeft;
   Point bottomRight;
   int score;
   int r;
   Ship ship[4];
   std::vector<Bullet> bullets;
   std::vector<Rocks*> rocks;
   
   bool isOnScreen(const Point & point);
   void advanceBullets();
   void advanceAsteroids();
   void advanceShip();
   void handleCollisions();
   void cleanUpZombies();
   
};
   
#endif /* GAME_H */
