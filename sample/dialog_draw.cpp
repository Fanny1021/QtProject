#include "dialog_draw.h"
#include "ui_dialog_draw.h"

Dialog_draw::Dialog_draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_draw)
{
    ui->setupUi(this);
    ui->widget->xAxis->setRange(-8, 8);//x轴范围
    ui->widget->yAxis->setRange(-8, 8);//y轴范围
    ui->widget->xAxis->setLabel("x Axis");//设置x轴名称
    ui->widget->yAxis->setLabel("y Axis");//设置y轴名称
    ui->widget->legend->setVisible(true);//设置每条曲线的说明可见,默认为不可见

    QFont legendFont = font();
    legendFont.setPointSize(10);//曲线说明的字体大小

    ui->widget->legend->setFont(legendFont);//使字体设置生效

    QVector<double> x1(10),y1(10),x2(10),y2(10),x3(10),y3(10),x4(10),y4(10);
    for(int i=0;i<10;i++)
    {
        x1[i]=i-5;
        y1[i]=x1[i];
        x2[i]=x1[i];
        y2[i]=y1[i]+1;
        x3[i]=x1[i]/2;
        y3[i]=pow(x3[i],2);
        x4[i]=x1[i]+0.5;
        y4[i]=x4[i]*2;
    }

    ui->widget->addGraph();//画曲线
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();

    ui->widget->graph(0)->setName(QString("test graph 1"));//给曲线命名
    ui->widget->graph(1)->setName("test Graph 2");
    ui->widget->graph(2)->setName(QString("test graph 3"));
    ui->widget->graph(3)->setName(QString("test graph 4"));

    ui->widget->graph(0)->setData(x1, y1);
    ui->widget->graph(1)->setData(x2, y2);
    ui->widget->graph(2)->setData(x3, y3);
    ui->widget->graph(3)->setData(x4, y4);


    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(2)));
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(4)));
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(6)));
    ui->widget->graph(3)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(9)));

    //标记三角形，点点等标记曲线
    //2为x标记，3为一个竖扛，4为空心圆，5为实心圆，6为空心正方形，7为空心棱形，8为＊，9为正空心三角形，10为倒空心三角形
    //11为里面带x的正方形，12为“田”，13，带x的圆
    QPen graphPen0;
    graphPen0.setColor(QColor(Qt::blue));
    graphPen0.setWidthF(1);
    ui->widget->graph(0)->setPen(graphPen0);//使用画笔绘制曲线

    QPen graphPen1;
    graphPen1.setColor(QColor(Qt::red));
    graphPen1.setWidthF(2);
    ui->widget->graph(1)->setPen(graphPen1);

    QPen graphPen2;
    graphPen2.setColor(QColor(Qt::green));
    graphPen2.setWidthF(10);
    ui->widget->graph(2)->setPen(graphPen2);

    QPen graphPen3;
    graphPen3.setColor(QColor(Qt::black));
    graphPen3.setWidthF(5);
    ui->widget->graph(3)->setPen(graphPen3);
}

Dialog_draw::~Dialog_draw()
{
    delete ui;
}
