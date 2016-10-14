#include <math.h>
#include<iostream>
#include "functions.hpp"

using namespace std;

// Texture numbers
GLuint woodenTexture;
GLuint wheelTexture;
GLuint wallTexture;
GLuint roofTexture;
GLuint paintTexture;

//for debugging
Vec supremo(0.0,0.0,0.0);
Vec eye(9.0 ,0.0, 0.0);
Vec up(0.0, 0.0, 1.0);

//back wheel angle parameter
//double theta = 0;
//front wheel angle parameter
//double phi = 0;
//front handle angle parameter
double theta2 = 0;
//pedal angle paramter
double phi2 = 30;

double ln_axle = 9.05;
double ds_front = 4.8;

inline double theta(double x){
    return 1.5*x;
}
inline double bw(double x){
    return 1.915*theta(x)*(M_PI/180.0);
}
inline double fw(double x){
    return ((bw(x)-ln_axle)*cos(theta2*(M_PI/180.0)) + sqrt(ln_axle*ln_axle + bw(x)*(2*ln_axle-bw(x))*sin(theta2*(M_PI/180.0))*sin(theta2*(M_PI/180.0))));
}
inline double phi(double x){
    return fw(x)/1.28;
}
inline double fcrot(double x){
    asin(fw(x)*cos(theta2*(M_PI/180.0))/ln_axle);
}
inline double fctrax(double x){
    return fw(x)*cos(theta2*(M_PI/180.0)) - ds_front*sin(fcrot(x));
}
inline double fctray(double x){
    return bw(x);
}

//seat paramter
double seat_height = 2.35;

void drawCycle(){
  float colorBlue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
  //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBlue);

  drawFrame();
    // draw back wheel
    glPushMatrix();
    glTranslatef(0,4.25,-1.5);
    glRotatef(theta(phi2),1.0,0.0,0.0);
    drawWheel(wheelTexture);
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
    drawHandle(phi(phi2),wheelTexture);
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

}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  gluLookAt(eye.x, eye.y, eye.z,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  up.x, up.y, up.z);      // up is in positive Y direction

  //draw the room
  float colorWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorWhite);

  glPushMatrix();
    glTranslatef(0.0, 0.0, 1.55);
    drawRoom(woodenTexture, wallTexture,roofTexture,paintTexture);
  glPopMatrix();

  //draw the cycle
  glPushMatrix();
    glTranslatef(fctrax(phi2),fctray(phi2),0);
    glRotatef(fcrot(phi2)*(180/M_PI),0.0,0.0,1.0);
    //drawCycle();
  glPopMatrix();

  glutSwapBuffers();
}

bool roomLights = true;

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

    //light
    case 'L':
       if(roomLights){
           glDisable(GL_LIGHT1);
           roomLights = !roomLights; 
       }
       else{
           glEnable(GL_LIGHT1);
           roomLights = !roomLights;
       }
       break;
  }
  if (key == 27)
  exit(0);

  glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
      case GLUT_KEY_UP:
 //         theta += 0.5;
          break;
      case GLUT_KEY_DOWN:
 //         theta -= 0.5;
          break;
      case GLUT_KEY_LEFT:
 //         phi -= 0.5;
          break;
      case GLUT_KEY_RIGHT:
 //         phi += 0.5;
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
  glEnable(GL_LIGHTING);

  //LIGHT0
  //glEnable(GL_LIGHT0);
   
  //Create light components
  GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
  GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };
   
   // Assign created components to GL_LIGHT0
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   //LIGHT1
  glEnable(GL_LIGHT1);
   
  //Create light components
  GLfloat specularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat position1[] = { -9.97f, 0.0f, 7.225f, 1.0f };
   
   // Assign created components to GL_LIGHT0
   glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
   glLightfv(GL_LIGHT1, GL_POSITION, position1);

   //load all textures
   int texw,texh;
   woodenTexture = LoadTexture("wooden.bmp", texw, texh);
   wheelTexture = LoadTexture("wheel.bmp", texw, texh);
   wallTexture = LoadTexture("wall.bmp", texw, texh);
   roofTexture = LoadTexture("roof.bmp", texw, texh);
   paintTexture = LoadTexture("painting.bmp", texw, texh);

  init();
  glutMainLoop();
  return 0;
}
