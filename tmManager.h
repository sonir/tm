#pragma once
// #define STRAIGHT_MOVE
#include <iostream>
#include "tmParams.h"
#include "tmTypes.h"
#include "tmRandom.h"
#include "tmTool.h"
#include "lineController.h"

class tmTool;

class tmManager {

  public:
    grid_t grids[COLUMN*ROW];
    point_t points[POINT_NUM];
    LineController *line;
    tmRandom random;

    tmManager();
    void cycle();
    void move(int point_id);


  private:
    tmTool *tool;
    //Methods
    int initGrids(grid_t *grids);
    int initPoints(point_t *points);
    void sync(point_t *pPoint);

};
