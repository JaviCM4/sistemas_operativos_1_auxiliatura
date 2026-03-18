#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

bool quiere[2] = {false, false};
int turno = 0;
int contador = 0;
const int ITERACIONES_P0 = 3;
const int ITERACIONES_P1 = 5;

void *proceso_0(void *arg) {
    for (int i = 0; i < ITERACIONES_P0; i++) {
        quiere[0] = true; // Indicamos que tenemos interes en entrar a la RC

        // Si quiere[1] = false, no entramos al bucle y pasamos a la RC
        // Si quiere[1] = true, entramos al bucle y esperamos mientras el proceso P1 realize sus acciones
        while (quiere[1]) {

            // Si turno = 1 Le toca a P1, cedemos nuestro turno
            // Si turno = 0 esperamos dentro del primer bucle a que el P1 termine y ponga a turno = 1
            // (SIRVE CUANDO AMBOS PROCESOS LEVANTAN SU BANDERA)

            // turno desempata cuando AMBOS procesos quieren entrar simultáneamente.
            // Si turno = 1: no es nuestro turno, entramos al if, bajamos bandera, esperamos
            //               hasta que P1 salga de su RC y ponga turno = 0
            // Si turno = 0: es nuestro turno, permanecemos en el while exterior
            //               esperando a que P1 baje su bandera (quiere[1] = false)
            if (turno != 0) {
                quiere[0] = false;  // Bajamos nuestra bandera indicando que ya no queremos entrar a la RC

                // Nos quedamos en espera de que el otro proceso termine y que cambie el valor de turno = 0
                while (turno != 0) {
                    // Espera activa
                }
                quiere[0] = true;  // El proceso P1 finalizo y ahora subimos nuestra bandera para mostrar interes
            }
        }

        // ============================ Región Crítica ============================
        printf("P0: Entrando a la RC (iteración %d)\n", i);

        int temp = contador;
        temp++;
        contador = temp;
        printf("P0: Contador incrementado a %d\n", contador);
        printf("P0: Saliendo de la RC\n\n");
        sleep(1);
        // ============================ Región Crítica ============================

        turno = 1; // Cedemos el turno al otro proceso
        quiere[0] = false; // Indicamos que ya no queremos entrar a la RC

        sleep(1);
    }

    printf("===================================\n");
    printf("P0: ¡TERMINÉ TODAS MIS ITERACIONES!\n");
    printf("===================================\n\n");

    return NULL;
}

void *proceso_1(void *arg) {
    for (int i = 0; i < ITERACIONES_P1; i++) {
        quiere[1] = true; // Indicamos que queremos entrar

        // Si quiere[0] = false, no entramos al bucle y pasamos a la RC
        // Si quiere[0] = true, entramos al bucle y esperamos mientras el proceso P0 realize sus acciones
        while (quiere[0]) {

            // turno desempata cuando AMBOS procesos quieren entrar simultáneamente.
            // Si turno = 0: no es nuestro turno, entramos al if, bajamos bandera, esperamos
            //               hasta que P0 salga de su RC y ponga turno = 1
            // Si turno = 1: es nuestro turno, permanecemos en el while exterior
            //               esperando a que P0 baje su bandera (quiere[0] = false)
            if (turno != 1) {
                quiere[1] = false; // Bajamos nuestra bandera indicando que ya no queremos entrar a la RC

                // Nos quedamos en espera de que el otro proceso termine y que cambie el valor de turno = 1
                while (turno != 1) {
                    // Espera activa
                }
                quiere[1] = true; // El proceso P0 finalizo y ahora subimos nuestra bandera para mostrar interes
            }
        }

        // ============================ Región Crítica ============================
        printf("P1: Entrando a región crítica (iteración %d)\n", i);

        int temp = contador;
        sleep(1);
        temp++;
        contador = temp;
        printf("P1: Contador incrementado a %d\n", contador);
        printf("P1: Saliendo de RC\n\n");
        sleep(1);
        // ============================ Región Crítica ============================

        turno = 0;  // Cedemos el turno al otro proceso
        quiere[1] = false;  // Indicamos que ya no queremos entrar a la RC

        sleep(1);
    }

    printf("===================================\n");
    printf("P1: ¡TERMINÉ TODAS MIS ITERACIONES!\n");
    printf("===================================\n\n");

    return NULL;
}

int main() {
    pthread_t hilo0, hilo1;

    printf("\n=============================\n");
    printf("INICIANDO ALGORITMO DE DEKKER\n");
    printf("=============================\n\n");

    pthread_create(&hilo0, NULL, proceso_0, NULL);
    pthread_create(&hilo1, NULL, proceso_1, NULL);

    pthread_join(hilo0, NULL);
    pthread_join(hilo1, NULL);

    return 0;
}