#pragma once
#include <cstdarg>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace Maths {
class Vector {
public:
    Vector();
    Vector(double array[], int noOfValues);
    Vector(double a, double b);
    Vector(double a, double b, double c);
    Vector(double a, double b, double c, double d);
    Vector(const std::vector<double> &values);

    double dotProduct(const Vector &vector) const;
    Vector vectorProduct(const Vector &vector);
    double angle(const Vector &vector) const;
    int length() const;
    double magnitude() const;
    double at(int index) const;
    double &operator[](int index);
    double &operator[](std::string name);
    double operator[](int index) const;

    // Index traditional mathematical variable (i.e. x, y, z or w).
    double operator[](std::string name) const;

    // Addition.
    Vector operator+(const Vector &vectorRhs) const;

    // Difference.
    Vector operator-(const Vector &vectorRhs) const;

    // Dot product.
    double operator*(const Vector &vectorRhs) const;

    // Scalar multiplication.
    Vector operator*(double scalarRhs) const;

    // Scalar division.
    Vector operator/(double scalar) const;

    std::string toString() const;

    std::vector<double>::iterator begin();
    std::vector<double>::iterator end();
    std::vector<double>::const_iterator begin() const;
    std::vector<double>::const_iterator end() const;

private:
    std::vector<double> values;

    Vector multiply(const Vector &vector) const;

    template <class BinaryOperation>
    Vector vectorOperation(Vector vector) const;

    Vector scalarOperation(
        double scalar, std::function<double(double)> function) const;

    // Assign array pointer and its corresponding length.
    void createVectorFromArray(double *array, int length);
    std::string pointToString(int pointIndex) const;
    std::string allPointsToString() const;
    std::vector<double> emptyStlVector() const;
};}

// Vector multiplication operator.
Maths::Vector operator*(double scalarLhs, const Maths::Vector &vectorRhs);

// Prints the vector's contents.
std::ostream &operator<<(std::ostream &_stream, const Maths::Vector &vector);