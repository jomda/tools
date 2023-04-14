#include "MainWindow.h"
#include <QApplication>
#include <QtCore>

#define CHARACTER_SETS           "utf-8"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName(CHARACTER_SETS));
    QTextCodec::setCodecForTr(QTextCodec::codecForName(CHARACTER_SETS));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(CHARACTER_SETS));
    
    MainWindow w;
    w.show();

    return a.exec();
}
