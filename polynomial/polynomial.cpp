#include "polynomial.h"

#include <sstream>
#include <iomanip>
#include <cmath>
using std::stringstream;
using std::showpos;
using std::fixed;
using std::setprecision;

// Parameter: a size_t degree
// Constructor: Creates a polynomial of given degree, initializing all coefficients to 0
Polynomial::Polynomial(size_t degree) : _degree(degree), _coefficients(new float[_degree + 1]) {
    for(size_t i = 0; i < _degree + 1; i++) {
        _coefficients[i] = 0.0;
    }
}

// Parameters: a size_t degree, float* coefficient
// Constructor: Creates a polynomial of given degree with the provided coefficient values
Polynomial::Polynomial(size_t degree, const float* coefficients) : _degree(degree), _coefficients(new float[_degree + 1]) {
    for (size_t i = 0; i < _degree + 1; i++) {
        _coefficients[i] = coefficients[i];
    }
}

// Parameter: an other polynomial
// Copy constructor: Creates a deep copy of another polynomial
Polynomial::Polynomial(const Polynomial& other) : _degree(other._degree), _coefficients(new float[other._degree + 1]) {
    for (size_t i = 0; i < _degree + 1; i++) {
        _coefficients[i] = other._coefficients[i];
    }
}

// Destructor: Cleans up dynamically allocated memory
Polynomial::~Polynomial() {
    _degree = 0;
    delete[] _coefficients;
}

// Parameter: a rhs polynomial
// Copy assignment operator: Assigns values from another polynomial, performing deep copy
const Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    delete[] _coefficients;
    _degree = rhs._degree;
    _coefficients = new float[_degree + 1];
    for(size_t i = 0; i <= _degree; i++) {
        _coefficients[i] = rhs._coefficients[i];
    }
    return *this;
}

// Parameter: a rhs polynomial
// Adds two polynomials term by term. Supports different degrees by treating missing terms as 0
const Polynomial Polynomial::Sum(const Polynomial& rhs)const {
    size_t bigDegree = std::max(_degree, rhs._degree);                   // finds the polynomial that has more coefficients
    float* values = new float[bigDegree + 1];
    for (size_t i = 0; i <= bigDegree; i++) {
        float lhsCoeff = 0.0f;
        float rhsCoeff = 0.0f;

        if (i<= _degree) {                                                   // checks if the current index in within bounds of the current polynomial
            lhsCoeff = _coefficients[i];
        }
        if (i <= rhs._degree) {
            rhsCoeff = rhs._coefficients[i];
        }
        values[i] = lhsCoeff + rhsCoeff;
    }

    Polynomial result(bigDegree, values);
    delete[] values;
    return result;
}

// Parameter: a rhs polynomial
// Subtracts rhs polynomial from this polynomial term by term. Like addition, handles different degrees
const Polynomial Polynomial::Subtract(const Polynomial& rhs)const {
    size_t bigDegree = std::max(_degree, rhs._degree);                   // finds the polynomial that has more coefficients
    float* values = new float[bigDegree + 1];
    for (size_t i = 0; i <= bigDegree; i++) {
        float lhsCoeff = 0.0f;
        float rhsCoeff = 0.0f;

        if (i <= _degree) {                                                  // checks if the current index in within bounds of the current polynomial
            lhsCoeff = _coefficients[i];
        }
        if (i <= rhs._degree) {
            rhsCoeff = rhs._coefficients[i];
        }
        values[i] = lhsCoeff - rhsCoeff;
    }

    Polynomial result(bigDegree, values);
    delete[] values;
    return result;
}

// Returns the additive inverse of the polynomial (i.e., multiplies every coefficient by -1)
const Polynomial Polynomial::Minus()const {
    float* inverse = new float[_degree + 1];
    for(size_t i = 0; i <= _degree; i++) {
        inverse[i] = -_coefficients[i];
    }
    Polynomial result(_degree, inverse);
    delete[] inverse;
    return result;
}

// Parameter: a rhs polynomial
// Multiplies two polynomials using the distributive property (nested loop over terms)
// This implements classical polynomial multiplication (FOIL method)
const Polynomial Polynomial::Multiply(const Polynomial& rhs)const {
    size_t degrees = _degree + rhs._degree;
    float* values = new float[degrees + 1]();      // initialize to zero
    for(size_t i = 0; i < _degree + 1; i++) {
        for(size_t j = 0; j < rhs._degree + 1; j++) {
            values[i + j] += _coefficients[i] * rhs._coefficients[j];
        }
    }
    Polynomial result(degrees, values);
    delete[] values;
    return result;
}

// Parameter: a rhs polynomial
// Performs polynomial long division: this / rhs
// Returns the quotient polynomial and ignores the remainder
// Implements the long division algorithm: subtract scaled divisor from dividend step-by-step
const Polynomial Polynomial::Divide(const Polynomial& rhs)const{
    size_t degreeDiff = _degree - rhs._degree;
    float* quoCoeff = new float[degreeDiff + 1]();
    Polynomial remainder = *this;
    for (int i = degreeDiff; i >= 0; i--) {
        float coeff = remainder._coefficients[i + rhs._degree] / rhs._coefficients[rhs._degree];  // divides heading term of the remainder by the leading term of the divisor
        quoCoeff[i] = coeff;

        for (size_t j = 0; j <= rhs._degree; j++){
            remainder._coefficients[i + j] -= coeff * rhs._coefficients[j];                       //Subtract rhs multiplied by the current coefficient from the remainder
        }
    }

    Polynomial quotient(degreeDiff, quoCoeff);
    delete[] quoCoeff;
    return quotient;
}

// Parameters: a rhs polynomial, a remainder polynomial
// Return: a polynomial that will contain the division of this with rhs
// The remainder will be placed in parameter by reference remainder
const Polynomial Polynomial::Divide(const Polynomial& rhs, Polynomial& remainder)const{
    int degreeDiff = _degree - rhs._degree;
    if (degreeDiff < 0) {                                                                           // If the degree of the divisor is greater, quotient is 0
        remainder = *this;
        return Polynomial(0);
    }

    float* quoCoeff = new float[degreeDiff + 1]();
    remainder = *this;
    for (int i = degreeDiff; i >= 0; i--) {
        float coeff = remainder._coefficients[i + rhs._degree] / rhs._coefficients[rhs._degree];    // divides heading term of the remainder by the leading term of the divisor
        quoCoeff[i] = coeff;

        for (size_t j = 0; j <= rhs._degree; j++) {
            remainder._coefficients[i + j] -= coeff * rhs._coefficients[j];                        //Subtract rhs multiplied by the current coefficient from the remainder
        }
    }

    Polynomial quotient(degreeDiff, quoCoeff);
    delete[] quoCoeff;
    return quotient;
}

// Computes the derivative of the polynomial using the power rule:
// For each term a_{i+1} * x^{i+1}, the derivative is (i+1) * a_{i+1} * x^i
// This loop builds the resulting polynomial: P'(x) = ∑ (i+1) * a_{i+1} * x^i
const Polynomial Polynomial:: Derive()const {
    float* derivative = new float[_degree];
    for(size_t i = 0; i < _degree ; i++) {
        derivative[i] = _coefficients[i + 1] * (i + 1);
    }
    Polynomial result(_degree - 1, derivative);
    delete[] derivative;
    return result;
}

// Parameter: a float x
// Evaluates the polynomial at a given x using direct computation
float Polynomial::Evaluate(float x)const {
    float result = 0.0;
    for(size_t i = 0; i < _degree + 1; i++) {
        result += _coefficients[i] * pow(x,i);            // Adds a_i * x^i to the result for each term
    }
    return result;
}

// Parameters: a float start, a float end
// Computes the definite integral of the polynomial from 'start' to 'end' using the power rule of integration:
// ∫ a*x^n dx = (a/(n+1)) * x^(n+1), then evaluate the result at 'end' and 'start' and subtract
float Polynomial::Integrate(float start, float end)const{
    float result = 0.0f;
    for(size_t i = 0; i <= _degree; i++ ) {
        float exponent = static_cast<float>(i + 1);
        result += _coefficients[i] * (pow(end, exponent) - pow(start, exponent)) / exponent;          // For each term a*x^n, compute a * [(end^(n+1) - start^(n+1)) / (n+1)]
    }
    return result;
}

// Parameter: a rhs polynomial
// Compares this polynomial to another for equality by checking each coefficient.
bool Polynomial:: Equals(const Polynomial& rhs)const {
    for(size_t i = 0; i < _degree + 1; i++) {
        if(_coefficients[i] != rhs._coefficients[i]) return false;
    }
    return true;
}

// GIVEN. Return: a string representation of the polynomial.
string Polynomial::ToString()const{
    stringstream ss;
    for (size_t i = _degree; i > 0; i--) {
        ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
    }
    ss << showpos << fixed << setprecision(2) << _coefficients[0];
    return ss.str();
}

// Parameter: an output stream to write to
// GIVEN. Writes a polynomial from the output stream.
ostream& Polynomial::Write(ostream& output)const{
    output << _degree << " ";
    for (size_t i = 0; i < _degree + 1; i++) {
        output << _coefficients[i] << " ";
    }
    return output;
}

// Parameter: an input stream to read from
// GIVEN. Reads a polynomial from the input stream.
istream& Polynomial::Read(istream& input){
    size_t degree;
    input >> degree;
    if (input.fail()){
        return input;
    }
    float* coefficients = new float[degree + 1];
    for (size_t i = 0; i < degree + 1; i++) {
        input >> coefficients[i];
        if (input.fail()){
            delete[] coefficients;
            return input;
        }
    }

    if (degree != _degree){
        if (_coefficients){
            delete[] _coefficients;
        }
        _degree = degree;
        _coefficients = coefficients;
    }else{
        for (size_t i = 0; i < _degree + 1; i++) {
            _coefficients[i] = coefficients[i];
        }
        delete[] coefficients;
    }
    return input;
}