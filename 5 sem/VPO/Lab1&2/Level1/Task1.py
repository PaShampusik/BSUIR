import random

def generate_random_exclamation():
    return '!' * random.randint(5, 50)

def main():
    print("Нello, world!")
    print("Andhiagain", generate_random_exclamation())

if __name__ == '__main__':
    main()