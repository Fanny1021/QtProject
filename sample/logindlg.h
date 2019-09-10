#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include "databasedata.h"

namespace Ui {
class logindlg;
}

class logindlg : public QDialog
{
    Q_OBJECT

public:
    explicit logindlg(QWidget *parent = 0);
    ~logindlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::logindlg *ui;
};

#endif // LOGINDLG_H
