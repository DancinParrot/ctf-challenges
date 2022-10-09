*Creator - Kai Zhe*

## Description
Grant Ward was accused of being a part of Hydra, an authoritarian paramilitary-subversive terrorist organization bent on world domination (in
the Marvel Universe). As a result, his personal belongings, including a laptop and a thumbdrive which were presumably, used to store Hydra's upcoming 
secret masterplan. It was revealed after the relevant authorities interrogated Ward, that Ironman may be targeted in this upcoming attack. 
Hence, as the world's best digital forensics investigor, you are tasked to ascertain the details of Hydra's secretplans. A memory dump of his laptop
as well as a copy of his thumbdrive were provided. 

## Hints (Optional)
1. Grant Ward seems to have an obsession with images of keys...
1. That's weird, why is the memory dump so large in size, as compared to others...

## Setup Guide (Optional)
Use Volatility to find the encrypted container and keyfile.
Use TrueCrypt for accessing the secret container.

## Solution
1. Use volatility to determine secret file (or by size) and key file.
2. Mount .img file.
3. Secret file: MEMDUMP1, Key file: stickman-drawn.png .
4. User image stegno decoder for key file (a.k.a sickman-drawn.png) to determine password.
5. Mount secret container with Truecrypt and decrypt with password.
6. Decode Base64 of the string found in secretLNC text file for the flag.

## Flag
LNC2022{aLl_H4iL_HyDrA_sH0rt_St3rKCoRp_c411s}

Pass for truecrypt container: @pesTogethe3Stronk%