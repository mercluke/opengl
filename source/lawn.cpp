#include "lawn.h"

//draw yellow dead grass
void lawn(int segments)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, TEX_GRASS);
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glRotatef(-90,1.0f,0.0f,0.0f);
		glTranslatef(0.0f, 0.0f, -5.0f);
		glColor3f(1.0f,1.0f,1.0f);
		glBegin( GL_TRIANGLE_FAN );
	        glVertex2f(0, 0);
	        int r = 30;
	        for( int i = 0; i <= 3*segments; i++ ) {
	        	//draw circle with maths, more detail == more points
	            GLfloat v = TAU*(float)i/((float)3*segments);
	            glVertex2f(r*sin(v), r*cos(v));
	            glTexCoord2f(3*sin(v), 3*cos(v));
	        }

		glDisable(GL_TEXTURE_2D);
		glEnd();
		glLoadIdentity();
	    glPopMatrix();
}