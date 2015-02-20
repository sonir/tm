#pragma once
#include <iostream>
#include "tmParams.h"
#include "tmTypes.h"
#include "tmRandom.h"

class tmManager {

  public:
    tmManager();

  private:
    //An Array for grid
    grid_t grids[COLUMN*ROW];
    point_t points[POINT_NUM];
    tmRandom random;

    //Methods
    int initGrids(grid_t *grids);
    int initPoints(point_t *points);

};
