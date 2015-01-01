#pragma once
class ODE
{
	// Declare fields used by the class
private:
	int numEqns; // number of equations to solve
	double *dependent; // array of dependent variables
	double independent; // independent variable
	// Constructor
public :
	// Constructor
	ODE:: ODE(int numEqns) {
		this->numEqns = numEqns;
		dependent = new double[numEqns];
	}
	// These methods return the number of equations or
	// the value of the dependent or independent variables.
	int getNumberOfEquations()
	{
		return numEqns;
	}

	double getIndependentVar()
	{
		return independent;
	}

	double getDependentVar(int index)
	{
		if ( index < numEqns)
			return dependent[index];
		else
			return -1.0;
		
	}

	double* getAllIndependentVariables()
	{
		return dependent;
	}

	void setIndependentValue(double Value)
	{
		independent = Value;
	}
	void setDependentValue(double value, int index) {
		dependent[index] = value;
	}
	virtual double* getRightHandSide(double IndependentVariable, double DependentVariables[],
		double DeltaOfDependents[], double DIndependent, double DependentScale)
	{
		return new double[1];
	}
};

class ODESolver
{
public:

	//Eulars Method
	static void RungeKutta(ODE& ode, double step)
	{
		double stepsize = 0.1;

		while (stepsize <= step)
		{

			//stepsize
		}
	}
	// Fourth-order Runge-Kutta ODE solver.
	static void RungeKutta4(ODE& ode, double stepSize)
	{
		// Define some convenience variables to make the
		// code more readable
		int j;
		int numEqns = ode.getNumberOfEquations();
		cout << numEqns << endl;
		double s;
		double *q;
		double *dq1 = new double[numEqns];
		double *dq2 = new double[numEqns];
		double *dq3 = new double[numEqns];
		double *dq4 = new double[numEqns];

		// Retrieve the current values of the dependent
		// and independent variables.
		s = ode.getIndependentVar();
		cout << s << endl;

		q = ode.getAllIndependentVariables();
		cout << q << endl;

		dq1 = ode.getRightHandSide(s, q, q, stepSize, 0.0);
		dq2 = ode.getRightHandSide(s + 0.5*stepSize, q, dq1, stepSize, 0.5);
		dq3 = ode.getRightHandSide(s + 0.5*stepSize, q, dq2, stepSize, 0.5);
		dq4 = ode.getRightHandSide(s + stepSize, q, dq3, stepSize, 1.0);

		// Update the dependent and independent variable values
		// at the new dependent variable location and store the
		// values in the ODE object arrays.
		ode.setIndependentValue(s + stepSize);

		for (j = 0; j < numEqns; j++)
		{

			q[j] = q[j] + (dq1[j] + 2.0*dq2[j] + 2.0*dq3[j] + dq4[j]) / 6.0;
			ode.setDependentValue(q[j], j);
			cout << q[j] << endl;
		}
		
	}

	//static void RungeKutta4(DragProjectile ode, double step)
	//{
	//	// Define some convenience variables to make the
	//	// code more readable
	//	int j;
	//	int numEqns = ode.getNumberOfEquations();
	//	double s;
	//	double *q;
	//	double *dq1 = new double[numEqns];
	//	double *dq2 = new double[numEqns];
	//	double *dq3 = new double[numEqns];
	//	double *dq4 = new double[numEqns];

	//	// Retrieve the current values of the dependent
	//	// and independent variables.
	//	s = ode.getIndependentVar();
	//	q = ode.getAllIndependentVariables();

	//	dq1 = ode.getRightHandSide(s, q, q, step, 0.0);
	//	dq2 = ode.getRightHandSide(s + 0.5*step, q, dq1, step, 0.5);
	//	dq3 = ode.getRightHandSide(s + 0.5*step, q, dq2, step, 0.5);
	//	dq4 = ode.getRightHandSide(s + step, q, dq3, step, 1.0);

	//	// Update the dependent and independent variable values
	//	// at the new dependent variable location and store the
	//	// values in the ODE object arrays.
	//	ode.setIndependentValue(s + step);

	//	for (j = 0; j < numEqns; j++)
	//	{
	//		q[j] = q[j] + (dq1[j] + 2.0*dq2[j] + 2.0*dq3[j] + dq4[j]) / 6.0;
	//		ode.setDependentValue(q[j], j);
	//	}
	//	
	//}

	//static void RungeKutta4(WindProjectile ode, double step)
	//{
	//	// Define some convenience variables to make the
	//	// code more readable
	//	int j;
	//	int numEqns = ode.getNumberOfEquations();
	//	double s;
	//	double *q;
	//	double *dq1 = new double[numEqns];
	//	double *dq2 = new double[numEqns];
	//	double *dq3 = new double[numEqns];
	//	double *dq4 = new double[numEqns];

	//	// Retrieve the current values of the dependent
	//	// and independent variables.
	//	s = ode.getIndependentVar();
	//	q = ode.getAllIndependentVariables();

	//	dq1 = ode.getRightHandSide(s, q, q, step, 0.0);
	//	dq2 = ode.getRightHandSide(s + 0.5*step, q, dq1, step, 0.5);
	//	dq3 = ode.getRightHandSide(s + 0.5*step, q, dq2, step, 0.5);
	//	dq4 = ode.getRightHandSide(s + step, q, dq3, step, 1.0);

	//	// Update the dependent and independent variable values
	//	// at the new dependent variable location and store the
	//	// values in the ODE object arrays.
	//	ode.setIndependentValue(s + step);

	//	for (j = 0; j < numEqns; j++)
	//	{
	//		q[j] = q[j] + (dq1[j] + 2.0*dq2[j] + 2.0*dq3[j] + dq4[j]) / 6.0;
	//		ode.setDependentValue(q[j], j);
	//	}
	//	
	//}
};
