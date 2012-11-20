#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QDate fecha;
    int estatus;
    ~MainWindow();
    
private slots:
    void on_btnDeshabilitar_clicked();
    void on_btnGuardar_clicked();
    void on_btnReleer_clicked();
    void on_btnNuevo_clicked();
    void on_listaCitas_itemClicked(QListWidgetItem *item);

private:
    void cargaCitasPendientes();
    void deshabilitaCita();
    void guardaCita();
    void inicializaFormulario();
    void cargaCitaSeleccionada();
    Ui::MainWindow *ui;    

};

#endif // MAINWINDOW_H
