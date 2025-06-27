#include "sqlitedb.h"

//构造函数，连接path的sqlite
SqliteDB::SqliteDB(QString path){
    rndnum=to_string(rand());
    db = QSqlDatabase::addDatabase("QSQLITE",QString::fromStdString(rndnum));
    db.setDatabaseName(path);
    if (!db.open()) {
        qDebug() << "没有成功打开数据库" << db.lastError().text();
    } else {
        qDebug() << "成功打开数据库";
    }
}
//析构函数
SqliteDB::~SqliteDB(){
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    if (QSqlDatabase::contains(QString::fromStdString(rndnum))) {
        QSqlDatabase::removeDatabase(QString::fromStdString(rndnum));
    }
}

//执行sql，create、insert等没有返回值的用
void SqliteDB::excusesql(QString sql){
    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "SQL执行发生错误:" << query.lastError().text();
    } else {
        qDebug() << "SQL执行成功";
    }
}

//查询，columns是要查询的列。返回值，第一维是行，第二维是列
vector<vector<string>> SqliteDB::query(string sql,const vector<string> &columns){
    vector<vector<string>> results;
    QSqlQuery query(db);
    if (!query.exec(QString::fromStdString(sql))) {
        qDebug() << "Query execution error:" << query.lastError().text();
        return results;
    }
    while (query.next()) {
        vector<string> row;
        for (const string &colNameStd : columns) {
            QString colName = QString::fromStdString(colNameStd);
            QString value = query.value(colName).toString();
            row.push_back(value.toStdString());
        }
        results.push_back(row);
    }
    return results;
}

