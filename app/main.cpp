#include <iostream> //Proporciona funciones para entrada y salida estándar en C++, como cin y cout para leer y escribir datos en la consola
#include <string>   //Ofrece una clase llamada string para trabajar con cadenas de caracteres de manera más sencilla y realizar operaciones de cadenas
#include <cstdlib>  //Contiene funciones para la gestión de memoria, control de flujo y conversiones de datos, a menudo utilizadas para generar números aleatorios
#include <fstream>  //Proporciona clases y funciones para operaciones de entrada y salida de archivos en C++
#include <vector>   //Incluye la clase vector para crear estructuras de datos dinámicas que pueden almacenar elementos de manera flexible.

using namespace std;            // Se utiliza para string, cin, cout, etc sin tener que escribir std::
const int dx[] = {0, 1, 0, -1}; // Se inicializa un array con las direcciones de X y sus posibles valores
const int dy[] = {1, 0, -1, 0}; // Se inicializa un array con las direcciones de Y y sus posibles valores

// Procedimiento encargado de recorrer los bordes del laberinto en búsqueda de la entrada y la salida
void recorrerBordeLaberinto(vector<string> &laberinto, int filas, int columnas, int &entradaX, int &entradaY, int &salidaX, int &salidaY);
// Función encargada de verificar el siguiente movimiento del pivote, los espacios en blanco dentro del laberinto son Movimientos Válidos
bool movimientoValido(vector<string> &laberinto, vector<vector<bool>> &visitados, int x, int y);
// Función que busca entre las 4 direcciones siguiente movimiento válido para mover el pivote
bool buscarCamino(vector<string> &laberinto, vector<vector<bool>> &visitados, vector<vector<int>> &copia, int x, int y, int objetivoX, int objetivoY, int contador);
// Función encargada de comparar los distintos caminos del laberinto, para corregirlo y encontrar el camino con menos pasos
vector<vector<int>> encontrarCaminoHaciaMaximo(const vector<vector<int>> &matrizNumeros, vector<string> &laberinto);
// Procedimiento que muestra el Título del taller, su ubicación y los integrantes
void participantes(string programa);

int main(int argc, char **argv)
{
    int filas = 0, columnas = 0;                                  // Se declaran filas y columnas y se inicializan en 0
    int entradaX = -1, entradaY = -1, salidaX = -1, salidaY = -1; // Se declaran las coordenadas de entrada y salida
    string linea;                                                 // Se crea el String linea, que separará linea por linea el archivo .txt esto para efectos de lectura y escritura
    vector<string> laberinto;                                     // Se crea un Vector de Lineas para almacenar el laberinto
    ifstream archivo("..//nuevogato.txt");                        // Se realiza la lectura del archivo (Para agregar un nuevo laberinto, mover el archivo a la carpeta /app y cambiar el nombre del .txt EN ESTA LÍNEA)
    if (!archivo)                                                 // Si no se encuentra el archivo en la dirección anterior
    {
        cerr << "Error" << endl; // Muestra por pantalla un mensaje de error
        return 1;                // Termina el programa
    }
    while (getline(archivo, linea)) // Mientras existan lineas dentro del laberinto
    {
        laberinto.push_back(linea);    // Carga la linea obtenida del archivo dentro del vector de líneas laberinto
        if (linea.length() > columnas) // Compara la longitud de cada linea con la longiutd de la columna actual, Se hace para rastrear la longitud máxima de línea en el archivo
        {
            columnas = linea.length(); // Esto se usa para determinar el número de columnas en el laberinto.
        }
        filas++; // Se cuentan las filas por cada iteración, para determinar el total de filas del laberinto
    }
    {
        cout << endl;
        // Recorre el laberinto sin camino
        for (const string &fila : laberinto) // Se crea un ciclo for para recorrer cada fila del laberinto para ello, se crea una constante string
        {
            for (char c : fila) // Se crea un ciclo for para recorrer cada caracter dentro de cada fila del laberinto para ello, se crea una variable char
            {
                cout << c; // Muestra en la pantalla cada caracter dentro de la fila actual
            }
            cout << endl; // Realiza un salto de línea cuando se termine la fila actual
        }
    }
    vector<vector<bool>> visitados(filas, vector<bool>(columnas, false));                     // Se crea una matriz con vectores, estos almacenan valores bool [0, 1] Para almacenar los caminos hacia el final
    vector<vector<int>> copia(filas, vector<int>(columnas));                                  // Se crea una matriz con vectores, que se encarga de contar los pasos realizados desde la entrada hasta la salida
    recorrerBordeLaberinto(laberinto, filas, columnas, entradaX, entradaY, salidaX, salidaY); // LLamada a la función para determinar las coordenadas de entrada y salida dentro del laberinto
    cout << "\n Entradas: " << entradaX << ", " << entradaY << endl;                          // Muestra por pantalla las coordenadas [x, y] de la Entrada del laberinto
    cout << "Salidas: " << salidaX << ", " << salidaY << endl                                 // Muestra por pantalla las coordenadas [x, y] de la Salida del laberinto
         << endl;
    copia[entradaX][entradaY] = 1;                                                      // Con las coordenadas listas, se da el primer paso dentro del laberinto y se almacena en copia
    laberinto[entradaX][entradaY] = '*';                                                // A su vez, se marca en el laberinto, el primer paso
    buscarCamino(laberinto, visitados, copia, entradaX, entradaY, salidaX, salidaY, 2); // LLamada a la función donde se desarrolla la búsqueda hacia la salida
    vector<vector<int>> copia_num = encontrarCaminoHaciaMaximo(copia, laberinto);       // Se crea una matriz con vectores, donde se almacenará el camino corregido, el que posea menos pasos hacia la salida
                                                                                        //  Recorre el laberinto resuelto
    for (const string &fila : laberinto)                                                // Se crea un ciclo for para recorrer cada fila del laberinto para ello, se crea una constante string
    {
        for (char c : fila) // Se crea un ciclo for para recorrer cada caracter dentro de cada fila del laberinto para ello, se crea una variable char
        {
            cout << c; // Muestra en la pantalla cada caracter dentro de la fila actual
        }
        cout << endl; // Realiza un salto de línea cuando se termine la fila actual
    }
    ofstream resuelto;                                    // Se crea la variable resuelto, para almacenar el laberinto resuelto dentro de un archivo
    resuelto.open("..//laberintoResuelto.txt", ios::out); // Se almacena el laberinto resuelto dentro de la carpeta actual
    if (resuelto.fail())                                  // Si no se encuentra el archivo en la dirección anterior
    {
        cerr << "Error en la creacion del archivo" << endl; // Muestra por pantalla un mensaje de error
        return 1;                                           // Termina el programa
    }
    // Recorre el Laberinto Resuelto, y lo almacena dentro del archivo .txt
    for (const string &fila : laberinto) // Se crea un ciclo for para recorrer cada fila del laberinto para ello, se crea una constante string
    {
        for (char c : fila) // Se crea un ciclo for para recorrer cada caracter dentro de cada fila del laberinto para ello, se crea una variable char
        {
            resuelto << c; // Guarda el caracter actual dentro del archivo resuelto
        }
        resuelto << endl; // Realiza un salto de línea cuando se termine la fila actual
    }

    resuelto.close(); // Una vez creado el archivo con éxito, se cierra

    ofstream resuelve;                                         // Se crea la variable resuelve, para almacenar el laberinto resuelto dentro de un archivo
    resuelve.open("..//laberintoResueltoPasos.txt", ios::out); // Se almacena el laberinto resuelto dentro de la carpeta actual
    if (resuelto.fail())                                       // Si no se encuentra el archivo en la dirección anterior
    {
        cerr << "Error en la creacion del archivo" << endl; // Muestra por pantalla un mensaje de error
        return 1;                                           // Termina el programa
    }
    // Recorre el laberinto resuelto y almacena los pasos dentro del archivo .txt
    for (const vector<int> &fila : copia_num) // Se crea un ciclo for para recorrer cada fila de la matriz de pasos para ello, se crea un vector de enteros
    {
        for (int valor : fila) // Se crea un ciclo for para recorrer cada número dentro de cada fila del laberinto para ello, se crea una variable int
        {
            resuelve << valor << " "; // Guarda el número actual dentro del archivo resuelto
        }
        resuelve << endl; // Realiza un salto de línea cuando se termine la fila actual
    }
    resuelve.close(); // Una vez creado el archivo con éxito, se cierra

    participantes(argv[0]); // Mostrar los integrantes

    return EXIT_SUCCESS; // Finaliza exitosamente el programa
}
// Procedimiento encargado de recorrer los bordes del laberinto en búsqueda de la entrada y la salida
void recorrerBordeLaberinto(vector<string> &laberinto, int filas, int columnas, int &entradaX, int &entradaY, int &salidaX, int &salidaY)
{
    // Recorrer la primera fila, en búsqueda de la entrada del laberinto
    for (int y = 0; y < columnas; y++) // Realiza un ciclo for y se crea una variable para recorrer la primera fila del laberinto
    {
        if (laberinto[0][y] == ' ') // Busca una "entrada" dentro de cada espacio de la fila
        {
            entradaX = 0; // Al ser la primera fila del laberinto se entiende que es 0
            entradaY = y; // Se almacena la posición Y dentro de la variable
            break;        // Termina la búsqueda
        }
    }
    // Recorrer la primera columna, en búsqueda de la entrada del laberinto
    if (entradaX == -1) // Si no se encuentra la entrada dentro de las filas procede a recorrer la primera columna
    {
        for (int x = 0; x < filas; x++) // Realiza un ciclo for y se crea una variable para recorrer la primera columna del laberinto
        {
            if (laberinto[x][0] == ' ') // Busca una "entrada" dentro de cada espacio de la fila
            {
                entradaX = x; // Se almacena la posición X dentro de la variable
                entradaY = 0; // Al ser la primera columna del laberinto se entiende que es 0
                break;        // Termina la búsqueda
            }
        }
    }
    // Recorrer la ultima columna, en búsqueda de la salida del laberinto
    for (int y = columnas; y > 0; y--) // Realiza un ciclo for y se crea una variable para recorrer la última columna del laberinto
    {
        if (laberinto[filas - 1][y] == ' ') // Busca una "salida" dentro de cada espacio de la fila
        {
            salidaX = filas - 1; // Al ser la última fila del laberinto se le resta 1 a la cantidad de filas ya que estas comienzan en 0
            salidaY = y;         // Se almacena la posición Y dentro de la variable
            break;               // Termina la búsqueda
        }
    }
    // Recorrer la ultima fila, en búsqueda de la salida del laberinto
    if (salidaX == -1) // Si no se encuentra la entrada dentro de las filas procede a recorrer la última fila
    {
        for (int x = filas; x > 0; x--) // Realiza un ciclo for y se crea una variable para recorrer la última fila del laberinto
        {
            if (laberinto[x][columnas - 1] == ' ') // Busca una "salida" dentro de cada espacio de la fila
            {
                salidaX = x;            // Se almacena la posición X dentro de la variable
                salidaY = columnas - 1; // Al ser la última columna del laberinto se le resta 1 a la cantidad de filas ya que estas comienzan en 0
                break;                  // Termina la búsqueda
            }
        }
    }
}
// Función que utiliza una matriz de casillas ya visitadas asignandoles true, y que retorna "True" si la casilla no cumple ninguna de las condiciones
// Función encargada de verificar el siguiente movimiento del pivote, los espacios en blanco dentro del laberinto son Movimientos Válidos
bool movimientoValido(vector<string> &laberinto, vector<vector<bool>> &visitados, int x, int y)
{
    if (x < 0 || x >= laberinto.size() || y < 0 || y >= laberinto[0].size() || laberinto[x][y] == '#' || visitados[x][y]) // Consulta por todas las posibilidades por las que no pueda ser un movimiento válido
        return false;                                                                                                     // Retorna false al cumplir con las condiciones señaladas
    return true;                                                                                                          // Retorna true ya qque se considera un movimiento válido
}
// Función que busca entre las 4 direcciones siguiente movimiento válido para mover el pivote
bool buscarCamino(vector<string> &laberinto, vector<vector<bool>> &visitados, vector<vector<int>> &copia, int x, int y, int objetivoX, int objetivoY, int contador)
{
    visitados[x][y] = true;               // Al ser un movimiento válido se guarda dentro de la matriz
    if (x == objetivoX && y == objetivoY) // Consulta si se llegó al final, comparando la posición actual con la posición de destino
    {                                     // Si es true se llegó a la salida
        return true;                      // Si se llegó al final, se termina la función
    }
    for (int i = 0; i < 4; ++i) // Realiza un ciclo for en las 4 direcciones para buscar el camino
    {
        int nuevoX = x + dx[i];                                     // Para cada dirección se calculan las nuevas coordenadas en X
        int nuevoY = y + dy[i];                                     // Para cada dirección se calculan las nuevas coordenadas en Y
        if (movimientoValido(laberinto, visitados, nuevoX, nuevoY)) // Consulta si las nuevas coordenadas son válidas para realizar un  moviemiento
        {
            copia[nuevoX][nuevoY] = contador; // Se guarda el paso actual dentro de la matriz de pasos
            // Llamada recursiva que va verificando un camino hasta que se llegue a Objetivo, sino el camino no sirve y se reemplaza por un espacio de nuevo pero ya se encuentra "visitado"
            if (buscarCamino(laberinto, visitados, copia, nuevoX, nuevoY, objetivoX, objetivoY, contador + 1)) // Realiza una llamada recursiva para buscar camino con las nuevas coordenadas
            {
                return true; // Si se encuentra un camino se encuentra un camino repite el proceso
            }
            copia[nuevoX][nuevoY] = 0; // Si no encuentra un camino, ingresa un 0 dentro de la matriz de pasos indicando que no es un movimiento valido
        }
    }
    return false; // Si no encuentra un camino, pasa a la siguiente dirección
}
// Función para encontrar el camino de números más altos en la matriz y modificar el laberinto
vector<vector<int>> encontrarCaminoHaciaMaximo(const vector<vector<int>> &matrizNumeros, vector<string> &laberinto)
{
    int n = matrizNumeros.size();    // Se crea una variable que guarda las filas de la matriz
    int m = matrizNumeros[0].size(); // Se crea una variable que guarda las columnas de la matriz

    // Encuentra la posición del número "1" en la matriz
    int x = -1, y = -1; // Se declaran estas variables para almacenar coordenadas

    for (int i = 0; i < n; ++i) // Ciclo for para recorrer las filas de la matriz de números
    {
        for (int j = 0; j < m; ++j) // Ciclo for para recorrer las columnas de la matriz de números
        {
            if (matrizNumeros[i][j] == 1) // Se busca encontrar el 1 que representa un movimiento válido dentro de la matriz
            {
                x = i; // Se almacena la coordenada de X del movimento
                y = j; // Se almacena la coordenada de Y del movimento
                break; // Termina la búsqueda
            }
        }
        if (x != -1) // Si ya se encontró la coordenada en X
            break;   // Termina la búsqueda
    }
    if (x == -1) // Si no encuentra la coordenada
    {
        cout << "No se encontró el número 1 en la matriz." << endl; // Muestra un mensaje por pantalla señalando el error
    }
    vector<vector<int>> numerosMasAltos(n, vector<int>(m, 0)); // Se crea una matriz de números más altos inicializada con 0
    // Inicia el camino en la posición del número "1"
    while (true) // Se realizará el ciclo siempre que no sea detenido
    {
        int maximoVecino = matrizNumeros[x][y]; // Se almacena la posición actual dentro de la variable maximoVecino
        int dirMaximoVecino = -1;               // Dirección del vecino con el número más alto

        // Busca el vecino con el número más alto
        for (int dir = 0; dir < 4; ++dir) // Realiza un ciclo for en las 4 direcciones para buscar el camino
        {
            int nx = x + dx[dir]; // Para cada dirección se calculan las nuevas coordenadas en X
            int ny = y + dy[dir]; // Para cada dirección se calculan las nuevas coordenadas en Y

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrizNumeros[nx][ny] > maximoVecino) // Se verifica si las coordenadas nx y ny están dentro de los límites de la matriz
            {
                maximoVecino = matrizNumeros[nx][ny]; // se actualiza maximoVecino con el nuevo valor encontrado
                dirMaximoVecino = dir;                // Se almacena la dirección donde se encontró el número más alto
            }
        }
        if (dirMaximoVecino != -1) // Consulta si no se encontró un vecino con un valor más alto
        {
            // Actualiza la matriz de números más altos
            int nx = x + dx[dirMaximoVecino];       // Para cada dirección se calculan las nuevas coordenadas en X
            int ny = y + dy[dirMaximoVecino];       // Para cada dirección se calculan las nuevas coordenadas en Y
            numerosMasAltos[nx][ny] = maximoVecino; // Se almacena en una matriz, el número más alto de los vecinos cercanos

            laberinto[nx][ny] = '*'; // Actualiza el laberinto con asteriscos en la dirección del vecino más alto

            // Avanza al siguiente paso en el camino
            x = nx;
            y = ny;
        }
        else
        {
            break; // Si no hay vecinos con números más altos, el camino ha terminado
        }
    }
    return numerosMasAltos;
    // No es necesario devolver la matriz de números más altos, ya que se pasa por referencia
}
void participantes(string programa) // Procedimiento que muestra el Título del taller, su ubicación y los integrantes
{
    cout << endl
         << "=== Taller 1 " << programa << " ===" << std::endl; // Muestra en pantalla el Nombre del taller junto con el path donde se ejecutó
    // Nombres de los integrantes del grupo
    cout << endl
         << "Diego Castillo ";
    cout << endl
         << "Javiera Gonzalez";
    cout << endl
         << "Axel Quezada" << endl;
}