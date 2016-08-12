#include "mydraw_class.hpp"

//-------------------
//color_t methods

color_t::color_t():r(0.0),g(0.0),b(0.0) { }

color_t::color_t(const float _r, const float _g, const float _b)
		 :r(_r),g(_g),b(_b) { }

void color_t::set(const float _r, const float _g, const float _b)
{ 
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

void fill_t::set_fc(const color_t _fc){
    fc = _fc;
}

void fill_t::draw(point_t seed){
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

void point_t::draw(void){
    //TODO:Implement the draw point
}

//---------------------
//canvas_t methods

canvas_t::canvas_t():w(512),h(512),bg(color_t()) {
    int size = w*h;
    pixels = new float[size*3];
    clear();
}

canvas_t::canvas_t(const int _w, const int _h, const color_t _bg)
		 :w(_w),h(_h),bg(_bg) { 
    int size = w*h;
    pixels = new float[size*3];
    clear();
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

//---------------------
