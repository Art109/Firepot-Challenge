#include "../include/geometry.h"
#include <cmath>
#include <vector>
#include <algorithm>

// ---------- Função utilitária ----------
static double cross(const Vector2& A, const Vector2& B, const Vector2& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

static bool segmentsIntersect(const Vector2& A, const Vector2& B,
                              const Vector2& C, const Vector2& D) {
    double d1 = cross(A, B, C);
    double d2 = cross(A, B, D);
    double d3 = cross(C, D, A);
    double d4 = cross(C, D, B);

    const double EPS = 1e-9;

    if ((d1 * d2) < -EPS && (d3 * d4) < -EPS)
        return true;

    auto onSegment = [&](const Vector2& P, const Vector2& Q, const Vector2& R) {
        return (std::min(P.x, R.x) - EPS <= Q.x && Q.x <= std::max(P.x, R.x) + EPS &&
                std::min(P.y, R.y) - EPS <= Q.y && Q.y <= std::max(P.y, R.y) + EPS);
    };

    if (std::fabs(d1) < EPS && onSegment(A, C, B)) return true;
    if (std::fabs(d2) < EPS && onSegment(A, D, B)) return true;
    if (std::fabs(d3) < EPS && onSegment(C, A, D)) return true;
    if (std::fabs(d4) < EPS && onSegment(C, B, D)) return true;

    return false;
}

// ---------- RECTANGLE ----------
Rectangle::Rectangle(int id, int reduction, int x, int y, int width, int height) {
    this->id = id;
    this->reduction = reduction;
    this->origin = {x, y};
    this->width = width;
    this->height = height;
}

bool Rectangle::isInside(const Vector2& p) const {
    return (p.x >= origin.x && p.x <= origin.x + width &&
            p.y >= origin.y && p.y <= origin.y + height);
}

int Rectangle::countIntersections(const Vector2& a, const Vector2& b) const {
    std::vector<Vector2> v = {
        {origin.x, origin.y},
        {origin.x + width, origin.y},
        {origin.x + width, origin.y + height},
        {origin.x, origin.y + height}
    };

    int count = 0;
    for (int i = 0; i < 4; i++)
        if (segmentsIntersect(a, b, v[i], v[(i + 1) % 4])) count++;

    return std::min(count, 2);
}

// ---------- CIRCLE ----------
Circle::Circle(int id, int reduction, int x, int y, int r) {
    this->id = id;
    this->reduction = reduction;
    this->center = {x, y};
    this->radius = r;
}

bool Circle::isInside(const Vector2& p) const {
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    return dx*dx + dy*dy <= radius*radius;
}

int Circle::countIntersections(const Vector2& a, const Vector2& b) const {
    Vector2 d = {b.x - a.x, b.y - a.y};
    Vector2 f = {a.x - center.x, a.y - center.y};

    double A = d.x*d.x + d.y*d.y;
    double B = 2 * (f.x*d.x + f.y*d.y);
    double C = f.x*f.x + f.y*f.y - radius*radius;

    double disc = B*B - 4*A*C;
    if (disc < 0) return 0;

    disc = sqrt(disc);
    double t1 = (-B - disc) / (2*A);
    double t2 = (-B + disc) / (2*A);

    int count = 0;
    if (t1 >= 0 && t1 <= 1) count++;
    if (t2 >= 0 && t2 <= 1) count++;
    return std::min(count, 2);
}

// ---------- LINE ----------
Line::Line(int id, int reduction, int x1, int y1, int x2, int y2) {
    this->id = id;
    this->reduction = reduction;
    this->p1 = {x1, y1};
    this->p2 = {x2, y2};
}

bool Line::isInside(const Vector2& p) const {
    return false;
}

int Line::countIntersections(const Vector2& a, const Vector2& b) const {
    return segmentsIntersect(a, b, p1, p2) ? 1 : 0;
}


