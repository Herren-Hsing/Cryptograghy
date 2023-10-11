import random

num_strings = 8000
string_length = 16

fixed_string = "00111010100101001101011000111111"

def generate_random_string(length):
    return ''.join(random.choice('01') for _ in range(length))

with open("plain.txt", "w") as file:
    for _ in range(num_strings):
        random_string = generate_random_string(string_length)
        file.write(random_string + "\n")
        file.write(fixed_string + "\n")