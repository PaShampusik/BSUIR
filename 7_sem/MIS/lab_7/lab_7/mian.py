import random
import binascii

# Параметры эллиптической кривой
p = 2 ** 256 - 2 ** 32 - 2 ** 9 - 2 ** 8 - 2 ** 7 - 2 ** 6 - 2 ** 4 - 1
a = 0
b = 7
G = (0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798,
     0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8)
n = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        if other is None:
            return self

        if self.x == other.x and self.y == other.y:
            lambd = (3 * self.x ** 2 + a) * pow(2 * self.y, p - 2, p) % p
        else:
            lambd = (other.y - self.y) * pow(other.x - self.x, p - 2, p) % p

        x = (lambd ** 2 - self.x - other.x) % p
        y = (lambd * (self.x - x) - self.y) % p
        return Point(x, y)

    def __mul__(self, n):
        if n == 0:
            return None

        Q = self
        R = None
        while n:
            if n & 1:
                R = R + Q if R else Q
            Q = Q + Q
            n //= 2
        return R

def generate_keys():
    private_key = random.randint(1, n - 1)
    public_key = Point(*G) * private_key
    return private_key, public_key

def encrypt(message, public_key):
    encrypted = b''
    k = random.randint(1, n - 1)
    R = Point(*G) * k
    for byte in message:
        m = Point(byte, 0)
        S = public_key * k
        c_x = (m.x + S.x) % p
        c_y = (m.y + S.y) % p
        encrypted += c_x.to_bytes(32, byteorder='big') + c_y.to_bytes(32, byteorder='big')
    return R, encrypted


# Дешифрование
def decrypt(R, encrypted, private_key):
    decrypted = b''
    for i in range(0, len(encrypted), 64):
        c_x = int.from_bytes(encrypted[i:i + 32], byteorder='big')
        c_y = int.from_bytes(encrypted[i + 32:i + 64], byteorder='big')
        c = Point(c_x, c_y)
        S = R * private_key
        m_x = (c.x - S.x) % p
        m_y = (c.y - S.y) % p
        m = Point(m_x, m_y)
        decrypted += bytes([m.x])
    return decrypted.decode('utf-8')


# Пример использования
plaintext = ('Привет, мир! Hello world 1234 !@#$ Добрый вечер, добрый день  вечер, добрый день  вечер, добрый день Добрый вечер, '
             'добрый день  вечер, добрый день  вечер, добрый день ')
private_key, public_key = generate_keys()
R, ciphertext = encrypt(plaintext.encode('utf-8'), public_key)
decrypted = decrypt(R, ciphertext, private_key)
print(f'Открытый ключ: {public_key.x}, {public_key.y}')
print(f'Закрытый ключ: {private_key}')
print(
    f'Зашифрованное сообщение: {binascii.hexlify(R.x.to_bytes(32, byteorder="big") + R.y.to_bytes(32, byteorder="big") + ciphertext)}')
print(f'Расшифрованное сообщение: {decrypted}')