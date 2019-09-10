#include "dialog_excel.h"
#include "ui_dialog_excel.h"

#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include <winnt.h>

Dialog_excel::Dialog_excel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_excel)
{
    ui->setupUi(this);

}

Dialog_excel::~Dialog_excel()
{
    delete ui;
}


