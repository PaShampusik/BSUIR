import os
import sys
import requests

def download_file(url, output_folder):
    try:
        if not os.path.isdir(output_folder):
            print("Указанная папка не существует.")
            return
        response = requests.get(url)
        if response.status_code == 200:
            # Получение имени файла из URL
            filename = url.split("/")[-1]
            output_path = os.path.join(output_folder, filename)
            with open(output_path, "wb") as file:
                file.write(response.content)

            print("Файл успешно сохранен:", output_path)
        else:
            print("Ошибка при загрузке файла. Код состояния:", response.status_code)
    except requests.exceptions.RequestException as e:
        print("Ошибка при выполнении запроса:", str(e))

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python Task2.py <url> <output_folder>")
    else:
        url = sys.argv[1]
        output_folder = sys.argv[2]
        download_file(url, output_folder)