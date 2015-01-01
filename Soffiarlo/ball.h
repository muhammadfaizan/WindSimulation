#pragma once
#include <windows.h>
#include "Physics.h"

class Ball
{
	public:

	Ball();
	Ball(float, float);
	void drawBall(float dx,float dy,float op);
	void drawBall(void);
	void moveBall(void);
	
	//private:
		float radius;
		Mass *mass;  

};

Ball::Ball()
{
   radius =	0.1;
}

Ball::Ball(float r,float m)
{
   // initial settings so ball go upward first
   this->radius =	r;
   this->mass = new Mass(20.0); // change mass 0.2 ,20,200 ,2000
   this->mass->pos = Vector2D(0.0f, 0.0f);  //a mass was created and we set its position to the origin
   this->mass->vel = Vector2D(0.0,1.0);
}

void Ball::drawBall()
{
	float dx = this->mass->pos.x;
	float dy = this->mass->pos.y;
	
	glPushMatrix();
		glTranslatef(dx,dy,0);
		glutSolidSphere(this->radius,40,40);
	glPopMatrix();

}


void Ball::drawBall(float dx,float dy,float opacity)
{
		
}







