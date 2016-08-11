#ifndef _MYDRAW_CLASS_HPP_
#define _MYDRAW_CLASS_HPP_

//Define all classes like the color class, adding appropriate methods and data members. 
//Implementation of the methods go into the corresponding cpp file

//------------------------
//color_t class

class color_t {
private:
  float r,g,b;
public:
  color_t();
  color_t(const float _r, const float _g, const float _b);

  void set(const float _r, const float _g, const float _b);
  float R(void);
  float G(void);
  float B(void);
};

//------------------------

//pen_t class

class pen_t {
private:
  unsigned int size;
  color_t c;
  bool mode;    //false means eraser mode, true means draw mode
public:
  pen_t();
  pen_t(const unsigned int _size, 
        const color_t _c, 
        const bool mode = true);

  void set_size(const unsigned int _size);
  void set_color(const color_t _c);
  void set_mode(const bool _mode);
  unsigned int Size(void);
  color_t Color(void);
  bool Mode(void);
};

//------------------------

//point_t class
class point_t {

};

//------------------------

#endif
