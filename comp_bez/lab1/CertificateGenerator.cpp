//
// Created by alexey on 14.04.2021.
//

#include "CertificateGenerator.h"

#include <utility>

CertificateGenerator::CertificateGenerator(int nRSABits,
                                           long days,
                                           bool encryptKey,
                                           std::string countryCode,
                                           std::string organization,
                                           std::string commonName,
                                           std::string path,
                                           std::string password) {
    this->nBits = nRSABits;
    this->days = days;
    this->encryptKey = encryptKey;
    this->countryCode = std::move(countryCode);
    this->organization = std::move(organization);
    this->commonName = std::move(commonName);
    this->path = std::move(path);
    this->password = std::move(password);

    this->generateRSAKey();
}

CertificateGenerator::~CertificateGenerator() {
    EVP_PKEY_free(pkey);
    if (x509 != nullptr) X509_free(x509);
    if (x509Req != nullptr) X509_REQ_free(x509Req);
}

void CertificateGenerator::generateRSAKey() {
//    rsa = RSA_new();
//    RSA_generate_key_ex(rsa, nBits, nullptr, nullptr);
    rsa = RSA_generate_key(nBits, RSA_F4, nullptr, nullptr);

    pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, rsa);
}

void CertificateGenerator::generateSelfSignedCert() {
    x509 = X509_new();

    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), 60 * 60 * 24 * days);

    X509_set_pubkey(x509, pkey);

    X509_NAME *name = X509_get_subject_name(x509);

    X509_NAME_add_entry_by_txt(name, "C",  MBSTRING_ASC, (unsigned char *)countryCode.data(),        -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O",  MBSTRING_ASC, (unsigned char *)organization.data(), -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)commonName.data(), -1, -1, 0);

    X509_set_issuer_name(x509, name);

    X509_sign(x509, pkey, EVP_sha1());
}

void CertificateGenerator::generateCertRequest() {
    x509Req = X509_REQ_new();

    X509_REQ_set_version(x509Req, 1);

    X509_NAME *name = X509_REQ_get_subject_name(x509Req);

    X509_NAME_add_entry_by_txt(name, "C",  MBSTRING_ASC, (unsigned char *)countryCode.data(),        -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O",  MBSTRING_ASC, (unsigned char *)organization.data(), -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)commonName.data(), -1, -1, 0);

    X509_REQ_set_pubkey(x509Req, pkey);

    X509_REQ_sign(x509Req, pkey, EVP_sha1());
}

void CertificateGenerator::saveAll() {
    FILE *f;
    std::string keyPath = path + "/key.pem";
    f = fopen(keyPath.data(), "wb");
    if (encryptKey) {
        PEM_write_PrivateKey(f,
                             pkey,
                             EVP_des_ede3_cbc(),
                             (unsigned char *)password.data(),
                             password.length(),
                             nullptr,
                             nullptr);
    } else {
        PEM_write_PrivateKey(f,
                             pkey,
                             nullptr,
                             nullptr,
                             0,
                             nullptr,
                             nullptr);
    }
    fclose(f);

    if (x509 != nullptr) {
        FILE *fx509;
        std::string certPath = path + "/cert.pem";
        fx509 = fopen(certPath.data(), "wb");
        PEM_write_X509(fx509, x509);
        fclose(fx509);
    }

    if (x509Req != nullptr) {
        FILE *fx509Req;
        std::string certReqPath = path + "/certReq.pem";
        fx509Req = fopen(certReqPath.data(), "wb");
        PEM_write_X509_REQ(fx509Req, x509Req);
        fclose(fx509Req);
    }
}
