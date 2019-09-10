#ifndef DIALOG_PARAMETER_H
#define DIALOG_PARAMETER_H

#include <QDialog>

namespace Ui {
class Dialog_parameter;
}

class Dialog_parameter : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_parameter(QWidget *parent = 0);
    ~Dialog_parameter();

private:
    Ui::Dialog_parameter *ui;
};

#endif // DIALOG_PARAMETER_H
