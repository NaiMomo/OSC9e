/*
 * Auteur: Frédéric Hamel
 * Date: 7 Février 2017
 * Compilation step:
 *  > nasm -f elf64 swap.s
 *  > gcc -o mutex_swap mutex_swap.o swap.o
 **/
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

// Ressource partage entre les threads.
bool mutex = false;

// La fonction qui permet de prendre la ressource.
extern void acquire(bool *lock);

// Relache la ressource.
void release(bool *lock)
{
  *lock = false;
}

// Routine qui acquiert la ressource
// puis la relache.
void* routine(void *args) {
  acquire(&mutex);
  printf("Acquiert la ressource apres l'attente.\n");
  release(&mutex);
  return NULL;
}

int main()
{
  pthread_t tid;
  // Le thread principal acquiert la ressource.
  acquire(&mutex);
  // Creation d'un thread.
  pthread_create(&tid, NULL, &routine, NULL);
  // Une pause
  getchar();
  // Release le mutex.
  release(&mutex);
  // Attend la terminaison du thread.
  pthread_join(tid, NULL);
  return 0;
}
