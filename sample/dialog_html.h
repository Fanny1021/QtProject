#ifndef DIALOG_HTML_H
#define DIALOG_HTML_H

#include <QDialog>
#include <QWebEngineView>
namespace Ui {
class Dialog_html;
}

class Dialog_html : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_html(QWidget *parent = 0);
    ~Dialog_html();

private:
    Ui::Dialog_html *ui;
    QWebEngineView* view;
};

#endif // DIALOG_HTML_H
