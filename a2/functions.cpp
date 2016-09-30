#include "functions.hpp"

void Seat::drawTop(){
      glBegin(GL_TRIANGLE_STRIP);

      glVertex3f(d,bw,0.0);
      glVertex3f(d,tw,th);
      glVertex3f(d,bw,-bh);
      glVertex3f(d,-tw,th);
      glVertex3f(d,-bw,-bh);
      glVertex3f(d,-bw,0.0);

      glEnd();
    }
void Seat::drawBottom(){
      glBegin(GL_TRIANGLE_STRIP);

      glVertex3f(-d,bw,0.0);
      glVertex3f(-d,tw,th);
      glVertex3f(-d,bw,-bh);
      glVertex3f(-d,-tw,th);
      glVertex3f(-d,-bw,-bh);
      glVertex3f(-d,-bw,0.0);

      glEnd();
    }
void Seat::drawSides(){
      glBegin(GL_TRIANGLE_STRIP);

      glVertex3f(d,bw,0.0);
      glVertex3f(-d,bw,0.0);
      glVertex3f(d,bw,-bh);
      glVertex3f(-d,bw,-bh);
      glVertex3f(d,-bw,-bh);
      glVertex3f(-d,-bw,-bh);
      glVertex3f(d,-bw,0.0);
      glVertex3f(-d,-bw,0.0);
      glVertex3f(d,-tw,th);
      glVertex3f(-d,-tw,th);
      glVertex3f(d,tw,th);
      glVertex3f(-d,tw,th);
      glVertex3f(d,bw,0.0);

      glEnd();
    }
void Seat::draw(){
        glColor3f(1.0,1.0,1.0);

        glPushMatrix();
        drawTop();
        drawBottom();
        drawSides();
        glPopMatrix();
    }


// cylinder drawing
void drawCylinder(double height, double radius, Vec trans, Vec rot, Vec color){
    int numMajor = 100;
    int numMinor = 100;

  double majorStep = height / numMajor;
  double minorStep = 2.0 * M_PI / numMinor;
  int i, j;

  glColor3f(color.x,color.y,color.z);

  glPushMatrix();

  glTranslatef(trans.x, trans.y, trans.z);
  glRotatef(rot.x, 1.0, 0.0, 0.0);
  glRotatef(rot.y, 0.0, 1.0, 0.0);
  glRotatef(rot.z, 0.0, 0.0, 1.0);

  for (i = 0; i < numMajor; ++i) {
      GLfloat z0 = 0.5 * height - i * majorStep;
      GLfloat z1 = z0 - majorStep;

      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= numMinor; ++j) {
          double a = j * minorStep;
          GLfloat x = radius * cos(a);
          GLfloat y = radius * sin(a);
          glVertex3f(x, y, z0);
          glVertex3f(x, y, z1);
      }
      glEnd();
  }
  glPopMatrix();
}

//gear drawing(solid cylinder)
void drawDisk(double height, double radius,double tooth_width, double tooth_height, Vec trans, Vec rot, Vec color){
    int numMajor = 100;
    int numMinor = 100;

  double majorStep = height / numMajor;
  double minorStep = 2.0 * M_PI / numMinor;
  int i, j;

  glColor3f(color.x,color.y,color.z);

  glPushMatrix();

  glTranslatef(trans.x, trans.y, trans.z);
  glRotatef(rot.x, 1.0, 0.0, 0.0);
  glRotatef(rot.y, 0.0, 1.0, 0.0);
  glRotatef(rot.z, 0.0, 0.0, 1.0);

  for (i = 0; i < numMajor; ++i) {
      GLfloat z0 = 0.5 * height - i * majorStep;
      GLfloat z1 = z0 - majorStep;

      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= numMinor; ++j) {
          double a = j * minorStep;
          GLfloat x = radius * cos(a);
          GLfloat y = radius * sin(a);
          glVertex3f(x, y, z0);
          glVertex3f(x, y, z1);
      }
      glEnd();
  }
      for (j=0; j<= numMinor; ++j) {
          double a = j * minorStep ;
          double next_a = ( j + 1 ) * minorStep;
          glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(0,0,height/2);
          glVertex3f(radius*cos(a),radius*sin(a),height/2);
          glVertex3f(radius*cos(next_a),radius*sin(next_a),height/2);
          glEnd();
          glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(0,0,-height/2);
          glVertex3f(radius*cos(a),radius*sin(a),-height/2);
          glVertex3f(radius*cos(a),radius*sin(a),-height/2);
     }
     for (j=0; j<=15; ++j){
          double a = j * 2.0 * M_PI / 15;
          double b = tooth_width / radius;
          glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(radius*cos(a-b),radius*sin(a-b),height/2);
          glVertex3f(radius*cos(a+b),radius*sin(a+b),height/2);
          glVertex3f((radius+tooth_height)*cos(a),(radius+tooth_height)*sin(a),0);
          glVertex3f(radius*cos(a+b),radius*sin(a+b),-height/2);
          glVertex3f(radius*cos(a-b),radius*sin(a-b),-height/2);
          glVertex3f((radius+tooth_height)*cos(a),(radius+tooth_height)*sin(a),0);
          glVertex3f(radius*cos(a-b),radius*sin(a-b),height/2);
          glEnd();
  }
  glPopMatrix();
}

//torus drawing
void drawTorus(double width, double radius, Vec trans, Vec rot, Vec color, double total=2.0*M_PI){
  int num = 100;

  double Step = total / num;
  double smallStep = 2.0*M_PI / num;
  int i, j;

  glColor3f(color.x,color.y,color.z); 

  glPushMatrix();

  glTranslatef(trans.x, trans.y, trans.z);
  glRotatef(rot.x, 1.0, 0.0, 0.0);
  glRotatef(rot.y, 0.0, 1.0, 0.0);
  glRotatef(rot.z, 0.0, 0.0, 1.0);

  for (i = 0; i < num; ++i) {
        double theta = i*Step;

      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= num; ++j) {
          double phi = j * smallStep;
          glVertex3f((radius-width*sin(phi))*cos(theta),(radius-width*sin(phi))*sin(theta), width*cos(phi));
          glVertex3f((radius-width*sin(phi))*cos(theta+Step),(radius-width*sin(phi))*sin(theta+Step), width*cos(phi)); 
      } 
      glEnd();
  }
  glPopMatrix();
}

//drawing wheel
void drawWheel(){
  drawTorus(0.08,1.875, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.1,0.1,0.1));
  drawTorus(0.075,1.7, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.7,0.7,0.7));
  drawCylinder(0.28, 0.1, Vec(0.0,0.0,0.0), Vec(0.0, 90.0, 0.0), Vec(0.7,0.0,0.0));
  //Back gear disk
  drawDisk(0.05, 0.3,0.06,0.1, Vec(0.08,0.0,0.0), Vec(0.0, 90.0, 0.0), Vec(1,1,1));
  
  for(int x=0;x<10;x++){
    glPushMatrix();
    glRotatef(36*x,1.0,0.0,0.0);
    drawCylinder(1.65, 0.02, Vec(0.02,0.825,0.0), Vec(90.0,5.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();
    glPushMatrix();
    glRotatef(36*x+18,1.0,0.0,0.0);
    drawCylinder(1.65, 0.02, Vec(-0.02,0.825,0.0), Vec(90.0, -5.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();	
  }	
}

void drawFrontWheel(){
  drawTorus(0.2,1.18, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.1,0.1,0.1));
  drawTorus(0.17,1.1, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.7,0.7,0.7));
  drawCylinder(0.64, 0.15, Vec(0.0,0.0,0.0), Vec(0.0, 90.0, 0.0), Vec(0.7,0.0,0.0));
  for(int x=0;x<10;x++){
    glPushMatrix();
    glRotatef(36*x,1.0,0.0,0.0);
    drawCylinder(1.05, 0.02, Vec(0.15,0.625,0.0), Vec(90.0,9.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();
    glPushMatrix();
    glRotatef(36*x+18,1.0,0.0,0.0);
    drawCylinder(1.05, 0.02, Vec(-0.15,0.625,0.0), Vec(90.0, -9.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();	
  }	
}

void drawFrame(){
  //big rod
  drawCylinder(3.2, 0.2, Vec(0.0, 0.5, 0.0), Vec(-15.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  //middle top rod
  drawCylinder(4.5, 0.15, Vec(0.0, -1.9, -0.3), Vec(60.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  //middle bottom rod
  drawCylinder(4.5, 0.15, Vec(0.0,-1.55, 1.15) , Vec(85.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  //front rod
  drawCylinder(1.7, 0.2, Vec(0.0, -3.95, 1.0), Vec(-17.0, 0.0, 0.0),Vec(0.0,0.1,0.85));

  //back top rods
  drawCylinder(1.1, 0.11, Vec(-0.15,1.2,1.1) , Vec(50.0, 15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(1.1, 0.11, Vec(0.15,1.2,1.1) , Vec(50.0, -15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.7, 0.11, Vec(-0.25,2.95,-0.35), Vec(50.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.7, 0.11, Vec(0.25,2.95,-0.35), Vec(50.0, 0.0, 0.0),Vec(0.0,0.1,0.85));

  //back bottom rods
  drawCylinder(1.1, 0.11, Vec(-0.15,0.65,-1.5) , Vec(90.0, 15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(1.1, 0.11, Vec(0.15,0.65,-1.5) , Vec(90.0, -15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.3, 0.11, Vec(0.25, 2.75, -1.5), Vec(90.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.3, 0.11, Vec(-0.25, 2.75, -1.5), Vec(90.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
}

void drawSeat(){
  Seat seat(0.66,1.5,0.25,0.75,0.15);
  seat.draw();
  glPushMatrix();
  glRotatef(-75,0.0,1.0,0.0);
  glTranslatef(-0.5,0.0,.7);
  drawCylinder(1.5,0.18,Vec(0.0,0.0,0.0),Vec(0.0,0.0,0.0),Vec(0.0,0.85,0.1));
  glPopMatrix();
}

void drawHandle(double phi){
    glPushMatrix();
    drawCylinder(3.0,0.18, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.5,0.2,0.7));
        glPushMatrix();
        glTranslatef(0.0,0.0,-1.5);
        drawTorus(0.18,0.5, Vec(0.0,0.0, -0.5), Vec(90.0,0,0.0), Vec(0.7,0.0,0.0),M_PI);
            glPushMatrix();
            drawCylinder(1.3, 0.175, Vec(0.5,0.00,-1.15), Vec(0.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
            drawCylinder(1.3, 0.175, Vec(-0.5,0.00,-1.15), Vec(0.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
                glPushMatrix();
                glTranslatef(0.0,0.0,-1.65);
                glRotatef(phi,1.0,0.0,0.0);
                drawFrontWheel();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        //drawing hand handle
        glPushMatrix();
            glTranslatef(0.0,0.5,1.5); 
            glRotatef(90,0.0,1.0,0.0);
            glRotatef(180.0,0.0,0.0,1.0);
            glPushMatrix();
            drawTorus(0.18,0.5, Vec(0.0,0.0, 0.0), Vec(00.0,0,0.0), Vec(0.7,0.0,0.0),M_PI/2);
            drawCylinder(0.8,0.18, Vec(0.5,-0.4,0.0), Vec(90.0,0.0,0.0), Vec(0.5,0.2,0.7));
            //draw hand hand handle
                glPushMatrix();
                    glTranslatef(0.5,-0.8,0.0);
                    glRotatef(90,0.0,0.0,1.0);
                    drawCylinder(3.6,0.18, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.7,0.0,0.7));
                    drawCylinder(0.8,0.20, Vec(0.0,0.0,1.4), Vec(0.0,0.0,0.0), Vec(0.7,0.7,0.7));
                    drawCylinder(0.8,0.20, Vec(0.0,0.0,-1.4), Vec(0.0,0.0,0.0), Vec(0.7,0.7,0.7));
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void drawBox(double a, double b, double c, Vec color)
{
    glColor3f(color.x, color.y, color.z);

    glBegin(GL_TRIANGLE_STRIP);

        glVertex3f(a,b,c);
        glVertex3f(a,b,-c);
        glVertex3f(a,-b,c);
        glVertex3f(a,-b,-c);
        glVertex3f(-a,-b,c);
        glVertex3f(-a,-b,-c);
        glVertex3f(-a,b,-c);
        glVertex3f(-a,b,c);

    glEnd();
    glBegin(GL_TRIANGLE_STRIP);

        glVertex3f(a,-b,c);
        glVertex3f(-a,-b,c);
        glVertex3f(a,b,c);
        glVertex3f(-a,b,c);
        glVertex3f(a,b,-c);
        glVertex3f(-a,b,-c);
        glVertex3f(-a,-b,-c);
        glVertex3f(a,-b,-c);

    glEnd();
}

void drawPedals(double phi2){
        //front gear disk
	glPushMatrix();
        drawDisk(0.1, 0.5,0.07,0.1, Vec(0.0,0.0,0.21), Vec(0.0, 0.0, 0.0), Vec(1,1,1));
	glPopMatrix();

    drawCylinder(1.6,0.18, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.0,0.1,0.7));
       
        //pedal rods
        glPushMatrix();
        glTranslatef(0.0,0.0,-0.8);
        glRotatef(60,0.0,1.0,0.0);
        glTranslatef(0.0,0.0,-0.4);
        drawCylinder(1.0,0.13, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.7,0.0,0.1));
            //pedal shafts
            glPushMatrix();
            glTranslatef(0.0,0.0,-0.5);
            glRotatef(-60,0.0,1.0,0.0);
            glTranslatef(0.0,0.0,-0.3);
            glRotatef(-phi2,0.0,0.0,1.0);
            drawBox(0.1,0.25,0.45,Vec(1.0,1.0,1.0));
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0,0.0,0.8);
        glRotatef(60,0.0,1.0,0.0);
        glTranslatef(0.0,0.0,0.4);
        drawCylinder(1.0,0.13, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.7,0.0,0.1));
            //pedal shafts
            glPushMatrix();
            glTranslatef(0.0,0.0,0.5);
            glRotatef(-60,0.0,1.0,0.0);
            glTranslatef(0.0,0.0,0.3);
            glRotatef(-phi2,0.0,0.0,1.0);
            drawBox(0.1,0.25,0.45,Vec(1.0,1.0,1.0));
            glPopMatrix();
        glPopMatrix();
}
