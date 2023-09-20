import unittest
from Task1 import get_valid_input, is_positive_number, calculate_rectangle_area
import builtins
from unittest import mock

class ProgramTestCase(unittest.TestCase):
    def test_get_valid_input_valid(self):
        user_input = "5"
        with mock.patch.object(builtins, 'input', return_value=user_input):
            result = get_valid_input("Введите число: ", int)
        self.assertEqual(result, 5)

    def test_get_valid_input_with_validation_func_valid(self):
        user_input = "10"
        with mock.patch.object(builtins, 'input', return_value=user_input):
            result = get_valid_input("Введите число: ", int, is_positive_number)
        self.assertEqual(result, 10)

    def test_is_positive_number_positive(self):
        result = is_positive_number(5)
        self.assertTrue(result)

    def test_is_positive_number_zero(self):
        result = is_positive_number(0)
        self.assertTrue(result)

    def test_is_positive_number_negative(self):
        result = is_positive_number(-5)
        self.assertFalse(result)

    def test_calculate_rectangle_area(self):
        length = 5
        width = 10
        result = calculate_rectangle_area(length, width)
        self.assertEqual(result, 50)

    def test_calculate_rectangle_area_with_zero_length(self):
        length = 0
        width = 10
        result = calculate_rectangle_area(length, width)
        self.assertEqual(result, 0)

    def test_calculate_rectangle_area_with_zero_width(self):
        length = 5
        width = 0
        result = calculate_rectangle_area(length, width)
        self.assertEqual(result, 0)

if __name__ == "__main__":
    unittest.main()