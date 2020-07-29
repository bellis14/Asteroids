#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#include "flyingObject.h"
#include "uiDraw.h"
#include "point.h"
#include "velocity.h"


/***************************************
 * CLASS :: SHIP
 * contains the data and methods for the ship
 ***************************************/ 
class Ship : public FlyingObject
{
private:
   float angle;
   bool thrust;
   int respondtime;

public:
   Ship();
   int getAngle() { return angle; }
   void setAngle(float a) { this->angle = a; }
   bool getThrust() { return thrust; }
   void setThrust(bool t) { this->thrust = t; }
   void applyThrust(Point, float);
   void moveLeft();
   void moveRight();
   virtual void draw();
   int getRespondTime() { return respondtime; } 
   void decRespondTime();
};

#endif /* ship_h */
