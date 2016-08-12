/*******************************
 *
 * CS475m Assignment 1 Basecode 
 *
 * Parag Chaudhuri, 2016
 *
 *******************************/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#include "mydraw_class.hpp"

//Window width
int win_width = 512;
//Window height
int win_height = 512;

canvas_t canvas(win_width, win_height, color_t(1.0f, 1.0f, 1.0f));
pen_t pen;

// the modes
int mode = 0;   //0 means point, 1 means line, 2 means triangle

//Display callback
void display( void )
{
  //This clears the colorbuffer (current window)
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(win_width, win_height, GL_RGB, GL_FLOAT, canvas.Pixels());

  //Flush the framebuffer to the screen
  glutSwapBuffers();
}

//Reshape callback
void reshape( int w, int h )
{
  if  ( h == 0 ) h = 1;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  glOrtho( 0.0, (GLdouble)w, 0.0, (GLdouble)h, -1., 1. );
  glViewport( 0, 0, w, h );

  win_width = w;
  win_height = h;

  glutPostRedisplay();
}

//Keyboard callback
void keyboard( unsigned char key, int x, int y ) {
  switch(key) {
  //Exit on pressing escape
  case 27: 
    exit(0);
    break;
  case 'J':
    unsigned int size;
    std::cout << "Enter new pen width: ";
    std::cin >> size;
    pen.set_size(size);
    break;
    //Ignore all other keypresses
  default:
    break;
  }
}

//Mouse callback
void mouse(int button, int state, int x, int y) 
{
   if (state == GLUT_DOWN) 
     {
       if (button == GLUT_LEFT_BUTTON) 
	 {
         point_t point(x, y);
         point.draw(canvas, pen);
	 }
     }
   glutPostRedisplay();
}       


int main (int argc, char *argv[]) 
{

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize( win_width, win_height );

  //Open a GLUT window
  glutCreateWindow( "MyDraw" );

  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutMouseFunc( mouse );
 
  glutMainLoop();
}
