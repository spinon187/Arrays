#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;


/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

Array *create_array (int capacity) {
	Array *arr = malloc(sizeof(Array));
	arr->capacity = capacity;
  arr->count = 0;
  arr->elements = malloc(sizeof(char*) * capacity);
  return arr;
}

void destroy_array(Array *arr) {
  for (int i = 0; i < arr->count; i++){
    free(arr->elements[i]);
  }
  free(arr->elements);
  free(arr);
}

void resize_array(Array *arr) {

  char **temp = malloc(sizeof(char*) * arr->capacity * 2);
  for(int i = 0; i < arr->count; i++){
    temp[i] = arr->elements[i];
  }
  free(arr->elements);
  arr->capacity = arr->capacity * 2;
  arr->elements = malloc(sizeof(char*) * arr->capacity);
  for(int i = 0; i < arr->count; i++){
    arr->elements[i] = temp[i];
  }
  free(temp);
}



/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

char *arr_read(Array *arr, int index) {

  if(index >= arr->count){
    fprintf(stderr, "string");
    return NULL;
  }
  return arr->elements[index];
}

void arr_insert(Array *arr, char *element, int index) {

  if(index > arr->count){
    fprintf(stderr, "string");
    return ;
  }
  if(arr->count == arr->capacity){
    resize_array(arr);
  }
  for(int i = arr->count; i > index; i--){
    arr->elements[i] = arr->elements[i-1];
  }
  arr->elements[index] = strdup(element);
  arr->count++;
}

void arr_append(Array *arr, char *element) {

  if(arr->count == arr->capacity){
    resize_array(arr);
  }
  arr->elements[arr->count] = strdup(element);
  arr->count++;
}


void arr_remove(Array *arr, char *element) {

  int found = -1;
  int i = 0;
  while(found == -1 && i < arr->count){
    if(strcmp(arr->elements[i], element) == 0){
      found = i;
    }
    else{
      i++;
    }
  }
  if (found != -1){
    free(arr->elements[found]);
    for(int j = found; j < arr->count; j++){
      arr->elements[j] = arr->elements[j+1];
    }
    arr->count--;
  }
}


/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("]\n");
}


#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
