#ifndef DIALOG_DRAW_H
#define DIALOG_DRAW_H

#include <QDialog>

namespace Ui {
class Dialog_draw;
}

class Dialog_draw : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_draw(QWidget *parent = 0);
    ~Dialog_draw();

private:
    Ui::Dialog_draw *ui;
};

#endif // DIALOG_DRAW_H
