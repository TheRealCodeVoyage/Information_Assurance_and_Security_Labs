# Assignment 2 – MD5 Collision Attack

_Note: This is an individual assignment._

The collision-resistance property ensures that it is computationally infeasible to find two different inputs `M1` and `M2`, such that `hash(M1) = hash(M2)`. Collision-resistance is an essential property for one-way hash functions, but several widely used one-way hash functions (e.g. _MD5_ and _SHA-1_) have trouble maintaining this property. In this lab, you will launch actual collision attacks against the MD5 hash function.

Follow instructions for Task 1 from SEED Project [seedsecuritylabs.org/Labs_20.04/Crypto/Crypto_MD5_Collision](https://seedsecuritylabs.org/Labs_20.04/Crypto/Crypto_MD5_Collision) on your SEED VM.

Note: It’s recommended that you install SEED Virtual Machine which contains md5collgen program; BUT if you decided to complete the assignment on any other Linux such as kali you must install the `md5collgen` first.
The repo of md5collgen can be found here: [https://github.com/zhijieshi/md5collgen](https://github.com/zhijieshi/md5collgen)

Note: the bytes in the instructions refer to the number of characters in the prefix file 
We will be using a program called `md5collgen` to generate two different files (given a common prefix file) with the same hash value. The program should be installed on the VM already, if not download it from the lab webpage 

Take screenshots of your code snippets and important results. Explain your observations. 

Answer the _questions in the SEED lab instructions_ as well as _the following questions_:

1.	By providing a scenario, explain why using MD5 for digital signatures is not a strong defense against non-repudiation attacks. 
2.	Code signing is the process of digitally signing executables and scripts to confirm the software author and guarantee that the code has not been altered or corrupted since it was signed. Imagine Adam has published a program along with its MD5 hash on a trusted website where his code is verified. Explain how he can release a malicious version of this program and trick users to trust it. 
3.	Which hash algorithms are vulnerable to collision attacks? 
4.	What hash algorithms are safe to use?
 
## Submission: 
Submit your report, with the screenshots and answers to the questions above, to the Assignment 2 on the Learning Hub before the deadline mentioned there. 
