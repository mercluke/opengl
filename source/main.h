#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gl.h"

#define KEY_ESC 27


GLfloat speed;
GLfloat hour;
GLfloat minute;
GLfloat discoRot;


// LIGHTS
GLfloat Light1Pos[] = {0.0, 10.0, 5.0, 1.0};
GLfloat Light2Pos[] = {0.0, 0.0, -2.0, 1.0};
GLfloat lightColor[] = {1.0f, 0.8f, 0.8f, 1.0f};

//CAMERA ROTATIONS
GLfloat rotY;
GLfloat rotYSpeed;
GLfloat rotX;
GLfloat rotXSpeed;
GLfloat zoom = ZOOM;

int paused = 1;

/**procedural objects like the clock and can look better when closer**/
GLfloat detail = 13.0;

// FUNCTIONS

void keyPressed (unsigned char key, int x, int y);
void reshape (int width, int height);
void drawObjs (void);
void init (void);

void display (void);
void GLPrint(char *, float x, float y);
void printControls(void);
