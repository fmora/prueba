# Código de Prueba
Descripción: Implementación de Dijkstra and Dial


# Ambiente de desarrollo
SO RHEL 6.5 y g++ 4.4.7.


# Instalación
Copiar archivos en carpeta a ejecutar.
Los archivos de textos deben ser copiados en la misma ruta que el código, el archivo resultado se generará en la misma ruta.
Ejecutar el comando 'make' en el directorio.


# Uso
En la carpeta del programa, se debe contar con los archivos nodos.txt y arcos.txt.
El archivo de nodos.txt debe contener el número de nodos que estarán en la topología a revisar (se crean nodos consecutivos desde 1 hasta la cantidad de nodos definidos).
El archivo arcos.txt debe contener todas las rutas de un salto entre par de nodos. Esta se definen por línea con la siguiente nomenclatura: <nodo origen> <nodo destino> <costo o distancia de la ruta>

Para llamar al programa, escribir ./algorithm
El programa consultará por consola el mensaje 
"Enter Source Node:"
Ingresar el número de nodo a seleccionar como punto de inicio.

Luego el programa consultará por consola el mensaje 
"Available algorithm
Enter 1 for Dijkstra
Enter 2 for Dial
Enter option:" 
Ingresar el número del algoritmo a ejecutar (1 o 2).
Como resultado, el programa creará/modificará el archivo salida.txt con la solución.


# Funciones
int readFiles(): Lee archivos de entrada. Retorna la cantidad de archivos que pudo leer (0, 1 ó 2).
void writeFile(): Genera archivo de salida salida.txt con el resultado.
void initValue(): inicializa variables de sistema.
void dijkstra(): función en base a algoritmo Dijkstra.
void dijkstra_recalDist(): función para recalculo de rutas de Dijkstra.
void dial(): función en base a algoritmo Dial.

# Autor
Fernando Mora Pastén
