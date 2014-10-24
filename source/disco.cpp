#include "disco.h"

//disco ball, these are super important to have in the outback
void disco(GLfloat rot, int segments)
{
	//give the ball a texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, TEX_BALL);
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		//bluish tint to the colour, 70% opacity
		glColor4f(0.6f,0.6f,1.0f,0.3f);
		glRotatef(rot,0.0f,1.0f,0.0f);
		GLUquadric* quad = gluNewQuadric();
		gluQuadricTexture(quad, true);
		glPushMatrix();
			glTranslatef(-10.0f, -2.0f, -5.0f);
			gluSphere (quad,1.0, 10*segments, 10*segments);
		glPopMatrix();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		free(quad);
	glPopMatrix();
}