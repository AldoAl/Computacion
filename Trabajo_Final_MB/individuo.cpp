#include "individuo.h"

individuo::individuo()
{

}

individuo::individuo(vector<int> crom)
{
    cromosoma = crom;
    memoria.resize(crom.size(),0);
}

individuo::individuo(int long_crom)
{
    cromosoma.resize(long_crom);
    memoria.resize(long_crom,0);
}

individuo::individuo(const individuo &ind)
{
    cromosoma = ind.cromosoma;
    memoria = ind.memoria;
    apt = ind.apt;
}

individuo & individuo::operator=(const individuo &i)
{
    cromosoma = i.cromosoma;
    apt = i.apt;
    memoria = i.memoria;

    return *this;
}

void individuo::contenido_aleatorio(int lim_inf, int lim_sup)
{
    for(unsigned int i=0;i<cromosoma.size();i++)
    {
        srand (time(NULL)+ rand());
        cromosoma[i] = rand() % lim_sup+1;
    }
    return;
}

void individuo::dividir_archivo(string nombre, int divisiones)
{
    fstream ficheroEntrada;

    vector<string> cadenas;

    string frase;

    ficheroEntrada.open ( nombre.c_str() , ios::in);
    if (ficheroEntrada.is_open())
    {
        while (! ficheroEntrada.eof() )
        {
            getline (ficheroEntrada,frase);
            cadenas.push_back(frase);
        }
        ficheroEntrada.close();
    }
    else
    {
        cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
        return;
    }

    int lineas_por_division = (cadenas.size()-1)/divisiones;
    //cout<<"lineas_por_division : "<<lineas_por_division<<endl;

    vector<string> bloque1;
    vector<string> bloque2;
    vector<string> bloque3;
    vector<string> bloque4;
    vector<string> bloque5;

    int cont=0;
    for(int i=0;i<lineas_por_division;i++)
    {
        bloque1.push_back(cadenas[cont]);
        cont++;
    }

    for(int i=0;i<lineas_por_division;i++)
    {
        bloque2.push_back(cadenas[cont]);
        cont++;
    }

    for(int i=0;i<lineas_por_division;i++)
    {
        bloque3.push_back(cadenas[cont]);
        cont++;
    }

    for(int i=0;i<lineas_por_division;i++)
    {
        bloque4.push_back(cadenas[cont]);
        cont++;
    }

    for(int i=0;i<lineas_por_division;i++)
    {
        bloque5.push_back(cadenas[cont]);
        cont++;
    }

    ofstream ficheroSalida;
    ficheroSalida.open ("dataset-fitness1");

    for(unsigned int i=0;i<bloque1.size();i++)
    {
        ficheroSalida<<bloque1[i]<<endl;
    }
    for(unsigned int i=0;i<bloque2.size();i++)
    {
        ficheroSalida<<bloque2[i]<<endl;
    }
    for(unsigned int i=0;i<bloque3.size();i++)
    {
        ficheroSalida<<bloque3[i]<<endl;
    }
    for(unsigned int i=0;i<bloque4.size();i++)
    {
        ficheroSalida<<bloque4[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness1.t");

    for(unsigned int i=0;i<bloque5.size();i++)
    {
        ficheroSalida<<bloque5[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness2");

    for(unsigned int i=0;i<bloque1.size();i++)
    {
        ficheroSalida<<bloque1[i]<<endl;
    }
    for(unsigned int i=0;i<bloque2.size();i++)
    {
        ficheroSalida<<bloque2[i]<<endl;
    }
    for(unsigned int i=0;i<bloque3.size();i++)
    {
        ficheroSalida<<bloque3[i]<<endl;
    }
    for(unsigned int i=0;i<bloque5.size();i++)
    {
        ficheroSalida<<bloque5[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness2.t");

    for(unsigned int i=0;i<bloque4.size();i++)
    {
        ficheroSalida<<bloque4[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness3");

    for(unsigned int i=0;i<bloque1.size();i++)
    {
        ficheroSalida<<bloque1[i]<<endl;
    }
    for(unsigned int i=0;i<bloque2.size();i++)
    {
        ficheroSalida<<bloque2[i]<<endl;
    }
    for(unsigned int i=0;i<bloque4.size();i++)
    {
        ficheroSalida<<bloque4[i]<<endl;
    }
    for(unsigned int i=0;i<bloque5.size();i++)
    {
        ficheroSalida<<bloque5[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness3.t");

    for(unsigned int i=0;i<bloque3.size();i++)
    {
        ficheroSalida<<bloque3[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness4");

    for(unsigned int i=0;i<bloque1.size();i++)
    {
        ficheroSalida<<bloque1[i]<<endl;
    }
    for(unsigned int i=0;i<bloque3.size();i++)
    {
        ficheroSalida<<bloque3[i]<<endl;
    }
    for(unsigned int i=0;i<bloque4.size();i++)
    {
        ficheroSalida<<bloque2[i]<<endl;
    }
    for(unsigned int i=0;i<bloque5.size();i++)
    {
        ficheroSalida<<bloque5[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness4.t");

    for(unsigned int i=0;i<bloque2.size();i++)
    {
        ficheroSalida<<bloque2[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness5");

    for(unsigned int i=0;i<bloque2.size();i++)
    {
        ficheroSalida<<bloque2[i]<<endl;
    }
    for(unsigned int i=0;i<bloque3.size();i++)
    {
        ficheroSalida<<bloque3[i]<<endl;
    }
    for(unsigned int i=0;i<bloque4.size();i++)
    {
        ficheroSalida<<bloque4[i]<<endl;
    }
    for(unsigned int i=0;i<bloque5.size();i++)
    {
        ficheroSalida<<bloque5[i]<<endl;
    }
    ficheroSalida.close();

    ficheroSalida.open ("dataset-fitness5.t");

    for(unsigned int i=0;i<bloque1.size();i++)
    {
        ficheroSalida<<bloque1[i]<<endl;
    }
    ficheroSalida.close();
    cadenas.clear();
    bloque1.clear();
    bloque2.clear();
    bloque3.clear();
    bloque4.clear();
    bloque5.clear();

    return;
}

float individuo::ejecutar_svm()
{
    dividir_archivo("dataset-fitness",5);

    cout<<endl<<"Primer conjunto de pruebas"<<endl;
    system("./libsvm-3.22/svm-train -s 0 -b 1 dataset-fitness1");
    system("./libsvm-3.22/svm-predict dataset-fitness1.t dataset-fitness1.model dataset-fitness1.t.predict");

    cout<<endl<<"Segundo conjunto de pruebas"<<endl;
    system("./libsvm-3.22/svm-train -s 0 -b 1 dataset-fitness2");
    system("./libsvm-3.22/svm-predict dataset-fitness2.t dataset-fitness2.model dataset-fitness2.t.predict");

    cout<<endl<<"Tercer conjunto de pruebas"<<endl;
    system("./libsvm-3.22/svm-train -s 0 -b 1 dataset-fitness3");
    system("./libsvm-3.22/svm-predict dataset-fitness3.t dataset-fitness3.model dataset-fitness3.t.predict");

    cout<<endl<<"Cuarto conjunto de pruebas"<<endl;
    system("./libsvm-3.22/svm-train -s 0 -b 1 dataset-fitness4");
    system("./libsvm-3.22/svm-predict dataset-fitness4.t dataset-fitness4.model dataset-fitness4.t.predict");

    cout<<endl<<"Quinto conjunto de pruebas"<<endl;
    system("./libsvm-3.22/svm-train -s 0 -b 1 dataset-fitness5");
    system("./libsvm-3.22/svm-predict dataset-fitness5.t dataset-fitness5.model dataset-fitness5.t.predict");

    double precision_total =0; //aqui me dará el resultado de la suma de cada precision sacada
    double precision = 0;
    cout<<"sacamos los valores de accuracy"<<endl;
    ifstream fichero("precision");
    char texto[200];
    fichero >> texto;           // Leo una primera linea del archivo acuracy
    while (!fichero.eof())      // Mientras se haya podido leer algo
    {
        precision = atof (texto); //
        precision_total += precision; //voy sumando la precision obtenida en cada linea
        fichero >> texto;
     }

    fichero.close();
    remove("precision"); //aqui borro el archivo acuracy porque necesito que los valores siempre se esten actualizando
    float precision_promedio = precision_total/5.0;
    cout<<" precision : "<<precision_promedio<<endl;

    remove("dataset-fitness");

    remove("dataset-fitness1");
    remove("dataset-fitness1.model");
    remove("dataset-fitness1.t");
    remove("dataset-fitness1.t.predict");

    remove("dataset-fitness2");
    remove("dataset-fitness2.model");
    remove("dataset-fitness2.t");
    remove("dataset-fitness2.t.predict");

    remove("dataset-fitness3");
    remove("dataset-fitness3.model");
    remove("dataset-fitness3.t");
    remove("dataset-fitness3.t.predict");

    remove("dataset-fitness4");
    remove("dataset-fitness4.model");
    remove("dataset-fitness4.t");
    remove("dataset-fitness4.t.predict");

    remove("dataset-fitness5");
    remove("dataset-fitness5.model");
    remove("dataset-fitness5.t");
    remove("dataset-fitness5.t.predict");

    return precision_promedio;
    }

void individuo::aptitud(const vector<float> &etiqueta, const vector< vector<double> > & dataset)
{
    string nombre = "dataset-fitness";

    ofstream ficheroSalida;
    ficheroSalida.open (nombre.c_str() , ios::out);

    for(unsigned int i=0;i<etiqueta.size();i++)
    {
        ficheroSalida<<etiqueta[i]<<" ";
        for(unsigned int j=0;j<cromosoma.size();j++)
        {
            ficheroSalida<<" "<<j+1<<":"<<dataset[i][cromosoma[j]];
        }
        ficheroSalida<<endl;
    }

    ficheroSalida.close();

    float valor_final;
    valor_final = ejecutar_svm();

    apt=valor_final;
    return;
}

void individuo::mutacion(unsigned int tam_dataset)
{
    srand (time(NULL)+ rand());
    int pos1 = rand() % cromosoma.size();
    cout<<pos1<<endl;

    srand (time(NULL)+ rand());
    int nuevo_valor = rand() % tam_dataset;
    cout<<nuevo_valor<<endl;

    //swap(cromosoma[pos1],cromosoma[pos2]);
    cromosoma[pos1] = nuevo_valor;
    //aptitud();
    return;
}

void individuo::mostrar_ind()
{
    for(unsigned int i=0;i<cromosoma.size();i++)
    {
        cout<<cromosoma[i]<<" ";
    }
    cout<<" - "<<apt<<endl<<endl;
}
