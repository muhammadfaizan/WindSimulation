#include <iostream>
#include <stdlib.h>
#include <vector>
//#include "RGBApixMap.h"

//#include "supportedClass.h"
#include <Windows.h>
#include "glut.h"
#include "RGBA.h"
#include "ball.h"
#include "Flower.h"



#define RATIO 1.618         
#define WW    200            // 
#define WH    (WW/RATIO)     // 
#define HALFX ((int)(WW/2))  
#define HALFY ((int)(WH/2))  


struct backgroundColor {
	GLbyte r, g, b, a;
};
class level
{
	unsigned short levelNo;
	std::vector<RealRect> pipes;
	Point2 goalPosition; // goal is a square, so when you draw goal, ask for its length too.
	backgroundColor bg, pipeColor, goalColor;
	RGBApixmap background, flower, background2, endOfGame, pipe;
	Flower dandelion;
	bool gameEnd;
	


public:
	level::level(short levelNumber, Point2 PositionOfGoal)
	{
		this->background.readBMPFile("sky.bmp", 1);
		this->background2.readBMPFile("hill.bmp", 1);
		this->background2.setChromaKey(255, 255, 255);
		glEnable(GL_TEXTURE_2D);
		/*this->endOfGame.readBMPFile("End.bmp", 1);
		this->endOfGame.setTexture(2001);*/



		
		pipe.readBMPFile("Pipe.bmp", 1);
		pipe.setChromaKey(255, 255, 255);
		pipe.setTexture(2002);

		this->endOfGame.readBMPFile("End.bmp", 1);
		this->endOfGame.setTexture(2001);


		this->bg.r = 1;
		this->bg.g = 1;
		this->bg.b = 1;

		this->pipeColor.r = 0;
		this->pipeColor.g = 1;
		this->pipeColor.b = 0;

		this->goalPosition = PositionOfGoal;
		this->dandelion = Flower();

	}
	void blowright()
	{
		this->dandelion.setWindVx(10.1);
		cout << "I was called" << endl;
	}

	void blowleft()
	{
		dandelion.setWindVx(-10.5);
	}
	void blowtop()
	{
		dandelion.setWindVy(10.5);
	}

	void blowbottom()
	{
		dandelion.setWindVy(-10.5);
	}

	void donotBlowX()
	{
		dandelion.setWindVx(10.5);
	}
	void donotBlowY()
	{
		dandelion.setWindVy(0.0);
	}
	level::level(short levelNumber, Point2 goalPosition, std::vector<RealRect> Pipes)
	{
		this->background.readBMPFile("sky.bmp", 1);
		this->background2.readBMPFile("hill.bmp", 1);
		this->background2.setChromaKey(255, 255, 255);
		flower.readBMPFile("dandalion.bmp", 1);
		flower.setChromaKey(255, 255, 255);


		this->pipes = Pipes;
		level(levelNumber, goalPosition);
	}// constructor
	void insertPipe(RealRect Pipe)
	{
		pipes.push_back(Pipe);
	}

	void clearPipes()
	{
		pipes.clear();
	}
	std::vector<RealRect> getPipes()
	{
		return pipes;
	}

	void updateTime(double dt) {
		dandelion.updateLocationAndVelocity(dt);
	}

	void draw()
	{
		glEnable(GL_TEXTURE_2D);
		glClearColor(bg.r, bg.g, bg.b, bg.a);
		//glColor3b(pipeColor.r, pipeColor.g, pipeColor.b);
		drawPipes();
		//glColor3b(goalColor.r, goalColor.g, goalColor.b);
		drawGoal(10);
		// please before drawing anything, reset your color to desired object color or else it will merge with goal color
		glRasterPos2d(0, 0); // bottom, left
		this->background.mDraw();
		this->background2.mDraw();
		dandelion.draw();
		glColor3f(1.0, 1.0, 1.0);
		//drawWall();

		

		checkCollision();
		if (gameEnd)
			draw2();

	}

	void checkCollision() {
		if (collidesRight() || collidesLeft() || collidesTop() || collidesBottom())
			gameEnd = true;
	}

	bool collidesRight() {
		if (dandelion.getX() >= HALFX * 2 - 5)
			return true;
		return false;
	}

	bool collidesLeft() {
		if (dandelion.getX() <= 5)
			return true;
		return false;
	}

	bool collidesTop() {
		if (dandelion.getY() >= HALFY * 2 - 5)
			return true;
		return false;
	}

	bool collidesBottom() {
		if (dandelion.getY() <= 5)
			return true;
		return false;
	}
	void draw2()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		//glClear(GL_COLOR_BUFFER_BIT);

		
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//gluOrtho2D(0, HALFX*2, 0, HALFY*2);

		glBindTexture(GL_TEXTURE_2D, 2001);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex2d(0, 0);

		glTexCoord2f(1.0, 0.0);
		glVertex2d(HALFX*2, 0);

		glTexCoord2f(1.0, 1.0);
		glVertex2d(HALFX*2, HALFY*2);

		glTexCoord2f(0.0, 1.0);
		glVertex2d(0, HALFY*2);
		glEnd();
		/*glRasterPos2d((HALFX / 4 )* 2, (HALFY/4) * 2);
		endOfGame.mDraw();*/
		//glutSwapBuffers();
	}

private:

	void drawWall() {
	
	glBindTexture(GL_TEXTURE_2D, 2002);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(HALFX, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex2d(HALFX + 10, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex2d(HALFX + 10, HALFY);
	glTexCoord2f(0.0, 1.0);
	glVertex2d(HALFX, HALFY);
	glEnd();

	}

	void drawGoal(GLint length)
	{
		glRectd(goalPosition.getX() - (length / 2.0), goalPosition.getY() + (length / 2.0), goalPosition.getX() + (length / 2.0), goalPosition.getY() - (length / 2.0));
	}

	void drawPipes()
	{
		for (int i = 0; i < pipes.size(); i++)
		{
			glRectd(pipes[i].getl(), pipes[i].gett(), pipes[i].getr(), pipes[i].getb());
		}
	}
	

};


