#include "background.h"

//draw red sand on a hella big square plane
void background()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, TEX_SAND);
	glPushMatrix();
	glTranslatef(0.0f,5.0f,0.0f);
	glRotated(-90.0, 1.0, 0.0, 0.0);
		//glColor3f(0.192f,0.501f,0.176f);
		glEnable(GL_TEXTURE_2D);

		glColor3f(1.0f,1.0f,1.0f);
		glBegin( GL_QUADS );
	    glNormal3f(0.0, 1.0f, 0.0f);  
		glTexCoord2f(100.0f, 100.0f);                	
		glVertex3f( 3000.0f, -3000.01f, -10.1f);
		glTexCoord2f(0.0f, 100.0f);     
		glVertex3f( -3000.0f, -3000.0f, -10.1f); 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f( -3000.0f, 3000.0f, -10.1f);
		glTexCoord2f(100.0f, 0.0f);          
		glVertex3f( 3000.0f, 3000.0f, -10.1f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
