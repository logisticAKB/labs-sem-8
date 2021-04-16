//
// Created by alexey on 14.04.2021.
//

#ifndef LAB1_CERTIFICATEGENERATOR_H
#define LAB1_CERTIFICATEGENERATOR_H

#include <string>

#include <openssl/pem.h>
#include <openssl/x509.h>

class CertificateGenerator {
public:
    explicit CertificateGenerator(int nRSABits,
                                  long days,
                                  bool encryptKey,
                                  std::string countryCode,
                                  std::string organization,
                                  std::string commonName,
                                  std::string path,
                                  std::string password);
    ~CertificateGenerator();

    void generateCertRequest();
    void generateSelfSignedCert();
    void saveAll();

private:
    void generateRSAKey();

    int nBits;
    long days;
    bool encryptKey;
    std::string countryCode, organization, commonName;
    std::string path, password;

    RSA *rsa = nullptr;
    EVP_PKEY *pkey = nullptr;
    X509 *x509 = nullptr;
    X509_REQ *x509Req = nullptr;
};


#endif //LAB1_CERTIFICATEGENERATOR_H
