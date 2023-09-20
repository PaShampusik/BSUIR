def calculate_rectangle_area(length, width):
    return length * width

if __name__ == "__main__":
    try:
        length = float(input("Введите длину прямоугольника: "))
        width = float(input("Введите ширину прямоугольника: "))
        area = calculate_rectangle_area(length, width)
        print("Площадь прямоугольника:", area)
    except ValueError:
        print("Ошибка: Некорректные значения длины или ширины")