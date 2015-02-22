#pragma once
#include <iostream>
#include "tmParams.h"
#include "tmTypes.h"
#include "tmRandom.h"
#include "tmTool.h"
class tmTool;

class tmManager {

  public:
    tmManager();
    grid_t grids[COLUMN*ROW];
    tmRandom random;


  private:
    //An Array for grid
    point_t points[POINT_NUM];
    tmTool *tool;

    //Methods
    int initGrids(grid_t *grids);
    int initPoints(point_t *points);
    void sync(point_t *pPoint);
};
