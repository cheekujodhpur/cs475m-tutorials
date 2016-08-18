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
//canvas_t class

class canvas_t {
private:
  int w;    //width
  int h;    //height
  color_t bg;   //background color
  float *pixels;   //storing the pixels
public:
  canvas_t();
  canvas_t(const int w, const int h, const color_t _bg);

  void set_bg(color_t _bg);
  void clear();

  float* Pixels(void);
  int W(void);
  int H(void);
  color_t BG(void);

  int set_pixel(int x, int y, color_t c);
  color_t get_pixel(int x, int y);
  bool match_pixel(int x, int y, color_t c);
};

//------------------------

//point_t class
class point_t {
private:
  int x, y;
public:
  point_t();
  point_t(const int _x, const int _y); 

  void set_x(int _x);
  void set_y(int _y);

  int X(void);
  int Y(void);

  void draw(canvas_t &canvas, pen_t pen);
};

//------------------------

//fill_t class

class fill_t {
private:
  color_t fc;
public:
  fill_t();
  fill_t(const color_t _fc);

  void set_fc(color_t _fc);
  void draw(canvas_t &canvas, color_t &bg, point_t seed);
};

//------------------------

//line_t class

class line_t {
private:
  point_t start, end;
public:
  line_t();
  line_t(const point_t _start, const point_t _end);

  void set_start(point_t _start);
  void set_end(point_t _end);

  point_t Start(void);
  point_t End(void);

  void draw(canvas_t &canvas, pen_t pen);  
};

//------------------------
//triangle_t class

class triangle_t {
private:
  point_t x1, x2, x3;
public:
  triangle_t();
  triangle_t(const point_t x_1,
            const point_t x_2,
            const point_t x_3);

  void draw(canvas_t &canvas, pen_t pen);
};

//------------------------

//drawing_t class

class drawing_t {
private:
  ;
public:
  drawing_t();

  void draw_point(point_t point);
  void draw_line(line_t line);
  void draw_triangle(triangle_t triangle);
};

//------------------------

#endif
