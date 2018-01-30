/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Solaris users must enter
 * gcc thrd.c -lpthreads
 *
 * Figure 4.9
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */
int num_threads;

void *runner(void *endpoints); /* the thread */

struct interval {
  unsigned int start;
  unsigned int end;
};

int main(int argc, char *argv[])
{
  pthread_attr_t attr; /* set of attributes for the thread */
  pthread_t tid[num_threads]; /* the thread identifier */

  
  if (argc != 3) {
    fprintf(stderr,"usage: a.out <integer value>\n");
    /*exit(1);*/
    return -1;
  }

  if (atoi(argv[1]) < 0) {
    fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
    /*exit(1);*/
    return -1;
  }

  num_threads = atoi(argv[2]);
  int j;
  sum = 0;
  int start = 1;
  int input = atoi(argv[1]);
  int end = input/num_threads;
  
  for(j=0;j<num_threads;j++){
    /* get the default attributes */
    pthread_attr_init(&attr);

    //    This code works
    /* struct interval* inter = malloc(sizeof(struct interval)); */
    /* inter->start = start; */
    /* inter->end = end; */
    /* pthread_create(&tid[j],&attr,runner, (void *) inter); */

    // This code does not
    struct interval inter;
    inter.start=start;
    inter.end  =end;
    pthread_create(&tid[j],&attr,runner, (void *) &inter);

    start = end + 1;
    end = end + input/num_threads;
  }
  for(j=0;j<num_threads;j++){
    /* now wait for the thread to exit */
    pthread_join(tid[j],NULL);
  }
  
  printf("sum = %d\n",sum);
}

/**
 * The thread will begin control in this function
 */
void *runner(void* input_interval)
{
  struct interval* inter = (struct interval*) input_interval;
  int i;

  printf("Start = %d, end = %d \n", inter->start, inter->end);
  
  for (i = inter->start; i <= inter->end; i++)
    sum += i;

  //  free(inter);
  pthread_exit(0);
}
