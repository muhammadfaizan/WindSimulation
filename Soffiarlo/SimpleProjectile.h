#pragma once
#include "ODE.h"
#define _VX 0
#define _X 1
#define _VY 2
#define _Y 3

class SimpleProjectile : public ODE {

public:
	// Gravitational acceleration.
	static double Gravity;

	SimpleProjectile::SimpleProjectile(double x0, double y0, 
		double vx0, double vy0,
		double t);
	
	// These methods return the location, velocity,
	// and time values.
	double getVx();
	double getVy();
	double getX();
	double getY();
	double getTime();

	// This method updates the velocity and position
	// of the projectile according to the gravity-only model.
	void updateLocationAndVelocity(double dt);

	// Because SimpleProjectile extends the ODE class,
	// it must implement the getRightHandSide method.
	// In this case, the method returns a dummy array.
	double* getRightHandSide(double s, double Q[],
		double deltaQ[], double ds, double qScale);

};

double SimpleProjectile::Gravity = -9.81;

SimpleProjectile::SimpleProjectile(double x0, double y0, 
	double vx0, double vy0,
	double t) :ODE(4)
{
	// Load the initial position, velocity, and time
	// values into the s field and q array from the
	// ODE class.
	setIndependentValue(t);
	setDependentValue(vx0, _VX);
	setDependentValue(x0, _X);
	setDependentValue(vy0, _VY);
	setDependentValue(y0, _Y);
}

void SimpleProjectile::updateLocationAndVelocity(double dt)
{
	double time = getIndependentVar();
	double vx0 = getDependentVar(0);
	double x0 = getDependentVar(1);
	double vy0 = getDependentVar(2);
	double y0 = getDependentVar(3);

	// Update the xy locations and the y-component
	// of velocity. The x-velocity doesn't change.
	double x = x0 + vx0*dt;
	double vy = vy0 + Gravity*dt;
	double y = y0 + vy0*dt + 0.5*Gravity*dt*dt; // s = S0 + (V0 * t + 1/2 a*t^2)
	
	//Update Time
	time = time + dt;

	//Load new values into ODE 
	setIndependentValue(time);
	setDependentValue(x, _X);
	setDependentValue(y, _Y);
	setDependentValue(vy, _VY);
}

double* SimpleProjectile::getRightHandSide(double s, double Q[],
	double deltaQ[], double ds, double qScale) {

	return new double[1];
}
double SimpleProjectile::getTime()
{
	return getIndependentVar();
}
double SimpleProjectile::getVx()
{
	return getDependentVar(_VX);
}
double SimpleProjectile::getX()
{
	return getDependentVar(_X);
}
double SimpleProjectile::getY()
{
	return getDependentVar(_Y);
}
double SimpleProjectile::getVy()
{
	return getDependentVar(_VY);
}

