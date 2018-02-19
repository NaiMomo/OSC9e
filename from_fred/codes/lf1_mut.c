/**
 * Solution utilisant des mutex de lockfree1.c
 */
#include <stdlib.h>
#define compare_and_swap __sync_val_compare_and_swap

pthread_mutex_t m;

// Solution start here
struct tree
{
  int key;
  void *val;
  struct tree *smaller, *larger;
};

struct tree *
tree_insert (struct tree *t, int key, void *val)
{
  struct tree *n = t;
  if (t == NULL) // une feuille
  {
    n->key = key;
    n->val = val;
    n->smaller = NULL;
    n->larger = NULL;
  }
  else if (key == t->key) // noeud trouvé
  {
    n->key = key;
    n->val = val;
    n->smaller = t->smaller;
    n->larger = t->larger;
  }
  else if (key < t->key)
  {
    n->key = t->key;
    n->val = t->val;
    n->larger = t->larger;
    n->smaller = tree_insert (t->smaller, key, val);
  }
  else
  {				/* key > t->key */
    n->key = t->key;
    n->val = t->val;
    n->smaller = t->smaller;
    n->larger = tree_insert (t->larger, key, val);
  }
  return n;
}

void
tree_set (struct tree **t, int key, void *val)
{
  mutex_lock(&m);
  *t = tree_insert (*t, key, val);
  mutex_unlock(&m);
}
