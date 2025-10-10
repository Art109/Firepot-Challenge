#include "../include/geometry.h"
#include <cmath>
#include <vector>
#include <algorithm>

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
    double distSq = dx*dx + dy*dy;
    return distSq <= radius * radius;
}


// ---------- LINE ----------
Line::Line(int id, int reduction, int x1, int y1, int x2, int y2) {
    this->id = id;
    this->reduction = reduction;
    this->p1 = {x1, y1};
    this->p2 = {x2, y2};
}

int Line::countIntersections(const Vector2& a, const Vector2& b) const {
    auto cross = [](const Vector2& A, const Vector2& B, const Vector2& C) {
        return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    };

    int d1 = cross(a, b, p1);
    int d2 = cross(a, b, p2);
    int d3 = cross(p1, p2, a);
    int d4 = cross(p1, p2, b);

    if ((d1 * d2 < 0) && (d3 * d4 < 0))
        return 1;
    return 0;
}

bool Line::isInside(const Vector2& p) const {
    // Linhas são infinitamente finas, então tecnicamente nada está "dentro"
    // Retornamos false para manter a consistência
    return false;
}


// ---------- RECTANGLE ----------
int Rectangle::countIntersections(const Vector2& a, const Vector2& b) const {
    const double EPS = 1e-6;
    std::vector<Vector2> corners = {
        {origin.x, origin.y},
        {origin.x + width, origin.y},
        {origin.x + width, origin.y + height},
        {origin.x, origin.y + height}
    };

    int count = 0;

    auto crosses = [&](Vector2 p1, Vector2 p2) -> bool {
        double denom = (b.x - a.x) * (p2.y - p1.y) - (b.y - a.y) * (p2.x - p1.x);
        if (std::fabs(denom) < EPS) return false; // paralelas

        double t = ((p1.x - a.x) * (p2.y - p1.y) - (p1.y - a.y) * (p2.x - a.x)) / denom;
        double u = ((p1.x - a.x) * (b.y - a.y) - (p1.y - a.y) * (b.x - a.x)) / denom;

        // interseção dentro dos limites dos segmentos
        return (t > EPS && t < 1.0 - EPS && u >= -EPS && u <= 1.0 + EPS);
    };

    for (int i = 0; i < 4; ++i)
        if (crosses(corners[i], corners[(i + 1) % 4])) count++;

    // se tangenciou o mesmo canto duas vezes, limita a 2 no máximo
    if (count > 2) count = 2;

    return count;
}



// ---------- CIRCLE ----------
int Circle::countIntersections(const Vector2& a, const Vector2& b) const {
    const double EPS = 1e-9;
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double fx = a.x - center.x;
    double fy = a.y - center.y;

    double A = dx*dx + dy*dy;
    double B = 2 * (fx*dx + fy*dy);
    double C = fx*fx + fy*fy - radius*radius;

    double discriminant = B*B - 4*A*C;
    if (discriminant < 0)
        return 0;

    discriminant = sqrt(discriminant);

    double t1 = (-B - discriminant) / (2*A);
    double t2 = (-B + discriminant) / (2*A);

    int count = 0;
    if (t1 > EPS && t1 < 1.0 - EPS) count++;
    if (t2 > EPS && t2 < 1.0 - EPS) count++;

    return count;
}


