#ifndef _CONVEX_HULL_H
#define _CONVEX_HULL_H

#include <iostream>
#include <stack>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include "types.h"
#include "constants.h"

 
int hide_invisible(SPARSE_MATRIX &points, SPARSE_MATRIX &result) {
  int count = 0;
  int x, y, filled;
  for (auto it = points.begin(); it != points.end(); ++it) {
    x = it->first.first;
    y = it->first.second;
    result[std::make_pair(x,  y)] = 1;
  }
  return count;
};


int get_reduced_cube(SPARSE_CUBE &cube) {
  int count = 0;
  for (int i = 0; i < cube.size(); ++i) {
    for (auto it = cube[i].begin(); it != cube[i].end(); ++it) {
      if (it->second && (i < cube.size())) {
        int k = i + 1;
        int partial_count = 1;
        while (k < cube.size() && cube[k][it->first]) {
          cube[k][it->first] = 0;
          ++partial_count;
          ++k;
          ++count;
        }
        cube[i][it->first] = partial_count;
      }
    }
  }
  return count;
};


static void DrawParallelepiped(
  GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ, GLenum type) {

  static GLfloat n[6][3] = {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };

  static GLint faces[6][4] = {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };

  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeY / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeY / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeZ / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeZ / 2;

  for (i = 5; i >= 0; --i) {
    glBegin(type);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}


#endif
