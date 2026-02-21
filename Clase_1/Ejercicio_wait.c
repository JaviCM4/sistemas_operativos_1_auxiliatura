// Librería de entrada y salida estándar (printf, scanf, etc.)
#include <stdio.h>

// Proporciona acceso a llamadas al sistema POSIX (fork, getpid, sleep, etc.)
#include <unistd.h>

// Define tipos de datos utilizados por el sistema (pid_t, size_t, etc.)
#include <sys/types.h>

// Proporciona el uso de funciones y macros para esperar procesos hijos
#include <sys/wait.h>

// Proporciona funciones y macros generales de utilidad para manejo de memoria y control de procesos
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;
    int tiempo_trabajo;

    printf("\n======== DEMOSTRACIÓN DE wait() ========\n\n");

    // Crear proceso hijo
    pid = fork();

    if (pid < 0) {
        printf("Error: No se pudo crear el proceso hijo\n");
        return EXIT_FAILURE;

    } else if (pid == 0) {
        // ===== PROCESO HIJO =====
        sleep(1);
        printf("\n=== PROCESO HIJO ===\n");
        printf("    Mi PID: %d\n", getpid());

        tiempo_trabajo = 5;
        printf("    HIJO: Trabajará por %d segundos\n", tiempo_trabajo);

        sleep(tiempo_trabajo);

        printf("    HIJO: Trabajo completado\n");

        // Cambia aquí para probar éxito o error
        int hubo_error = 0;

        if (hubo_error) {
            printf("    HIJO: Terminando con EXIT_FAILURE\n");
            return EXIT_FAILURE;
        } else {
            printf("    HIJO: Terminando con EXIT_SUCCESS\n");
            return EXIT_SUCCESS;
        }

    } else {
        // ===== PROCESO PADRE =====
        printf("=== PROCESO PADRE ===\n");
        printf("    Mi PID: %d\n", getpid());

        pid_t hijo_terminado = wait(&status);

        printf("\n=== PROCESO PADRE ===\n");
        printf("    PADRE: El hijo PID=%d ha terminado\n", hijo_terminado);

        if (WIFEXITED(status)) {
            int codigo_salida = WEXITSTATUS(status);

            if (codigo_salida == EXIT_SUCCESS) {
                printf("    PADRE: El hijo terminó correctamente (EXIT_SUCCESS)\n");
            } else if (codigo_salida == EXIT_FAILURE) {
                printf("    PADRE: El hijo terminó con error (EXIT_FAILURE)\n");
            }
        } else {
            printf("    PADRE: El hijo terminó anormalmente\n");
        }

        printf("    PADRE: Proceso Terminado\n");
    }

    return EXIT_SUCCESS;
}
