#include "dialog_showexcel.h"
#include "ui_dialog_showexcel.h"

#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include <winnt.h>

Dialog_showexcel::Dialog_showexcel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_showexcel)
{
    ui->setupUi(this);
    tmpRow = 0;
    tmpList = 0;

    QVariant var;

    //动态获取Excel表
//    QString strFile = QFileDialog::getOpenFileName(this,QStringLiteral("选择Excel文件"),"",tr("Exel file(*.xls *.xlsx)"));
//     if (strFile.isEmpty())
//    {
//    }


    //excel操作
     QAxObject excel("Excel.Application");
     excel.setProperty("Visible",false);
     QAxObject *workbooks = excel.querySubObject("WorkBooks");
     workbooks->dynamicCall("Open (const QString&)",QString("d:/b.xlsx"));
     QAxObject *workbook = excel.querySubObject("ActiveWorkBook");              //获取活动工作簿
     QAxObject *worksheets = workbook->querySubObject("WorkSheets");            //获取所有的工作表
     QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);      //获取所有的工作表

//     QAxObject *range = worksheet->querySubObject("Cells(int,int)",10,1);     //获取cell的值 行数和列数
//     var = range->dynamicCall("Value()");


     QAxObject *usedRange = worksheet->querySubObject("UsedRange");
     var = usedRange->dynamicCall("Value");

     QAxObject * rows = usedRange->querySubObject("Rows");
     QAxObject * columns = usedRange->querySubObject("Columns");

     listCount = columns->property("Count").toInt();                            //获取Excel表的行数
     rowCount = rows->property("Count").toInt();                                //获取Excel表的列数

     QVariantList varRows = var.toList();                                       //获取Excel表行数
     QVariantList rowData;
     for(int i=0;i<rowCount;++i)
     {
        rowData = varRows[i].toList();
        res.push_back(rowData);
     }

     workbooks->dynamicCall( "Close(Boolen)", false); // 关闭文件
     excel.dynamicCall( "Quit(void)" );              // 退出
     terminateExcel();   // 结束 Excel 进程，否则系统会很卡顿！！！

    //绘画曲线表操作
    //建立一个曲线图表
        customPlot = new QCustomPlot(this);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setBackground(Qt::white); //设置背景颜色
        customPlot->setGeometry(QRect(130, 120, 800, 400)); //设置 显示 位置 高度

        customPlot->plotLayout()->insertRow(0);
        customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, "Cure")); //插入一行并且添加一个标题元素
        customPlot->addGraph(); // blue line
        customPlot->graph(0)->setPen(QPen(Qt::blue));
        customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
        customPlot->graph(0)->setAntialiasedFill(false);


     //显示当前数值文本
       textLabel = new QCPItemText(customPlot);
       customPlot->addItem(textLabel);
       textLabel->setPositionAlignment(Qt::AlignTop);  //布局内控件
       textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);                    //按比例设置位置，依赖于坐标轴矩形大小，区别于按视口大小
       textLabel->position->setCoords(0, 0); // place position at center/top of axis rect
       textLabel->setFont(QFont(font().family(), 15)); // make font a bit larger
       textLabel->setPen(QPen(Qt::black)); // show black border around text

        //设置当前曲线名字文本
       textLabel2 = new QCPItemText(customPlot);
       customPlot->addItem(textLabel2);
       textLabel2->setPositionAlignment(Qt::AlignBottom);
       textLabel2->position->setType(QCPItemPosition::ptAxisRectRatio);
       textLabel2->position->setCoords(0, 1.0);
       textLabel2->setFont(QFont(font().family(), 15)); // make font a bit larger
       textLabel2->setPen(QPen(Qt::black)); // show black border around text
       CureName="123";                                                                   //设置曲线名字
       textLabel2->setText("CureName:"+CureName);                                        //显示当前值


       //x坐标轴设置
       customPlot->xAxis->setLabel("time:");                                            //设置坐标名字
       customPlot->xAxis->setLabelColor(Qt::black);                                     //设置坐标颜色
       customPlot->xAxis->setLabelPadding(1);                                           //设置坐标轴名称文本距离坐标轴刻度线距离

       //y坐标轴设置
       customPlot->yAxis->setAutoTickStep(false);  ////设置是否自动分配刻度间距
       customPlot->yAxis->setTickStep(25);                                              // 数值的大小是y轴的一半，设置刻度间距
       customPlot->yAxis->setLabelColor(QColor(0, 160, 230));                           //设置文本颜色
        customPlot->yAxis->setRange(-10,80);                                            //y轴的范围

       customPlot->xAxis2-> setTicks(false);                                            //不显示坐标轴
       customPlot->yAxis2-> setTicks(false);                                            //不显示坐标轴


        value0=1; //测试用到
        key=7;
        QTimer *dataTimer = new QTimer(this);
        connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
        dataTimer->start(500);
}

Dialog_showexcel::~Dialog_showexcel()
{
    delete ui;
}

void Dialog_showexcel::realtimeDataSlot()
{
    key++;
    tmpList++;

    static double lastPointKey = 0;

    if(tmpRow < rowCount-1)
    {
        if(tmpList==listCount)
        {
            tmpList = 0;
            tmpRow = tmpRow + 1;
        }
        value0 = res[tmpRow][tmpList].toDouble();                                       //获取Excel表格数据
    }

    customPlot->graph(0)->addData(key, value0);
    lastPointKey = key;


    textLabel->setText("Current:"+QString::number( value0 ));                           //显示当前值
    customPlot->xAxis->setAutoTickStep(false);  ////设置是否自动分配刻度间距
    customPlot->xAxis->setTickStep(1);                                                  // 数值的大小是y轴的一半，设置刻度间距
    customPlot->xAxis->setRange(key,8,Qt::AlignRight);
    customPlot->replot();
}

void Dialog_showexcel::terminateExcel()
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

        //现在我们获得了所有进程的信息。
        //将从hSnapShot中抽取数据到一个PROCESSENTRY32结构中
        //这个结构代表了一个进程，是ToolHelp32 API的一部分。
        //抽取数据靠Process32First()和Process32Next()这两个函数。
        //这里我们仅用Process32Next()，他的原形是：
        //BOOL WINAPI Process32Next(HANDLE hSnapshot,LPPROCESSENTRY32 lppe);
        //我们程序的代码中加入：
        PROCESSENTRY32* processInfo=new PROCESSENTRY32;
        // 必须设置PROCESSENTRY32的dwSize成员的值 ;
        processInfo->dwSize=sizeof(PROCESSENTRY32);
        int index=0;
        //这里我们将快照句柄和PROCESSENTRY32结构传给Process32Next()。
        //执行之后，PROCESSENTRY32 结构将获得进程的信息。我们循环遍历，直到函数返回FALSE。
        int ID = 0;
        while(Process32Next(hSnapShot,processInfo)!=FALSE)
        {
            index++;
            int size=WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,NULL,0,NULL,NULL);
            char *ch=new char[size+1];
            if(WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,ch,size,NULL,NULL))
            {
                //使用这段代码的时候只需要改变"cmd.exe".将其改成你要结束的进程名就可以了。
                if(strstr(ch,"EXCEL.EXE"))
                {
                    ID = processInfo->th32ProcessID;
                    HANDLE hProcess;
                    // 现在我们用函数 TerminateProcess()终止进程，这里我们用PROCESS_ALL_ACCESS
                    hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,ID);
                    TerminateProcess(hProcess,0);
                    CloseHandle(hProcess);
                }
            }
        }
        CloseHandle(hSnapShot);
        delete processInfo;
}

