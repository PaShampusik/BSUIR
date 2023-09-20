import unittest
from Task2 import generate_html

class ProgramTestCase(unittest.TestCase):
    def test_generate_html_with_n_3(self):
        n = 3
        result = generate_html(n)
        expected_html = "<table style = \"width: 8000px;\">\n<tr style=\"padding-bottom: 0px; background-color: rgb(255, 255, 255)\"><td>1</td></tr>\n<tr style=\"padding-bottom: 0px; background-color: rgb(170, 170, 170)\"><td>2</td></tr>\n<tr style=\"padding-bottom: 0px; background-color: rgb(85, 85, 85)\"><td>3</td></tr>\n</table>"
        self.assertEqual(result, expected_html)

    def test_generate_html_with_n_5(self):
        n = 5
        result = generate_html(n)
        expected_html = "<table style = \"width: 8000px;\">\n<tr style=\"padding-bottom: 0px; background-color: rgb(255, 255, 255)\"><td>1</td></tr>\n<tr style=\"padding-bottom: 0px; background-color: rgb(204, 204, 204)\"><td>2</td></tr>\n<tr style=\"padding-bottom: 0px; background-color: rgb(153, 153, 153)\"><td>3</td></tr>\n<tr style=\"padding-bottom: 0px; background-color: rgb(102, 102, 102)\"><td>4</td></tr>\n<tr style=\"padding-bottom: 0px; background-color: rgb(51, 51, 51)\"><td>5</td></tr>\n</table>"
        self.assertEqual(result, expected_html)

if __name__ == "__main__":
    unittest.main()