#include "adminwidgetdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdminWidgetDemo* w = new AdminWidgetDemo;
    QList<QString> userName;
    QList<QString> password;
//    QList<int> permission={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    userName<<"Mary"<<"Mike"<<"Jack"<<"Alice"<<"Rose"<<"Jane"<<"Apple"<<"Orange"<<"Peach"<<"Tree";
    userName<<"Mary2"<<"Mike2"<<"Jack2"<<"Alice2"<<"Rose2"<<"Jane2"<<"Apple2"<<"Orange2"<<"Peach2"<<"Tree2";
    password<<"123"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456";
    password<<"123"<<"111"<<"222"<<"333"<<"434"<<"555"<<"666"<<"777"<<"888"<<"999";
    w->DisplayUserInfo(userName,password);
    w->show();
    return a.exec();
}
