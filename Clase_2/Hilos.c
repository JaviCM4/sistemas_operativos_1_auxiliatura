#include <stdio.h>      // Librería para entrada y salida estándar (printf)
#include <stdlib.h>     // Librería para funciones de utilidad general (malloc, free)
#include <pthread.h>    // Librería para manejo de hilos (pthread_create, pthread_join)
#include <unistd.h>     // Librería para funciones de control de tiempo (sleep)

// Función que ejecutará cada hilo
void *funcion_hilo(void *arg) {
    // Se recibe un puntero a entero, que corresponde al ID del hilo
    int id = *(int*)arg;

    printf("    Hilo %d: Iniciado\n", id);
    sleep(2);

    printf("    Hilo %d: Trabajando 2 segundos\n", id);
    sleep(1);

    printf("    Hilo %d: Termino\n", id);

    // Reservamos memoria para el resultado que se devolverá al hilo principal
    int *resultado = malloc(sizeof(int));
    if (resultado == NULL) {
        printf("    Hilo %d: Error al reservar memoria\n", id);
        pthread_exit(NULL);
    }

    // Guardamos un resultado calculado
    *resultado = id * 10;

    // Terminamos el hilo devolviendo el puntero al resultado
    pthread_exit((void*)resultado);
}

int main() {
    pthread_t hilos[3];  // Array para guardar los identificadores de los 3 hilos
    int ids[3];           // Array para guardar los IDs de los hilos

    printf("\n========================\n");
    printf("EJERCICIO 1: CREAR HILOS\n");
    printf("========================\n\n");

    printf("Creando 3 hilos\n\n");

    // Crear los 3 hilos
    for (int i = 0; i < 3; i++) {
        ids[i] = i + 1;  // Asignamos ID a cada hilo (1, 2, 3)

        // Se crea el hilo que ejecutará la función 'funcion_hilo'
        if (pthread_create(&hilos[i], NULL, funcion_hilo, &ids[i]) != 0) {
            printf("    ERROR: No se pudo crear hilo %d\n", i+1);
            return 1;  // Salir si falla la creación de algún hilo
        }
    }

    sleep(1);
    printf("    Todos los hilos creados\n");
    printf("    Esperando a que terminen...\n\n");

    // Esperar a que cada hilo termine y recoger su resultado
    for (int i = 0; i < 3; i++) {
        void *retorno;  // Puntero para recibir el valor devuelto por el hilo

        if (pthread_join(hilos[i], &retorno) != 0) {
            printf("    ERROR al hacer join del hilo %d\n", i+1);
            continue;
        } else {
            if (retorno != NULL) {
                // Convertimos el puntero de vuelta a entero y mostramos el resultado
                int resultado = *(int*)retorno;
                printf("    Hilo: %d terminó con resultado: %d\n", i+1, resultado);
                free(retorno);  // Liberamos la memoria reservada en el hilo
            }
        }
    }

    printf("\n==========================\n");
    printf("TODOS LOS HILOS TERMINARON\n");
    printf("==========================\n");

    // Termina el hilo principal, liberando recursos de pthread
    pthread_exit(NULL);
}