#include <QCoreApplication>
#include "poblacion.h"

int main(int argc, char *argv[])
{
    poblacion P(100,0.7,0.3);
    P.leer_dataset("leu");
    P.generar_pob_inicial(2);
    //P.mostrar_etiquetas();
    //P.mostrar_dataset();
    //P.cargar_datos("leu");
    //P.mostrar_pob();
    P.ejecucion(10);
    cout<<"Poblacion final:---------------------------------------"<<endl;
    //P.mostrar_pob();

    cout<<"Hola Mundo!"<<endl;
    QCoreApplication a(argc, argv);

    return a.exec();
}
