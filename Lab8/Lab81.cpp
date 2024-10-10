#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <cstdlib> 
#include <unistd.h>

#define Num_Personas 10
#define Num_Libros 5
sem_t Libros;

void* prestarLibro(void* arg) {

    std::cout << "Persona " << *(int*)arg << " esta intentando prestar un libro" << std::endl;
    sleep(1);
    sem_wait(&Libros);
    std::cout << "Persona " << *(int*)arg << " ha prestando un libro" << std::endl;
    sleep(rand() % 9 + 7);
    sem_post(&Libros); 
    std::cout << "Persona " << *(int*)arg << " ha devuelto un libro" << std::endl;
    return NULL;

}

int main(){
    pthread_t threads[Num_Personas];
    int thread_args[Num_Personas];

    sem_init(&Libros, 0, Num_Libros);

    for (int i = 0; i < Num_Personas; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, prestarLibro, &thread_args[i]);
    }

    for (int i = 0; i < Num_Personas; i++) { 
        pthread_join(threads[i], NULL); 
    }

    sem_destroy(&Libros);
    std::cout << "Fin: Todas las personas prestaron un libro" << std::endl;
    return 0;

}