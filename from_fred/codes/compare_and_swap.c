/*
 * Auteur: Frédéric Hamel
 * Date: 7 Février 2017
 * Compilation step:
 *  > gcc -pthread -o compare_and_swap compare_and_swap.c
 **/
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

// Ressource partage entre les threads.
bool mutex = false;

// La fonction qui permet de prendre la ressource.
void acquire(bool *lock)
{
  if(!__sync_bool_compare_and_swap(lock, false, true)) {
    // Si la resource n'est pas libere il y a death lock.
    printf("[tid=%ld]: Attente\n", syscall(SYS_gettid));
    while(!__sync_bool_compare_and_swap(lock, false, true));
  }
  printf("[tid=%ld]: Rentrer dans la section critique\n", syscall(SYS_gettid));
}

// Relache la ressource.
void release(bool *lock)
{
  printf("[tid=%ld]: Quitte la section critique\n", syscall(SYS_gettid));
  *lock = false;
}

// Routine qui acquiert la ressource
// puis la relache.
void* routine(void *args) {
  acquire(&mutex);
  printf("[tid=%ld]: Acquiert la ressource apres l'attente.\n", syscall(SYS_gettid));
  release(&mutex);
  pthread_exit(NULL);
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
