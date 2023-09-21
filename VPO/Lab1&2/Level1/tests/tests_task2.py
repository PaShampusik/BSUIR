import unittest
from unittest.mock import patch
from io import StringIO
from ..Task2 import get_valid_input, is_positive_number, main

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

    @patch('builtins.input', side_effect=['3', 'John', 'Doe', '30', 'Jane', 'Smith', '25', 'Mike', 'Johnson', '40'])
    def test_multiple_people(self, mock_input):
        expected_output = "Список людей:\nDoe John 30\nSmith Jane 25\nJohnson Mike 40\nСамый малый возраст: 25\nСамый большой возраст: 40\nСредний возраст: 31.67\n"

        with patch('sys.stdout', new=StringIO()) as mock_stdout:
            main()

        self.assertEqual(mock_stdout.getvalue(), expected_output)
    
    @patch('builtins.input', side_effect=['1', 'John', 'Doe', '30'])
    def test_single_person(self, mock_input):
        expected_output = "Список людей:\nDoe John 30\nСамый малый возраст: 30\nСамый большой возраст: 30\nСредний возраст: 30.00\n"

        with patch('sys.stdout', new=StringIO()) as mock_stdout:
            main()

        self.assertEqual(mock_stdout.getvalue(), expected_output)

