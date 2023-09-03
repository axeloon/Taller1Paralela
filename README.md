# Taller n°01 Computación Paralela y Distribuida
Taller 01 Computación Paralela y Distribuida 2023-02
* Profesor: Sebastián Salazar Molina

 ## Integrantes
 * Diego Castillo Arias
 * Javiera González Rojas
 * Axel Quezada Calquín

## Instrucciones:
 Para el funcionamiento de la app se debe tener instaladas el conjutno de herramientas y librerias de MinGW. 
 Además si utiliza la IDE VisualStudio debe instalar las extensiones 
 * CodeRunner
 * CMake 
 * Cmake Tools 
 * C/C++ Compile Run. 

 Si desea cargar un nuevo laberito, debe adjuntar un archivo tipo .txt, dentro de la carpeta "app" y cambiar el nombre dentro del archivo main.cpp, en la linea 28. 

 ## Funcionamineto
 A Continuación, se presenta un breve resumen del funcionamiento del codigo, para una explicación más detallada leer los comentarios de mismo codigo.

* Primeramente se implementa unas función que  se encarga de encontrar las posiciones de entrada y salida en el laberinto, recorriendo sus bordes.
* Luego, la siguiente función comprueba si un movimiento a una posición dada en el laberinto es válido, es decir, si no se sale de los límites del laberinto y si la casilla no está marcada como visitada ni es un obstáculo.
* A continuación, se implementa una función que utiliza una búsqueda recursiva para encontrar un camino desde la entrada hasta la salida del laberinto. Marca las casillas visitadas y registra el camino en una matriz. Si encuentra un camino válido, lo devuelve.
* Finalmente, para encontrar el camino correcto, se implemneta la ultima función que se encarga de encontar un camino desde la posición del número "1" en una matriz de pasos realizados hacia el número más alto, registrando este camino con asteriscos en el laberinto. Esta función modifica tanto la matriz de números como el laberinto. 

## Resultados
Para el laberinto propuesto, se muestra lo siquiente en consola:

<img src="resultado laberinto.png"  background="#e8e8e8" padding="2px">


Donde:

* *: Representa un camino transitado o espacio libre.
* #: Representa una pared u obstáculo, es decir, una parte del laberinto que no se puede atravesar.
* Espacios en blanco: También representan espacios transitables.
Dado este patrón, podemos identificar la estructura general del laberinto:

* La entrada del laberinto parece estar en la esquina superior izquierda, marcada por un espacio en blanco.
* La salida del laberinto parece estar en la esquina inferior derecha, marcada por un espacio en blanco.
* El camino solución para este laberinto esta representado por *.