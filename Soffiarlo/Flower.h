#pragma once
#include "WindProjectile.h"
//#include "supportedClass.h"
#include "vector.h"
#include "RGBA.h"
#include "glut.h"
#define PI 3.1415726 
class Flower : public WindProjectile
{
private :
	double radius;
	RGBApixmap img;


	
	/*WindProjectile::WindProjectile(
		double x0, double y0,
		double vx0, double vy0, 
		double time, double mass, double area, double density, double Cd,
		);*/
public:
	Flower::Flower(Point2 PositionOfFlower, double mass,
		double area, double density, double Cd);
	Flower::Flower();

	void draw()
	{
		glRasterPos2d(this->getX()+radius, this->getY()-radius);
		img.mDraw();
	}
};

Flower::Flower() :WindProjectile(30,30, 0.0,10, 0.0, 0.02, PI * 4,1.225,1.2)
{
	this->radius = 2.0;
	img.readBMPFile("dandalion.bmp", 1);
	img.setChromaKey(255, 255, 255);
}

Flower::Flower(Point2 PositionOfFlower, double mass,
	double area, double density, double Cd) :
	WindProjectile(PositionOfFlower.getX(), PositionOfFlower.getY(), 0.0, 0.0, 0.0, mass, PI * 4, 1.225, 0.47)
{
	this->radius = 2.0;
	img.readBMPFile("dandalion.bmp", 1);
	img.setChromaKey(255, 255, 255);
}