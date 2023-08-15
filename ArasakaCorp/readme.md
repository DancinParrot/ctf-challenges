# Arasaka Corp

Author: Kai Zhe

Date Created/Modified: 31/10/2022

Flag: LNC2023{aR@sA$@_c0rP_D0wNF@LL_2@89}

## Description
The Arasaka Corporation, one of the most influential multinational conglomerate that deals in a lot of stuff, including some very shady stuff. Get into their mainframe, expose their unethical practices to the international community and bust their business!

## Hints
1. Arasaka Crop's financial statements show that they have a huge buffer of assets and are overflowing in cash!
2. Wait, what is wrong with their string formatting?

## Distribution
These are the files that will be sent to the participants
- ArasakaCorp
    - SHA1: `d6c024860e2c2b40c41eb94ec5161a5e8d10c6c9`

## Solution
The solution will be split into 3 parts: Static Analysis, Buffer Overflow, and Format String Exploit.

### Static Analysis
1. You may use checksec, readelf, and file cli-tools to have a brief overview of the ELF executable and verifiy that it has no PIE, no canary, so no stack protection whatsoever, and that it's 64-bit (important to consider the architecture when crafting payload).
2. Fire up Ghidra and use it to open and analyze the binaries of the ELF executable
3. Use Ghidra to go through the source code and notice the a few interesting parts, the hidden dev() function, the seemingly-innocent auth global variable, as well as the `printf(password)` function that lacks a format string specifier and an insecure gets() function used. Thus, forming the hypothesis of a potential buffer overflow and format string vulnerability.

### Buffer Overflow
1. Execute readelf -s ./ArasakaCorp and note down the addresses of dev() and the auth global variable, you can use grep here.
2. As seen in the first section of the `exploit.py` file, put some padding (16 'A's) and there will be a segfault, indicating that the offset we need is 16, and then after which, append the address of dev() function.
3. `p.sendline(payload1)` and you will have access to the secret function.

### Format String Exploitation
1. This is a bit tricky to describe in words, so I highly recommend you to watch this video by [LiveOverflow](https://youtu.be/_lO_rwaK_pY) instead where he demos the difference between working with a 32-bit and 64-bit executables as well. 
2. Basically, use some wrappers that are easily identifiable in hex, such as A (0x41) or B (0x42) and so forth, to wrap the payload within.
3. The payload will contain format string operators such as %p or %x which are used to leak memory addresses off the stack, and by appending the address of the auth variable, you should see its address being reflected as an output. 
4. However, you don't. This is because of the fact that the prinft() function terminates on null bytes, and thus the rest of the output is not shown. To solve this, shift the address of the auth global variable to the end of the payload.
5. After which, shorten the padding of the payload such that the address of the auth global variable is exactly the last one.
6. With that, you may write arbitrary values using the operator, "%n" and use it in this format "%offset$n" to write to a specific position.

Finally, execute the second payload, and you should get access to the shell and view the flag using `cat flag`.

Notes (FYI):
- Apparently, the OS you use matters! Since the payload was crafted on Kali Linux, but was instead deployed on an Ubuntu docker container, the payload crashes the program with the error, "Got EOF while in interactive".
- As Kali Linux is based on Debian, the payload is deployed on Debian instead as a workaround.
- ynetd doesn't output stderr, hence on Docker doesn't show Seg Fault error message.

## Deployment Guide
1. Build docker image by cd into `./service` then run `docker build -t image-name . `
2. Run docker image at port 8085 with `docker run -d -p 8085:8085 image-name`
3. nc ip-address 8085
4. Execute payload and you're in!

You may compile the binary with the following command:
`gcc main.c -o ArasakaCorp -no-pie -fno-stack-protector`

## Docker Guide
1. List existing containers `docker container ls`
2. Stop container `docker stop container-id`
3. Remove container `docker rm container-id`

## Extra
Here's another interesting and simpler [solution](https://github.com/duckupus/ctf-writeups/blob/main/LNC%203.0/Pwn/Arasaka%20Corp/README.md) by [@duckupus](https://github.com/duckupus)
