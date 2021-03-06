/**
 * File              : array.c
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 28.09.2019
 * Last Modified Date: 13.10.2019
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
/**
 * lib/array.c
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
#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "matrix.h"

double *allocArray(double *vec, int size){
#if DEBUG
  printf("DEBUG::pre-allocArray size: %d \t|\t vec location: %x\n", sizeof(&vec), vec);
#endif
  vec = calloc(size, sizeof(double ));
#if DEBUG
  printf("DEBUG::post-allocArray size: %d \t|\t vec location: %x\n", sizeof(&vec), vec);
#endif
  return vec;
}

void printArray(double *vec, int size){
  printf("vec[%d]: [\n", size);
  for(int i=0; i<size; i++) printf("\t%f\n", vec[i]);  
  printf("]\n");
}

void assignValsV(vectorV vec, void (*vals[])(double)){
  vec._e = vals;
}
void assignVals(double *vec, double vals[], int len){
  for(int i=0; i<len;i++) *(vec + i) = vals[i];
}

