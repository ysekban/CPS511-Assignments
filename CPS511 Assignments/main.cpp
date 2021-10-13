///////////////////////////////////////////////////////////////////////////
//
//
//  2D Camera manipulation
//
//  creates two viewports in glutwindow. One is a zoomed view
//  use F1 key to zoom in, F2 to zoom out
//  arrow keys to move "camera" left/right/up/down
//
//
//////////////////////////////////////////////////////////////////////////


#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void init(void);
void display(void);
void drawObjects();

void keyboardHandler(unsigned char key, int x, int y);
void specialKeyHandler(int key, int x, int y);


GLint windowWidth = 1000;
GLint windowHeight = 250;
GLint viewportWidth = windowWidth / 2;
GLint viewportHeight = windowHeight;


// Boundaries of your world - openGL is never told about these boundaries - 
//                            it is only told about your view of the world 
//                            using glOrtho2D

GLdouble worldLeft = -400.0;
GLdouble worldRight = 400.0;
GLdouble worldBottom = -200.0;
GLdouble worldTop = 200.0;

// Fixed view of the world , displayed in the left viewport
#define WVLEFT   -400.0
#define WVRIGHT   400.0
#define WVBOTTOM -200.0
#define WVTOP     200.0

// Boundaries of world view (wv) window - also called the clip window
// or clip rectangle
GLdouble wvLeft = -200.0,
wvRight = 200.0,
wvBottom = -100.0,
wvTop = 100.0;


double aspectRatio = 2.0;

GLdouble red = 1.0;
GLdouble green = 0.0;
GLdouble blue = 0.0;


int main(int argc, char** argv)
{
	printf("hello graphics world!\n");

	glutInit(&argc, (char**)argv);

	//glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB /* | GLUT_DEPTH */); 
	// Use double buffer mode when doing animations
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB   /* | GLUT_DEPTH */);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("2D Camera Manipulating Program with 2 viewports");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(specialKeyHandler);

	init();

	glutMainLoop();

	return 0;
}


void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(wvLeft, wvRight, wvBottom, wvTop);

	// Now set up the MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//       The display callback function - here is where we draw our scene
//       This function is called by OpenGL for us once at the beginning and
//       every time we call glutPostRedisplay(). We *never* call this function
//       directly
/////////////////////////////////////////////////////////////////////////////////////

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Left viewport shows whole world scene
	glViewport(0, 0, viewportWidth, viewportHeight);


	// In the previous openGL examples we have seen, we set up the 
	// view of the world by calling glOrtho2D() ONCE in init()
	// In this example, we will be moving the "camera" around in the right viewport
	// (i.e. changing the position the view/clip window) and we will be
	// changing the size of the "camera lens" to zoom in/out (i.e. changing 
	// the size of the view window) using special keys in the special key 
	// handler callback function. 
	glMatrixMode(GL_PROJECTION);
	// First set it to the identity matrix
	glLoadIdentity();
	// The left viewport looks at the whole world and never changes
	gluOrtho2D(WVLEFT, WVRIGHT, WVBOTTOM, WVTOP);

	// Set mode back to MODELVIEW matrix in case we want to move 
	// some *objects* around using glTranslate()/glRotate() etc.
	glMatrixMode(GL_MODELVIEW);

	//Draw boundary of view/clip window (the "camera") in the left viewport
	// This visually indicates to us what part of the world will be 
	// displayed in the right viewport
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(wvLeft, wvBottom, 0.0);
	glVertex3f(wvRight, wvBottom, 0.0);
	glVertex3f(wvRight, wvTop, 0.0);
	glVertex3f(wvLeft, wvTop, 0.0);
	glEnd();

	drawObjects();


	// Right viewport shows zoomed scene. We can moved this view around by 
	// changing wvLeft, wvRight etc.
	glViewport(windowWidth / 2, 0, viewportWidth, viewportHeight);

	glMatrixMode(GL_PROJECTION);
	// First set it to the identity matrix
	glLoadIdentity();
	gluOrtho2D(wvLeft, wvRight, wvBottom, wvTop);

	// Set mode back to MODELVIEW matrix in case we want to move 
	// some *objects* around
	glMatrixMode(GL_MODELVIEW);


	drawObjects();

	// using double buffering here because we are animating - we'll talk
	// more about this next week
	glutSwapBuffers();

}


void drawObjects()
{

	//Draw some polygons of various colors
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(50.0, 50.0, 0.0);
	glVertex3f(70.0, 50.0, 0.0);
	glVertex3f(70.0, 70.0, 0.0);
	glVertex3f(50.0, 70.0, 0.0);
	glEnd();


	glColor3f(0.0, 0.4, 0.8);
	glBegin(GL_POLYGON);
	glVertex3f(255.0, -175.0, 0.0);
	glVertex3f(375.0, -150.0, 0.0);
	glVertex3f(375.0, 170.0, 0.0);
	glVertex3f(145.0, 190.0, 0.0);
	glEnd();


	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-300, 100.0, 0.0);
	glVertex3f(-200.0, 100.0, 0.0);
	glVertex3f(-200.0, 150.0, 0.0);
	glVertex3f(-250.0, 250.0, 0.0);
	glVertex3f(-300.0, 250.0, 0.0);
	glEnd();


	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-30.0, -50.0, 0.0);
	glVertex3f(-10.0, -50.0, 0.0);
	glVertex3f(-20.0, -30.0, 0.0);
	glEnd();


	glColor3f(0.4, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-300.0, -150.0, 0.0);
	glVertex3f(-200.0, -150.0, 0.0);
	glVertex3f(-250.0, -100.0, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-30.0, 150.0, 0.0);
	glVertex3f(-10.0, 150.0, 0.0);
	glVertex3f(-20.0, 200, 0.0);
	glEnd();

}






void keyboardHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
	case 27:
		/* Esc, q, or Q key = Quit */
		exit(0);
		break;
	}
	glutPostRedisplay();
}


void specialKeyHandler(int key, int x, int y)
{
	double clipWindowWidth;
	double clipWindowHeight;
	double wvCenterX = wvLeft + (wvRight - wvLeft) / 2.0;
	double wvCenterY = wvBottom + (wvTop - wvBottom) / 2.0;
	double wvWidth = wvRight - wvLeft;
	double wvHeight = wvTop - wvBottom;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		wvLeft -= 5.0;
		wvRight -= 5.0;
		break;
	case GLUT_KEY_RIGHT:
		wvLeft += 5.0;
		wvRight += 5.0;
		break;
	case GLUT_KEY_UP:
		wvTop += 5.0;
		wvBottom += 5.0;
		break;
	case GLUT_KEY_DOWN:
		wvTop -= 5.0;
		wvBottom -= 5.0;
		break;
		// Want to zoom in/out and keep  aspect ratio = 2.0
	case GLUT_KEY_F1:

		clipWindowWidth = wvWidth * 0.8;
		clipWindowHeight = wvHeight * 0.8;

		wvRight = wvCenterX + clipWindowWidth / 2.0;
		wvTop = wvCenterY + clipWindowHeight / 2.0;
		wvLeft = wvCenterX - clipWindowWidth / 2.0;
		wvBottom = wvCenterY - clipWindowHeight / 2.0;

		break;
	case GLUT_KEY_F2:
		clipWindowWidth = wvWidth * 1.25;
		clipWindowHeight = wvHeight * 1.25;

		wvRight = wvCenterX + clipWindowWidth / 2.0;
		wvTop = wvCenterY + clipWindowHeight / 2.0;
		wvLeft = wvCenterX - clipWindowWidth / 2.0;
		wvBottom = wvCenterY - clipWindowHeight / 2.0;


		break;
	}
	glutPostRedisplay();
}
