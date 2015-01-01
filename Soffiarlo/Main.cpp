#include <stdio.h>
#include<stdlib.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include "glut.h"
//#include "RGBApixMap.h"
#include "RGBA.h"
#include "canvas.h"
#include "textures.h"
#include "vector.h"
#include "ball.h"
#include "wav.h"
#include "level.h"
#include "Flower.h"

using namespace std;



#define RATIO 1.618         
#define WW    200            // 
#define WH    (WW/RATIO)     // 
#define HALFX ((int)(WW/2))  
#define HALFY ((int)(WH/2))  
#define deltat .001	        
#define PI 3.1415
int WindowWidth;
int WindowHeight;

void Timer(int time);
void InitGL();
void Display();
float getTime();
void Keyboard(unsigned int Btn, int x, int y);
void Reshape(int, int);
void pressKeySpecial(int key, int x, int y);
void releaseKeySpecial(int key, int x, int y);
void drawBoundary(GLint left, GLint top, GLint right, GLint bottom);
static bool tweenForward = true;


Flower dandelion = Flower();
level L1 = level(1, Point2(-HALFX + 10, HALFY - 10));
Ball Dandelion(2, 0.002);
Vector2D Gravity = Vector2D(sin(Dandelion.mass->pos.y), -0.2);
HWAV background, wind = NULL, errorSound= NULL;
bool isWindBlowing = false;
void(*callback);



void main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);


	WindowWidth = (int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.8);
	WindowHeight = (int)(WindowWidth / RATIO);


	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition((int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.1), (glutGet((GLenum)GLUT_SCREEN_HEIGHT) / 2) - (WindowHeight / 2));
	glutCreateWindow("Project");
	InitGL();

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	//glutKeyboardFunc(myKB_Handler);
	glutTimerFunc(100, Timer, 1);

	glutMainLoop();

}
void PlayErrorSound()
{
	errorSound = PlayWavFile("bells.wav", false);
}
void pressKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		//Dandelion.mass->applyForce(Vector2D(10.0,sin(rand()%4)));
		//dandelion.setWindVx(30.1);
		L1.blowright();
		break;

	case GLUT_KEY_RIGHT:
		//Dandelion.mass->applyForce(Vector2D(-10.0, sin(rand() % 4)));
		//dandelion.setWindVx(-30.1);
		L1.blowleft();
		break;

	case GLUT_KEY_UP:
		//Dandelion.mass->applyForce(Vector2D(0, -8.0));
		//dandelion.setWindVy(-30.5);
		L1.blowbottom();
		break;

	case GLUT_KEY_DOWN:
		//Dandelion.mass->applyForce(Vector2D(0.0, 10.0));
		//dandelion.setWindVy(30.5);
		L1.blowtop();
		break;
	}
	if (!isWindBlowing)
	{
		PlayForegroundSound("wind.wav");
		isWindBlowing = true;
	}
	/*if (wind != NULL)
	{
		StopPlayingWavFile(wind);
		wind = PlayWavFile("wind.wav", true);
	}
	else 
	{
		wind = PlayWavFile("wind.wav", false);
	}	*/
	glutPostRedisplay();

}


void releaseKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Dandelion.mass->init();
		dandelion.setWindVx(0.0);
		break;

	case GLUT_KEY_RIGHT:
		Dandelion.mass->init();
		dandelion.setWindVx(0.0);
		break;

	case GLUT_KEY_UP:
		Dandelion.mass->init();
		dandelion.setWindVy(0.0);
		break;

	case GLUT_KEY_DOWN:
		Dandelion.mass->init();
		dandelion.setWindVy(0.0);
		break;
	}
	isWindBlowing = false;
	/*if (wind != NULL)
	{
		StopPlayingWavFile(wind);
	}
	*/
	glutPostRedisplay();

}
void Display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	L1.draw();
	glPointSize(5);
	//Dandelion.drawBall();
	
	glLineWidth(4.0);
	drawBoundary(0, HALFY*2, HALFX*2, 0);
	//L1.draw2();
	//L1.draw2();
	glutSwapBuffers();
	//glutPostRedisplay();

}



void drawBoundary(GLint left, GLint top, GLint right, GLint bottom)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(left, top);
	glVertex2i(right, top);
	glVertex2i(right, bottom);
	glVertex2i(left, bottom);
	glEnd();
}

void checkBoundary(GLint left, GLint top, GLint right, GLint bottom, void (*func_ptr)())
{
	if (Dandelion.mass->pos.x <= 10 || Dandelion.mass->pos.x >= HALFX*2)
	{
		Dandelion.mass->vel.x = 0;
		if (Dandelion.mass->pos.x <= 10)
		{
			Dandelion.mass->pos.x = 10;
			
		}
		else
		{
			Dandelion.mass->pos.x = HALFX*2;
		}
		if (errorSound == NULL)
		{
			func_ptr();
		}
	}
	if (Dandelion.mass->pos.y < 10 || Dandelion.mass->pos.y > HALFY*2)
	{
		Dandelion.mass->vel.y = 0;
		if (Dandelion.mass->pos.y <= 10)
		{
			Dandelion.mass->pos.y = 10;
		}
		else
		{
			Dandelion.mass->pos.y = HALFY*2;
		}
		if (errorSound == NULL)
		{
			func_ptr();
		}
	}

}

void Timer(int t)
{

	static float prevTime = 0.0f;
	float currTime = getTime();
	double elapsedTime = currTime - prevTime;
		//printf("%f\n", elapsedTime);
	dandelion.updateLocationAndVelocity(1/10.0);
	L1.updateTime(1/10.0);
	prevTime = currTime;
	//printf("%f", elapsedTime
	int random = rand()%4;
	// this equation worked well --> cos(random)-pow(cos(random),2.0)/1000
	//cout << random << endl;
	Dandelion.mass->accelerate(Vector2D(cos(random) - pow(cos(random), 2.0) / 1000, -0.009));

	//Dandelion.mass->accelerate(Vector2D(0, -0.009));
	checkBoundary(-HALFX, HALFY, HALFX, -HALFY,PlayErrorSound);
	Dandelion.mass->runPhysics(elapsedTime);
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void Reshape(int w, int h)
{
	glutReshapeWindow(w, (int)(w / RATIO));
	WindowWidth = w;
	WindowHeight = (int)(w / RATIO);
	InitGL();
}


void InitGL()
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-HALFX, HALFX, -HALFY, HALFY);
	gluOrtho2D(0, HALFX*2, 0, HALFY*2);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);
	//background = PlayWavFile("atmos1.wav", true);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, WindowWidth, WindowHeight);

	/*
#define RATIO 1.618         
#define WW    200            // 
#define WH    (WW/RATIO)     // 
#define HALFX ((int)(WW/2))  
#define HALFY ((int)(WH/2))  
#define deltat .001	        
#define PI 3.1415
	
	*/

}
