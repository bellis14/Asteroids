#include "bullet.h"
#include <cmath>

/***************************************
 * BULLET :: CONSTRUCTOR
 * initialize flyingobject constructor
 * and lifetime variable
 ***************************************/ 
Bullet :: Bullet() : FlyingObject() 
{
   lifetime = 0;
}

/***************************************
 * BULLET :: DRAW
 * draw the bullet
 ***************************************/ 
void Bullet :: draw()
{
  drawDot(getPoint());
}

/***************************************
 * BULLET :: FIRE
 * fire the bullet with speed and direction
 ***************************************/ 
void Bullet :: fire(Point p, float angle, Velocity vil)
{
   setPoint(p);
   Velocity v;
   float dx = BULLET_SPEED * (-cos(M_PI / 180.0 * angle));
   float dy = BULLET_SPEED * (sin(M_PI / 180.0 * angle));
   v.setDx(dx + vil.getDx());
   v.setDy(dy + vil.getDy());
   setVelocity(v);
}

/***************************************
 * BULLET :: BULLET LIFE
 * track the life of the bullet
 ***************************************/ 
void Bullet :: bulletLife()
{
   if (lifetime == BULLET_LIFE)
      kill();
   else
      lifetime++;
}

