#ifndef POBLACION_H
#define POBLACION_H

#include "individuo.h"
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

class poblacion
{
    private:
        vector< vector<double> > dataset;
        vector<float> etiqueta;

        unsigned int tam_pob;
        vector<individuo> pob;

        unsigned int limite_mem;

        float cruz_ratio;
        float mut_ratio;

        individuo mejor_ind;

        double extraer_dato(string cadena);
        friend bool comparacion(individuo a, individuo b);
        void sel_nueva_pob();

        unsigned int sel_padre();
        void cruzamiento(int padre1, int padre2);

        individuo buscar_mejor();

    public:
        poblacion(int pob, float cr_rat, float mut_rat);
        void leer_dataset(string nombre);

        void generar_pob_inicial(int num_gen_selec);

        void ejecucion(int cant_it);

        void mostrar_etiquetas();
        void mostrar_dataset();
        void mostrar_pob();
        void mostrar_mejor();
};

#endif // POBLACION_H
