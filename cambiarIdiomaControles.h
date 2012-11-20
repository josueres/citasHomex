#ifndef CAMBIARIDIOMACONTROLES_H
#define CAMBIARIDIOMACONTROLES_H
#include <QTranslator>
#include <QApplication>
#include <QTranslator>

class cambiaIdiomaControles
{

    //Tipo idiomas
    enum Idiomas
    {
        //Elemento español
        espanol = 1
    };

public:

    //Metodo que cambia el idioma de los controles segun selección
    QTranslator establecerIdioma(Idiomas lang, QApplication app)
    {
        //Declarando objeto de traducción
        QTranslator traduccion;
        //Seleccion de idioma de acuerdo al parametro recibido
        switch (lang)
        {
            case espanol:
            {
            //Aplicando idioma español a controles
            traduccion.load("qt_es", app.applicationDirPath());
            break;
            }
        }
        //Retornando resultado
        return traduccion;
    }

    //Destructor de la clase
    ~cambiaIdiomaControles()
    {
    }

};

#endif // CAMBIARIDIOMACONTROLES_H
