#pragma once

#include "DragProjectile.h"
#include <math.h>
#define _VX 0
#define _X 1
#define _VY 2
#define _Y 3


class WindProjectile : public DragProjectile
{
private:
	double static windVx;
	double static windVy;
public:
	WindProjectile::WindProjectile(
		double x0, double y0,
		double vx0, double vy0, 
		double time, double mass, double area, double density, double Cd);

	double getWindVx();
	double getWindVy();
	void setWindVx(double);
	void setWindVy(double);

	double* getRightHandSide(double IndependentVariable,
		double DependentVariables[],
		double DeltaOfDependents[], 
		double DIndependent, 
		double IndependentScale);
	void updateLocationAndVelocity(double dt);
};



WindProjectile::WindProjectile(double x0, double y0,
	double vx0, double vy0, double time,
	double mass, double area, double density, double Cd
	) : DragProjectile(x0, y0, vx0, vy0, time, mass,
	area, density, Cd)
{
	
}

double WindProjectile::getWindVx()
{
	return windVx;
}
double WindProjectile::getWindVy()
{
	return windVy;
}

void WindProjectile::setWindVx(double value)
{
	WindProjectile::windVx = value;
}

void WindProjectile::setWindVy(double value)
{
	WindProjectile::windVy = value;
}

double* WindProjectile::getRightHandSide(double 
	IndependentVariable,
	double DependentVariables[],
	double DeltaOfDependents[],
	double DIndependent,
	double DependentScale)
{
	double *dDepVar = new double[4];
	double *newDepVar = new double[4];

	// Compute the intermediate values of the
	// dependent variables.
	for (int i = 0; i< 4; ++i) {
		cout << DependentVariables[i] << " + " << DependentScale << "*" << DeltaOfDependents[i] << endl;
		newDepVar[i] = DependentVariables[i] + DependentScale*DeltaOfDependents[i];
	}

	// Declare some convenience variables representing
	// the intermediate values of velocity.
	double vx = newDepVar[_VX];
	double vy = newDepVar[_VY];
	cout << "Vy = " << vy << endl;
	// Compute the apparent velocities by subtracting
	// the wind velocity components from the projectile
	// velocity components.

	double vax = vx - WindProjectile::windVx;
	double vay = vy - WindProjectile::windVy;
	cout << "Vax = " << vax << endl;
	cout << "Vay = " << vay << endl;
	// Compute the apparent velocity magnitude. The 1.0e-8 term
	// ensures there won't be a divide by zero later on
	// if all of the velocity components are zero.
	double va = sqrt(vax*vax + vay*vay ) + 1.0e-8;
	cout << "Va = " << va << endl;
	double density = getDensity(), area = getArea(), Cd = getCd();
	// Compute the total drag force.
	double Fd = 0.5*density*area*Cd*va*va;
	cout << "Fd = " << Fd << endl;
	
	
	// Compute the right-hand sides of the six ODEs.
	//dDepVar[_VX] = -DIndependent*Fd*vax / (getMass()*va);
	dDepVar[_VX] = -DIndependent*vax * 10 / (getMass()*va);
	cout << "dVx = " << dDepVar[_VX] << endl;

	dDepVar[_X] = DIndependent*vx;
	cout << "dX = "<< dDepVar[_X] << endl;

	//dDepVar[_VY] = DIndependent*(Gravity - Fd*vay / (getMass()*va
	dDepVar[_VY] = DIndependent*(Gravity - vay * 10 / (getMass()*va));
	cout << "dVy = "<< dDepVar[_VY] << endl;

	dDepVar[_Y] = DIndependent*vy;
	cout << "dY = " << dDepVar[_Y] << endl;

	return dDepVar;
}


double WindProjectile::windVx = 0;
double WindProjectile::windVy = 0;
void WindProjectile::updateLocationAndVelocity(double dt)
{
	ODESolver::RungeKutta4(*this, dt);
	cout << "dt - > " << dt << endl;
	cout << "X - > " << this->getX() << endl;
	cout << "Y - > " << this->getY() << endl;
	cout << "VX - > " << this->getVx() << endl;
	cout << "Vy - > " << this->getVy() << endl;
	cout << "+++++++++++++++++++++++++++" << endl;

}