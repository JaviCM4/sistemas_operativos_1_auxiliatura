#include <stdio.h>      // Librería para entrada y salida estándar (printf)
#include <stdlib.h>     // Librería para funciones generales (rand, srand)
#include <pthread.h>    // Librería para manejo de hilos (pthread_create, mutex, etc.)
#include <unistd.h>     // Librería para control de tiempo (usleep)
#include <time.h>       // Librería para obtener la hora actual (time)

// Variable global compartida entre todos los hilos
int contador = 0;

// Declaración e inicialización de un mutex (candado)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Función que ejecutará cada hilo
void *funcion_hilo(void *arg) {
    int id = *(int*)arg;  // Obtenemos el ID del hilo
    printf("Hilo %d: Iniciado\n", id);

    for (int i = 0; i < 5; i++) {

        // Bloqueamos el mutex antes de acceder a la variable compartida
        // Esto evita que dos hilos modifiquen "contador" al mismo tiempo
        pthread_mutex_lock(&mutex);

        // Leemos el valor actual del contador
        int tmp = contador;

        // Incrementamos el valor localmente
        tmp = tmp + 1;

        // imulamos tiempos de trabajo diferente
        usleep(100 + rand() % 1950);

        // Guardamos el valor actualizado en la variable global
        contador = tmp;

        // Mostramos el valor actual del contador
        printf("Hilo %d: contador = %d\n", id, contador);

        // Desbloqueamos el mutex para que otro hilo pueda entrar
        pthread_mutex_unlock(&mutex);
    }

    // Finaliza la ejecución del hilo
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[3];  // Array para almacenar los identificadores de los 3 hilos
    int ids[3];          // Array para los IDs de cada hilo

    // Inicializamos la semilla para números aleatorios
    srand(time(NULL));

    // Creamos los 3 hilos
    for (int i = 0; i < 3; i++) {
        ids[i] = i + 1;  // Asignamos IDs 1, 2 y 3
        pthread_create(&hilos[i], NULL, funcion_hilo, &ids[i]);
    }

    // Esperamos a que todos los hilos terminen su ejecución
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Mostramos el valor final del contador
    printf("Valor final del contador: %d\n", contador);

    // Liberamos los recursos asociados al mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}