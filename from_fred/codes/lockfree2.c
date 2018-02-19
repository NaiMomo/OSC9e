/**
 * Code de la question 2 sur lockfree de la demo 5.
 */
#include <stdlib.h>

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
    *t = n;
  }
  else if (key == n->key)
  {
    n->val = val;
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
