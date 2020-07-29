#include "ship.h"

/***************************************
 * SHIP :: CONSTRUCTOR
 * initialize the flyingobject constructor
 ***************************************/ 
Ship :: Ship() : FlyingObject() 
{
   angle = 0;
   thrust = false;
   respondtime = 40;
}

/***************************************
 * SHIP :: DRAW
 * draw the ship
 ***************************************/ 
void Ship :: draw()
{
   drawShip(getPoint(), 90 - angle, thrust);
   return;
}

/***************************************
 * SHIP :: APPLY THRUST
 * apply thrust in the direction the ship 
 * is pointing
 ***************************************/
void Ship :: applyThrust(Point p, float angle)
{
   vel.setDx(vel.getDx() + ((THRUST_AMOUNT) * (-cos(M_PI / 180.0 * angle))));
	 vel.setDy(vel.getDy() + ((THRUST_AMOUNT) * (sin(M_PI / 180.0 * angle))));
}

/***************************************
 * SHIP :: MOVE LEFT
 * moves the ships head to the left
 ***************************************/
void Ship :: moveLeft()
{
   angle += ROTATE_AMOUNT;
}

/***************************************
 * SHIP :: MOVE RIGHT
 * moves the ships head to the right
 ***************************************/
void Ship :: moveRight()
{
   angle -= ROTATE_AMOUNT;
}

/***************************************
 * SHIP :: DECREASE RESPOND TIME
 * provides the user sometime to get out 
 * of the way of incoming rocks upon starting
 * a new life. The respond time is decreased
 * with each unit of time
 ***************************************/
void Ship :: decRespondTime()
{
   respondtime--;
}

