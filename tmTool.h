#pragma once
#include <iostream>
#include "tmTypes.h"
#include "tmRandom.h"
#include <stdlib.h>
#include "tmManager.h"

class tmManager; //Inter Reference

class tmTool {

  public:
    tmManager *manager;
    tmRandom random;

    // EDirection direction;
    // tmTool(tmManager *manager, int tmp_row, int tmp_column, int tmp_node_num, int tmp_point_num);
    tmTool(tmManager *pM, int tmp_row, int tmp_column, int tmp_node_num, int tmp_point_num);
    position_t nodeToPosition(int node_id);
    void move(point_t *point, int distance);
    void moveManual(point_t *point, int distance, EDirection dir);
    int doStep(EDirection dir, point_t *point);
    bool isDestinationReturnPath(point_t *point, int destination);
    EDirection directionIs(point_t *point);
    bool isGridActive(int grid_id, EDirection direction);

  private:
    int row;
    int column;
    int node_num;
    int point_num;

    bool isNotTopColumn(int node_id);
    bool isRandomMode(int distance);

};
