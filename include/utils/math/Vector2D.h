#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <ostream>
#include <cmath>

class Vector2D {
private:
    int x_;
    int y_;
public:
    Vector2D();

    Vector2D(int, int);

    Vector2D(Vector2D&);

    Vector2D(const Vector2D&);

    Vector2D(Vector2D&&);

    ~Vector2D();

    bool operator==(const Vector2D&);
    bool operator!=(const Vector2D&);
    bool operator< (const Vector2D&);
    bool operator> (const Vector2D&);
    bool operator>= (const Vector2D&);
    bool operator<= (const Vector2D&);

    bool operator==(const Vector2D&) const;
    bool operator!=(const Vector2D&) const;
    bool operator< (const Vector2D&) const;
    bool operator> (const Vector2D&) const;
    bool operator>= (const Vector2D&) const;
    bool operator<= (const Vector2D&) const;

    Vector2D& operator=(const Vector2D&);
    Vector2D& operator=(Vector2D&&);

    Vector2D& operator+=(const Vector2D&);

    Vector2D& operator-=(const Vector2D&);

    Vector2D operator+(const Vector2D&);

    Vector2D operator-(const Vector2D&);

    Vector2D operator*(int);

    int getX();
    int getY();
    
    void setX(int);
    void setY(int);

    int getX() const;
    int getY() const;

    double getLength();
    double getLength() const;
};

std::ostream& operator<< (std::ostream&, const Vector2D&);
std::istream& operator>> (std::istream&, Vector2D&);

static int getDistanceBetweenVectors2D(const Vector2D& vector_one, const Vector2D& vector_two) {
    return (abs(vector_one.getX() - vector_two.getX()) + abs(vector_one.getY() - vector_two.getY()));
}

const Vector2D zeroVector(0, 0);
const Vector2D upVector(0, -1);
const Vector2D rightVector(1, 0);
const Vector2D downVector(0, 1);
const Vector2D leftVector(-1, 0);
const Vector2D onesVector(1, 1);

#endif // VECTOR2D_H