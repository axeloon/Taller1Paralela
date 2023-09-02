#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

//Procedimiento para encontrar las posiciones de entrada y salidas.
void recorrerBordeLaberinto(vector<string> &laberinto, int filas, int columnas, int &entradaX, int &entradaY, int &salidaX, int &salidaY){
    // Recorrer la primera fila
    for (int y = 0; y < columnas; y++){
        if (laberinto[0][y] == ' '){
            entradaX = 0;
            entradaY = y;
            break;
        }
    }
    // Recorrer la primera columna
    if (entradaX == -1){
        for (int x = 0; x < filas; x++){
            if (laberinto[x][0] == ' '){
                entradaX = x;
                entradaY = 0;
                break;
            }
        }
    }
    // Recorrer la ultima fila
    for (int y = columnas; y > 0; y--){
        if (laberinto[filas - 1][y] == ' '){
            salidaX = filas - 1;
            salidaY = y;
            break;
        }
    }
    // Recorrer la ultima columna
    if (salidaX == -1){
        for (int x = filas; x > 0; x--){
            if (laberinto[x][columnas - 1] == ' '){
                salidaX = x;
                salidaY = columnas - 1;
                break;
            }
        }
    }
}
//Función que utiliza una matriz de casillas ya visitadas asignandoles true, y que retorna "True" si la casilla no cumple ninguna de las condiciones
bool movimientoValido(vector<string> &laberinto, vector<vector<bool>> &visitados, int x, int y){
    if (x < 0 || x >= laberinto.size() || y < 0 || y >= laberinto[0].size() || laberinto[x][y] == '#' || visitados[x][y])
        return false;
    return true;
}
bool buscarCamino(vector<string> &laberinto, vector<vector<bool>> &visitados, vector<vector<int>> &copia, int x, int y, int objetivoX, int objetivoY, int contador){
    visitados[x][y] = true;
    if (x == objetivoX && y == objetivoY){//Si es true se llegó a la salida
        return true;
    }
    for (int i = 0; i < 4; ++i){
        int nuevoX = x + dx[i];
        int nuevoY = y + dy[i];
        if (movimientoValido(laberinto, visitados, nuevoX, nuevoY)){
            copia[nuevoX][nuevoY] = contador;
            //cout << contador << endl;
            if (buscarCamino(laberinto, visitados, copia, nuevoX, nuevoY, objetivoX, objetivoY, contador + 1)){//Llamada recursiva que va verificando un camino hasta que se llegue a Objetivo, sino el camino no sirve y se reemplaza por un espacio de nuevo pero ya se encuentra "visitado"
                return true;
            }
            copia[nuevoX][nuevoY] = 0;
        }
    }
    return false;
}

// Función para encontrar el camino de números más altos en la matriz y modificar el laberinto
vector<vector<int>> encontrarCaminoHaciaMaximo(const vector<vector<int>>& matrizNumeros, vector<string>& laberinto) {
    int n = matrizNumeros.size();
    int m = matrizNumeros[0].size();

    // Encuentra la posición del número "1" en la matriz
    int x = -1, y = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrizNumeros[i][j] == 1) {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1) break;
    }
    if (x == -1) {
        cout << "No se encontró el número 1 en la matriz." << endl;
    }

    // Crear una matriz de números más altos inicializada con 0
    vector<vector<int>> numerosMasAltos(n, vector<int>(m, 0));
    // Inicia el camino en la posición del número "1"
    while (true) {
        int maximoVecino = matrizNumeros[x][y];
        int dirMaximoVecino = -1; // Dirección del vecino con el número más alto

        // Busca el vecino con el número más alto
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrizNumeros[nx][ny] > maximoVecino) {
                maximoVecino = matrizNumeros[nx][ny];
                dirMaximoVecino = dir;
            }
        }

        if (dirMaximoVecino != -1) {
            // Actualiza la matriz de números más altos
            int nx = x + dx[dirMaximoVecino];
            int ny = y + dy[dirMaximoVecino];
            numerosMasAltos[nx][ny] = maximoVecino;

            // Actualiza el laberinto con asteriscos en la dirección del vecino más alto
            laberinto[nx][ny] = '*';

            // Avanza al siguiente paso en el camino
            x = nx;
            y = ny;
        } else {
            // Si no hay vecinos con números más altos, el camino ha terminado
            break;
        }
    }
    return numerosMasAltos;
    // No es necesario devolver la matriz de números más altos, ya que se pasa por referencia
}

int main(int argc, char **argv){
    srand(time(0));
    int filas = 0;
    int columnas = 0;
    int cont=0;
    int entradaX = -1, entradaY = -1, salidaX = -1, salidaY = -1;
    vector<string> laberinto;
    string linea;
    ifstream archivo("..//laberintoprueba.txt");
    if (!archivo){
        cerr << "Error" << endl;
        return 1;
    }
    while (getline(archivo, linea)){ // Vector de strings en vez de un arreglo[][] de char, columna y filas permiten la separación
        laberinto.push_back(linea);
        if (linea.length() > columnas){
            columnas = linea.length();
        }
        filas++;
    }
    for (const string &fila : laberinto){//Recorre el laberinto sin camino
        for (char c : fila){
            cout << c;
        }
        cout << endl;
    }
    vector<vector<bool>> visitados(filas, vector<bool>(columnas, false));
    vector<vector<int>> copia(filas, vector<int>(columnas));
    recorrerBordeLaberinto(laberinto, filas, columnas, entradaX, entradaY, salidaX, salidaY);
    cout << "Entradas: " << entradaX << ", " << entradaY << endl;
    cout << "Salidas: " << salidaX << ", " << salidaY << endl;
    copia[entradaX][entradaY]=1;
    laberinto[entradaX][entradaY]='*';
    buscarCamino(laberinto, visitados, copia, entradaX, entradaY, salidaX, salidaY, 2);
    vector<vector<int>> copia_num=encontrarCaminoHaciaMaximo(copia, laberinto);
    for (const string &fila : laberinto){
        for (char c : fila){
            cout << c;
        }
        cout << endl;
    }
    ofstream resuelto;
    resuelto.open("..//laberintoResuelto.txt", ios::out);
    if(resuelto.fail()){
        cerr << "Error en la creacion del archivo" << endl;
        return 1;
    }
    //Recorre el laberinto vacío
    for (const string &fila : laberinto){
        for (char c :fila) {
            resuelto << c;
        }
        resuelto << endl;
    }

    resuelto.close();

    ofstream resuelve;
    resuelve.open("..//laberintoResueltonum.txt", ios::out);
    if(resuelto.fail()){
        cerr << "Error en la creacion del archivo" << endl;
        return 1;
    }
    //Recorre el laberinto vacío
    for (const vector<int> &fila : copia_num){
        for (int valor : fila){
            resuelve << valor <<" ";
        }
        resuelve << endl;
    }
    resuelve.close();
/*for (const vector<int> &fila : copia_num){
        for (int valor : fila){
            cout << valor << " ";
        }
        cout << endl;
    }*/
    return EXIT_SUCCESS;
}
