#include <iostream>
#include <omp.h>

#define N 1000 // Cantidad de elementos a manejar en los arreglos
#define chunk 100 // Tamaño de los pedazos de los arreglos para cada hilo
#define mostrar 10 // Cantidad de datos a imprimir
 
void imprimeArreglo(float *d); //Funcion para imprimir arreglos

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N]; // 3 arreglos a,b,c, arreglo c va a ser la suma de a+b
    int i;

    for (i = 0; i < N; i++) // Ciclo for para generar valores aleatorios en los arreglo a y b
    { 
        int random = rand() % 10; // Genera valores aleatorios entre 0 al 9
        a[i] = i * random; // valores aleatorios para a
        b[i] = (i + random) * 2.1; // valores aleatorios para b
    }
    int pedazos = chunk; // asigna a la variable pedazos nuestro constante chunk para el tamaño de hilo

    //programacion paralela, los arreglos a,b,c y pedazos comparten memoria mientras que constante i debe ser privada para evitar mezcla
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static,pedazos)// Programacion paralela para ciclo for

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl; // Imprimir los primeros 10 valores del arreglo a
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl; // Imprimir los primeros 10 valores del arreglo b
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl; // Imprimir los primeros 10 valores del arreglo c
    imprimeArreglo(c);
}

void imprimeArreglo(float *d) // funcion para imprimir los arreglos
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " , ";
    std::cout << std::endl;
}


   


