from SHA_1 import SHA_1
from GOST_34_11 import GOST_34_11

res = SHA_1("Hellow world 1234 !@#$%^&*(")
assert res == "9a5005690dc9db028b6b1012ef9f9214d3f13f4e"
print(res)

res = SHA_1("")
assert res == "da39a3ee5e6b4b0d3255bfef95601890afd80709"
print(res)

print(GOST_34_11("Hellow world 1234 !@#$%^&*(", '00'.zfill(256)))

print(GOST_34_11("", '00'.zfill(256)))