#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>


/*
------------------------------------------------Eventos--------------------------------------------------------
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inicializaFormulario();
}

//Destructor de la clase
MainWindow::~MainWindow()
{
    delete ui;
}

//Evento producido por el boton deshabilitar
void MainWindow::on_btnDeshabilitar_clicked()
{
    //Llamada al metodo deshabilitaCita;
    deshabilitaCita();
}

//Evento producido por el boton Guardar
void MainWindow::on_btnGuardar_clicked()
{
    //Llamada al metodo guardaCita()
    guardaCita();
}

//Evento producido por el boton releer
void MainWindow::on_btnReleer_clicked()
{
    //Llamada al metodo citasPendientes
    cargaCitasPendientes();
}

//Evento producido al presionar el boton Nuevo
void MainWindow::on_btnNuevo_clicked()
{

}

//Evento producido al cambiar el item seleccionado
void MainWindow::on_listaCitas_itemClicked(QListWidgetItem *item)
{
    //Llamando metódo que muestra la cita seleccionada
    cargaCitaSeleccionada();
}



/*
------------------------------------------------Metodos-------------------------------------------------------
*/

//Metódo que inicializa formulario
void MainWindow::inicializaFormulario()
{
    //Mostrando la fecha actual
    ui->lblFecha->setText(fecha.currentDate().toString());
    //Llamada al metódo citas pendientes
    cargaCitasPendientes();
}

//Metódo que carga las citas pendientes
void MainWindow::cargaCitasPendientes()
{
    //Limpiando lista
    ui->listaCitas->clear();
    //Generando metodo para el query
    QSqlQuery cargarCitas;
    //Cargando citas pendientes
    cargarCitas.exec("select cliente from citas where estatus = 1");
    //Realizando llenado de ListWidget
    while (cargarCitas.next())
    {
        QListWidgetItem *nombreCliente = new QListWidgetItem(cargarCitas.value(0).toString());
        ui->listaCitas->addItem(nombreCliente);
    }
}

//Metódo que deshabilita la cita actual
void MainWindow::deshabilitaCita()
{
    //Generando dialogo de decisión
    QString text = QObject::tr("¿Seguro que desea cancelar?");
    QMessageBox msgBox(QObject::tr("Cancelar"), text, QMessageBox::Warning, QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape, QMessageBox::NoButton);
    try
    {
        //Deshabilitando registro
        if (msgBox.exec() == QMessageBox::Yes)
        {
            QSqlQuery cancelarCitas;
            cancelarCitas.exec("update citas set estatus = 0 where id = '"+ui->lblId->text()+"'");
            QMessageBox::information(this,"Listo","Cita cancelada exitosamente","Aceptar");
        }
    }
    catch (QSqlError e)
    {
        qDebug() << e;
    }
}

//Metódo que guarda la cita
void MainWindow::guardaCita()
{
    //Generando dialogo de desición
    QString text = QObject::tr("¿Insertar Cita?");
    QMessageBox msgBox(QObject::tr("Insertar"), text, QMessageBox::Warning, QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape, QMessageBox::NoButton);
    try
    {
        //Si se acepto
        if (msgBox.exec() == QMessageBox::Yes)
        {
            //Insertando cita
            QSqlQuery insertaCita;
            insertaCita.exec("INSERT INTO citas VALUES (null,'"+ui->txtcliente->text()+"', '"+ui->txtlugar->text()+"', '"+ui->txtVendedor->text()+"', '"+ui->timeEdit->text()+"', '"+ui->plainTextEdit->toPlainText()+"', '"+ui->dateEdit->date().toString("yyyy.MM.dd")+"', 1)");
            if (insertaCita.lastError().isValid())
            {
                QMessageBox::critical(this,"Error",insertaCita.lastError().text(),QMessageBox::Ok);
            }
            else
                QMessageBox::information(this,"Insertado","Cita insertada correctamente","Aceptar");
        }
    }
    catch (QSqlError e)
    {
        qDebug() << e;
    }
}


void MainWindow::cargaCitaSeleccionada()
{
    qDebug() << ui->listaCitas->currentItem()->text();
    //Obteniendo nombre de cliente
    QSqlQuery cargaCita;
    cargaCita.exec("SELECT * FROM citas WHERE cliente = '"+ui->listaCitas->currentItem()->text()+"'");
    //Cargando los datos correspondientes
    while(cargaCita.next())
    {
        ui->lblId->setText(cargaCita.value(0).toString());
        ui->txtcliente->setText(cargaCita.value(1).toString());
        ui->txtlugar->setText(cargaCita.value(2).toString());
        ui->txtVendedor->setText(cargaCita.value(3).toString());
        ui->timeEdit->setTime(cargaCita.value(4).toTime());
        ui->plainTextEdit->setPlainText(cargaCita.value(5).toString());
        ui->dateEdit->setDate(cargaCita.value(6).toDate());
    }
}
