#include "tmManager.h"

tmManager::tmManager(){

  tool = new tmTool(this, COLUMN, ROW, NODE_NUM, POINT_NUM);
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

      points[i].point_id = i;
      points[i].now_node = (int)random.randomWith(NODE_NUM);
      points[i].pre_node = 0;
      points[i].position = tool->nodeToPosition(points[i].now_node);

      // std::cout << "id:"<< points[i].point_id <<":position:" << "node=" << points[i].now_node << "," << points[i].position.x << "," << points[i].position.y << std::endl;

    }

    return 0;

}

void tmManager::sync(point_t *pPoint){


}
