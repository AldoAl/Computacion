#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

class individuo
{
    private:
        void dividir_archivo(string nombre, int divisiones);
        //float ejecutar_svm(string nombre);
        float ejecutar_svm();
    public:
        vector<int> cromosoma;
        float apt;
        vector<int> memoria;

        individuo();
        individuo(int long_crom);
        individuo(vector<int> crom);
        individuo(const individuo &ind);

        individuo & operator=(const individuo &i);

        void contenido_aleatorio(int lim_inf, int lim_sup);
        void aptitud(const vector<float> &etiqueta, const vector< vector<double> > & dataset);
        void mutacion(unsigned int tam_dataset);
        void mostrar_ind();
};

#endif // INDIVIDUO_H
