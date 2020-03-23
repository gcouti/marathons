import os
import sys
from math import sqrt
from itertools import count, islice


def is_prime(n):
    """
    Check if a number is prime
    :param n:
    :return: boolean
    """
    return n > 1 and all(n % i for i in islice(count(2), int(sqrt(n) - 1)))


if __name__ == "__main__":
    print(is_prime(int(sys.argv[1])))
