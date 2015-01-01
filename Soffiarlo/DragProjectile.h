#pragma once

#include "SimpleProjectile.h"
#include "ODE.h"
#include <math.h>
#define _VX 0
#define _X 1
#define _VY 2
#define _Y 3


class DragProjectile : public SimpleProjectile {

private : 
	double mass, area, density, Cd;

public:
	DragProjectile::DragProjectile(double x0, double y0,
		double vx0, double vy0, double time,
		double mass, double area, double density, double Cd);

	// These methods return the value of the fields
	// declared in this class.
	double getMass();
	double getArea();
	double getDensity();
	double getCd();

	// This method updates the velocity and location
	// of the projectile using a 4th order Runge-Kutta
	// solver to integrate the equations of motion.
	void updateLocationAndVelocity(double dt);

	double* getRightHandSide(double IndependentVariable, double DependentVariables[],
		double DeltaOfDependents[], double DIndependent, double IndependentScale);
};

DragProjectile::DragProjectile(double x0, double y0,
	double vx0, double vy0, double time,
	double mass, double area, double density, 
	double Cd) : SimpleProjectile(x0,y0,vx0,vy0,time)
{
	// Initialize variables declared in the DragProjectile class.
	this->mass = mass;
	this->area = area;
	this->density = density;
	this->Cd = Cd;
}

double DragProjectile::getMass()
{
	return this->mass;
}
double DragProjectile::getArea()
{
	return this->area;
}
double DragProjectile::getDensity()
{
	return this->density;
}
double DragProjectile::getCd()
{
	return this->Cd;
}

void DragProjectile::updateLocationAndVelocity(double dt)
{

	ODESolver::RungeKutta4(*this, dt);
}

double* DragProjectile::getRightHandSide(double IndependentVariable, double DependentVariables[],
	double DeltaOfDependents[], double DIndependent, double DependentScale)
{
	double *dDepVar = new double[4];
	double *newDepVar = new double[4];

	// Compute the intermediate values of the
	// dependent variables.
	for (int i = 0; i< 4; ++i) {
		newDepVar[i] = DependentVariables[i] + DependentScale*DeltaOfDependents[i];
	}

	// Declare some convenience variables representing
	// the intermediate values of velocity.
	double vx = newDepVar[_VX];
	double vy = newDepVar[_VY];

	// Compute the velocity magnitude. The 1.0e-8 term
	// ensures there won't be a divide by zero later on
	// if all of the velocity components are zero.
	double v = sqrt(vx*vx + vy*vy) + 1.0e-8; // Magnitude of Velocity Vector


	// Compute the total drag force.
	double Fd = 0.5*density*area*Cd*v*v; // Fd = 1/2(P.V^2.A.Cd)

	// compute the right hand sides of the 4 ODEs
	dDepVar[_VX] = -DIndependent*Fd*vx / (mass*v);// dVx= (dt * DragForce * Vx)/ (Mass * V)
	dDepVar[_X] = DIndependent*vx;
	dDepVar[_VY] = DIndependent*(Gravity - Fd*vy / (mass*v));
	dDepVar[_Y] = DIndependent * vy;

	return dDepVar;

}