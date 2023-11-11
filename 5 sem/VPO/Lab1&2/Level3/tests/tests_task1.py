import unittest
from unittest.mock import patch
from io import StringIO
import os
from ..Task1 import find_files_with_extension

class ProgramTestCase(unittest.TestCase):
    def setUp(self):
        self.folder = "test_folder"
        os.mkdir(self.folder)
        self.file1 = os.path.join(self.folder, "file1.txt")
        with open(self.file1, "w") as f:
            f.write("Test file 1")
        self.file2 = os.path.join(self.folder, "file2.txt")
        with open(self.file2, "w") as f:
            f.write("Test file 2")
        self.file3 = os.path.join(self.folder, "file3.jpg")
        with open(self.file3, "w") as f:
            f.write("Test file 3")

    def tearDown(self):
        os.remove(self.file1)
        os.remove(self.file2)
        os.remove(self.file3)
        os.rmdir(self.folder)

    def test_find_files_with_extension_existing_folder(self):
        extension = ".txt"
        expected_output = f"{self.file1}\n{self.file2}\n"
        with patch("sys.stdout", new=StringIO()) as fake_out:
            find_files_with_extension(self.folder, extension)
            self.assertEqual(fake_out.getvalue(), expected_output)

    def test_find_files_with_extension_non_existing_folder(self):
        non_existing_folder = "non_existing_folder"
        extension = ".txt"
        expected_output = "Указанная папка не существует.\n"
        with patch("sys.stdout", new=StringIO()) as fake_out:
            find_files_with_extension(non_existing_folder, extension)
            self.assertEqual(fake_out.getvalue(), expected_output)

    def test_find_files_with_extension_invalid_extension(self):
        extension = "txt"
        expected_output = "Расширение файла должно начинаться с точки (например, '.txt').\n"
        with patch("sys.stdout", new=StringIO()) as fake_out:
            find_files_with_extension(self.folder, extension)
            self.assertEqual(fake_out.getvalue(), expected_output)

if __name__ == "__main__":
    unittest.main()