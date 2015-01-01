
#pragma once
#include <math.h>

// class Vector2D		---> An object to represent a 3D vector or a 3D point in space
class Vector2D
{
public:
	float x;									// the x value of this Vector2D
	float y;									// the y value of this Vector2D

	Vector2D()									// Constructor to set x = y = z = 0
	{
		x = 0;
		y = 0;
	}

	Vector2D(float x, float y)			// Constructor that initializes this Vector2D to the intended values of x, y and z
	{
		this->x = x;
		this->y = y;
	}

	Vector2D& operator= (Vector2D v)			// operator= sets values of v to this Vector2D. example: v1 = v2 means that values of v2 are set onto v1
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2D operator+ (Vector2D v)				// operator+ is used to add two Vector2D's. operator+ returns a new Vector2D
	{
		return Vector2D(x + v.x, y + v.y);
	}

	Vector2D operator- (Vector2D v)				// operator- is used to take difference of two Vector2D's. operator- returns a new Vector2D
	{
		return Vector2D(x - v.x, y - v.y);
	}
	Vector2D operator* (Vector2D v)				// operator- is used to take difference of two Vector2D's. operator- returns a new Vector2D
	{
		return Vector2D(x * v.x, y * v.y);
	}

	Vector2D operator* (float value)			// operator* is used to scale a Vector2D by a value. This value multiplies the Vector2D's x, y and z.
	{
		return Vector2D(x * value, y * value);
	}

	Vector2D operator/ (float value)			// operator/ is used to scale a Vector2D by a value. This value divides the Vector2D's x, y and z.
	{
		return Vector2D(x / value, y / value);
	}

	Vector2D& operator+= (Vector2D v)			// operator+= is used to add another Vector2D to this Vector2D.
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2D& operator-= (Vector2D v)			// operator-= is used to subtract another Vector2D from this Vector2D.
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2D& operator*= (Vector2D v)			// operator-= is used to subtract another Vector2D from this Vector2D.
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}
	Vector2D& operator*= (float value)			// operator*= is used to scale this Vector2D by a value.
	{
		x *= value;
		y *= value;
		return *this;
	}

	Vector2D& operator/= (float value)			// operator/= is used to scale this Vector2D by a value.
	{
		x /= value;
		y /= value;
		return *this;
	}


	Vector2D operator- ()						// operator- is used to set this Vector2D's x, y, and z to the negative of them.
	{
		return Vector2D(-x, -y);
	}

	float length()								// length() returns the length of this Vector2D
	{
		return sqrtf(x*x + y*y);
	};			   		

	void unitize()								// unitize() normalizes this Vector2D that its direction remains the same but its length is 1.
	{
		float length = this->length();

		if (length == 0)
			return;

		x /= length;
		y /= length;
	}

	Vector2D unit()								// unit() returns a new Vector2D. The returned value is a unitized version of this Vector2D.
	{
		float length = this->length();

		if (length == 0)
			return *this;
		
		return Vector2D(x / length, y / length);
	}

};

// class Mass			---> An object to represent a mass
class Mass
{
public:
	float m;									// The mass value
	Vector2D pos;								// Position in space
	Vector2D vel;								// Velocity
	Vector2D force;								// Force applied on this mass at an instance

	Mass(float m)								// Constructor
	{
		this->m = m;
	}

	/*
	  void applyForce(Vector2D force) method is used to add external force to the mass. 
	  At an instance in time, several sources of force might affect the mass. The vector sum 
	  of these forces make up the net force applied to the mass at the instance.
	*/
	void applyForce(Vector2D force)
	{
		this->force += force;					// The external force is added to the force of the mass
	}

	/*
	  void init() method sets the force values to zero
	*/
	void init()
	{
		force.x = 0;
		force.y = 0;
	}

	void accelerate(Vector2D a)
	{	
		force = force + a * m;	
	}

	Vector2D acceleration()
	{	
		return force * (1 / m);
	}

	/*
	  void simulate(float dt) method calculates the new velocity and new position of 
	  the mass according to change in time (dt). Here, a simulation method called
	  "The Euler Method" is used. The Euler Method is not always accurate, but it is 
	  simple. It is suitable for most of physical simulations that we know in common 
	  computer and video games.
	*/
	
		
	void runPhysics(float dt)
	{
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
  										        // The change is proportinal with the acceleration (force / m) and change in time

		pos += vel * dt;						// Change in position is added to the position.
												// Change in position is velocity times the change in time
	}

};

