#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>
#include <string>
#include <QVector>
#include <QString>
#include <QObject>

class Diccionario : public QObject
{
    Q_OBJECT
  private:
    QString m_palabra;
    QString m_palabraSinAcento;
    QVector<QString> v_palabras;
    QVector<QString> v_palabrasSinAcento;
    int m_caracteresEncontrados;

  public:
    Diccionario();
    bool cargarPalabras();
    bool seleccionarPalabrasAzar();
    bool buscarCaracter(QChar caracter);
    QString lanzarPalabra() const;
    int tamanoPalabra() const;

  signals:
    void nuevoEvento(bool encontrado);
    void nuevoCaracterEncontrado();
    void escribePalabra(QString palabra);
    void dibujeRayas(int cantidad);
    void palabraEcontrada();
    void escribaLetra(int pos);

  public slots:
    void crearNuevaPalabra();
    void verificarGane();



};
#endif // DICCIONARIO_H
