from SETS import Diff
import unittest
from teests import TestDiff
import sys


def run_tests():
    suite = unittest.TestLoader().loadTestsFromTestCase(TestDiff)
    result = unittest.TextTestRunner().run(suite)

    if not result.wasSuccessful():
        print("The tests don't run. Exiting.")
        sys.exit(1)


def main():
    print("1 by yourself, 2 by file")
    choice = int(input())
    filename = "input.txt"
    operation = Diff()

    if choice == 1:
        print("Enter set A in the format like an example: {A, B, <C, D>}:")
        set_a_str = input().strip()

        try:
            set_a = operation.parse_set(set_a_str)
        except ValueError as e:
            print("Error in set A:", e)
            exit()
        print("Enter set B in the format like an example {<A, B>, C, D}:")
        set_b_str = input().strip()

        try:
            set_b = operation.parse_set(set_b_str)
        except ValueError as e:
            print("Error in set B:", e)
            exit()

        result = operation.find_difference_ruchkami(set_a, set_b)
        print("Difference:", result)

    elif choice == 2:
        try:
            set_a, set_b = operation.read_from_file(filename)
            result = operation.find_difference_ruchkami(set_a, set_b)
            print("Difference:", result)
        except FileNotFoundError:
            print("Error: File not found")
        except ValueError as e:
            print("Error:", e)

    else:
        print("Error: Invalid choice")


if __name__ == "__main__":
    run_tests()
    main()
