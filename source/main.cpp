/********************************************************************
Modeling of environment:
	3 simple objects				: disco ball (sphere),
									can (cylinder/disks),
									grass/footpath/sand
	2 composite objects 			: clock (circle, two skewed squares),
									building (cylinder, cone)
Lighting
	2 light sources					: ambient, diffused
Textures
	3 different surface finishes	: GL_BLEND  on building
									GL_RGB solid colour, un-textured objects such as clock face
									GL_TEXTURE_2D on all bmp textured objects
Zoom
	Level-of-details implementation	: cyclinders, spheres and circles
									rendered have more vertices at
									higher zoom
Animation
	Reasonable and smooth animation : export can dis/apearing,
									clock hands,
									disco ball
	Complexity of animation 		: clock hands render actual
									position when passed hr and min
Key Input
	Correct Zoom in/out <Z/z>		: keyPressed()
	Correct rotation of scene X/Y 	: keyPressed()
	Correct functionof of remaining : keyPressed()
Misc
	Display key func in window 		: printControls()
	Quality and reasonable setting 	: yes, super high quality
		of objects
	Texture on objects				: grass.bmp, bricks.bmp, 
									steel.bmp, glass.bmp,
    								sand.bmp, can.bmp, ball.bmp
	Other effects - transparency	: building is transluscent




********************************************************************/




#include "main.h"
#include "imageloader.h"
#include "can.h"
#include "building.h"
#include "lawn.h"
#include "path.h"
#include "background.h"
#include "clock.h"
#include "disco.h"



// Texture loading function
void loadTexture(Image *image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RGB,
				image->width, image->height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				image->pixels);
}


//handles window size/shape changing
void reshape (int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}


//draw all the objects (all those other cpp files)
void drawObjs(void)
{

	glPushMatrix();
	glScalef(zoom,zoom,zoom);
	glRotatef(rotY,0.0f,1.0f,0.0f); //rotate about y
	glRotatef(rotX,1.0f,0.0f,0.0f); //rotate about x

	//lcock figures out how to rotate hands by given hour/minute
	clock(hour, minute, detail);
	//disco ball that floats for reasons
	disco(discoRot, detail);
	//clocktower thing
	building(detail);
	path();
	lawn(detail);
	background();
	//8pm is export time
	if (hour >= 20)
	{
		can(detail);
	}

	glLoadIdentity();
	glPopMatrix();


	rotX+=rotXSpeed;
	rotY+=rotYSpeed;
	
	//don't animate if animation paused
	if(!paused)
	{
		minute += speed;
		if(minute >= 60){minute -= 60; hour++;}
		hour = (hour >= 24) ? hour -= 24 : hour;
		discoRot+=speed;
	}
}

void init (void)
{

	//grab system time and set the clock to display it
	time_t rawtime;
	time ( &rawtime );
	struct tm * currtime = localtime ( &rawtime );
	minute = currtime->tm_min;
	hour = currtime->tm_hour;


	//lights
	glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
    glLightfv(GL_LIGHT1, GL_POSITION, Light2Pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//action
    glShadeModel (GL_SMOOTH);
    

    //load all textures, there are some #defined constants in gl.h telling me which is which 
    Image* image1 = loadBMP("textures/grass.bmp");
    Image* image2= loadBMP("textures/bricks.bmp");
    Image* image3= loadBMP("textures/steel.bmp");
    Image* image4= loadBMP("textures/glass.bmp");
    Image* image5=loadBMP("textures/sand.bmp");
    Image* image6=loadBMP("textures/can.bmp");
    Image* image7= loadBMP("textures/ball.bmp");

	loadTexture(image1);
	loadTexture(image2);
	loadTexture(image3);
	loadTexture(image4);
	loadTexture(image5);
	loadTexture(image6);
	loadTexture(image7);

	delete image1;
	delete image2;
	delete image3;
	delete image4;
	delete image5;
	delete image6;
	delete image7;
}

//rudimentary text display
//draw a given line of text from supplied x,y
void GLPrint(const char* text, float x, float y)
{

	int i;
	int length = strlen(text);
	
	glColor3f(1.0,1.0,1.0);
	glRasterPos3f(x,y,-10.0f);
	glPushMatrix();

	//one char at a time
	for(i=0; i < length; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
		}
	glPopMatrix();
}

//tell user what buttons do
void printControls()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glRotatef(-15.0f,1.0f,0.0f,0.0f);

		GLPrint("Input:",-15.0,12.0);
		GLPrint("<z>/<Z> : Zooms in/out",-15.0,11.0);
		GLPrint("<x>/<X> : X-axis rotation clock/anti-clockwise",-15.0,10.0);
		GLPrint("<y>/<Y> : Y-axis rotation clock/anti-clockwise",-15.0,9.0);
		GLPrint("<p>/<P> : Turn on Smooth/Flat Shading",-15.0,8.0);
		GLPrint("<a>/<A> : Start animation",-15.0,7.0);
		GLPrint("<t>/<T> : Pause animation",-15.0,6.0);
		GLPrint("<c>/<C> : Resume Animation",-15.0,5.0);
		GLPrint("<Esc> : Quit the program",-15.0,4.0);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

//blank screen with colour then draw all the objects/print text
void display (void)
{

	float daylight[3] = {0.0f,
		(float)191/255,
		1.0f};


	if(hour < 12)
	{
		daylight[1] *= (hour + minute/60)/12;
		daylight[2] *= (hour + minute/60)/12;
	}
	else
	{
		daylight[1] *= 1-((hour-12 + minute/60)/12);
		daylight[2] *= 1-((hour-12 + minute/60)/12);
	}


	glClearColor(daylight[0],daylight[1],daylight[2],0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt (0.0, 2.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//camera	
	glTranslatef(0.0f, 0.0f, -10.0f);
	drawObjs();
	printControls();

	//flips the buffer you were working on to now display onscreen
	glutSwapBuffers();
	
}

int main (int argc, char **argv)
{
	//tell opengl which funstions to use for what
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Luke Mercuri - 17365547");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	
}


//key presses and ternaries. best function 2014
void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
		//quit
		case KEY_ESC:
			exit(EXIT_SUCCESS);
		break;
		//faster animation
		case 'f':
		case 'F':
			speed = (speed < 1) ? speed + 0.01: speed;
		break;
		//slower aniimation
		case 's':
		case 'S':
			speed = (speed >= 0.01) ? speed - 0.01 : speed;
		break;
		//stop animation
		case 't':
		case 'T':
			paused = 1;
		break;
		//continue animation
		case 'c':
		case 'C':
			paused = 0;		
		break;	
		//begin/contniue animation
		case 'a':
		case 'A':
			paused = 0;
			speed = (speed < 0.01) ? speed + 0.01 : speed;
		break;
		//rotate  about y axis
		case 'Y':
			rotYSpeed = (rotYSpeed < 0.3f) ? rotYSpeed + 0.1f : rotYSpeed;
			rotY = (rotY > 360) ? rotY - 360 : rotY; 
		break;
		//rotate other direction about y axis
		case 'y':
			rotYSpeed = (rotYSpeed > -0.3f) ? rotYSpeed - 0.1f : rotYSpeed;
			rotY = (rotY > 360) ? rotY - 360 : rotY; 
		break;
		//rotate about x axis
		case 'X':
			rotXSpeed = (rotXSpeed < 0.3f) ? rotXSpeed + 0.1f : rotXSpeed;
		break;
		//rotate other direction about x axis
		case 'x':
			rotXSpeed = (rotXSpeed > -0.3f) ? rotXSpeed - 0.1f: rotXSpeed;
		break;
		//zoom in
		case 'z': 
		if (zoom < 3.0f)
		{
			detail++;
			zoom = zoom + ZOOM;
		}
        break;
        //zom out
        case 'Z': 
        if (zoom-ZOOM > 0.1f)
        {
        	detail--;
			zoom = zoom - ZOOM;
		}
        break;
        //smooth shading
		case 'P':
			glShadeModel (GL_SMOOTH); 		
		break;
		//flat shading
		case 'p':
			glShadeModel (GL_FLAT); 			
		break;	
		
	}
	


}
