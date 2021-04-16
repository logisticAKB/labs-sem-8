//
// Created by alexey on 16.04.2021.
//

#ifndef LAB2_MAINWINDOW_H
#define LAB2_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void generatePublicKeyState();

    void encrypt();
    void decrypt();

    void bruteForcePublicKey();
    void bruteForcePrivateKey();

private:
    Ui::MainWindow *ui;

};


#endif //LAB2_MAINWINDOW_H
