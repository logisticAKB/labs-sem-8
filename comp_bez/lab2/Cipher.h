//
// Created by alexey on 16.04.2021.
//

#ifndef LAB2_CIPHER_H
#define LAB2_CIPHER_H

#include <vector>

class Cipher {
public:
    struct keys {
        int mod;
        int publicKey;
        int privateKey;
    };

    static keys generateKeys();

    static int encryptMessage(int msg, int publicKey, int mod);
    static int decryptMessage(int msg, int privateKey, int mod);

    static int encryptLongMessage(int msg, int publicKey, int mod);
    static int decryptLongMessage(int msg, int privateKey, int mod);

    static int bruteForcePublicKey(int msg, int encryptedMsg, int mod);
    static int bruteForcePrivateKey(int encryptedMsg, int decryptedMsg, int mod);

private:
    static std::vector<int> generatePrimeNumbers();

};


#endif //LAB2_CIPHER_H
