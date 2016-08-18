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
#include <vector>
#include <GL/glut.h>

#include "mydraw_class.hpp"

//Window width
int win_width = 512;
//Window height
int win_height = 512;
float r,g,b;
canvas_t canvas(win_width, win_height, color_t(1.0f, 1.0f, 1.0f));
pen_t pen;
color_t bg_color;
// the modes
int mode = 0;   //0 means point, 1 means line, 2 means triangle
std::vector<point_t> lpoints;
int lpcount = 0;

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
  case 'H':
    std::cout << "Enter pen color (r,g,b): ";
    std::cin >> r >> g >> b;
    pen.set_color(color_t(r, g, b));
	break;
  case 'I':
    std::cout << "Enter background color (r,g,b): ";
    std::cin >> r >> g >> b;
    bg_color.set(r,g,b);
    canvas.set_bg(bg_color);
    break;
  case 'C':
    canvas.clear();
  	glutPostRedisplay();
    break;
    //Ignore all other keypresses
  case '1':
    lpoints.clear();
    lpcount = 0;
    if(mode==1){
        mode = 0;
    }
    else mode = 1;
    break;
  case '2':
    lpoints.clear();
    lpcount = 0;
    if(mode==2){
        mode = 0;
    }
    else mode = 2;
    break;
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
         // Simple point drawing
         if(mode==0){
             point.draw(canvas, pen);
         }
         // Line drawing
         else if(mode == 1){
             lpcount++;
             lpoints.push_back(point);

             if(lpcount == 2){
                 line_t line(lpoints.end()[-2], lpoints.end()[-1]);
                 line.draw(canvas, pen);
                 lpcount--;
             }
         }
         else if(mode == 2){
             lpcount++;
             lpoints.push_back(point);

             if(lpcount == 3){
                 line_t line1(lpoints.end()[-3], lpoints.end()[-2]);
                 line_t line2(lpoints.end()[-2], lpoints.end()[-1]);
                 line_t line3(lpoints.end()[-1], lpoints.end()[-3]);
                 line1.draw(canvas, pen);
                 line2.draw(canvas, pen);
                 line3.draw(canvas, pen);
                 lpcount--;
             }
         }
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
