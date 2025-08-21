// Sections: (1) Encryption, (2) Decryption, (3) Signing, (4) Verification

#include <stdio.h>
/* Using Big Number library provided by openssl*/
#include <openssl/bn.h>
#define NBITS 256

// Pretty-print a BIGNUM in hex
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
    // ---- Core RSA parameters and scratch context ----
    BN_CTX *ctx = BN_CTX_new(); // Big-number scratchpad (Context)
    BIGNUM *n = BN_new();   //  modulus (public)
    BIGNUM *e = BN_new();   //  public exponent
    BIGNUM *d = BN_new();   //  private exponent (keep secret)

    // Working variables
    BIGNUM *m = BN_new();           //  message (or recovered hash in verify)
    BIGNUM *enc = BN_new();         //  Encrypted Message (ciphertext)
    BIGNUM *dec = BN_new();         //  Decrypted Message (plaintext)
    BIGNUM *hash = BN_new();        //  SHA256 hash of the message
    BIGNUM *signature = BN_new();   //  RSA signature
    BIGNUM *enc_key = BN_new();     //  key used for encryption (usually e)
    BIGNUM *dec_key = BN_new();     //  key used for decryption (usually d)

    // ---- Load demo RSA key (Alice) ----
    // e = 0x10001, and n, d are provided as in the original file
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
    
    // =====================================================================
    // (1) ENCRYPTION: enc = m^enc_key mod n
    // ---------------------------------------------------------------------
    // TODO: Provide plaintext m as a hex number (not ASCII). For ASCII, hex-encode first.
    // Example (ASCII "42" -> hex 0x3432): BN_hex2bn(&m, "3432");
    // Or plug in your lab’s plaintext/message hash, already in hex.
    // BN_hex2bn(&m, "<HEX_MESSAGE_HERE>");
    // Choose encryption key (normally e):
    // enc_key = ;
    // BN_mod_exp(enc, m, enc_key, n, ctx);
    // printBN("Encrypted message (enc) =", enc);

    // =====================================================================
    // (2) DECRYPTION: dec = enc^dec_key mod n
    // ---------------------------------------------------------------------
    // TODO: If starting from a given ciphertext, set enc first:
    // BN_hex2bn(&enc, "<HEX_CIPHERTEXT_HERE>");
    // Choose decryption key (normally d):
    // dec_key = ;
    // BN_mod_exp(dec, enc, dec_key, n, ctx);
    // printBN("Decrypted message (dec) =", dec);

    // =====================================================================
    // (3) SIGNING: signature = hash^d mod n
    // ---------------------------------------------------------------------
    // TODO: Provide the SHA-256 (or other) message digest as hex.
    // BN_hex2bn(&hash, "<HEX_HASH_OF_MESSAGE>");
    // BN_mod_exp(signature, hash, d, n, ctx);
    // printBN("Signature =", signature);

    // =====================================================================
    // (4) VERIFICATION: recovered = signature^e mod n  (compare to expected hash)
    // ---------------------------------------------------------------------
    // TODO: Provide expected hash and a signature to verify (both hex).
    // If you just signed above, you can reuse `signature` and `hash`.
    // Otherwise, set them explicitly as below:
    // BN_hex2bn(&hash,      "<EXPECTED_HEX_HASH>");
    // BN_hex2bn(&signature, "<SIGNATURE_TO_VERIFY_HEX>");

    // Example verification scaffold (uncomment after setting hash/signature):
    // BN_mod_exp(m, signature, e, n, ctx);         // m = recovered hash
    // printBN("Recovered hash (from signature) =", m);
    // if (BN_cmp(m, hash) == 0) {
    //     printf("Signature is VERIFIED.\n");
    // } else {
    //     printf("Signature verification FAILED.\n");
    // }


    // ---- Cleanup ---- (Freeing allocated memories)
    printf("------------------------------\n-----------Disclaimer-----------\nErrors after this LINE can be ignored. Curious? ask your instructor for why!\n");
    BN_free(d);
    BN_free(m);
    BN_free(e);
    BN_free(n);
    BN_free(enc);
    BN_free(enc_key);
    BN_free(dec);
    BN_free(dec_key);
    BN_free(hash);
    BN_free(signature);
    BN_CTX_free(ctx);
    return 0;
}
