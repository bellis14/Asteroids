#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include <string>
#include "velocity.h"
#include "point.h"
#include "flyingObject.h"


/***************************************
* CLASS :: ROCKS (BASECLASS)
* contains all the data and method functions
* for big, medium, and small rocks
****************************************/
class Rocks : public FlyingObject
{
private:
   protected:
      int angle;
      string identity;
      int spindirection;

public:
   Rocks();
   string getIdentity() { return identity; }
   int getAngle() { return angle; }
   virtual void setAngle(int a)= 0; 
   
};

/***************************************
* CLASS :: BIGROCK (SUBCLASS)
* contains all the data and method functions
* for big rocks
****************************************/
class BigRock : public Rocks
{
public:
   BigRock();
   virtual void draw();
   virtual void setAngle(int a);
};

/***************************************
* CLASS :: MEDIUMROCK (SUBCLASS)
* contains all the data and method functions
* for medium rocks
****************************************/
class MediumRock : public Rocks
{
public:
   MediumRock();
   virtual void draw();
   virtual void setAngle(int a);
};

/***************************************
* CLASS :: SMALLROCK (SUBCLASS)
* contains all the data and method functions
* for small rocks
****************************************/
class SmallRock : public Rocks
{
public:
   SmallRock();
   virtual void draw();
   virtual void setAngle(int a);
};

#endif /* rocks_h */
