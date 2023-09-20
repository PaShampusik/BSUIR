import unittest
from unittest.mock import patch
import random
from io import StringIO
import sys
from Task1 import generate_random_exclamation, main

class FuncTestCase(unittest.TestCase):
    @patch('random.randint')
    def test_generate_random_exclamation(self, mock_randint):
        mock_randint.return_value = 10
        result = generate_random_exclamation()
        self.assertEqual(result, "!!!!!!!!!!")

    @patch('random.randint')
    def test_generate_random_exclamation(self, mock_randint):
        mock_randint.return_value = 14
        result = generate_random_exclamation()
        self.assertEqual(result, "!!!!!!!!!!!!!!")

    @patch('random.randint')
    def test_generate_random_exclamation(self, mock_randint):
        mock_randint.return_value = 5
        result = generate_random_exclamation()
        self.assertEqual(result, "!!!!!")

class MainTestCase(unittest.TestCase):
    @patch('sys.stdout', new_callable=StringIO)
    @patch('random.randint')
    def test_main(self, mock_randint, mock_stdout):
        mock_randint.return_value = 7
        main()
        output = mock_stdout.getvalue()
        expected_output = "Нello, world!\nAndhiagain !!!!!!!\n"
        self.assertEqual(output, expected_output)

    @patch('sys.stdout', new_callable=StringIO)
    @patch('random.randint')
    def test_main(self, mock_randint, mock_stdout):
        mock_randint.return_value = 10
        main()
        output = mock_stdout.getvalue()
        expected_output = "Нello, world!\nAndhiagain !!!!!!!!!!\n"
        self.assertEqual(output, expected_output)

if __name__ == "__main__":
    unittest.main()