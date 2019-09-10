#ifndef DIALOG_SHOWEXCEL_H
#define DIALOG_SHOWEXCEL_H

#include <QDialog>
#include <qcustomplot.h>
#include <qmath.h>
#include <QTimer>
#include <QString>

#include <ActiveQt/QAxObject>
#include <QFileDialog>
namespace Ui {
class Dialog_showexcel;
}

class Dialog_showexcel : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_showexcel(QWidget *parent = 0);
    ~Dialog_showexcel();

private:
    Ui::Dialog_showexcel *ui;
    QString strVal;
    QList<QList<QVariant>> res;
    int rowCount;
    int listCount;
    int tmpRow;
    int tmpList;

//绘图变量
   double value0;
   double key;
   QString  CureName;//设置曲线名字
   QCustomPlot *customPlot;
   QCPItemText *textLabel;
   QCPItemText *textLabel2;

private slots:
  void realtimeDataSlot();
  void terminateExcel();
};

#endif // DIALOG_SHOWEXCEL_H
