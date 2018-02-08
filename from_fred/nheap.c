#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _heap heap;

struct _heap {
	int* array;
	int size;
	int nbelem;
	int arity;
};
void heap_swim(heap* h, int index, int elem ); 
void heap_sink(heap* h, int parent);
int heap_minchild(heap* h, int index );

heap* heap_new(int arity, int size){
	heap* h = malloc(sizeof(heap));
	h->size = size;
	h->arity = arity;
	h->nbelem = 0;
	h->array = malloc(size*sizeof(int));
	return h;	
} 

void heap_free(heap* h){
	if (h){
		free(h->array); 
		free(h);
	}	
}

#ifdef __DEBUG__
void heap_debugprint(heap* h) {
	for (int i=0;i<h->size;i++){
		printf("%d ", h->array[i]); 
	}
	printf("\n"); 
}
#else
void heap_debugprint(heap* h) {
	for (int i=0;i<h->nbelem;i++){
		printf("%d ",h->array[i]); 
	}
	printf("\n"); 
}
#endif

void heap_supersize(heap* h){
	h->size *= 2;
	h->array = realloc(h->array, h->size*sizeof(int));
} 

void  heap_subsize(heap* h){
	if (h-> size/2 > h->arity +1){
		h->size /=2;
		h->array = realloc(h->array, h->size*sizeof(int));	
	}	
}
int heap_insert(heap* h, int elem ) {
	if (h->nbelem+1 > h->size)
		heap_supersize(h);
  heap_swim(h, h->nbelem, elem);		
  h->nbelem++;
	return elem;
}
int heap_deleteMin(heap* h) {
	if (h->nbelem == 0){
		return -1;		
	}	
	int tmp = h->array[0];
	heap_sink(h,0);	
	if (h->nbelem< h->size /4)
		heap_subsize(h);	 
	return tmp;
	
}

void heap_swim(heap* h, int index, int elem ) {		
	int parent = (index-1)/h->arity;	
	while (index && elem < h->array[parent]){
		h->array[index] = h->array[parent];
		index = parent;	
		parent = (index-1)/h->arity;
	}
	h->array[index] = elem;
}

void heap_sink(heap* h, int parent) {
	int min = heap_minchild(h, parent);
	while(min > 0) {
		h->array[parent] = h->array[min];
		parent = min;
		min = heap_minchild(h, parent);
	}	
	h->nbelem--;
	heap_swim(h,parent,h->array[h->nbelem]);
}

int heap_minchild(heap* h, int index ) {
	int cte = h->arity * index;
	int min = cte+1;
	if (min >= h->nbelem)
		return -1; 	
	for (int i = 2; i <= h->arity &&  cte +i < h->nbelem ;i++) {	
		if (h->array[cte +i] < h->array[min]) {
			min = cte +i;
		}
	}
	return min;
}

int main(int argc, char** argv){
	srand(time(0)); 
	heap *h = NULL; // heap_new(4,16);
	for (int i = 17; i> 3; i--){
		heap_insert(h,i);
		printf("%d ",i);
	}
	printf("\n debug 1:\n");	
	heap_debugprint(h);
	
	printf("\n insert 2:\n");
	for (int i = 0; i< 26; i++){
		heap_insert(h,rand() % 512);
		printf("%d ",i);
	}
	printf("\n debug 2:\n");	
	heap_debugprint(h);	
	
	printf("\n debug list1:\n");	
	int min;
	for (int i =3; i< 7;i++){
		printf("%d ",heap_deleteMin(h));	
		
	}
	printf("\n debug 3:\n");
	heap_debugprint(h);
	
	printf("\n debug list2:\n");
	while((min = heap_deleteMin(h))!= -1){
		printf("%d ",min);				
	}
	
	printf("\n debug 4:\n");
	heap_debugprint(h);
	heap_free(h);
	return 0;	
}
