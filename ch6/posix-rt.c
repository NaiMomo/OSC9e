/**
 * A simple pthread program illustrating RT pthread scheduling.
 *
 * Figure 6.20
 *
 * To compile:
 *
 *	gcc posix-rt.c -o posix-rt -lpthread
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#define NUM_THREADS 5

/* the thread runs in this function */
void *runner(void *param); 
struct sched_param {  
  int sched_priority;
};

int main(int argc, char *argv[])
{
  int i, policy,priority, ret;
  priority=10;
  sched_param param;
  pthread_t tid[NUM_THREADS]; 	/* the thread identifier */
  pthread_attr_t attr; 		/* set of attributes for the thread */

  /* get the default attributes */
  pthread_attr_init(&attr);

  /* get the current scheduling policy */
  if (pthread_attr_getschedpolicy(&attr,&policy) != 0)
    fprintf(stderr, "Unable to get policy.\n");
  else {
    if (policy == SCHED_OTHER)
      printf("SCHED_OTHER\n");
    else if (policy == SCHED_RR)
      printf("SCHED_RR\n");
    else if (policy == SCHED_FIFO)
      printf("SCHED_FIFO\n");
  }
  
  /* set the scheduling policy - FIFO, RT, or OTHER */
  if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0)
    printf("unable to set scheduling policy to SCHED_OTHER \n");
  
  /* create the threads */
  for (i = 0; i < NUM_THREADS; i++){
    /* safe to get existing scheduling param */
    ret = pthread_attr_getschedparam (&attr, &param);
    param.sched_priority = priority;
    /* setting the new scheduling param */
    ret = pthread_attr_setschedparam (&attr, &param);
    priority--;
    pthread_create(&tid[i],&attr,runner,NULL);
  }
  
  /**
   * Now join on each thread
   */
  for (i = 0; i < NUM_THREADS; i++) 
    pthread_join(tid[i], NULL);
}

/**
 * The thread will begin control in this function.
 */
void *runner(void *param) 
{
  for (int i=0;i<10;i++){
    printf("hello %d \n",i);
    //    sleep(1);
  }

  pthread_exit(0);
}

