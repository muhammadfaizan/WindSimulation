#include "Physics.h"
#include <stdlib.h>
#include <math.h>
class Wind
{
private:
	Vector2D Flow = Vector2D(0, 0);
	const float MaxWindAllowed = 10;
	bool floatRight, floatLeft, floatUp,floatDown;
public: 
	void FlowRight();
	void FlowLeft();
	void FlowUp();
	void FlowDown();
	void DoNotFlow();
	Vector2D getCurrentFlow();
};


Vector2D Wind::getCurrentFlow()
{
	return Flow;
}
void Wind::FlowRight()
{

	if (Flow.x < MaxWindAllowed)
	{
		Flow += Vector2D(MaxWindAllowed/100.0, sin( (float)(rand() % 5)));
	}
	else  if (Flow.x > MaxWindAllowed) {
		Flow = Vector2D(MaxWindAllowed, sin((float)(rand() % 5)));
	}
}
void Wind::FlowLeft()
{

	if (Flow.x > -MaxWindAllowed)
	{
		Flow -= Vector2D(-MaxWindAllowed / 100.0, sin((float)(rand() % 5)));
	}
	else  if (Flow.x < -MaxWindAllowed) {
		Flow = Vector2D(-MaxWindAllowed, sin((float)(rand() % 5)));
	}
}
void Wind::FlowUp()
{

	if (Flow.y < MaxWindAllowed)
	{
		Flow += Vector2D(0.0, MaxWindAllowed / 100.0);
	}
	else  if (Flow.y > MaxWindAllowed) {
		Flow = Vector2D(0.0, MaxWindAllowed);
	}
}

void Wind::FlowDown()
{

	if (Flow.y < MaxWindAllowed)
	{
		Flow += Vector2D(MaxWindAllowed / 100.0, sin((float)(rand() % 4)));
	}
	else  if (Flow.y < -MaxWindAllowed) {
		Flow = Vector2D(-MaxWindAllowed, sin((float)(rand() % 4)));
	}
}
