#include "rocks.h"
#include "flyingObject.h"

/***************************************
 * ROCKS :: CONSTRUCTOR
 * initialize the identity and the starting 
 * angle of the rock
 ***************************************/
Rocks :: Rocks() : FlyingObject() 
{
   identity = "";
   angle = random(0, 360);
   spindirection = random(0, 1);
} 

/***************************************
 * BIGROCK :: CONSTRUCTOR
 * initialize the identity of the big rock
 ***************************************/
BigRock :: BigRock() : Rocks() 
{
   identity = "Big";
}
   
/***************************************
 * MEDIUMROCK :: CONSTRUCTOR
 * initialize the identity of the medium rock
 ***************************************/
MediumRock :: MediumRock() : Rocks() 
{
   identity = "Medium";
}

/***************************************
 * SMALLROCK :: CONSTRUCTOR
 * initialize the identity of the small rock
 ***************************************/  
SmallRock :: SmallRock() : Rocks() 
{
   identity = "Small";
}
/***************************************
 * BIGROCK :: SET ANGLE
 * sets the rotation of the big rock
 ***************************************/
void BigRock :: setAngle(int a)
{ 
   if (spindirection == 1)
      angle = a + BIG_ROCK_SPIN;
   else if (spindirection == 0)
      angle = a - BIG_ROCK_SPIN;
}

/***************************************
 * MEDIUMROCK :: SET ANGLE
 * sets the rotation of the medium rock
 ***************************************/
void MediumRock :: setAngle(int a)
{ 
   if (spindirection == 0)
      this->angle = a + MEDIUM_ROCK_SPIN;
   else if (spindirection == 1)
      this->angle = a - MEDIUM_ROCK_SPIN;
}

/***************************************
 * SMALLROCK :: SET ANGLE
 * sets the rotation of the small rock
 ***************************************/
void SmallRock :: setAngle(int a)
{ 
   if (spindirection == 0)
      this->angle = a + SMALL_ROCK_SPIN;
   else if (spindirection == 1)
      this->angle = a - SMALL_ROCK_SPIN;
}


/***************************************
 * BIGROCK :: DRAW
 * draw the big rock with the correct speed
 ***************************************/  
void BigRock :: draw()
{
   setAngle(angle);
   drawLargeAsteroid(getPoint(), angle);
   return;
}

/***************************************
 * MEDIUMROCK :: DRAW
 * draw the medium rock with the correct speed
 ***************************************/  
void MediumRock :: draw()
{
   setAngle(angle);
   drawMediumAsteroid(getPoint(), angle);
   return;
}

/***************************************
 * SMALLROCK :: DRAW
 * draw the small rock with the correct speed
 ***************************************/  
void SmallRock :: draw()
{
   setAngle(angle);
   drawSmallAsteroid(getPoint(), angle);
   return;
}
