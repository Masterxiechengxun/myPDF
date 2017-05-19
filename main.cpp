#include "mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog l;
    l.setWindowTitle("MyPDFSYS");
    l.setWindowIcon(QIcon(":/images/mdragon"));
    if(l.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
        return 0;
}
