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


def main():
    people = []
    num_people = get_valid_input("Введите количество людей: ", int, is_positive_number)

    for _ in range(num_people):
        name = get_valid_input("Введите имя: ", str)
        surname = get_valid_input("Введите фамилию: ", str)
        age = get_valid_input("Введите возраст: ", int, is_positive_number)

        person = {"name": name, "surname": surname, "age": age}
        people.append(person)

    if len(people) > 0:
        print("Список людей:")
        for person in people:
            print(f"{person['surname']} {person['name']} {person['age']}")

        ages = [person['age'] for person in people]
        min_age = min(ages)
        max_age = max(ages)
        average_age = sum(ages) / len(ages)
        print(f"Самый малый возраст: {min_age}")
        print(f"Самый большой возраст: {max_age}")
        print(f"Средний возраст: {average_age:.2f}")


if __name__ == '__main__':
    main()