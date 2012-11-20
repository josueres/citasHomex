#ifndef CONEXION_H
#define CONEXION_H
#include <QSqlDatabase>
#include <QDir>

class baseDatos
{
public:
    void construirDB()
    {
        QSqlDatabase conexion = QSqlDatabase::addDatabase("QSQLITE3");
        #ifdef Q_WS_WIN
            conexion.setDatabaseName(QDir::toNativeSeparators(QApplication::applicationDirPath()+"\\db.bd"));
        #else
            conexion.setDatabaseName(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/db.bd"));
        #endif
    }

    //Destructor de la clase
    ~baseDatos()
    {
    }
};

#endif // CONEXION_H
