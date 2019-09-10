#include "databasedata.h"


DatabaseData::DatabaseData()
{
}

bool DatabaseData::VerificationLogin(QString Username, QString Password)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败

    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");//localhost
    db.setDatabaseName("student");
    db.setUserName("root");
    db.setPassword("");
    if(db.open())
    {
        //数据库操作
        QSqlQuery query(db);//实例一个查询对象SELECT * FROM student.student;
        if(query.exec("SELECT * FROM student.student where id >= 0"))//代表选择id=3的一行内容
        {
            while(query.next())//遍历数据表格student.student每一行，从第0行到最后一行
            {
                QString id = query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格
                QString password = query.value(1).toString().trimmed();
                if((Username.trimmed() == id) && (Password == password))//id,password对应数据库表中列
                    return true;
            }
            db.close();
        }
    }
    return false;
}




