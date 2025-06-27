#ifndef SQLITEDB_H
#define SQLITEDB_H
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariant>
#include<QString>
#include<vector>
#include<random>
using namespace std;
class SqliteDB{
public:
    SqliteDB(QString path);
    void excusesql(QString sql);
    vector<vector<string>> query(string sql,const vector<string> &columns);
    ~SqliteDB();
private:
    string rndnum;
    QSqlDatabase db;
};
#endif // SQLITEDB_H
