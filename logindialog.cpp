#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->usrLineEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QString name,password;
    name = ui->usrLineEdit->text().trimmed();
    password = ui->pswLineEdit->text().trimmed();
    connService *conn = connService::getService();
    QString info = QString("login %1 %2").arg(name).arg(password);
    if(conn->isConnected())
    {
        conn->dataWrite(info);
        QByteArray result = conn->getBuf();
        if(static_cast<QString>(result) == "true")
        {
            usr = name;
            QDialog::accept();
            QString str = QString("%1 欢迎你！").arg(name);
            QMessageBox::about(this, tr("登录成功"), str);
            this->close();
            return;
        }
        //输入的密码或者账户错误
        QMessageBox::about(this, tr("警告"), tr("用户名或者密码错误！"));
        ui->usrLineEdit->clear();
        ui->pswLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}

void LoginDialog::on_forgetBtn_clicked()
{

}

void LoginDialog::on_registBtn_clicked()
{
    connService *conn = connService::getService();
    if(conn->isConnected())
    {
        RegisterDialog r(this);
        if(r.exec() == QDialog::Accepted)
        {
            ui->usrLineEdit->setFocus();
        }
    }
}

void LoginDialog::on_guestBtn_clicked()
{
    usr = tr("Guest");
    QDialog::accept();
    this->close();
}
