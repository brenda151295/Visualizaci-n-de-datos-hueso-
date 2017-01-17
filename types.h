#ifndef _TYPES_H
#define _TYPES_H

#include <opencv2/core/core.hpp>
#include <utility>
#include <vector>
#include <map>

typedef typename std::pair<int, int> POINT;
typedef typename std::vector< std::pair<int, int> > POINT_VECTOR;
typedef typename std::vector< std::vector< std::pair<int, int> > > IMAGES_VECTOR;
typedef typename std::map< std::pair<int, int>, int > SPARSE_MATRIX;
typedef typename std::vector< std::map< std::pair<int, int>, int > > SPARSE_CUBE;

#endif
