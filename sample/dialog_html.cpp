#include "dialog_html.h"
#include "ui_dialog_html.h"

Dialog_html::Dialog_html(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_html)
{
    ui->setupUi(this);
    view = new QWebEngineView(this);
    view->load(QUrl("http://www.baidu.com/"));
    view->show();
}

Dialog_html::~Dialog_html()
{
    delete ui;
}
