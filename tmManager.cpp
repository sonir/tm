#include "tmManager.h"

tmManager::tmManager(int column, int row, int number_of_point){

  grid_column = column;
  grid_row = row;
  node_num = grid_column*grid_row;
  point_num = number_of_point;

  tool = new tmTool(this, grid_column, grid_row, node_num, point_num);
  line = new LineController(grid_column);
  initGrids();
  initPoints();

  initForTest();


}; //Constructor

void tmManager::initForTest( void ){

  points[0].now_node = 5; points[0].pre_node = 5;
  points[1].now_node = 5; points[1].pre_node = 5;
  points[2].now_node = 5; points[2].pre_node = 5;
  points[3].now_node = 8; points[3].pre_node = 8;


}

int tmManager::initGrids(){

      //Set initial values to each grid
      for(int i=0;i<node_num;i++){

        grid_t g;
        g.grid_id = (i+1);
        g.isUpConnected = false;
        g.isDownConnected = false;
        g.isLeftConnected = false;
        g.isRightConnected = false;
        g.isULeftConnected = false;
        g.isURightConnected = false;
        g.isDLeftConnected = false;
        g.isDRightConnected = false;

        grids.push_back(g);

        // grids[i].grid_id = (i+1);
        // grids[i].isUpConnected = false;
        // grids[i].isDownConnected = false;
        // grids[i].isLeftConnected = false;
        // grids[i].isRightConnected = false;
        // grids[i].isULeftConnected = false;
        // grids[i].isURightConnected = false;
        // grids[i].isDLeftConnected = false;
        // grids[i].isDRightConnected = false;

      }

      return 0;

}

int tmManager::initPoints(){

    for(int i=0; i<POINT_NUM; i++){

      point_t p;
      p.point_id = i;
      p.now_node = (int)random.randomWith(node_num);
      p.pre_node = 0;
      p.position = tool->nodeToPosition(p.now_node);
      points.push_back(p);

      // points[i].point_id = i;
      // points[i].now_node = (int)random.randomWith(NODE_NUM);
      // points[i].pre_node = 0;
      // points[i].position = tool->nodeToPosition(points[i].now_node);

      // std::cout << "id:"<< points[i].point_id <<":position:" << "node=" << points[i].now_node << "," << points[i].position.x << "," << points[i].position.y << std::endl;

    }

    return 0;

}

void tmManager::sync(point_t *pPoint){

  EDirection dir;
  dir = tool->getDirection(*pPoint);

  // std::cout << pPoint->pre_node << std::endl;
  line->setLine(pPoint->pre_node, dir);
  connectGrids(pPoint);

}

void tmManager::connectGrids(point_t *pPoint){

  EDirection dir;
  dir = tool->getDirection(*pPoint);

  // std::cout << pPoint->now_node << std::endl;

  switch(dir){

    case UP:
    grids[pPoint->pre_node].isUpConnected=true;
    grids[pPoint->now_node].isDownConnected=true;    
    break;

    case DOWN:
    grids[pPoint->pre_node].isDownConnected=true;
    grids[pPoint->now_node].isUpConnected=true;    
    break;

    case LEFT:
    grids[pPoint->pre_node].isLeftConnected=true;
    grids[pPoint->now_node].isRightConnected=true;    
    break;

    case RIGHT:
    grids[pPoint->pre_node].isRightConnected=true;
    grids[pPoint->now_node].isLeftConnected=true;        
    break;

    case ULEFT:
    grids[pPoint->pre_node].isULeftConnected=true;
    grids[pPoint->now_node].isDRightConnected=true;    
    break;

    case URIGHT:
    grids[pPoint->pre_node].isURightConnected=true;
    grids[pPoint->now_node].isDLeftConnected=true;    
    break;

    case DLEFT:
    grids[pPoint->pre_node].isDLeftConnected=true;
    grids[pPoint->now_node].isURightConnected=true;    
    break;

    case DRIGHT:
    grids[pPoint->pre_node].isDRightConnected=true;
    grids[pPoint->now_node].isULeftConnected=true;    
    break;

    default:
    exit(EXIT_FAILURE);
    break;

  }


}

void tmManager::cycle(){

    for(int i=0; i<POINT_NUM ;i++){

        tool->move(&points[i], 1);

    }

}

void tmManager::move(int point_id, EDirection dir){

    tool->moveManual(&points[point_id], 1, dir);
    sync(&points[point_id]);

}
