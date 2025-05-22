RADIX = 26

def calculate_hash(s: str, len: int) -> int:
    hash_value = 0

    for i in range(len):
        hash_value = (hash_value * RADIX) + ord(s[i])

    return hash_value

def strStr(haystack: str, needle: str) -> int:
    n = len(needle)
    m = len(haystack)

    if n > m: return -1

    hash_needle = calculate_hash(needle, n)
    hash_running = calculate_hash(haystack, n)

    if (hash_needle == hash_running) and (needle == haystack[0:n]): return 0

    MAX_POWER = RADIX**(n - 1)

    for i in range(n, len(haystack)):
        hash_running -= (MAX_POWER * ord(haystack[i - n]))
        hash_running *= RADIX
        hash_running += ord(haystack[i])

        if (hash_needle == hash_running) and (needle == haystack[i - n + 1:i + 1]):
            return i - n + 1

    return -1

print(strStr("hello", "ll"))   # Output: 2
print(strStr("aaaaa", "bba"))  # Output: -1