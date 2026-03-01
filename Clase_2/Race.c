#include <stdio.h>      // Librería para entrada y salida estándar (printf)
#include <stdlib.h>     // Librería para funciones de utilidad general (rand, srand)
#include <pthread.h>    // Librería para manejo de hilos (pthread_create, pthread_join)
#include <unistd.h>     // Librería para funciones de control de tiempo (usleep)
#include <time.h>       // Librería para obtener la hora actual (time), usada en srand()

// Variable global compartida entre todos los hilos
int contador = 0;

// Función que ejecutará cada hilo
void *funcion_hilo(void *arg) {
    int id = *(int*)arg;  // Obtenemos el ID del hilo
    printf("Hilo %d: Iniciado\n", id);

    for (int i = 0; i < 5; i++) {
        // Leemos el valor actual del contador
        int tmp = contador;
        tmp = tmp + 1;  // Incrementamos localmente

        // Simulamos tiempos de trabajo diferente
        usleep(100 + rand() % 250);

        // Guardamos el valor incrementado de nuevo en la variable global
        contador = tmp;

        // Mostramos el valor actual del contador
        printf("Hilo %d: contador = %d\n", id, contador);
    }

    pthread_exit(NULL);  // Termina el hilo sin devolver valor
}

int main() {
    pthread_t hilos[3];  // Array para guardar los identificadores de los 3 hilos
    int ids[3];           // Array para los IDs de los hilos

    srand(time(NULL));    // Se utliza para números aleatorios

    // Crear los 3 hilos
    for (int i = 0; i < 3; i++) {
        ids[i] = i + 1;  // Asignamos ID al hilo (1, 2, 3)
        pthread_create(&hilos[i], NULL, funcion_hilo, &ids[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Mostramos el valor final del contador
    printf("Valor final del contador: %d\n", contador);
    return 0;
}