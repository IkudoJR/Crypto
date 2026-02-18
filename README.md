# Crypto
## ⚠️ Disclaimer
**This project is for educational purposes and cybersecurity research only.**

The code provided here is a Proof of Concept (PoC) demonstrating how encryption and obfuscation techniques work at a low level. It is intended to help security professionals understand malware behavior to build better defenses.

**The author is not responsible for any misuse of this software.** Do not use this code on systems you do not own or have explicit permission to test.

This is a PoC of a ransomware using assembly and C++
can be easily modified with any other encryption/decryption algorithm.

It uses C++ for file management and manipulation, a makefile to make editing
and modifying easier. It works mainly on Linux OS, but it can be easily
modified to work on Windows.

I saw that the “XOR” encryption was the easiest one, so I decided to
work on it and change it later if needed. I tried to do the file
management with assembly, but it was hard and didn’t work. 

Since I was familiar with C++, having done 150+ solutions
I decided to do the file management with it.
So, I worked on “Crypto”.

Crypto encrypts a directory and its contents using XOR.
In Linux using “/” as the targeted directory makes the code work on everything.
Permissions are the only limitation, and I didn’t want to change that.
If it had all the privileges, it would also encrypt system files, potentially
ruining the OS completely, which would defeat the goal of a ransomware.

## Technical Details
- **Language:** C++ & Assembly
- **Encryption:** Custom XOR-based algorithm
- **Target OS:** Windows & Linux

## Files Explanation
**C++ code:**
First, it declares the assembly (crypto function) to use it later.
Then, it creates a function to encrypt/decrypt a single file.
It gets the size of the file for faster memory allocation, stores the content
and calls the encryption/decryption function from the assembly code to XOR the content.
After that, it overwrites the file with the encrypted/decrypted content.
Next, it creates a function to encrypt/decrypt a directory.
This function finds the directory by its name, applies error handling
and uses the function created above to XOR each file in the directory recursively.
The main function allows us to modify the file path and key
and then calls the directory encryption/decryption function.

**Assembly code:**
First, it declares the function globally so it can be linked.
It checks if the length is zero and jumps to "done" if true.
Then it checks if the buffer has fewer than 8 bytes
in which case it jumps to the single encryption function.
The buffer is loaded and XOR-ed, then replaced.
The pointer is moved, the length is decreased, and the process loops.
The small loop function is designed to handle cases where fewer than 8
bytes remain in memory. It XORs the data byte by byte.

**Makefile:**
It is a simple makefile that I made to make debugging easier and is well
explained in the code itself.

## Workflow Summary
1.  **Initialize:** Define the target directory path and the XOR key in `main.cpp`.
2.  **Scan:** The C++ logic recursively identifies all files within the target directory.
3.  **Process:** Each file is loaded into memory; the C++ wrapper passes the memory pointer and file length to the Assembly engine.
4.  **Transform:** The Assembly engine XORs the content in place.
5.  **Finalize:** C++ overwrites the original file with the transformed data.

**Technical Note:** This PoC is modular. The XOR logic in the `.asm` file can be swapped for more complex algorithms (like AES) without modifying the C++ file management layer.
