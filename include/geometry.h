#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>
#include <memory>

struct Vector2 {
    int x, y;
    Vector2(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Light {
    int id;
    double intensity;
    Vector2 pos;
};

struct Point {
    int id;
    Vector2 pos;
};

class Obstacle {
public:
    int id;
    int reduction; // em porcentagem (ex: 50 = 50%)
    virtual int countIntersections(const Vector2& a, const Vector2& b) const = 0;
    virtual bool isInside(const Vector2& p) const = 0;
    virtual ~Obstacle() = default;
};

class Rectangle : public Obstacle {
public:
    Vector2 origin;
    int width, height;
    Rectangle(int id, int reduction, int x, int y, int width, int height);
    int countIntersections(const Vector2& a, const Vector2& b) const override;
    bool isInside(const Vector2& p) const override;
};

class Circle : public Obstacle {
public:
    Vector2 center;
    int radius;
    Circle(int id, int reduction, int x, int y, int r);
    int countIntersections(const Vector2& a, const Vector2& b) const override;
    bool isInside(const Vector2& p) const override;
};

class Line : public Obstacle {
public:
    Vector2 p1, p2;
    Line(int id, int reduction, int x1, int y1, int x2, int y2);
    int countIntersections(const Vector2& a, const Vector2& b) const override;
    bool isInside(const Vector2& p) const override;
};


#endif
