#include "dialog_parameter.h"
#include "ui_dialog_parameter.h"

Dialog_parameter::Dialog_parameter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_parameter)
{
    ui->setupUi(this);
    //获取系统日期
    QDateTime sysTime = QDateTime::currentDateTime();
    QStringList list = sysTime.toString("yyyy-MM-dd").split('-');
    ui->dateEdit->setDate(QDate(list[0].toInt(),list[1].toInt(), list[2].toInt()));
    ui->dateEdit->setMinimumDate(QDate::currentDate().addDays(-365));  // -365天
    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(365));  // +365天
    ui->dateEdit->setCalendarPopup(true);  // 日历弹出

}

Dialog_parameter::~Dialog_parameter()
{
    delete ui;
}
