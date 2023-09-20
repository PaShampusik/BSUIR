import os
import sys

def find_files_with_extension(folder, extension):
    if not os.path.isdir(folder):
        print("Указанная папка не существует.")
        return

    if not extension.startswith("."):
        print("Расширение файла должно начинаться с точки (например, '.txt').")
        return

    for root, dirs, files in os.walk(folder):
        for file in files:
            if file.endswith(extension):
                file_path = os.path.join(root, file)
                print(file_path)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python Task1.py <folder> <extension>")
    else:
        folder = sys.argv[1] #Path must be like:  "C:\Program Files\"
        extension = sys.argv[2]
        find_files_with_extension(folder, extension)