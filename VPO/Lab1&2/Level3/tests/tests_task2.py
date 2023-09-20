import unittest
from unittest.mock import patch, MagicMock
from io import StringIO
import os
import requests
from Task2 import download_file

class ProgramTestCase(unittest.TestCase):
    def setUp(self):
        self.url = "https://africau.edu/images/default/sample.pdf"
        self.output_folder = "D:\\Downloads"

    @patch("requests.get")
    def test_download_file_successful(self, mock_get):
        mock_response = MagicMock()
        mock_response.status_code = 200
        mock_response.content = b"This is the content of the PDF file."

        mock_get.return_value = mock_response

        expected_output = f"Файл успешно сохранен: {os.path.join(self.output_folder, 'sample.pdf')}\n"
        with patch("sys.stdout", new=StringIO()) as fake_out:
            download_file(self.url, self.output_folder)
            self.assertEqual(fake_out.getvalue(), expected_output)

    @patch("requests.get")
    def test_download_file_failed(self, mock_get):
        mock_response = mock_get.return_value
        mock_response.status_code = 404

        expected_output = "Ошибка при загрузке файла. Код состояния: 404\n"
        with patch("sys.stdout", new=StringIO()) as fake_out:
            download_file(self.url, self.output_folder)
            self.assertEqual(fake_out.getvalue(), expected_output)

    @patch("requests.get")
    def test_download_file_exception(self, mock_get):
        mock_get.side_effect = requests.exceptions.RequestException("Connection error")

        expected_output = "Ошибка при выполнении запроса: Connection error\n"
        with patch("sys.stdout", new=StringIO()) as fake_out:
            download_file(self.url, self.output_folder)
            self.assertEqual(fake_out.getvalue(), expected_output)

    def test_download_file_non_existing_folder(self):
        non_existing_folder = "non_existing_folder"

        expected_output = "Указанная папка не существует.\n"
        with patch("sys.stdout", new=StringIO()) as fake_out:
            if os.path.exists(non_existing_folder):
                os.rmdir(non_existing_folder)
            download_file(self.url, non_existing_folder)
            self.assertEqual(fake_out.getvalue(), expected_output)

if __name__ == "__main__":
    unittest.main()