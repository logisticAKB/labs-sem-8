//
// Created by alexey on 14.04.2021.
//

#ifndef LAB1_MAINWINDOW_H
#define LAB1_MAINWINDOW_H

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
    void generateCertificate();
    void enablePassword();
    void openFileManager();

private:
    Ui::MainWindow *ui;

};


#endif //LAB1_MAINWINDOW_H
