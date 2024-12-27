#include <stdio.h>
/* Using Big Number library provided by openssl*/
#include <openssl/bn.h>
#define NBITS 256
void printBN(char *msg, BIGNUM *a)
{
    /* Use BN_bn2hex(a) for hex string
* Use BN_bn2dec(a) for decimal string */
    char *number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}
    int main()
    {
        BN_CTX *ctx = BN_CTX_new(); // Context
        BIGNUM *m = BN_new();   //  Plaintext
        BIGNUM *e = BN_new();   //  Alice's Public Key
        BIGNUM *n = BN_new();   //  Alice's Modulus (part of public key)
        BIGNUM *d = BN_new();   //  Alice's Private Key
        BIGNUM *enc = BN_new(); //  Encrypted Message
        BIGNUM *dec = BN_new(); //  Decrypted Message
        BIGNUM *enc_key = BN_new(); //  Encryption Key
        BIGNUM *dec_key = BN_new(); //  Decryption Key
        BIGNUM *hash = BN_new();    //  SHA256 hash of the message
        BIGNUM *signature = BN_new();   //  The RSA signature

        // Initialize e,n,d
        //e is used as public key
        //n is modulus
        //d is used as private key
        BN_hex2bn(&e, "010001");
        BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
        BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
        
        //Uncomment next line and Initialize plaintext m (in hex) if needed
        // BN_hex2bn(&m, "");
    
        //Uncomment next line and Initialize encrypted text (ciphertext) enc if needed
        //BN_hex2bn(&enc, "");


        //  DOCUMENTATION. DO NOT UNCOMMENT THIS BLOCK
        //  Encryption Formula: 
        //  Encrypted Message = Plaintext ^ Encryption Key mod Modulus
        //  enc = m ^ enc_key mod n


        //Uncomment next 3 lines and Initialize the encryption key based on the task
        enc_key = ;
        BN_mod_exp(enc,m,enc_key,n,ctx);
        printBN("Encrypted message = ", enc);


        //  DOCUMENTATION. DO NOT UNCOMMENT THIS BLOCK
        //  Decryption Formula:
        //  Decrypted Message = Encrypted Message ^ Decryption Key mod Modulus 
        //  dec = enc ^ dec_key mod n


        //Uncomment next 3 lines and Initialize the decryption key based on the task
        //dec_key = ;
        //BN_mod_exp(dec,enc,dec_key,n,ctx);
        //printBN("Decrypted message = ", dec);


        //  DOCUMENTATION. DO NOT UNCOMMENT THIS BLOCK
        //  RSA Signature Formula:
        //  Signature = Hashed Message ^ Private Key mod Modulus
        //  signature = hash ^ d mod n


        //Uncomment next 3 lines to Sign a message with Alice's Private Key
        //BN_hex2bn(&hash, "insert_hash_value_of_the_message_here");
        //BN_mod_exp(signature, hash, d, n, ctx);
        //printBN("Signature: ", signature);


        //  DOCUMENTATION. DO NOT UNCOMMENT THIS BLOCK
        //  RSA Signature Verification Formula:
        //  Plaintext (in hex) = Signature ^ Public Key mod Modulus
        //  m = signature ^ e mod n


        //Uncomment thi block to Verify the signature of Alice using their Public Key
        BN_hex2bn(&hash, "insert_hash_value_of_the_message_here");
        BN_hex2bn(&signature, "signature_given_in_task_4");
        BN_mod_exp(m, signature, e, n, ctx);
        printBN("Recovered hash from signature (in hex):", m);
        // To compare the recovered hash (m) with the expected hash
        if (BN_cmp(m, hash) == 0) {
            printf("Signature is verified.\n");
        } else {
            printf("Signature verification failed.\n");
        }

        
        
        
        
        //  Free allocated memory
        // BN_free(d);
        // BN_free(m);
        // BN_free(e);
        // BN_free(n);
        // BN_free(enc);
        // BN_free(enc_key);
        // BN_free(dec);
        // BN_free(dec_key);
        // BN_free(hash);
        // BN_free(signature);
        // BN_CTX_free(ctx);
        return 0;
    }
