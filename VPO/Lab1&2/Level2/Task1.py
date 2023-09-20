def get_valid_input(prompt, data_type, validate_func=None):
    while True:
        try:
            user_input = data_type(input(prompt))
            if validate_func and not validate_func(user_input):
                raise ValueError
            return user_input
        except ValueError:
            print("Ошибка: некорректный ввод. Пожалуйста, повторите попытку.")


def is_positive_number(number):
    return number >= 0

def calculate_rectangle_area(length, width):
    return length * width

if __name__ == "__main__":
    try:
        length = get_valid_input("Введите длину прямоугольника: ", float, is_positive_number)
        width = get_valid_input("Введите ширину прямоугольника: ", float, is_positive_number)
        area = calculate_rectangle_area(length, width)
        print("Площадь прямоугольника:", area)
    except ValueError:
        print("Ошибка: Некорректные значения длины или ширины")