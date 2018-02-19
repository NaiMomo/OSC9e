/**
 * Solution utilisant compare_and_swap de lockfree2.c
 */
#include <stdlib.h>
#define compare_and_swap __sync_val_compare_and_swap

struct tree
{
  int key;
  void *val;
  struct tree *smaller, *larger;
};

void
tree_set (struct tree **t, int key, void *val)
{
  struct tree *n = *t;
  if (n == NULL)
  {
    n = malloc (sizeof (struct tree));
    n->key = key; n->val = val;
    n->smaller = NULL; n->larger = NULL;
    if(compare_and_swap(t, NULL, n) != NULL) {
      free(n);
      n = *t;
    }
    else {
      return;
    }
  }

  if (key == n->key)
  {
    n->val = val; // Unavoidable course condition (the slowest will win).
  }
  else if (key < n->key)
  {
    tree_set (&n->smaller, key, val);
  }
  else
  { /* key > t->key */
    tree_set (&n->larger, key, val);
  }
}
