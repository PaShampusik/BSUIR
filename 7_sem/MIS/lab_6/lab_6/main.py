import hashlib
import random


class Point:
    def __init__(self, a, b, p, q, x, y):
        self.a = a
        self.b = b
        self.p = p
        self.q = q
        self.x = x
        self.y = y

    def __add__(self, other):
        if (self.x, self.y) == (0, 0):
            return other
        if (other.x, other.y) == (0, 0):
            return self
        if self.x == other.x and (self.y != other.y or self.y == 0):
            return Point(self.a, self.b, self.p, self.q, 0, 0)
        if self.x == other.x and self.y == other.y:
            m = (3 * self.x ** 2 + self.a) * multiplicative_inverse(2 * self.y, self.p)
        else:
            m = (self.y - other.y) * multiplicative_inverse(self.x - other.x, self.p)

        x_r = (m ** 2 - self.x - other.x) % self.p
        y_r = (m * (self.x - x_r) - self.y) % self.p

        return Point(self.a, self.b, self.p, self.q, x_r, y_r)

    def __mul__(self, number):
        result = Point(self.a, self.b, self.p, self.q, 0, 0)
        addend = self

        for bit in bits(number):
            if bit == 1:
                result += addend
            addend += addend
        return result


def bits(number):
    while number:
        yield number & 1
        number >>= 1


def get_bezout_coeffs(a, b):
    x, x_, y, y_ = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a % b
        x, x_ = x_, x - x_ * q
        y, y_ = y_, y - y_ * q
    return x, y


def multiplicative_inverse(a, b):
    x, y = get_bezout_coeffs(a, b)
    if x < 0:
        return b + x
    return x


def sign(d, message, q, P):
    h = hashlib.sha256(message).digest()

    z = int.from_bytes(h, byteorder='big')
    e = z % q
    if e == 0:
        e = 1

    s = 0
    while True:
        k = random.randint(1, q - 1)
        C = P * k
        r = C.x % q
        if r == 0:
            continue
        s = (r * d + k * e) % q
        if s != 0:
            break

    return r, s


def verify(Q, message, signature, q, P):
    r, s = signature
    if not r < q or not s < q:
        return False

    h = hashlib.sha256(message).digest()

    z = int.from_bytes(h, byteorder='big')
    e = z % q
    if e == 0:
        e = 1

    v = multiplicative_inverse(e, q)

    z1 = s * v % q
    z2 = -r * v % q

    C = P * z1 + Q * z2
    R = C.x % q

    if R == r:
        return True
    else:
        return False

if __name__ == '__main__':

    # простое число, модуль эллиптической кривой такой, что меньше 2^256
    p = 0x8000000000000000000000000000000000000000000000000000000000000431

    # эллиптическая прямая задается параметрами a и b, которые принадлежат конечному полю из p элементов
    a = 0x7
    b = 0x5FBFF498AA938CE739B8E022FBAFEF40563F6E6A3472FC2A514C0CE9DAE23B7E

    # простое число q, порядок некоторой циклической подгруппы группы точек эллиптической кривой
    q = 0x8000000000000000000000000000000150FE8A1892976154C59CFC193ACCF5B3

    # координаты точки P эллиптичеаской кривой E. Точка P является генератором подгруппы порядка q:  q * P = 0
    x = 0x2
    y = 0x8E2A8A0E65147D4BD6316030E16D19C85C97F0A9CA267122B96ABBCEA7E8FC8
    P = Point(a, b, p, q, x, y)

    # ключ шифрования d,  0 < d < q, d есть у всех пользователей
    d = 0x7A929ADE789BB9BE10ED359DD39A72C11B60961F49397EEE1D19CE9891EC3B28

    # ключ расшифрования
    Q = P * d

    message = "BSUIR"
    signature = sign(d, message.encode(), q, P)
    is_correct = verify(Q, message.encode(), signature, q, P)
    print(f"Message: {message}")
    print(f"Signature: ({signature[0]:x}, {signature[1]:x})")
    if is_correct:
        print("Correct signature")
    else:
        print("Wrong signature")