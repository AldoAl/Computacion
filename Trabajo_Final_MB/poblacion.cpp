#include "poblacion.h"

poblacion::poblacion(int pob, float cr_rat, float mut_rat)
{
    tam_pob=pob;
    cruz_ratio=cr_rat;
    mut_ratio=mut_rat;
    cout<<"Algoritmo Genético creado correctamente."<<endl;
    cout<<"Tamaño de Poblacion : "<<tam_pob<<endl;
    cout<<"Ratio de Cruzamiento : "<<cruz_ratio<<endl;
    cout<<"Ratio de Mutación : "<<mut_ratio<<endl;
}

double poblacion::extraer_dato(string cadena)
{
    int i=0;
    for(;cadena.size();i++)
    {
        if(cadena[i]==':')
        {
            i++;
            break;
        }
    }
    return stod(cadena.substr(i,cadena.size()-1));
}

void poblacion::leer_dataset(string nombre)
{
    fstream ficheroEntrada;
    string frase;

    ficheroEntrada.open ( nombre.c_str() , ios::in);
    if (ficheroEntrada.is_open())
    {
        int filas;
        int columnas;

        ficheroEntrada>>filas>>columnas;

        etiqueta.resize(filas);
        dataset.resize(filas);

        getline (ficheroEntrada,frase);

        for(int i=0;i<filas;i++)
        {
            string etiq;
            string aux;

            for(int j=0;j<columnas+1;j++)
            {
                if(j==0)
                {
                    ficheroEntrada>>etiq;
                    etiqueta[i]=stof(etiq);
                }
                else
                {
                    ficheroEntrada>>aux;
                    dataset[i].push_back(extraer_dato(aux));
                }
            }
        }
        ficheroEntrada.close();
    }
    else
    {
        cout<<"Fichero inexistente o faltan permisos para abrirlo"<<endl;
    }
    return;
}

void poblacion::generar_pob_inicial(int num_gen_selec)
{
    pob.resize(tam_pob);
    for(unsigned int i=0;i<tam_pob;i++)
    {
        pob[i]=individuo(num_gen_selec);
        pob[i].contenido_aleatorio(0,dataset[0].size());
        pob[i].aptitud(etiqueta,dataset);
    }

    //cout<<"Buscar al mejor individuo"<<endl;
    mejor_ind = buscar_mejor();
    //cout<<"Mostrar al mejor individuo"<<endl;
    mostrar_mejor();
    cout<<"Tamaño de población inicial : "<<pob.size()<<endl<<endl;
    return;
}

unsigned int poblacion::sel_padre()
{
    int aptitud_total=0;

    for(unsigned int i=0;i<pob.size();i++)
    {
        aptitud_total+=pob[i].apt;
    }

    vector <float> porc_ind(pob.size());
    for(unsigned int i=0;i<pob.size();i++)
    {
        porc_ind[i]=( (float)pob[i].apt / aptitud_total)*100;
    }

    vector <float> porc_acu(pob.size());

    porc_acu[0]=porc_ind[0];
    for(unsigned int i=1;i<pob.size();i++)
    {
        porc_acu[i]=porc_acu[i-1]+porc_ind[i];
    }

    srand (time(NULL)+ rand());

    int pad1 = rand() % 100;

    int cont1=0;
    while(porc_acu[cont1] <= pad1)
    {
        cont1++;
    }

    return cont1;
}

void poblacion::cruzamiento(int padre1, int padre2)
{
    int pos=pob[padre1].cromosoma.size()/2;
    vector<int> h1(pob[padre1].cromosoma.size());
    vector<int> h2(pob[padre1].cromosoma.size());

    for(int i=0;i<pos;i++)
    {
        h1[i]=pob[padre1].cromosoma[i];
        h2[i]=pob[padre2].cromosoma[i];
    }
    for(unsigned int i=pos;i<pob[padre1].cromosoma.size();i++)
    {
        h1[i]=pob[padre2].cromosoma[i];
        h2[i]=pob[padre1].cromosoma[i];
    }

    individuo hijo1(h1);
    srand (time(NULL)+ rand());
    float mut1 = rand() % 100;
    mut1 = mut1/100;
    if(mut1 <= mut_ratio)
    {
        cout<<"Mutación Hijo 1"<<endl;
        hijo1.mutacion(dataset[0].size());
        hijo1.aptitud(etiqueta,dataset);
    }
    else
    {
        hijo1.aptitud(etiqueta,dataset);
    }

    //Algoritmo Memético
    while(hijo1.apt < pob[padre1].apt || hijo1.apt < pob[padre2].apt)
    {
        hijo1.mutacion(dataset[0].size());
        hijo1.aptitud(etiqueta,dataset);
    }
    ////////////////////

    individuo hijo2(h2);
    srand (time(NULL)+ rand());
    float mut2 = rand() % 100;
    mut2 = mut2/100;
    if(mut2 <= mut_ratio)
    {
        cout<<"Mutación Hijo 2"<<endl;
        hijo2.mutacion(dataset[0].size());
        hijo2.aptitud(etiqueta,dataset);
    }
    else
    {
        hijo2.aptitud(etiqueta,dataset);
    }

    //Algoritmo Memético
    while(hijo2.apt < pob[padre1].apt || hijo2.apt < pob[padre2].apt)
    {
        hijo2.mutacion(dataset[0].size());
        hijo2.aptitud(etiqueta,dataset);
    }
    ////////////////////

    pob.push_back(hijo1);
    pob.push_back(hijo2);

    return;
}

void poblacion::mostrar_etiquetas()
{
    cout<<"Etiquetas:"<<endl;
    for(unsigned int i=0;i<etiqueta.size();i++)
    {
        cout<<etiqueta[i]<<endl;
    }
    return;
}

void poblacion::mostrar_dataset()
{
    cout<<"Dataset:"<<endl;
    for(unsigned int i=0;i<dataset.size();i++)
    {
        for(unsigned int j=0;j<dataset[0].size();j++)
        {
            cout<<dataset[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}

void poblacion::mostrar_pob()
{
    for(unsigned int i=0;i<pob.size();i++)
    {
        pob[i].mostrar_ind();
    }
    return;
}

void poblacion::mostrar_mejor()
{
    mejor_ind.mostrar_ind();
    return;
}

bool comparacion(individuo a, individuo b)
{
    return a.apt>b.apt;
}

void poblacion::sel_nueva_pob()
{
    sort(pob.begin(),pob.end(),comparacion);

    while(pob.size() > tam_pob)
    {
        pob.pop_back();
    }
    return;
}

individuo poblacion::buscar_mejor()
{
    unsigned int pos_mejor=0;
    float mejor_apt=pob[0].apt;

    for(unsigned int i=1;i<pob.size();i++)
    {
        if(pob[i].apt > mejor_apt)
        {
            pos_mejor=i;
            mejor_apt=pob[i].apt;
        }
    }

    individuo mejor(pob[pos_mejor]);

    return mejor;
}

void poblacion::ejecucion(int cant_it)
{
    for(int i=0;i<cant_it;i++)
    {
        cout<<"---------- Iteración N° "<<i+1<<" ----------"<<endl;

        srand (time(NULL)+ rand());
        float cruz = rand() % 100;
        cruz = cruz/100;

        if(cruz <= cruz_ratio)
        {
            cout<<"Cruzamiento: "<<cruz_ratio<<" -> "<<cruz<<endl;

            unsigned int padre1 = sel_padre();
            unsigned int padre2 = sel_padre();

            while(padre2 == padre1)
            {
                padre2 = sel_padre();
            }

            cruzamiento(padre1,padre2);
        }

        cout<<"Autómata de aprendizaje"<<endl<<endl;

        for(unsigned int i=0;i<pob.size();i++)
        {
            float v1 = pob[i].apt;
            srand (time(NULL)+ rand());
            unsigned int pos = rand() % pob[i].cromosoma.size();

            individuo ind_mod(pob[i]);
            srand (time(NULL)+ rand());
            ind_mod.cromosoma[pos] = rand() % dataset[0].size();
            ind_mod.aptitud(etiqueta,dataset);

            float v2 = ind_mod.apt;

            if(v1 >= v2)
            {
                cout<<"v1 >= v2"<<endl;

                if(pob[i].memoria[pos] < limite_mem)
                {
                    pob[i].memoria[pos]++;
                }
                else
                {
                    if(pob[i].memoria[pos] > 0)
                    {
                        pob[i].memoria[pos]--;
                    }
                    else
                    {
                        pob[i] = ind_mod;
                    }
                }
            }
        }

        sel_nueva_pob();

        individuo candidato_mejor = buscar_mejor();

        if(candidato_mejor.apt > mejor_ind.apt)
        {
            mejor_ind.cromosoma = candidato_mejor.cromosoma;
            mejor_ind.apt = candidato_mejor.apt;
        }

    }

    cout<<"Mejor solución después de "<<cant_it<<" iteraciones:"<<endl;
    mostrar_mejor();
    return;
}
