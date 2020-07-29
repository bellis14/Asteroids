#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40


#include <iostream>
#include "flyingObject.h"
#include "uiDraw.h"

/***************************************
 * CLASS :: BULLET
 * contains attributes and methods for bullets
 ***************************************/ 
class Bullet : public FlyingObject
{
private:
   int lifetime;

public:
   Bullet();
   virtual void draw();
   void bulletLife();
   void fire(Point, float, Velocity);
};



#endif /* bullet_h */
