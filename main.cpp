#include <QtGui/QApplication>
#include <QTranslator>
#include <QMessageBox>
#include "mainwindow.h"
#include "cambiaCodificacionUTF.h"
#include "conexion.h"

int main(int argc, char *argv[])
{
    //Declarando aplicación
    QApplication a(argc, argv);
    //Instanciando formulario principal
    MainWindow w;
    //Mostrando formulario principal
    w.show();

    //Declarando objeto de traducción
    QTranslator traduccion;
    //Aplicando idioma español a controles
    traduccion.load("qt_es", a.applicationDirPath());
    a.installTranslator(&traduccion);

    //Instanciando clase cambiaCodificacion
    cambiaCodificacion *codificacion;
    //Estableciendo codificación a UTF-8
    codificacion->estableceCodificacionUTF();

    //Instanciando clase base de datos
    baseDatos db;
    db.construirDB();
    //Evaluando si se ha relizado la conexión
    if (QSqlDatabase::database().isOpenError())
    {
        //Muestra mensaje de exito
        QMessageBox::warning(0,"Error","Error al intentar abrir la Base de Datos",QMessageBox::Ok);
    }
    else
    {
        //Muestra mensaje de error
        QMessageBox::information(0,"Exito","Conexión realizada",QMessageBox::Ok);
    }


    return a.exec();
}
