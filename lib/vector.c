/**
 * File              : vector.c
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 28.09.2019
 * Last Modified Date: 28.09.2019
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
/**
 * lib/vector.c
 * Copyright (c) 2019 Philipp Zettl <philipp.zettl@godesteem.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void vec_init(vector *vec){
  // initializes a vector struct
  vec->storageSize = INIT_STORAGE_SIZE;
  vec->totalItems = 0;
  vec->items = malloc(sizeof(double*) * vec->storageSize); 
}

int vec_total(vector *vec){
  // amount of total items in vector
  return vec->totalItems;
}

static void vec_resize(vector *vec, int newSize){
  // resizes the vector
  double **items = realloc(vec->items, sizeof(double*)*newSize);
  if(items){
    vec->items = items;
    vec->totalItems=newSize;
  }
}

void vec_add(vector *vec, double *item){
  // appends the vector
  if(vec->storageSize==vec->totalItems)
    vec_resize(vec, vec->storageSize * 2);
  vec->items[vec->totalItems++] = item;
}

void vec_set(vector *vec, int pos, double *item){
  // setter function for x[i]
  if(pos>=0 && pos < vec->totalItems){
    vec->items[pos] = item;
  }
}

double *vec_get(vector *vec, int pos){
  // getter function for x[i]
  if(pos>=0 && pos < vec->totalItems){
    return vec->items[pos];
  }
  return NULL;
}

void vec_delete(vector *vec, int pos){
  // delete item from vec and clean afterwards 
  if(pos < 0 || pos >= vec->totalItems){
    return;
  }
  vec->items[pos] = NULL;
  
  // now we basically shift the array to be without any holes
  for(int i=pos; i<vec->totalItems; i++){
    vec->items[i] = vec->items[i+1]; // i+1 since we dont want to shift i yet
    vec->items[i+1] = NULL; 
  }
  vec->totalItems--;

  if(vec->totalItems > 0 && vec->totalItems == vec->storageSize / 4){
    vec_resize(vec, vec->storageSize / 2);
  }
}

void vec_free(vector *vec){
  // destructor
  free(vec->items);
}
