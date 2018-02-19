/**
 * Code de la question 1 sur lockfree de la demo 5.
 */
#include <stdlib.h>

struct tree
{
  int key;
  void *val;
  struct tree *smaller, *larger;
};

struct tree *
tree_insert (struct tree *t, int key, void *val)
{
  struct tree *n = malloc (sizeof (struct tree));
  if (t == NULL) // Test pour NULL pointer
  {
    n->key = key; n->val = val;
    n->smaller = NULL; n->larger = NULL;
  }
  else if (key == t->key)
  {
    n->key = key; n->val = val;
    n->smaller = t->smaller; n->larger = t->larger;
  }
  else if (key < t->key)
  {
    n->key = t->key; n->val = val; // key->val
    n->larger = t->larger;
    n->smaller = tree_insert (t->smaller, key, val);
    return n;
  }
  else
  { /* key > t->key */
    n->key = t->key; n->val = t->val;
    n->smaller = t->smaller;
    n->larger = tree_insert (t->larger, key, val);
  }
  return n;
}

void
tree_set (struct tree **t, int key, void *val)
{
  *t = tree_insert (*t, key, val);
}
