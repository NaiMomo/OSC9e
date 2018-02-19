/**
 * Solution utilisant des mutex de lockfree2.c
 */
#include <stdlib.h>
#include <pthread.h>
struct tree {
  pthread_mutex_t m;
  int key;
  void* val;
  struct tree *smaller, *larger;
};

struct tree_head {
  pthread_mutex_t m;
  struct tree *head;
};

void tree_set_internal(struct tree* s, int key, void *val)
{
  struct tree *n;
  pthread_mutex_lock(&s->m);
  if(key == s->key)
  {
    s->val = val;
    pthread_mutex_unlock(&s->m);
  }
  else if(key < s->key)
  {
    if(s->smaller == NULL)
    {
      n = malloc(sizeof(struct tree));
      pthread_mutex_init(&n->m, NULL);
      n->key = key;
      n->val = val;
      s->smaller = n;
      pthread_mutex_unlock(&s->m);
    }
    else
    {
      pthread_mutex_unlock(&s->m);
      tree_set_internal(s->smaller, key, val);
    }
  }
  else
  {
    if(s->larger == NULL)
    {
      n = malloc(sizeof(sizeof(struct tree)));
      pthread_mutex_init(&n->m, NULL);
      n->key = key;
      n->val = val;
      s->larger = n;
      pthread_mutex_unlock(&s->m);
    }
    else
    {
      pthread_mutex_unlock(&s->m);
      tree_set_internal(s->larger, key, val);
    }
  }

}

void tree_set(struct tree_head* th, int key, void *val)
{
  struct tree *n;
  if(th->head == NULL)
  {
    pthread_mutex_lock(&th->m);
    if(th->head == NULL)
    {
      n = malloc(sizeof(struct tree));
      pthread_mutex_init(&n->m, NULL);
      n->key = key; n->val = val;
      th->head = n;
      pthread_mutex_unlock(&th->m);
    }
    else
    {
      pthread_mutex_unlock(&th->m);
      tree_set_internal(th->head, key, val);
    }
  }
  else
  {
    tree_set_internal(th->head, key, val);
  }
}

