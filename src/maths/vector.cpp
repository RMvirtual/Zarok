#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "maths/vector.h"

Maths::Vector::Vector() {this->values = {};}
Maths::Vector::Vector(double a, double b) {this->values = {a, b};}
Maths::Vector::Vector(double a, double b, double c) {this->values = {a, b, c};}

Maths::Vector::Vector(double a, double b, double c, double d)
{
    this->values = {a, b, c, d};
}

Maths::Vector::Vector(const std::vector<double> &values)
{
    this->values = values;
}

Maths::Vector::Vector(double array[], int arrayLength)
{
    this->values = {array, array + arrayLength};
}

double Maths::Vector::dotProduct(const Maths::Vector &vector) const
{
    auto multiples = this->multiply(vector);

    return std::accumulate(multiples.begin(), multiples.end(), 0.0);
}

Maths::Vector Maths::Vector::vectorProduct(const Maths::Vector &vector)
{
    Maths::Vector self = *this;
    const int x = 0, y = 1, z = 2;

    double crossX = (self[y] * vector[z]) - (self[z] * vector[y]);
    double crossY = (self[z] * vector[x]) - (self[x] * vector[z]);
    double crossZ = (self[x] * vector[y]) - (self[y] * vector[x]);

    return {crossX, crossY, crossZ};
}

double Maths::Vector::angle(const Maths::Vector &vector) const
{
    auto magnitudeProduct = this->magnitude() * vector.magnitude();
    auto dotProduct = this->dotProduct(vector);

    return acos(dotProduct / magnitudeProduct);
}

int Maths::Vector::length() const {return this->values.size();}
double Maths::Vector::at(int index) const {return this->values[index];}

double Maths::Vector::magnitude() const
{
    auto squareAndSum = [](double sumAccumulator, double value)
    { return sumAccumulator + pow(value, 2.0); };

    auto sum = std::accumulate(
        this->values.begin(), this->values.end(), 0.0, squareAndSum);

    return sqrt(sum);
}

Maths::Vector Maths::Vector::multiply(const Maths::Vector &vector) const
{
    return this->vectorOperation<std::multiplies<double>>(vector);
}

double &Maths::Vector::operator[](int index){return this->values[index];}

double &Maths::Vector::operator[](std::string name)
{
    std::unordered_map<std::string, int> variableNotations{
        {"x", 0}, {"y", 1}, {"z", 2}, {"w", 3}};

    return this->values[variableNotations[name]];
}

double Maths::Vector::operator[](int index) const {return this->at(index);}

double Maths::Vector::operator[](std::string name) const
{
    std::unordered_map<std::string, int> variableNotations{
        {"x", 0}, {"y", 1}, {"z", 2}, {"w", 3}};

    return this->at(variableNotations[name]);
}

Maths::Vector Maths::Vector::operator+(const Maths::Vector &vector) const
{
    return this->vectorOperation<std::plus<double>>(vector);
}

template <class BinaryOperation>
Maths::Vector Maths::Vector::vectorOperation(Maths::Vector vector) const
{
    auto newElements = this->emptyStlVector();

    std::transform(
        this->begin(), this->end(), vector.begin(),
        newElements.begin(), BinaryOperation());

    return {newElements};
}

Maths::Vector Maths::Vector::scalarOperation(
    double scalar, std::function<double(double)> unaryOperation) const
{
    auto newElements = this->emptyStlVector();

    std::transform(
        this->begin(), this->end(), newElements.begin(), unaryOperation);

    return {newElements};
}

Maths::Vector Maths::Vector::operator-(const Maths::Vector &vector) const
{
    return this->vectorOperation<std::minus<double>>(vector);
}

double Maths::Vector::operator*(const Maths::Vector &vector) const
{
    return this->dotProduct(vector);
}

Maths::Vector Maths::Vector::operator*(double scalar) const
{
    auto multiplyOp = [scalar](double value) { return scalar * value; };

    return this->scalarOperation(scalar, multiplyOp);
}

Maths::Vector operator*(double scalar, const Maths::Vector &vector)
{
    return vector * scalar;
}

Maths::Vector Maths::Vector::operator/(double scalar) const
{
    auto divideOp = [scalar](double value) { return value / scalar; };

    return this->scalarOperation(scalar, divideOp);
}

std::vector<double>::iterator Maths::Vector::begin()
{
    return this->values.begin();
}

std::vector<double>::iterator Maths::Vector::end()
{
    return this->values.end();
}

std::vector<double>::const_iterator Maths::Vector::begin() const
{
    return this->values.begin();
}

std::vector<double>::const_iterator Maths::Vector::end() const
{
    return this->values.end();
}

std::string Maths::Vector::toString() const
{
    return "[" + this->allPointsToString() + "]";
}

std::string Maths::Vector::allPointsToString() const
{
    int noOfPoints = this->length();

    auto morePointsRemaining = [noOfPoints](int pointNo) {
        return pointNo < noOfPoints - 1;
    };

    std::string points = "";

    for (int pointNo = 0; pointNo < noOfPoints; pointNo++) {
        points += this->pointToString(pointNo);

        if (morePointsRemaining(pointNo))
            points += ", ";
    }

    return points;
}

std::string Maths::Vector::pointToString(int pointIndex) const
{
    auto pointIndexString = std::to_string(pointIndex);
    auto pointValue = std::to_string(this->at(pointIndex));

    return pointIndexString + ": " + pointValue;
}

std::ostream &operator<<(std::ostream &outstream, const Maths::Vector &vector)
{
    return outstream << vector.toString();
}

std::vector<double> Maths::Vector::emptyStlVector() const
{
    return std::vector<double>(this->length());
}