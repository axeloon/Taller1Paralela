#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <cstring>
#define size 9 // tamaño del laberinto

using namespace std;
/**
 * Función que muestra los participantes del grupo
 * @param programa nombre del ejecutable
 */
void participantes(std::string programa);
ifstream leerArchivo();
void printMatrix(char a[size][size]);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char **argv)
{
    // Incluir acá la lógica del programa

    ifstream Laberinto = leerArchivo();
    string contenido;
    char charArray[size + 2]; // Asegúrate de asignar suficiente espacio

    char matrix[size][size];
    int cont = size + 1;
    int i = 0, j = 0;

    while (!Laberinto.eof())
    {
        getline(Laberinto, contenido);
        // Convertir string a char array
        strcpy(charArray, contenido.c_str());

        // LLenar Matriz con el charArray
        for (j = 0; j < cont; j++)
        {
            matrix[i][j] = charArray[j];
        }

        i++;
    }

    printMatrix(matrix);

    // Print del laberinto(matriz)

    if (argc > 1)
    {
        // @TODO programar proyecto
    }
    else
    {
        // Mostrar los integrantes
        participantes(argv[0]);
    }
    return EXIT_SUCCESS;
}

void participantes(std::string programa)
{
    cout << std::endl
         << "=== Taller " << programa << " ===" << std::endl;
    cout << std::endl
         << "Juanito"; // Reemplazar por su nombre
    cout << std::endl
         << "Pedrito"; // Reemplazar por su nombre
    cout << std::endl
         << "Dieguito" << std::endl; // Reemplazar por su nombre
}

ifstream leerArchivo()
{
    ifstream archivo;

    archivo.open("..//laberinto.txt", ios::in);

    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    return archivo;
}

void printMatrix(char a[size][size])
{

    int cont = size + 1;

    for (int i = 0; i < cont; i++)
    {
        for (int j = 0; j < cont; j++)
        {
            cout << a[i][j];
        }
        cout << endl;
    }
    cout << "█" << endl;
    cout << endl;
}
// https://www.youtube.com/watch?v=ksnBUo-08Uw Lectura de archivos en C++