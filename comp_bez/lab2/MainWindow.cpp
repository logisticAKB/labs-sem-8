//
// Created by alexey on 16.04.2021.
//

#include <string>
#include <iostream>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Cipher.h"
#include "Binary.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    Cipher::keys key = Cipher::generateKeys();

    ui->MOD->setText(std::to_string(key.mod).data());
    ui->publicKey->setText(std::to_string(key.publicKey).data());
    ui->privateKey->setText(std::to_string(key.privateKey).data());

    connect(ui->genKeysChecker, &QCheckBox::stateChanged, this, &MainWindow::generatePublicKeyState);

    connect(ui->encryptButton, &QPushButton::clicked, this, &MainWindow::encrypt);
    connect(ui->decryptButton, &QPushButton::clicked, this, &MainWindow::decrypt);

    connect(ui->bfPublicKeyButton, &QToolButton::clicked, this, &MainWindow::bruteForcePublicKey);
    connect(ui->bfPrivateKeyButton, &QToolButton::clicked, this, &MainWindow::bruteForcePrivateKey);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::generatePublicKeyState() {
    if (ui->genKeysChecker->isChecked()) {
        ui->MOD->setEnabled(false);
        ui->publicKey->setEnabled(false);
        ui->privateKey->setEnabled(false);
        ui->bfPublicKeyButton->setEnabled(false);
        ui->bfPrivateKeyButton->setEnabled(false);

        Cipher::keys key = Cipher::generateKeys();

        ui->MOD->setText(std::to_string(key.mod).data());
        ui->publicKey->setText(std::to_string(key.publicKey).data());
        ui->privateKey->setText(std::to_string(key.privateKey).data());
    } else {
        ui->MOD->setEnabled(true);
        ui->publicKey->setEnabled(true);
        ui->privateKey->setEnabled(true);
        ui->bfPublicKeyButton->setEnabled(true);
        ui->bfPrivateKeyButton->setEnabled(true);
    }
}

//void MainWindow::encrypt() {
//    int msg = ui->message->text().toInt();
//    int publicKey = ui->publicKey->text().toInt();
//    int mod = ui->MOD->text().toInt();
//    int encryptedMsg = Cipher::encryptLongMessage(msg, publicKey, mod);
////    int encryptedMsg = Cipher::encryptMessage(msg, publicKey, mod);
//    ui->encryptedMsg->setText(std::to_string(encryptedMsg).data());
//}

void MainWindow::encrypt() {
    ui->encryptedMsg->setText(Binary::sum(ui->message->text().toStdString(), ui->publicKey->text().toStdString()).data());
}

void MainWindow::decrypt() {
    ui->decryptedMsg->setText(Binary::sum(ui->encryptedMsg->text().toStdString(), ui->publicKey->text().toStdString()).data());
}

//void MainWindow::decrypt() {
//    int msg = ui->encryptedMsg->text().toInt();
//    int privateKey = ui->privateKey->text().toInt();
//    int mod = ui->MOD->text().toInt();
//    int decryptedMsg = Cipher::decryptLongMessage(msg, privateKey, mod);
////    int decryptedMsg = Cipher::decryptMessage(msg, privateKey, mod);
//    ui->decryptedMsg->setText(std::to_string(decryptedMsg).data());
//}

//void MainWindow::bruteForcePublicKey() {
//    int msg = ui->message->text().toInt();
//    int encryptedMsg = ui->encryptedMsg->text().toInt();
//    int mod = ui->MOD->text().toInt();
//    int publicKey = Cipher::bruteForcePublicKey(msg, encryptedMsg, mod);
//    ui->publicKey->setText(std::to_string(publicKey).data());
//}

void MainWindow::bruteForcePublicKey() {
    ui->publicKey->setText(Binary::unsum(ui->encryptedMsg->text().toStdString(), ui->decryptedMsg->text().toStdString()).data());
}

//void MainWindow::bruteForcePrivateKey() {
//    int encryptedMsg = ui->encryptedMsg->text().toInt();
//    int decryptedMsg = ui->decryptedMsg->text().toInt();
//    int mod = ui->MOD->text().toInt();
//    int privateKey = Cipher::bruteForcePrivateKey(encryptedMsg, decryptedMsg, mod);
//    ui->privateKey->setText(std::to_string(privateKey).data());
//}

void MainWindow::bruteForcePrivateKey() {
    int encryptedMsg = Binary::toInt(ui->encryptedMsg->text().toStdString());
    int decryptedMsg = Binary::toInt(ui->decryptedMsg->text().toStdString());
    int mod = ui->MOD->text().toInt();
    int privateKey = Cipher::bruteForcePrivateKey(encryptedMsg, decryptedMsg, mod);
    std::string privateKeyBin = Binary::toBinaryString(privateKey);
    ui->privateKey->setText(privateKeyBin.data());
}
