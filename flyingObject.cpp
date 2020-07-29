#include "flyingObject.h"


/***************************************
 * FLYINGOBJECT :: CONSTRUCTOR
 * initialize the point and velocity 
 * constructors and the alive variable
 ***************************************/  
FlyingObject :: FlyingObject() : vel() , point()
{
   alive = true;
}

/***************************************
 * FLYINGOBJECT :: ADVANCE
 * move flyingobjects one unit of time
 ***************************************/ 
void FlyingObject :: advance()
{
   point.addY(vel.getDy());
   point.addX(vel.getDx());
   
   return;
}

/***************************************
 * FLYINGOBJECT :: WRAP
 * wrap flyingobjects from one side of the 
 * screen on to the other side
 ***************************************/ 
void FlyingObject :: wrap(Point tl, Point br, Point p)
{
   // wrap right to left 
   if (p.getX() > br.getX())
   {
      p.setX(tl.getX());
      setPoint(p);
   }
   
   // wrap left to right
   else if (p.getX() < tl.getX())
   {
      p.setX(br.getX());
      setPoint(p);
   }
   
   // wrap top to bottom
   else if (p.getY() > tl.getY())
   {
      p.setY(br.getY());
      setPoint(p);
   }
   
   //wrap bottom to top
   else if (p.getY() < br.getY())
   {
      p.setY(tl.getY());
      setPoint(p);
   }

   return;
}
