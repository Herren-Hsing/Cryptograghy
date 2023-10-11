with open('plain.txt', 'r') as plain_file, open('cipher.txt', 'r') as cipher_file:
    plain_lines = plain_file.readlines()  
    cipher_lines = cipher_file.readlines() 

with open('input.txt', 'w') as output_file:
    if len(plain_lines) < len(cipher_lines) * 2:
        raise ValueError("plain.txt 中的行数不足以与 cipher.txt 的行数匹配")

        
        output_file.write(plain_lines[i]) 
        output_file.write(cipher_lines[i // 2])  
        output_file.write('\n') 