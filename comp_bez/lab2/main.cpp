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



//    auto key = Cipher::generateKeys();
//
//    printf("mod = %f, public = %f, private = %f\n", key.mod,
//                                                            key.publicKey,
//                                                            key.privateKey);
//
//    int msg = 54634623;
//    auto encMsg = Cipher::encryptLongMessage(msg, key.publicKey, key.mod);
//    double decMsg = Cipher::decryptLongMessage(encMsg, key.privateKey, key.mod);
//    std::cout << (int)decMsg << std::endl;
//
//    std::string bs = "1001110011100111001";
//    std::vector<bool> b(bs.length());
//    for (int i = 0; i < bs.length(); ++i) {
//        if (bs[i] == '1') b[i] = true;
//        else b[i] = false;
//    }
//    auto p = b.begin()._M_p;
//    std::cout << *p << std::endl;

//    int x = 321337;
////    std::bitset<std::numeric_limits<int>::digits> b(x);
//    std::bitset<std::numeric_limits<int>::digits> b(bs);
//    std::cout << b.to_string() << std::endl;
