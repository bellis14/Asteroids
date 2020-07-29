/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include <vector>
#define OFF_SCREEN_BORDER_AMOUNT 5

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br) 
{  
   // Start the game with 3 lives
   score = 3;
   r = 0; 
   ship[3].setAlive(false);
   // Initialize the game with 5 asteroids
   for (int i = 0; i < 5; i++)
   {
      Point point(random(-185, 185), random(-185, 185));
      int dx = random(-1,1);
      int dy = random(-1,1);
      while (dy == 0 && dx == 0)
      {
         dx = random(-1,1);
         dy = random(-1,1);
      }
      Velocity vel(dx, dy);
      rocks.push_back(new BigRock());
      rocks[i]->setVelocity(vel);
      rocks[i]->setPoint(point);
   
   }
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   advanceAsteroids();
   advanceShip();
   advanceBullets();
   handleCollisions();
   cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE SHIP
 * advance the ship one unit of time
 ***************************************/
void Game :: advanceShip()
{
   if (ship[r].isAlive())
   {
      // this ship is alive, so tell it to move forward
      ship[r].advance();
      ship[r].decRespondTime();
         
      if (!isOnScreen(ship[r].getPoint()))
      {
         // the bullet has left the screen
         ship[r].wrap(topLeft, bottomRight, ship[r].getPoint());
      }
         
   }
   

}

/***************************************
 * GAME :: ADVANCE ASTEROIDS
 * advance the asteroids one unit of time
 ***************************************/
void Game :: advanceAsteroids()
{
   // Move each of the asteroids
   for (vector<Rocks*>::iterator it = rocks.begin(); it != rocks.end(); ++it)
   {
      if ((*it)->isAlive())
      {
         // this bullet is alive, so tell it to move forward
         (*it)->advance();
         
         if (!isOnScreen((*it)->getPoint()))
         {
            // the bullet has left the screen and should wrap around
            (*it)->wrap(topLeft, bottomRight, (*it)->getPoint());
         }   
      }
   }
   

}

/***************************************
 * GAME :: DRAW
 * draw the objects on the screen
 ***************************************/
void Game :: draw(const Interface & ui)
{
   // draw the ship if its alive
   if(ship[r].isAlive())
   {
      if (r > 0 && ship[r].getRespondTime() > 0)
      {
        int j = random(1, 3);
        if (j == 2)
           ship[r].draw();
      }
      else
         ship[r].draw();
   }
      
   // draw the asteroids
   for (vector<Rocks*>::iterator it = rocks.begin(); it != rocks.end(); ++it)
      (*it)->draw(); 

   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         bullets[i].draw();
      }
   }
   Point scoreLocation;
   scoreLocation.setX(topLeft.getX() + 5);
   scoreLocation.setY(topLeft.getY() - 5);
   
   drawNumber(scoreLocation, score);
   if (score == 0)
      drawText(Point(), "Game Over");
}

/*******************************************************
 * GAME :: HANDLE COLLISIONS
 * handle collisions between the ship, bullets and rocks
 *****************************************************/
void Game :: handleCollisions()
{
   // check for collisions between rocks and bullets
   for (int i = 0; i < bullets.size(); i++)
   {
      for (int j = 0; j < rocks.size(); j++)
      {   
          if (bullets[i].isAlive())
          {
             // this bullet is alive, see if its too close
    
             // check if the rock is at this point (in case it was hit)
             if (rocks[j]->isAlive())
             {
                // BTW, this logic could be more sophisiticated, but this will
                // get the job done for now...
                if (fabs(bullets[i].getPoint().getX() - rocks[j]->getPoint().getX()) < CLOSE_ENOUGH
                    && fabs(bullets[i].getPoint().getY() - rocks[j]->getPoint().getY()) < CLOSE_ENOUGH)
                {
                   // we have a hit
                   // the bullet is dead and the rock is as well
                   bullets[i].kill();
                   rocks[j]->kill();
                   if (rocks[j]->getIdentity() == "Big") // Create the two medium and one small rocks
                   {
                      int end = rocks.size();
                      Velocity v;
                      rocks.push_back(new MediumRock());
                      rocks[end]->setPoint(rocks[j]->getPoint());
                      v.setDy(rocks[j]->getVelocity().getDy() + 1);
                      v.setDx(rocks[j]->getVelocity().getDx());
                      rocks[end]->setVelocity(v);
                      end++;
                      rocks.push_back(new MediumRock());
                      rocks[end]->setPoint(rocks[j]->getPoint());
                      v.setDy(rocks[j]->getVelocity().getDy() - 1);
                      v.setDx(rocks[j]->getVelocity().getDx());
                      rocks[end]->setVelocity(v);
                      end++;
                      rocks.push_back(new SmallRock);
                      rocks[end]->setPoint(rocks[j]->getPoint());
                      v.setDy(rocks[j]->getVelocity().getDy());
                      v.setDx(rocks[j]->getVelocity().getDx() + 2);
                      rocks[end]->setVelocity(v);
                   }
                   // If a bullet hit a medium rock generate two small rocks
                   if (rocks[j]->getIdentity() == "Medium")
                   {
                      int end = rocks.size();
                      Velocity v;
                      rocks.push_back(new SmallRock());
                      rocks[end]->setPoint(rocks[j]->getPoint());
                      v.setDy(rocks[j]->getVelocity().getDy());
                      v.setDx(rocks[j]->getVelocity().getDx() + 3);
                      rocks[end]->setVelocity(v);
                      end++;
                      rocks.push_back(new SmallRock()); 
                      rocks[end]->setPoint(rocks[j]->getPoint());
                      v.setDy(rocks[j]->getVelocity().getDy());
                      v.setDx(rocks[j]->getVelocity().getDx() - 3);
                      rocks[end]->setVelocity(v);
                      end++;
                   }
                }
             }
          } 
      }
      
   } 
   // check for collisions between rocks and the ship
   for (int k = 0; k < rocks.size(); k++)
   {
      
      if (ship[r].isAlive())
      {
         // the ship is alive, check to see if the rock and ship are at the same point
         if (fabs(ship[r].getPoint().getX() - rocks[k]->getPoint().getX()) < CLOSE_ENOUGH
             && fabs(ship[r].getPoint().getY() - rocks[k]->getPoint().getY()) < CLOSE_ENOUGH && ship[r].getRespondTime() < 0)
         {
            // we have a hit
            ship[r].kill(); // the ship is dead
            if (score > 0)
            {
               r++; // next ship
               score--; // lose a life
            }

            
            rocks[k]->kill(); // the rock is dead
            
            // If the ship hit a big rock generate 
            // two medium and one small rock with the 
            // correct velocities and locations
            if (rocks[k]->getIdentity() == "Big")
            {
               int end = rocks.size();
               Velocity v;
               rocks.push_back(new MediumRock());
               rocks[end]->setPoint(rocks[k]->getPoint());
               v.setDy(rocks[k]->getVelocity().getDy() + 1);
               v.setDx(rocks[k]->getVelocity().getDx());
               rocks[end]->setVelocity(v);
               end++;
               rocks.push_back(new MediumRock());
               rocks[end]->setPoint(rocks[k]->getPoint());
               v.setDy(rocks[k]->getVelocity().getDy() - 1);
               v.setDx(rocks[k]->getVelocity().getDx());
               rocks[end]->setVelocity(v);
               end++;
               rocks.push_back(new SmallRock);
               rocks[end]->setPoint(rocks[k]->getPoint());
               v.setDy(rocks[k]->getVelocity().getDy());
               v.setDx(rocks[k]->getVelocity().getDx() + 2);
               rocks[end]->setVelocity(v);
            }
            
            // If the ship hit a medium rock generate 
            // two small rocks with the 
            // correct velocities and locations      
            if (rocks[k]->getIdentity() == "Medium")
            {
               int end = rocks.size();
               Velocity v;
               rocks.push_back(new SmallRock());
               rocks[end]->setPoint(rocks[k]->getPoint());
               v.setDy(rocks[k]->getVelocity().getDy());
               v.setDx(rocks[k]->getVelocity().getDx() + 3);
               rocks[end]->setVelocity(v);
               end++;
               rocks.push_back(new SmallRock()); 
               rocks[end]->setPoint(rocks[k]->getPoint());
               v.setDy(rocks[k]->getVelocity().getDy());
               v.setDx(rocks[k]->getVelocity().getDx() - 3);
               rocks[end]->setVelocity(v);
               end++;
            }
         }
      }
   }
}

/***************************************
 * GAME :: CLEAN UP ZOMBIES
 * delete all the dead bullets, and rocks
 ***************************************/
void Game :: cleanUpZombies()
{
   vector<Rocks*>::iterator rocksIt = rocks.begin();
   while (rocksIt != rocks.end())
   {
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      Rocks* pRock = *rocksIt;
      
      if (!pRock->isAlive())
      {
            // If we had a list of pointers, we would need to delete the memory here...
            delete pRock;
            pRock = NULL;
            // remove from list and advance
            rocksIt = rocks.erase(rocksIt);
      }
      else
      {
         rocksIt++; // advance
      }
   }
   // Look for dead bullets
   vector<Bullet>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet bullet = *bulletIt;
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      //Bullet* pBullet = *bulletIt;
      
      if (!bullet.isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
   
}

/***************************************
 * GAME :: IS ON SCREEN
 * determine if an object is on the screen
 ***************************************/
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/***************************************
 * GAME :: HANDLE INPUT
 * move the ship and fire bullets
 ***************************************/
void Game :: handleInput(const Interface & ui)
{ 
   // Change the direction of the ship counterclock-wise
   if (ui.isLeft())
   {
      ship[r].moveRight();
   }
   // Change direction of the ship clockwise
   if (ui.isRight())
   {
      ship[r].moveLeft();
   }
   
   if (ui.isUp())
   {
      ship[r].applyThrust(ship[r].getPoint(), ship[r].getAngle());
   }
   
   // Check for "Spacebar
   if (ui.isSpace() && ship[r].isAlive())
   {
     Bullet newBullet;
     newBullet.fire(ship[r].getPoint(), ship[r].getAngle(), ship[r].getVelocity());
     bullets.push_back(newBullet); 
   }
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * advance the bullets one unit of time
 ***************************************/
void Game :: advanceBullets()
{
   // Move each of the bullets forward if it is alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i].advance();
         bullets[i].bulletLife();
         
         if (!isOnScreen(bullets[i].getPoint()))
         {
            // the bullet has left the screen
            bullets[i].wrap(topLeft, bottomRight, bullets[i].getPoint());
         }
         
      }
   }
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
/*
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}
*/

