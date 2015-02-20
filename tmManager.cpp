#include "tmManager.h"

tmManager::tmManager(){

  initGrids(grids);

}; //Constructor

int tmManager::initGrids(grid_t *grids){

      //Set initial values to each grid
      for(int i=0;i<NODE_NUM;i++){

        grids[i].grid_id = (i+1);
        grids[i].isUpConnected = false;
        grids[i].isDownConnected = false;
        grids[i].isLeftConnected = false;
        grids[i].isRightConnected = false;

      }

      return 0;

}

int tmManager::initPoints(point_t *points){

    for(int i=0; i<POINT_NUM; i++){

      points[i].position.x = 0.;
      points[i].position.y = 0.;


    }

    return 0;

}
