#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonOK,SIGNAL(clicked()),this,SLOT(show_exe()));



    //connect(ui->pushButtonCancel,SIGNAL(clicked()),this,SLOT(show_draw()));


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::show_exe()
{
    /*QProcess process;
    process.execute("D:\\work\\USR-TCP232-Test.exe");
    //阻塞方式调用*/
    //非阻塞方式调用
    QProcess::startDetached("D:\\work\\USR-TCP232-Test.exe",QStringList());
}

void Dialog::show_draw()
{



}

void Dialog::on_pushButtonClose_clicked()
{
    Dialog_draw1 = new Dialog_draw;
    Dialog_draw1->show();
}

void Dialog::on_pushButtonCancel_clicked()
{
    Dialog_html1 = new Dialog_html;
    Dialog_html1->show();
}


void Dialog::on_pushButtonExcel_clicked()
{
    showexcel = new Dialog_showexcel;
    showexcel->show();
}

void Dialog::on_pushButtonOK_clicked()
{

}

void Dialog::on_pushButton_para_clicked()
{
    showpara = new Dialog_parameter;
    showpara->show();
}
