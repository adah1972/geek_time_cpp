#ifndef SHAPE_H
#define SHAPE_H

#include <stdexcept>  // std::logic_error
#include <stdio.h>    // puts

enum class shape_type {
    circle,
    triangle,
    rectangle,
};

class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
    circle() { puts("circle()"); }
    ~circle() { puts("~circle()"); }
};

class triangle : public shape {
public:
    triangle() { puts("triangle()"); }
    ~triangle() { puts("~triangle()"); }
};

class rectangle : public shape {
public:
    rectangle() { puts("rectangle()"); }
    ~rectangle() { puts("~rectangle()"); }
};

inline shape* create_shape(shape_type type)
{
    switch (type) {
    case shape_type::circle:
        return new circle();
    case shape_type::triangle:
        return new triangle();
    case shape_type::rectangle:
        return new rectangle();
    }
    throw std::logic_error("shape type is invalid");
}

#endif // SHAPE_H
