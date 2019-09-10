#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QProcess>
#include"dialog_draw.h"
#include"dialog_html.h"
#include"dialog_showexcel.h"
#include"dialog_parameter.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    Dialog_draw *Dialog_draw1;
    Dialog_html *Dialog_html1;
    Dialog_showexcel *showexcel;
    Dialog_parameter *showpara;
public slots:
    void show_exe();
    void show_draw();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonExcel_clicked();

    void on_pushButtonOK_clicked();

    void on_pushButton_para_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
