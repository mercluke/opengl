#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif
#ifdef __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <math.h>

#define TAU (6.283185308)
#define ZOOM (0.1)

#define TEX_GRASS	1
#define TEX_BRICKS	2
#define TEX_STEEL	3
#define TEX_GLASS	4
#define TEX_SAND	5
#define TEX_CAN		6
#define TEX_BALL	7
