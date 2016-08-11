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
