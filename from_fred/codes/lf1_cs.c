/**
 * Solution utilisant compare_and_swap de lockfree1.c
 */
#include <stdlib.h>
#define compare_and_swap __sync_val_compare_and_swap

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
  struct tree *n = malloc (sizeof(struct tree));
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

void tree_free(struct tree *t) {
  if (!t) {
    tree_free(t->larger);
    tree_free(t->smaller);
    free(t);
  }
}

void
tree_set (struct tree **t, int key, void *val)
{
  struct tree *n = NULL; // newval
  struct tree *s = NULL; // oldval
  do
  {
    if(n){ // gestion memoire
      tree_free(n); // possible bug
      n = NULL;
    }
    s = *t;
    n = tree_insert (s, key, val);
  }
  while (s != compare_and_swap (t, s, n));
}

int main()
{
  struct tree *t = NULL;


}
