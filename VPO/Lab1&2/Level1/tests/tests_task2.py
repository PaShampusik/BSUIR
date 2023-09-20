import unittest
from unittest.mock import patch
from Task2 import get_valid_input, is_positive_number, main

class ProgramTestCase(unittest.TestCase):
    def test_get_valid_input_valid(self):
        user_input = "5"
        with unittest.mock.patch('builtins.input', return_value=user_input):
            result = get_valid_input("Введите число: ", int)
        self.assertEqual(result, 5)

    def test_get_valid_input_with_validation_func_valid(self):
        user_input = "10"
        with unittest.mock.patch('builtins.input', return_value=user_input):
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
