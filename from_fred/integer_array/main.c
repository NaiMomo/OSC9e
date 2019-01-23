// Author: Frédéric Hamel
// Date: Jan 23, 2019
//
// Description: Exemple de création de tableau dynamique
// en C. Ce programme lit des entier de l'utilisateur avec
// "scanf" (pas approprié pour les chaine de caractère) jusqu'à
// ce que l'utilisateur envoie un EOF (appui sur CTRL+D).
//
// La structure "integer_array_t" utilisé est composé de trois champs: data, size et nbElem.
// Le champs "data" contient les entiers que l'utilisateur a entré.
// Le champs "size" est la taille du tableau "data".
// Le champs "nbElem" est le nombre d'éléments actuellement dans le tableau "data".
//
// Note: le nombre d'élément n'est pas forcément égal à la taille du tableau.
//
// Les fonctions pour manipuler la structure "integer_array_t" sont:
//
// - integer_array_init(struct integer_array_t *self, size_t size):
//      Initialise les champs structure self et alloue un tableau de taille
//      initial "size" qui est assigné à "self->data".
//
// - integer_array_expand(struct integer_array_t *self):
//      Agrandit la espace disponible du tableau dans le champs "data".
//
// - integer_array_append(struct integer_array_t *self, int e):
//      Ajoute l'élément "e" à la fin du table "self->data" agrandissant
//      l'espace au besoin.
//
// Pour libérer un "struct integer_array_t", il suffit d'invoquer la procédure
// "free" sur le champs "data".
//
// Note: Cette exemple ne fait pas de "error checking" sur la valeur de retour
// de "malloc" et "realloc".
//
// Note: Il est possible d'adapter cette exemple pour des tableau de différent
// type autre que les entier (par exemple des caractères ou même des chaine de
// caractère).
#include <stdio.h>
#include <stdlib.h>

struct integer_array_t {
    int *data;
    size_t size;
    size_t nbElem;
};

void
integer_array_init(struct integer_array_t *self, size_t size) {
    self->nbElem = 0;
    self->size = size;
    self->data = malloc(size * sizeof(*self->data));
}

void
integer_array_expand(struct integer_array_t *self) {
    self->size = self->size << 1;
    self->data = realloc(self->data, self->size * sizeof (*self->data));
}

void
integer_array_append(struct integer_array_t *self, int elem) {
    size_t i = self->nbElem++;
    if (self->nbElem == self->size) {
        integer_array_expand(self);
    }
    self->data[i] = elem;
}

int main() {
    // pas error checking.
    struct integer_array_t array;
    integer_array_init(&array, 4);

    int e;
    int ret;
    for (;;) {
        printf("Entrer un entier: ");
        ret = scanf("%d", &e);

        // EOF ou pas un entier.
        if (ret == EOF || ret == 0) {
            putchar('\n');
            break;
        }

        integer_array_append(&array, e);
    }

    // Affiche le contenu du tableau.
    for (size_t i = 0; i < array.nbElem; ++i) {
        printf("array[%ld] = %d\n", i, array.data[i]);
    }

    // Libère le tableau
    free(array.data);
    return 0;
}
