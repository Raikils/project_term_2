#include "mainwindow.h"
#include "profilemenu.h"

#include <QApplication>
#include <QFile>
#include "randomgenerate.h"
#include <QDebug>
#include <QString>
#include "film.h"

int main(int argc, char *argv[])
{
    /*RandomGenerate rand;
    qDebug() << rand.randomBetween(0, 0);
    qDebug() << rand.randomBetween(0, 10);
    qDebug() << rand.randomBetween(0, 10);
    qDebug() << rand.randomBetween(0, 10);
    qDebug() << rand.randomBetween(0, 10);
    qDebug() << rand.randomBetween(0, 10);
    qDebug() << rand.randomBetween(0, 10);
    qDebug() << rand.randomBetween(0, 10);*/
    /*Film f("tt3501632");
    std::map<std::string, std::string> v = f.get_full_info();
    for (const auto& x : v) {
        qDebug() << QString::fromStdString(x.first) << " " << QString::fromStdString(x.second);
    }*/
    QApplication a(argc, argv);
     MainWindow *w = new MainWindow;
     w->show();
   return a.exec();
}
