/**
 * File              : matrix.c
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 28.09.2019
 * Last Modified Date: 21.10.2019
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
/**
 * lib/matrix.c
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
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "styling.h"

#define SIZE sizeof

vector initVec(vector vec, uint _size){
  vec._e = calloc(_size, SIZE(double));
  vec.size = _size;
  return vec;
}
vectorV initVecV(vectorV vec, uint _size){
  vec._e = calloc(_size, SIZE(void));
  vec.size = _size;
  return vec;
}

matrixD initMatrix(matrixD Mat, int rows, int cols){
  vector Elems;
  Elems = initVec(Elems, cols * rows);
  Mat._e = Elems._e;
  Mat.rows = rows;
  Mat.cols = cols;
  Mat = mScalarMult(Mat, 0);
  return Mat; 
}

vector mVecMultiplication(matrixD mat, vector vec){
  if(mat.cols != vec.size){
    cprint(RED, 1, stderr);
    printf("mat::mVecMultiplication is not working with [%d x %d] * [%d x 1]", mat.rows, mat.cols, vec.size);
    cprint(RESET, 0, stderr);
    vector ERROR;
    return ERROR;
  }
  vector result;
  result = initVec(result, mat.rows);
  register int i = 0;
  register int j = 0;
  register int curRow = 0;

  for(i=0;i<mat.rows;++i){
    for(j=0;j<mat.cols;++j){
      result._e[i] += mat._e[getIndex(i, j, mat.rows, mat.cols)] * vec._e[j];
    }
  }
  return result;
}

void printVec(vector vec){
  printArray(vec._e, vec.size);
}

int getIndex(int row, int col, u_int rows, u_int cols){
  return row * cols + col;
}

void printMat(matrixD mat){
  printf("mat[%d x %d]: [\n", mat.rows, mat.cols);
  for(int i=0; i<mat.rows*mat.cols; ++i){
    if(i % mat.cols == 0 && i != 0) printf("\n");
    printf("\t%f", mat._e[i]);
  }
  printf("\n]\n");
}

matrixD mScalarMult(matrixD mat, double lambda){
  for(int i=0; i<mat.cols*mat.rows; ++i){
    mat._e[i] *= lambda;
  }
  return mat;
}

matrixD mMatMult(matrixD A, matrixD B){
  if(A.cols != B.rows){
    cprint(RED, 1, stderr);
    printf("matrix::mMatMult::ERROR [%d x %d] * [%d x %d] not possible\n", A.rows, A.cols, B.rows, B.cols);
    cprint(RESET, 0, stderr);
    matrixD ERROR;
    return ERROR;
  }

  matrixD result;
  result = initMatrix(result, A.rows, B.cols);
  double a = 0., b = 0., c = 0.;
  for(int iA=0; iA<A.rows; ++iA){
    for(int jB=0; jB<B.cols; ++jB){
      c = 0.;
      for(int jA=0; jA<A.cols; ++jA){
        a = A._e[getIndex(iA, jA, A.rows, A.cols)];
        b = B._e[getIndex(jA, jB, B.rows, B.cols)];
        c += a*b;
      }
      result._e[getIndex(iA, jB, result.rows, result.cols)] = c;
    }
  }
  return result;
}

matrixD transpose(matrixD mat){
  matrixD result;
  result = initMatrix(result, mat.cols, mat.rows);

  for(int i=0;i<mat.rows;++i){
    for(int j=0;j<mat.cols;++j){
      int indexA = getIndex(i, j, mat.rows, mat.cols);
      int indexB = getIndex(j, i, mat.cols, mat.rows);
      double elem = mat._e[indexA];
      result._e[indexB] = elem;
    }
  }
  return result;
}

matrixD invertMatrixD(matrixD mat){
  double p = 0, d = 1;
  matrixD result;
  result = initMatrix(result, mat.cols, mat.rows);
  for(p = 0; p<result.cols;++p){
    int index = getIndex(p, p, result.cols, result.rows);
    double a = mat._e[index];
    if(a == 0){
      fprintf(stderr, "matrix::invertMatrixD cannot calculate A^-1.\n");
      // break?
      break;
    }
    double d_ = d * a;
    for(int j=0; j<result.rows;++j){
      if(j == p){
        continue;
      }
      int newIndex = getIndex(p, j, result.cols, result.rows);
      result._e[newIndex] = mat._e[newIndex] / a;
    }
    printMat(result);
    for(int i=0; i<result.cols;++i){
      if(i == p){
        continue;
      }
      int newIndex = getIndex(i, p, result.cols, result.rows);
      result._e[newIndex] = -mat._e[newIndex] / a; 
    }
    printMat(result);
    for(int i=0; i<result.cols;++i){
      for(int j=0; j<result.rows;++j){
        if(i == p || j == p){
          continue;
        }
        int ij = getIndex(i, j, result.cols, result.rows);
        int pj = getIndex(p, j, result.cols, result.rows);
        int ip = getIndex(i, p, result.cols, result.rows);
        result._e[ij] = mat._e[ij] + mat._e[pj] * result._e[ip];
      }
    }
    result._e[index] = 1/mat._e[index];
    printMat(result);
  }
  return result;
}
