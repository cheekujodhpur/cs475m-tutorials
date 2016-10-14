#include <GL/glut.h>
#include <math.h>

struct Vec {
  double x, y, z; Vec(double x_=0, double y_=0, double z_=0){ x=x_; y=y_; z=z_; } Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); }
  Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); }
  Vec operator*(double b) const { return Vec(x*b,y*b,z*b); } Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); }
  Vec& norm(){ return *this = *this * (1/sqrt(x*x+y*y+z*z)); }
  double dot(const Vec &b) const { return x*b.x+y*b.y+z*b.z; } // cross:
  Vec operator%(Vec&b){return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}
};

void drawCylinder(double height, double radius, Vec trans, Vec rot, Vec color);
void drawTorus(double width, double radius, Vec trans, Vec rot, Vec color,double total);
void drawTorusTexture(double width, double radius, Vec trans, Vec rot, Vec color,GLuint texture, double total);

struct Seat{
    double th, bh; //top height, bottom height
    double tw, bw; //top width, bottom width
    double d; //thickness
    Seat(double th_, double bh_, double tw_, double bw_, double d_):th(th_),bh(bh_),tw(tw_),bw(bw_),d(d_){}
    void drawTop();
    void drawBottom();
    void drawSides();
    void draw();
};

void drawWheel(GLuint texture);
void drawFrontWheel(GLuint texture);
void drawFrame();
void drawSeat();
void drawHandle(double phi,GLuint texture);
void drawBox(double a, double b, double c, Vec color);
void drawPedals(double phi2);
void drawDisk(double height, double radius,double tooth_width, double tooth_height, Vec trans, Vec rot, Vec color);
void drawRoom(GLuint texture,GLuint texture1,GLuint texture2, GLuint texture3);

GLuint LoadTexture(const char* filename, int &width, int &height);
