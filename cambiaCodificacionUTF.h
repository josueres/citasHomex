#ifndef CAMBIACODIFICACIONUTF_H
#define CAMBIACODIFICACIONUTF_H
#include <QTextCodec>

class cambiaCodificacion
{
public:
    //Metódo que establece la codificación a UTF-8
    void estableceCodificacionUTF()
    {
        //Definiendo codificación de caracteres a UTF-8
        QTextCodec *Codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForTr(Codec);
        QTextCodec::setCodecForCStrings(Codec);
        QTextCodec::setCodecForLocale(Codec);
    }

    //Destructor de la clase
    ~cambiaCodificacion()
    {
    }
};

#endif // CAMBIACODIFICACIONUTF_H
