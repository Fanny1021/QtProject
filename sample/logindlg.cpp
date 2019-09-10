#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>

logindlg::logindlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindlg)
{
    ui->setupUi(this);
}

logindlg::~logindlg()
{
    delete ui;
}

void logindlg::on_pushButton_clicked()
{
    //连接数据库
    DatabaseData database;
    //判断用户名和密码是否正确
    //如果错误则弹出警告对话框
    //读取数据库的用户名和密码
    if(database.VerificationLogin(ui->UserNameEdit->text().trimmed(), ui->PasswordEdit->text().trimmed()))//trimmed表示修剪的，去掉编辑框前面的空格ui->UserNameEdit->text().trimmed() == "admin" && ui->PasswordEdit->text() == "nengxing"
    {
        //登录成功，则触发accept函数
        accept();
        QMessageBox::warning(this,tr("warning"),tr("success"),QMessageBox::Yes);
    }
    else
    {
        //登录失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
        QMessageBox::warning(this,tr("warning"),tr("password error"),QMessageBox::Yes);
        ui->UserNameEdit->clear();//清空用户编辑框
        ui->PasswordEdit->clear();
        ui->UserNameEdit->setFocus();//设置光标到用户编辑框
    }
}
