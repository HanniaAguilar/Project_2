#include "Vista.h"
#include "Raya.h"

class ObjectoProp;
class PartesCuerpo;

Vista::Vista(QGraphicsScene *escena)
    :QGraphicsView(escena)
    ,m_svgRenderer(Q_NULLPTR)
    ,m_fondo(Q_NULLPTR)
    ,teclas (Q_NULLPTR)

{
  #if ! defined(Q_OS_ANDROID)
    resize(960, 540);
  #endif
}

void Vista::insertarComponentes(QGraphicsScene* m_escena,Diccionario* diccionario)//ahora recibe un diccionario
{
    m_svgRenderer = new QSvgRenderer(QString(":/Resources/assets.svg"), this);

    this->dibujeFondo(m_escena);
    this->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Se agrega el teclado
    teclas = new Teclas(diccionario);
    teclas->agregarTeclado();
    teclas->cargarTeclado(m_svgRenderer,m_escena);
    teclas->mostrarTeclado();

    m_marcador = new Marcador("Puntos",0,Qt::black);
    m_marcador->setPos(710,20);
    m_escena->addItem(m_marcador);

    rayas= new Raya();
    rayas->cargarRayas(m_svgRenderer,m_escena);
    //rayas->colocarPalabra(m_escena);

    cuerpo = new PartesCuerpo(m_svgRenderer, m_escena);
    cuerpo->agregarPartes();
    cuerpo->colocarCuerpo();

    /// se conectan eventos de ambas clases
    QObject::connect(diccionario,SIGNAL(nuevoEvento(bool)),cuerpo,SLOT(revisarEvento(bool)));
    QObject::connect(diccionario,SIGNAL(nuevoCaracterEncontrado()),diccionario,SLOT(verificarGane()));
    QObject::connect(diccionario,SIGNAL(palabraEcontrada()),m_marcador,SLOT(incrementePuntos()));
    QObject::connect(diccionario,SIGNAL(palabraEcontrada()),cuerpo,SLOT(esconderCuerpo()));
    QObject::connect(diccionario,SIGNAL(palabraEcontrada()),teclas,SLOT(restablecerTeclado()));
    QObject::connect(diccionario,SIGNAL(escribePalabra(QString)),rayas,SLOT(colocarPalabra(QString)));
    QObject::connect(diccionario,SIGNAL(escribaLetra(int)),rayas,SLOT(mostrarLetra(int)));
    QObject::connect(diccionario,SIGNAL(dibujeRayas(int)),rayas,SLOT(actualizarRayas(int)));
    QObject::connect(cuerpo,SIGNAL(perdio()),diccionario,SLOT(crearNuevaPalabra()));
    QObject::connect(cuerpo,SIGNAL(perdio()),teclas,SLOT(restablecerTeclado()));
    //QObject::connect(diccionario,SIGNAL(palabraEcontrada()),cuerpo,SLOT(dibujarGane()));
}

void Vista::dibujeFondo (QGraphicsScene* m_escena){
     m_fondo = new ObjetoProp("fondo");
     m_fondo->setSharedRenderer(m_svgRenderer);
     m_fondo->setPos(45,5);
     m_escena->addItem(m_fondo);
     m_fondo->setZValue(-1);
}

Vista::~Vista()
{
}
