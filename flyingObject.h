#ifndef flyingObject_h
#define flyingObject_h

#include <iostream>
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

/***************************************
* CLASS :: FLYINGOBJECT
* contains all the data and method functions
* for bullets, rocks, and the ship
****************************************/
class FlyingObject
{
private:
   protected:
      Velocity vel;
      Point point;
      bool alive;

public:
   FlyingObject();
   Point getPoint() { return point; }
   void setPoint(Point p) { this->point = p; return; }
   Velocity getVelocity() { return vel; }
   void setVelocity(Velocity v) { this->vel = v; return; }
   bool isAlive() { return alive; }
   void setAlive(bool a) { this->alive = a; return; }
   void advance();
   void kill() { alive = false; return; }
   virtual void draw()= 0;
   void wrap(Point tl, Point br, Point p); 
};

#endif /* flyingObject_h */
