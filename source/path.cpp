#include "path.h"

//draw brick path
void path()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TEX_BRICKS);
	glPushMatrix();
	glTranslatef(0.0f,0.05f,0.0f);
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f,1.0f,1.0f);
		glBegin( GL_QUADS );
	    glNormal3f(0.0, 1.0f, 0.0f);  
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 1.0f, -5.0f, -5.0f);
		glTexCoord2f(0.0f, 1.0f);     
		glVertex3f( -1.0f, -5.0f, -5.0f); 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f( -1.4f, -5.0f, 3.0f); //Fake perspective
		glTexCoord2f(1.0f, 0.0f);          
		glVertex3f( 1.4f, -5.0f, 3.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}