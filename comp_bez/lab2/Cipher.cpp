//
// Created by alexey on 16.04.2021.
//

#include <random>
#include <chrono>
#include <cmath>
#include <iostream>

#include "Cipher.h"

std::vector<int> Cipher::generatePrimeNumbers() {
    int n = 100;
    std::vector<bool> isPrime(true, n + 1);
    
    for (int i = 2; i*i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i*i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::vector<int> primeNumbers;
    for (int i = 30; i < n + 1; ++i) {
        if (isPrime[i]) primeNumbers.push_back(i);
    }
    return primeNumbers;
}

Cipher::keys Cipher::generateKeys() {
    std::vector<int> primeNumbers = generatePrimeNumbers();

    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dis1(0, primeNumbers.size() - 1);

    int p = primeNumbers[dis1(gen)];
    int q = primeNumbers[dis1(gen)];

    int mod = p * q;
    int phi = (p - 1)*(q - 1);

    int publicKey = 2;
    while (publicKey < phi) {
        if (std::gcd((int)publicKey, (int)phi) == 1) break;
        else publicKey++;
    }

    double candidateKey, intPart;
    int x = 1;
    while (true) {
        candidateKey = (1 + x * phi) / (double)publicKey;
        if (modf(candidateKey, &intPart) == 0.0) break;
        x++;
    }
    int privateKey = (int)candidateKey;

    return Cipher::keys{mod, publicKey, privateKey};
}

int Cipher::encryptMessage(int msg, int publicKey, int mod) {
    int encryptedMsg = msg % mod;
    int first = msg % mod;
    for (int i = 0; i < publicKey - 1; ++i) {
        encryptedMsg = (encryptedMsg * first) % mod;
    }

    return encryptedMsg;
}

int Cipher::decryptMessage(int msg, int privateKey, int mod) {
    int decryptedMsg = msg % mod;
    int first = msg % mod;
    for (int i = 0; i < privateKey - 1; ++i) {
        decryptedMsg = (decryptedMsg * first) % mod;
    }

    return decryptedMsg;
}

int Cipher::encryptLongMessage(int msg, int publicKey, int mod) {
    return (msg / (mod - 1)) * encryptMessage(mod - 1, publicKey, mod) +
            encryptMessage(msg - (mod - 1) * (msg / (mod - 1)), publicKey, mod);
}

int Cipher::decryptLongMessage(int msg, int privateKey, int mod) {
    return (msg / (mod - 1)) * decryptMessage(mod - 1, privateKey, mod) +
            decryptMessage(msg - (mod - 1) * (msg / (mod - 1)), privateKey, mod);
}

int Cipher::bruteForcePublicKey(int msg, int encryptedMsg, int mod) {
    int publicKey = 1;
    while (true) {
        if (encryptLongMessage(msg, publicKey, mod) == encryptedMsg) {
            break;
        }
        publicKey += 1;
    }

    return publicKey;
}

int Cipher::bruteForcePrivateKey(int encryptedMsg, int decryptedMsg, int mod) {
    int privateKey = 1;
    while (true) {
        if (decryptLongMessage(encryptedMsg, privateKey, mod) == decryptedMsg) {
            break;
        }
        privateKey += 1;
    }

    return privateKey;
}
