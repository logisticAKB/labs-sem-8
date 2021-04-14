//
// Created by alexey on 14.04.2021.
//

#include <QFileDialog>
#include <QMessageBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CertificateGenerator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->encryptKey, &QCheckBox::stateChanged, this, &MainWindow::enablePassword);
    connect(ui->saveToButton, &QPushButton::clicked, this, &MainWindow::openFileManager);
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateCertificate);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::enablePassword() {
    if (ui->encryptKey->isChecked()) {
        ui->passwordLabel->setEnabled(true);
        ui->password->setEnabled(true);
    } else {
        ui->passwordLabel->setEnabled(false);
        ui->password->setEnabled(false);
    }
}

void MainWindow::openFileManager() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    if (dialog.exec()) {
        QString path = dialog.selectedFiles()[0];
        ui->savePath->setText(path);
    }
}

void MainWindow::generateCertificate() {
    CertificateGenerator generator(ui->rsaBits->value(),
                                   ui->days->value(),
                                   ui->encryptKey->isChecked(),
                                   ui->countryCode->text().toStdString(),
                                   ui->organization->text().toStdString(),
                                   ui->commonName->text().toStdString(),
                                   ui->savePath->text().toStdString(),
                                   ui->password->text().toStdString());
    if (ui->certType->currentText() == "Self-signed certificate") {
        generator.generateSelfSignedCert();
    } else {
        generator.generateCertRequest();
    }
    generator.saveAll();

    QMessageBox messageBox;
    messageBox.setWindowTitle("Success");
    messageBox.setText("The certificate has been created.");
    messageBox.exec();
}
