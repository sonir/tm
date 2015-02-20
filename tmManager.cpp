#include "tmManager.h"

tmManager::tmManager(){

  initGrids(grids);
  initPoints(points);

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

      points[i].position.x = (int)random.randomWith(COLUMN)-1;
      points[i].position.y = (int)random.randomWith(ROW)-1;

      std::cout<< i <<":position" << points[i].position.x << "," << points[i].position.y << std::endl;

    }

    return 0;

}
