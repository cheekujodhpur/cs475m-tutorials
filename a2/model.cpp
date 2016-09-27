#include <math.h>
#include<iostream>
#include "functions.hpp"

using namespace std;

//for debugging
Vec supremo(0.0,0.0,0.0);
Vec eye(9.0 ,0.0, 0.0);
Vec up(0.0, 0.0, 1.0);

//back wheel angle parameter
double theta = 0;
//front wheel angle parameter
double phi = 0;
//front handle angle parameter
double theta2 = 0;
//pedal angle paramter
double phi2 = 30;

//seat paramter
double seat_height = 2.35;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  gluLookAt(eye.x, eye.y, eye.z,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  up.x, up.y, up.z);      // up is in positive Y direction

  //start drawing frame 
  glPushMatrix();
  drawFrame();
    // draw back wheel
    glPushMatrix();
    glTranslatef(0,4.25,-1.5);
    glRotatef(theta,1.0,0.0,0.0);
    drawWheel();
    glPopMatrix();

    // draw seat
    glPushMatrix();
    glRotatef(90,1.0,0.0,0.0);
    glRotatef(90,0.0,0.0,1.0);

    glRotatef(15,0.0,1.0,0.0);
    glTranslatef(seat_height,0.0,0.0);
    glRotatef(-15,0.0,1.0,0.0);

    drawSeat();
    glPopMatrix();

    //draw handle
    glPushMatrix();
    glTranslatef(0.0,-3.9,1.15);
    glRotatef(-17.0, 1.0, 0.0, 0.0);
    glRotatef(theta2, 0.0, 0.0, 1.0);
    drawHandle(phi);
    glPopMatrix();

    //draw pedals
    glPushMatrix();
    glTranslatef(0.0,0.15,-1.30);
    glRotatef(90,0.0,1.0,0.0);
    glRotatef(phi2,0.0,0.0,1.0);
    drawPedals(phi2);
    glPopMatrix();
    
    //draw chain
    glPushMatrix();
    glRotatef(90,1.0,0.0,0.0);
    drawCylinder(4.114,0.03, Vec(0.148,-0.94,-2.2), Vec(-6,2.165,27.324), Vec(0.1,0.9,0.1));
    drawCylinder(4.114,0.03, Vec(0.148,-1.85,-2.2), Vec(1,2.165,-27.324), Vec(0.1,0.9,0.1));
    glPopMatrix();

  glutSwapBuffers();
}

//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 'w':
      supremo.z += 0.05;
      break;
    case 's':
      supremo.z -= 0.05;
      break;
    case 'a':
      supremo.y -= 0.05;
      break;
    case 'd':
      supremo.y += 0.05;
      break;
    case 'q':
      supremo.x += 0.05;
      break;
    case 'e':
      supremo.x -= 0.05;
      break;
    case 'p':
    cout << supremo.x << " " << supremo.y << " " << supremo.z << endl; 
    break;
    case 'v':
    if(eye.x==0){
        eye.x = 9.0;
        eye.y = 0.0;
	    eye.z = 0.0;
        up.x = 0.0;
	    up.y = 0.0;
        up.z = 1.0;
    }
    else if(eye.x==9.0){
        eye.x = 0.0;
        eye.z = 9.0;
        up.x = -1.0;
        up.z = 0.0;
    }
    break;
    case 'k':
    if(eye.x==0){
	eye.x = 9.0;
	eye.z = 0.0;
	eye.y = 0.0;	
	up.x = 0.0;
	up.y = 0.0;
	up.z = 1.0;
    }
    else if(eye.x=9.0){
	eye.y = -9.0;
	eye.x = 0.0;
    }  
    break;

    //seat height
    case 'h':
        if(seat_height>2.05)
            seat_height-=0.05;
        break;
    case 'H':
        if(seat_height<2.95)
            seat_height+=0.05;
        break;

    //pedal angle
    case 'x':
        phi2 -= 2.5;
        break;
    case 'X':
        phi2 += 2.5;
        break;
  }
  if (key == 27)
  exit(0);

  glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
      case GLUT_KEY_UP:
          theta += 0.5;
          break;
      case GLUT_KEY_DOWN:
          theta -= 0.5;
          break;
      case GLUT_KEY_LEFT:
          phi -= 0.5;
          break;
      case GLUT_KEY_RIGHT:
          phi += 0.5;
          break;
      case GLUT_KEY_PAGE_UP:
          theta2 += 0.5;
          break;
      case GLUT_KEY_PAGE_DOWN:
          theta2 -= 0.5;
          break;
  }
  //Redraw
  glutPostRedisplay();
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(9.0, 0.0, 0.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 0.0, 1.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700,700);
  glutCreateWindow("Assignment 2");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}
