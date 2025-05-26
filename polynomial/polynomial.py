from typing import List, Tuple
import math


class Polynomial:
    """
    A class representing a polynomial with arithmetic operations.
    """

    def __init__(self, degree: int, coefficients: List[float] = None):
        """
        Initialize a polynomial with given degree and optional list of coefficients.

        Parameters:
            degree (int): The degree of the polynomial.
            coefficients (List[float], optional): Coefficients in ascending order of power (index 0 = constant).
                                                  If not provided, initializes to 0 for all terms.
        """
        self._degree = degree
        if coefficients is None:
            self._coefficients = [0.0] * (degree + 1)
        else:
            self._coefficients = coefficients[:degree + 1]

    def copy(self) -> 'Polynomial':
        """
        Create a deep copy of the polynomial.
        Returns: A new polynomial with the same coefficients and degree.
        """
        return Polynomial(self._degree, self._coefficients.copy())

    def __eq__(self, other: 'Polynomial') -> bool:
        """
        Check equality between two polynomials.
        Parameters: The polynomial to compare with.
        Returns: True if coefficients are the same, False otherwise.
        """
        return self._coefficients == other._coefficients

    def sum(self, rhs: 'Polynomial') -> 'Polynomial':
        """
        Add two polynomials.
        Parameters: The right-hand side polynomial to add.
        Returns: The result of the addition.
        """
        big_degree = max(self._degree, rhs._degree)
        result_coeffs = [0.0] * (big_degree + 1)

        for i in range(big_degree + 1):
            lhs_val = self._coefficients[i] if i <= self._degree else 0.0
            rhs_val = rhs._coefficients[i] if i <= rhs._degree else 0.0
            result_coeffs[i] = lhs_val + rhs_val

        return Polynomial(big_degree, result_coeffs)

    def subtract(self, rhs: 'Polynomial') -> 'Polynomial':
        """
        Subtract another polynomial from this one.
        Parameters: The polynomial to subtract (this - rhs).
        Returns: The result of the subtraction.
        """
        big_degree = max(self._degree, rhs._degree)
        result_coeffs = [0.0] * (big_degree + 1)

        for i in range(big_degree + 1):
            lhs_val = self._coefficients[i] if i <= self._degree else 0.0
            rhs_val = rhs._coefficients[i] if i <= rhs._degree else 0.0
            result_coeffs[i] = lhs_val - rhs_val

        return Polynomial(big_degree, result_coeffs)

    def minus(self) -> 'Polynomial':
        """
        Return the negation of the polynomial.
        Returns: The negated polynomial (-1 * this).
        """
        result_coeffs = [-c for c in self._coefficients]
        return Polynomial(self._degree, result_coeffs)

    def multiply(self, rhs: 'Polynomial') -> 'Polynomial':
        """
        Multiply two polynomials.
        Parameters: The right-hand side polynomial to multiply.
        Returns: The product polynomial.
        """
        new_degree = self._degree + rhs._degree
        result_coeffs = [0.0] * (new_degree + 1)

        for i in range(self._degree + 1):
            for j in range(rhs._degree + 1):
                result_coeffs[i + j] += self._coefficients[i] * rhs._coefficients[j]

        return Polynomial(new_degree, result_coeffs)

    def divide(self, rhs: 'Polynomial') -> 'Polynomial':
        """
        Perform polynomial division and return only the quotient.
        Parameters: The divisor polynomial.
        Returns: The quotient polynomial.
        """
        quotient, _ = self._divide_with_remainder(rhs)
        return quotient

    def divide_with_remainder(self, rhs: 'Polynomial') -> Tuple['Polynomial', 'Polynomial']:
        """
        Divide the polynomial and return both the quotient and remainder.
        Parameters: The divisor polynomial.
        Returns: Tuple[Polynomial, Polynomial]: (quotient, remainder)
        """
        return self._divide_with_remainder(rhs)

    def _divide_with_remainder(self, rhs: 'Polynomial') -> Tuple['Polynomial', 'Polynomial']:
        """
        Internal method to divide polynomials using long division.
        Parameters: The divisor polynomial.
        Returns: Tuple[Polynomial, Polynomial]: (quotient, remainder)
        """
        if rhs._degree > self._degree:
            return Polynomial(0, [0.0]), self.copy()

        degree_diff = self._degree - rhs._degree
        quo_coeffs = [0.0] * (degree_diff + 1)
        remainder = self._coefficients[:]

        for i in reversed(range(degree_diff + 1)):
            coeff = remainder[i + rhs._degree] / rhs._coefficients[rhs._degree]
            quo_coeffs[i] = coeff
            for j in range(rhs._degree + 1):
                remainder[i + j] -= coeff * rhs._coefficients[j]

        return Polynomial(degree_diff, quo_coeffs), Polynomial(len(remainder) - 1, remainder)

    def derive(self) -> 'Polynomial':
        """
        Compute the derivative of the polynomial.
        Returns: The first derivative of the polynomial.
        """
        if self._degree == 0:
            return Polynomial(0, [0.0])

        derived_coeffs = [(i + 1) * self._coefficients[i + 1] for i in range(self._degree)]
        return Polynomial(self._degree - 1, derived_coeffs)

    def evaluate(self, x: float) -> float:
        """
        Evaluate the polynomial at a specific value of x.
        Parameters: The input value.
        Returns: The result of the polynomial evaluated at x.
        """
        return sum(self._coefficients[i] * math.pow(x, i) for i in range(self._degree + 1))

    def integrate(self, start: float, end: float) -> float:
        """
        Compute the definite integral from start to end.
        Parameters:
            start (float): Lower limit of integration.
            end (float): Upper limit of integration.
        Returns: The definite integral result.
        """
        result = 0.0
        for i in range(self._degree + 1):
            exponent = i + 1
            result += self._coefficients[i] * (math.pow(end, exponent) - math.pow(start, exponent)) / exponent
        return result

    def __str__(self) -> str:
        """
        Convert the polynomial to a human-readable string.
        Returns: Polynomial as a string in descending order.
        """
        terms = []
        for i in reversed(range(1, self._degree + 1)):
            coeff = self._coefficients[i]
            terms.append(f"{coeff:+.2f}x^{i}")
        terms.append(f"{self._coefficients[0]:+.2f}")
        return ' '.join(terms)

    def read(self, input_string: str) -> bool:
        """
        Read polynomial data from a string of space-separated numbers.
        Parameters: The input string. First number is degree, followed by coefficients.
        Returns: True if successful, False if format is invalid.
        """
        try:
            parts = list(map(float, input_string.strip().split()))
            degree = int(parts[0])
            if len(parts[1:]) != degree + 1:
                return False
            self._degree = degree
            self._coefficients = parts[1:]
            return True
        except:
            return False

    def write(self) -> str:
        """
        Write polynomial data as a string.
        Returns: A string starting with degree, followed by coefficients.
        """
        return f"{self._degree} " + ' '.join(f"{c:.2f}" for c in self._coefficients)