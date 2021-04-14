#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    MainWindow window;
    window.setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                           Qt::AlignCenter,
                                           window.size(),
                                           QApplication::desktop()->availableGeometry()));
    window.show();

    return QApplication::exec();
}
