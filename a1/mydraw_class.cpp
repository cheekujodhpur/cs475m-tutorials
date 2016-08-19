#include "mydraw_class.hpp"
#include <stack>

//-------------------
//color_t methods

color_t::color_t():r(0.0),g(0.0),b(0.0) { }

color_t::color_t(const float _r, const float _g, const float _b)
		 :r(_r),g(_g),b(_b) { }
void color_t::set(const float _r, const float _g, const float _b) { 
  r=_r; g=_g; b=_b;
}

float color_t::R(void) { return r; }
float color_t::G(void) { return g; }
float color_t::B(void) { return b; }

//---------------------

//-------------------
//pen_t methods

pen_t::pen_t():size(1),c(color_t()),mode(true) { }

pen_t::pen_t(const unsigned int _size, 
             const color_t _c, 
             const bool _mode)
		 :size(_size),c(_c),mode(_mode) { }

void pen_t::set_size(const unsigned int _size){
    size = _size;
}
void pen_t::set_color(const color_t _c){
    c = _c;
}
void pen_t::set_mode(const bool _mode){
    mode = _mode;
}

unsigned int pen_t::Size(void) { return size; }
color_t pen_t::Color(void) { return c; }
bool pen_t::Mode(void) { return mode; }


//---------------------

//-------------------
//fill_t methods

fill_t::fill_t():fc(color_t()) { }

fill_t::fill_t(const color_t _fc)
		 :fc(_fc) { }

void fill_t::set_fc(color_t _fc){
    fc = _fc;
}

void fill_t::draw(canvas_t &canvas, color_t &bg, point_t seed){

  std::stack<point_t> to_color;
  to_color.push(seed);
  while(!to_color.empty()){
      point_t pt = to_color.top();
      int x = pt.X(), y = pt.Y();
      canvas.set_pixel(x, y, fc);
      to_color.pop(); // now remove

      if(canvas.match_pixel(x-1,y,bg)){
          to_color.push(point_t(x-1,y));
      }
      if(canvas.match_pixel(x+1,y,bg)){
          to_color.push(point_t(x+1,y));
      }
      if(canvas.match_pixel(x,y-1,bg)){
          to_color.push(point_t(x,y-1));
      }
      if(canvas.match_pixel(x,y+1,bg)){
          to_color.push(point_t(x,y+1));
      }
  }
}

//---------------------

//-------------------
//point_t methods

point_t::point_t():x(0),y(0) { }

point_t::point_t(const int _x, const int _y)
		 :x(_x),y(_y) { }

void point_t::set_x(int _x){
    x = _x;
}
void point_t::set_y(int _y){
    y = _y;
}

int point_t::X(void){return x;}
int point_t::Y(void){return y;}

void point_t::draw(canvas_t &canvas, pen_t pen){
    float *pixels = canvas.Pixels();
    int w = canvas.W(), h = canvas.H();     // to know the maximum extent

    color_t c;
    // pen Mode
    if(pen.Mode())
        c = pen.Color();
    else
        c = canvas.BG();

    unsigned int size = pen.Size();
    if(size%2){
        size = size/2;
        for(int i = x-size; i<=x+size; i++){
            for(int j = y-size; j<=y+size; j++){
                canvas.set_pixel(i, j, c);
            }
        }
    }
    else{
        size = size/2;
        for(int i = x-size; i<x+size; i++){
            for(int j = y-size; j<y+size; j++){
                canvas.set_pixel(i, j, c);
            }
        }
    }
}

//---------------------
//canvas_t methods

canvas_t::canvas_t():w(512),h(512),bg(color_t(1.0f,1.0f,1.0f)) {
    int size = w*h;
    pixels = new float[size*3];
    clear();
    drawing = new drawing_t(*this);
}

canvas_t::canvas_t(const int _w, const int _h, const color_t _bg)
		 :w(_w),h(_h),bg(_bg) { int size = w*h; pixels = new float[size*3];
    clear();
    drawing = new drawing_t(*this);
}

void canvas_t::set_bg(color_t _bg){
    bg = _bg;
}

void canvas_t::clear(void){
    int size = w*h;
    for(int i = 0;i < size;i++){
        *((color_t*)&pixels[i*3]) = bg; //clear with background color
    } 
}

float* canvas_t::Pixels(void){return pixels;}
int canvas_t::W(void){return w;}
int canvas_t::H(void){return h;}
color_t canvas_t::BG(void){return bg;}

int canvas_t::set_pixel(int x, int y, color_t c){
    int gl_x = x, gl_y = h-y;
    if(gl_x>=0 && gl_x<w && gl_y>=0 && gl_y<h){
        *((color_t*)&pixels[3*(w*gl_y+gl_x)]) = c;
        return 1;
    }
    else
        return 0;
}
color_t canvas_t::get_pixel(int x, int y){
    int gl_x = x, gl_y = h-y;
    if(gl_x>=0 && gl_x<w && gl_y>=0 && gl_y<h)       
        return *((color_t*)&pixels[3*(w*gl_y+gl_x)]);
    else
        return color_t(0.0f,0.0f,0.0f);
}

bool canvas_t::match_pixel(int x, int y, color_t &c){
    int gl_x = x, gl_y = h-y;
    if(gl_x>=0 && gl_x<w && gl_y>=0 && gl_y<h){
        color_t pc = *((color_t*)&pixels[3*(w*gl_y+gl_x)]);

        if(pc.R()==c.R() && pc.G() == c.G() && pc.B() == c.B())
            return true;
        else return false;
    }
    else
        return false;
}

//---------------------
//-------------------
//line_t methods
line_t::line_t(){
    start = point_t();
    end = point_t();
}

line_t::line_t(const point_t _start, const point_t _end){
	start = _start;
	end = _end;
}

void line_t::set_start(point_t _start){
	start = _start;
}

void line_t::set_end(point_t _end){
    start = _end;
}

point_t line_t::Start(void){return start;}
point_t line_t::End(void){return end;}

void line_t::draw(canvas_t &canvas, pen_t pen){
	int x0 = start.X();
	int y0 = start.Y();
	int x1 = end.X();
	int y1 = end.Y();
 	bool steep;
	float abs = (float(y1-y0)/float(x1-x0));
	if ( abs>1 || abs<(-1) )
		steep = true;
	else 
		steep = false;
  	if (steep)
    {
      	int temp = x0; 
		x0=y0;
		y0=temp;
        temp = x1; 
        x1=y1;
        y1=temp;
    }
  	if (x0 > x1)
    {
   		int temp = x0; 
        x0=x1;
        x1=temp;
        temp = y0;     
        y0=y1;
        y1=temp;
    }
  	int deltax = x1 - x0;
  	int deltay;
	if ((y1 - y0)>0)
		deltay = y1 - y0 ;
	else
		deltay = y0 - y1;

  	float error = 0.0;
  	float deltaerr = (float)deltay / (float)deltax;

  	int ystep;
  	int y = y0;
	if (y0 < y1) ystep = 1; else ystep = -1;

  	for (int x=x0; x < x1; x++)
    {
      	if (steep)
          point_t(y,x).draw(canvas, pen);
      	else
          point_t(x,y).draw(canvas, pen);

      	error = error + deltaerr;
      	if (error >= 0.5)
        {
          y = y + ystep;
          error = error - 1.0;
        }
    }

}
//---------------------
//-------------------
//triangle_t methods

triangle_t::triangle_t():x1(point_t()),x2(point_t()),x3(point_t()){}

triangle_t::triangle_t(const point_t _x1,
                    const point_t _x2,
                    const point_t _x3){
    x1 = _x1;
    x2 = _x2;
    x3 = _x3;
}

void triangle_t::draw(canvas_t &canvas, pen_t pen){
    line_t(x1,x2).draw(canvas, pen);
    line_t(x2,x3).draw(canvas, pen);
    line_t(x3,x1).draw(canvas, pen);
}


//---------------------
//-------------------
//drawing_t methods

drawing_t::drawing_t(){}

drawing_t::drawing_t(canvas_t &_canvas){
    canvas = &_canvas;
}

void drawing_t::attachCanvas(canvas_t &_canvas){
    canvas = &_canvas;
}

void drawing_t::draw_point(point_t point){
}
void drawing_t::draw_line(line_t line){
}
void drawing_t::draw_triangle(triangle_t triangle){
}

//---------------------
