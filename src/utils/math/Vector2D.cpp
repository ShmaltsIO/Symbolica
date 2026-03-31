#include "Vector2D.h"

Vector2D::Vector2D(): x_(0), y_(0) {}

Vector2D::Vector2D(int x, int y): x_(x), y_(y) {}

Vector2D::Vector2D(Vector2D& new_vector) {
    *this = new_vector;
}

Vector2D::Vector2D(const Vector2D& new_vector) {
    *this = new_vector;
}

Vector2D::Vector2D(Vector2D&& new_vector): x_(new_vector.getX()), y_(new_vector.getY()) {
    new_vector.setX(0);
    new_vector.setY(0);
}

Vector2D::~Vector2D() {
    x_ = 0;
    y_ = 0;
}

bool Vector2D::operator== (const Vector2D& another_vector) {
    return (this->getX() == another_vector.getX() && this->getY() == another_vector.getY());
}

bool Vector2D::operator!= (const Vector2D& another_vector) {
    return (this->getX() != another_vector.getX() && this->getY() != another_vector.getY());
}

bool Vector2D::operator> (const Vector2D& another_vector) {
    return (this->getX() > another_vector.getX() && this->getY() > another_vector.getY());
}

bool Vector2D::operator< (const Vector2D& another_vector) {
    return (this->getX() < another_vector.getX() && this->getY() < another_vector.getY());
}

bool Vector2D::operator>= (const Vector2D& another_vector) {
    return (this->getX() >= another_vector.getX() && this->getY() >= another_vector.getY());
}

bool Vector2D::operator<= (const Vector2D& another_vector) {
    return (this->getX() <= another_vector.getX() && this->getY() <= another_vector.getY());
}

bool Vector2D::operator== (const Vector2D& another_vector) const {
    return (this->getX() == another_vector.getX() && this->getY() == another_vector.getY());
}

bool Vector2D::operator!= (const Vector2D& another_vector) const {
    return (this->getX() != another_vector.getX() && this->getY() != another_vector.getY());
}

bool Vector2D::operator> (const Vector2D& another_vector) const {
    return (this->getX() > another_vector.getX() && this->getY() > another_vector.getY());
}

bool Vector2D::operator< (const Vector2D& another_vector) const {
    return (this->getX() < another_vector.getX() && this->getY() < another_vector.getY());
}

bool Vector2D::operator>= (const Vector2D& another_vector) const {
    return (this->getX() >= another_vector.getX() && this->getY() >= another_vector.getY());
}

bool Vector2D::operator<= (const Vector2D& another_vector) const {
    return (this->getX() <= another_vector.getX() && this->getY() <= another_vector.getY());
}

Vector2D& Vector2D::operator= (const Vector2D& new_vector) {
    if (*this == new_vector) {
        return *this;
    }
    this->setX(new_vector.getX());
    this->setY(new_vector.getY());
    return *this;
}

Vector2D& Vector2D::operator= (Vector2D&& new_vector) {
    if (this == &new_vector) {
        return *this;
    }
    int x = this->getX();
    int y = this->getY();
    this->setX(new_vector.getX());
    this->setY(new_vector.getY());
    new_vector.setX(x);
    new_vector.setY(y);
    return *this;
}

Vector2D Vector2D::operator+ (const Vector2D& another_vector) {
    return {this->getX() + another_vector.getX(), this->getY() + another_vector.getY()};
}

Vector2D Vector2D::operator- (const Vector2D& another_vector) {
    return {this->getX() - another_vector.getX(), this->getY() - another_vector.getY()};
}

Vector2D& Vector2D::operator+= (const Vector2D& another_vector) {
    this->setX(this->getX() + another_vector.getX());
    this->setY(this->getY() + another_vector.getY());
    return *this;
}

Vector2D& Vector2D::operator-= (const Vector2D& another_vector) {
    this->setX(this->getX() - another_vector.getX());
    this->setY(this->getY() - another_vector.getY());
    return *this;
}

Vector2D Vector2D::operator* (int scalar) {
    return {this->getX()*scalar, this->getY()*scalar};
}

int Vector2D::getX() {
    return x_;
}

int Vector2D::getY() {
    return y_;
}

void Vector2D::setX(int x) {
    x_ = x;
}

void Vector2D::setY(int y) {
    y_ = y;
}

inline int Vector2D::getX() const {
    return x_;
}

int Vector2D::getY() const {
    return y_;
}

std::ostream& operator<< (std::ostream& out, const Vector2D& vector) {
    out << "(" << vector.getX() << ";" << vector.getY() << ")" << std::endl;
    return out;
}

double Vector2D::getLength() {
    return sqrt(x_*x_ + y_*y_);
}

double Vector2D::getLength() const {
    return sqrt(x_*x_ + y_*y_);
}
