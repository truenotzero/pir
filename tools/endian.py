
print("Endianness reverser tool")
while True:
    num = input(">")
    joined = "".join(num.strip().split())
    if len(joined) % 2 != 0:
        joined = '0' + joined
    
    rev = ""
    for b in (joined[pos:pos + 2] for pos in range(0, len(joined), 2)):
        rev = b + rev + ' '
    print(rev)

