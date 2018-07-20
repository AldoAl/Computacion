#include <stdio.h>   
#include <stdlib.h>    
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>

using namespace std;

void dividir_archivo(string nombre, int divisiones)
{
    fstream ficheroEntrada;
    ofstream ficheroSalida;

    vector<string> cadenas;

    string frase;

    ficheroEntrada.open ( nombre.c_str() , ios::in);
    if (ficheroEntrada.is_open())
    {
        //getline (ficheroEntrada,frase);

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

    int cont=0;
    for(int i=1;i<=divisiones;i++)
    {
        string s = to_string(i);

        ofstream ficheroSalida;
        ficheroSalida.open (nombre + s + ".t");

        //cout<<"***"<<(i-1)*lineas_por_division<<" - "<<(i-1)*lineas_por_division + lineas_por_division<<endl;

        //cout<<"Division : "<<i<<endl;

        for(int j=0;j<lineas_por_division;j++)
        {
            ficheroSalida<<cadenas[cont]<<endl;
            cont++;
        }
        if(i == divisiones)
        {
            if(cont<cadenas.size()-1)
            {
                for(int j=cont;j<cadenas.size()-1;j++)
                {
                    ficheroSalida<<cadenas[j]<<endl;
                }
            }
        }

        ficheroSalida.close();
    }
}

/**********En estas funciones se obtiene el archivo de entrenamiento para dataset-fitness.t
           tuve que separarlo en pequeñas  funciones para que funcione porque hacer todas las 
           combinaciones en una funcion los archivos me botaban vacios **********/

void leer2()
{
  ifstream file1( "dataset-fitness1.t" ) ;
   ifstream file3( "dataset-fitness3.t" ) ;
   ifstream file4( "dataset-fitness4.t" ) ;
   ifstream file5( "dataset-fitness5.t" ) ;

   //en esta parte uno los .t 1-3-4-5 para formar el archivo de entrenamiento 2
   ofstream combined_file2( "dataset-fitness2" ) ;
   combined_file2 << file4.rdbuf();
   combined_file2 << file1.rdbuf();
   combined_file2 << file3.rdbuf();
   combined_file2 << file5.rdbuf();
   combined_file2.close();
   return;
}

void leer3()
{
  ifstream file1( "dataset-fitness1.t" ) ;
   ifstream file2( "dataset-fitness2.t" ) ;
   ifstream file4( "dataset-fitness4.t" ) ;
   ifstream file5( "dataset-fitness5.t" ) ;
  
  //en esta parte uno los .t 1-2-4-5 para formar el archivo de entrenamiento 3
   ofstream combined_file3( "dataset-fitness3" ) ;
   combined_file3 << file5.rdbuf();
   combined_file3 << file4.rdbuf();
   combined_file3 << file1.rdbuf();
   combined_file3 << file2.rdbuf();
   combined_file3.close();
   return;
}

void leer4()
{
  ifstream file1( "dataset-fitness1.t" ) ;
   ifstream file2( "dataset-fitness2.t" ) ;
   ifstream file3( "dataset-fitness3.t" ) ;
   ifstream file5( "dataset-fitness5.t" ) ;

   //en esta parte uno los .t 1-2-3-5 para formar el archivo de entrenamiento 4
   ofstream combined_file4( "dataset-fitness4" ) ;
   combined_file4 << file5.rdbuf();
   combined_file4<< file3.rdbuf();
   combined_file4 << file1.rdbuf();
   combined_file4 << file2.rdbuf();
   combined_file4.close();
   return;
}

void leer5()
{
  ifstream file1( "dataset-fitness1.t" ) ;
  ifstream file2( "dataset-fitness2.t" ) ;
  ifstream file4( "dataset-fitness4.t" ) ;
  ifstream file3( "dataset-fitness3.t" ) ;

  //en esta parte uno los .t 1-2-3-4 para formar el archivo de entrenamiento 5
  ofstream combined_file5( "dataset-fitness5" ) ;
  combined_file5 << file3.rdbuf();
  combined_file5 << file4.rdbuf();
  combined_file5 << file1.rdbuf();
  combined_file5 << file2.rdbuf();
  combined_file5.close();
  return;
}

void obtener_datatrain()
{
   ifstream file1( "dataset-fitness1.t" ) ;
   ifstream file2( "dataset-fitness2.t" ) ;
   ifstream file3( "dataset-fitness3.t" ) ;
   ifstream file4( "dataset-fitness4.t" ) ;
   ifstream file5( "dataset-fitness5.t" ) ;

   //en esta parte uno los .t 2-3-4-5 para formar el archivo de entrenamiento 1
   ofstream combined_file( "dataset-fitness1");
   combined_file << file3.rdbuf();
   combined_file << file4.rdbuf();
   combined_file << file5.rdbuf();
   combined_file << file2.rdbuf();
   combined_file.close();

   leer2();
   leer3();
   leer4(); 
   leer5();
   return;
}

float ejecutar_svm(string nombre)
{
  
  dividir_archivo("dataset-fitness",5);
  obtener_datatrain();
  //aqui se hace el entrenamiento y se saca la precision de la data set partida en 5
  system("./svm-train -s 0 -b 1 dataset-fitness1");
  system("./svm-predict dataset-fitness1.t dataset-fitness1.model dataset-fitness1.t.predict");

  system("./svm-train -s 0 -b 1 dataset-fitness2");
  system("./svm-predict dataset-fitness2.t dataset-fitness2.model dataset-fitness2.t.predict");

  system("./svm-train -s 0 -b 1 dataset-fitness3");
  system("./svm-predict dataset-fitness3.t dataset-fitness3.model dataset-fitness3.t.predict");

  system("./svm-train -s 0 -b 1 dataset-fitness4");
  system("./svm-predict dataset-fitness4.t dataset-fitness4.model dataset-fitness4.t.predict");

  system("./svm-train -s 0 -b 1 dataset-fitness5");
  system("./svm-predict dataset-fitness5.t dataset-fitness5.model dataset-fitness5.t.predict");
  
  /*Como guardé todos los resultados de las precisiones obtenidas en el archivo acuracy
    ahora leo ese archivo y sumo todas las precisiones y la divido entre 5*/
  
  double precision_total =0; //aqui me dará el resultado de la suma de cada precision sacada 
  double precision = 0; 
 cout<<"sacamos los valores de acuracy"<<endl;
  ifstream fichero("acuracy"); 
  char texto[200]; 
  fichero >> texto;           // Leo una primera linea del archivo acuracy
  while (!fichero.eof())      // Mientras se haya podido leer algo 
  { 
   precision = atof (texto); //
   precision_total += precision; //voy sumando la precision obtenida en cada linea
   fichero >> texto;
   } 
  fichero.close();  
  remove("acuracy"); //aqui borro el archivo acuracy porque necesito que los valores siempre se esten actualizando
  float precision_promedio = precision_total/5.0;
  return precision_promedio;
}


int main ()
{
  float valor_final;
  valor_final = ejecutar_svm("dataset-fitness");
  cout<<"valor final: "<<valor_final<<endl;
  return 0;
}

