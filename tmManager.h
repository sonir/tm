#pragma once
#include <iostream>
#include <vector>
#include "tmParams.h"
#include "tmTypes.h"
#include "tmRandom.h"
#include "tmTool.h"
#include "lineController.h"

class tmTool;

class tmManager {

  public:
    //grid_t grids[COLUMN*ROW];
    std::vector<grid_t> grids;
    //point_t points[POINT_NUM];
    std::vector<point_t> points;
    LineController *line;
    tmRandom random;
    int grid_column;
    int grid_row;
    int node_num;
    int point_num;


    tmManager(int column, int row, int number_of_point);
    void cycle();
    void move(int point_id, EDirection dir);
    void connectGrids(point_t *pPoint);    


  private:
    tmTool *tool;
    //Methods
    int initGrids();
    int initPoints();
    void initForTest( void );
    void sync(point_t *pPoint);

};
