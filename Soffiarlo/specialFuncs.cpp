#include <cmath>
#include <Windows.h>
#include "glut.h"

using namespace std;

float waterMovement = 0.0;  // define as extern in main.cpp

//The length of a single repetition of the water texture image 
extern const float WATER_TEXTURE_SIZE ;
float waterTextureOffset = 0;
//The opacity of the water 
const float WATER_ALPHA = 0.5f; 




void drawWater(int id)
		{
			glDisable(GL_LIGHTING);
			
			glEnable(GL_TEXTURE_2D); 
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glDisable(GL_NORMALIZE); 
			
			glEnable(GL_BLEND);
			
			glColor4f(1, 1, 1, WATER_ALPHA); 
			//glNormal3f(0, 0,1);
			
			glBegin(GL_QUADS);
			// //Here’s a quad whose texture follows a sinusoidal path in the x axis (waterMovement is the current time in seconds):	
			   glTexCoord2f(0.0f, 0.0f);		glVertex2f(-10,-10);
			   glTexCoord2f(1.0f, 0.0f);		glVertex2f(10,-10);
			   glTexCoord2f(1.0,  1.0);		    glVertex2f( 10,0);
			   glTexCoord2f(0.0, 1.0f);		    glVertex2f(0,0);
			glEnd(); 

       			
			glDisable(GL_BLEND); glEnable(GL_LIGHTING);

			glDisable(GL_TEXTURE_2D); 
			//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		}  // endWater()


/////////////////////////////////////////////  Get curretn systme time, Hard ware dependent/////////////////////


float getTime()
{
    static __int64 i64Frequency=0;
    static __int64 i64BeginCount=0;
    if (i64Frequency==0){	// do this only for the first time
       QueryPerformanceFrequency((LARGE_INTEGER*)&i64Frequency);
       QueryPerformanceCounter((LARGE_INTEGER*)&i64BeginCount); //retrieve the number of
												//ticks since system start (64bit int).

    }
    __int64 i64CurrentCount;
    QueryPerformanceCounter((LARGE_INTEGER*)&i64CurrentCount);
    return  (float)(i64CurrentCount-i64BeginCount)/i64Frequency;
}
