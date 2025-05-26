import math
from typing import Tuple

def is_operator(op: str) -> bool:
    """
    Check if the given string is a valid arithmetic operator.
    Parameters: A single-character string to check.
    Returns: True if op is one of the valid operators, False otherwise.
    """
    return op in {"+", "-", "*", "/", "^"}


def is_number(token: str) -> bool:
    """
    Check if a given token (string) can be converted to a floating-point number.
    Parameters: The token to check.
    Returns: True if token can be safely converted to float, False otherwise.
    """
    try:
        float(token)
        return True
    except ValueError:
        return False


def evaluate(postfix: str) -> Tuple[float, bool]:
    """
    Evaluate a postfix (Reverse Polish Notation) arithmetic expression.
    The function uses a stack to evaluate the postfix expression one token at a time.
    Valid expressions must contain only numbers and supported operators, with proper formatting.

    Parameters: A space-separated string containing a postfix expression.
                Example: "3 4 + 2 *" evaluates to (3 + 4) * 2 = 14.0

    Returns:
        Tuple[float, bool]:
            - The final result of the expression if valid
            - A boolean flag indicating whether an error occurred (True = error)
    """
    stack: list[float] = []  # Stack to store operands during evaluation
    tokens = postfix.split()  # Split the input string into individual tokens

    for token in tokens:
        if is_number(token):
            # If the token is a number, convert it to float and push to stack
            stack.append(float(token))
        elif is_operator(token):
            # Operator needs at least two operands on the stack
            if len(stack) < 2:
                return 0.0, True  # Error: not enough operands

            # Pop the two topmost operands
            b = stack.pop()
            a = stack.pop()

            try:
                # Perform the appropriate operation and push result back on stack
                if token == "+":
                    stack.append(a + b)
                elif token == "-":
                    stack.append(a - b)
                elif token == "*":
                    stack.append(a * b)
                elif token == "/":
                    if b == 0:
                        return 0.0, True  # Error: division by zero
                    stack.append(a / b)
                elif token == "^":
                    stack.append(math.pow(a, b))
            except Exception:
                # Catch any unexpected runtime errors
                return 0.0, True
        else:
            # Error: unknown or invalid token
            return 0.0, True

    # After evaluation, there must be exactly one result left on the stack
    if len(stack) != 1:
        return 0.0, True  # Error: invalid postfix format

    # Return the result and indicate no error
    return stack[0], False