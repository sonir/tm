#include "tmTool.h"

//Function ProtoTypes
bool isGridRightEnd(int grid);
bool isGridLeftEnd(int grid);
bool isGridTop(int grid);
bool isGridBottom(int grid);

// tmTool::tmTool(tmManager *manager, int tmp_row, int tmp_column, int tmp_node_num, int tmp_point_num){
tmTool::tmTool(tmManager *pM, int tmp_row, int tmp_column, int tmp_node_num, int tmp_point_num){

  manager = pM;
  row = tmp_row;
  column = tmp_column;
  node_num = tmp_node_num;
  point_num = tmp_point_num;

}


position_t tmTool::nodeToPosition(int node_id){

  position_t posi;
  node_id = node_id-1; //id is start from 1

  if(isNotTopColumn(node_id+1)) posi.x = node_id%row; //isNotTopColumn requires actual id num , therefore arg is id+1
  else posi.x = (float)node_id;

  posi.y = (node_id/column);

  return posi;

}

bool tmTool::isNotTopColumn(int node_id){

  if( node_id<=column ) return false;
  else return true;

}

void tmTool::move(point_t *point, int distance){

  int step;
  enum EMode{RANDOM_WITH_MAX_NUM, SPECIFIED};
  EMode mode;



  if(isRandomMode(distance)) mode = RANDOM_WITH_MAX_NUM;
  else mode = SPECIFIED;

  //Strip negative sign
  distance = abs(distance);
  // std::cout << "dist:" << distance << std::endl;

  //Set actual number to move
  if(mode == RANDOM_WITH_MAX_NUM) step=random.randomWith(distance);
  else if(mode == SPECIFIED) step = distance;
  // std::cout << "step:" << step << std::endl;

  EDirection dir;
  dir = directionIs(point); // <- this param is utilized for STRAIGHT_MOVE mode only. (it makes direction once only for straight move)
    //Move the point by step
  for(int i=0; i<step; i++){

      int destination;

      #ifdef STRAIGHT_MOVE
          while(!isGridActive(point->now_node, dir)){ //Must check each time because first dir sometimes incorrect in step process.
            dir = directionIs(point); //if the dir is deadend, change the dir
          }

          destination = doStep(dir,point); //Set next position
          while(isDestinationReturnPath(point,destination)){ //If new position was return
            dir = directionIs(point); //Change it
            destination = doStep(dir,point);
          }
      #endif

      #ifndef STRAIGHT_MOVE
        do{
            dir = directionIs(point);
            destination = doStep(dir,point);
        }while(isDestinationReturnPath(point,destination));
      #endif

      //Set prev position to avoid return
      point->pre_node = point->now_node;
      //Set the new position
      point->now_node = destination;
      // printf("%d\n" , point->now_node);
  }


}

int tmTool::doStep(EDirection dir, point_t *point) {

    //Check the direction is correct
    if(!isGridActive(point->now_node,dir)){
      printf("ERR::<tmTool.cpp>doStep : the set direction was not active\n");
      exit (EXIT_FAILURE);
    }

    int destination=0;

    switch(dir){

        case UP:
        destination = (point->now_node) - COLUMN;
        break;

        case DOWN:
        destination = (point->now_node) + COLUMN;
        break;

        case LEFT:
        destination = (point->now_node) - 1;
        break;

        case RIGHT:
        destination = (point->now_node) + 1;
        break;

        case ULEFT:
        destination = ( (point->now_node) - COLUMN ) - 1;
        break;

        case URIGHT:
        destination = ( (point->now_node) - COLUMN ) + 1;
        break;

        case DLEFT:
        destination = ( (point->now_node) + COLUMN ) - 1;
        break;

        case DRIGHT:
        destination = ( (point->now_node) + COLUMN ) + 1;
        break;

        default:
        break;

    }

  return destination;

}

bool tmTool::isDestinationReturnPath(point_t *point, int destination){

  if(point->pre_node==destination)return true;
  return false;

}

bool tmTool::isRandomMode(int distance){

  if(distance>=0) return true; //Negative value means "without random"
  else return false;

}

EDirection tmTool::directionIs(point_t *point){

  grid_t *grids = manager->grids; //Get pointer of the array
  grid_t *now_grid = &grids[(point->now_node-1)]; //get the actual pointer of now grid
  int destination;
  bool isDestinationNotCorrect = true;
  EDirection direction;

  do {

    direction = (EDirection)(random.randomWith(8)-1);
    // printf("directionIs():new dir is %d \n" , direction);
    if(isGridActive(now_grid->grid_id, direction))isDestinationNotCorrect = false;
    // printf("%d-\n",now_grid->grid_id);
  } while(isDestinationNotCorrect);


  return direction;

}


bool tmTool::isGridActive(int grid_id, EDirection direction){

  //Out of Range
  if(grid_id < 1 || grid_id>NODE_NUM) {
    std::cout << "ERR: tmTool.isGridActive();  The specified position is not exist." << std::endl;
    exit (EXIT_FAILURE);
  }

  //RIGHT BORDER
  if(isGridRightEnd(grid_id)){

    if( direction==RIGHT || direction==URIGHT || direction==DRIGHT ) return false;

  }

  //LEFT BORDER
  if(isGridLeftEnd(grid_id)){

    if( direction==LEFT || direction==ULEFT || direction==DLEFT ) return false;

  }

  //TOP BORDER
  if(isGridTop(grid_id)){

    if( direction==UP || direction==ULEFT || direction==URIGHT ) return false;

  }

  //TOP BORDER
  if(isGridBottom(grid_id)){

    if( direction==DOWN || direction==DLEFT || direction==DRIGHT ) return false;

  }


  return true; //If survive the above check, it is active

}



bool isGridRightEnd(int grid){

  if(grid%COLUMN==0)return true;
  else return false;

}

bool isGridLeftEnd(int grid){

  if(grid%COLUMN==1||grid==1)return true;
  else return false;

}

bool isGridTop(int grid){

  if(grid<=COLUMN) return true;
  else return false;

}

bool isGridBottom(int grid){

  if(grid > COLUMN*(ROW-1)) return true;
  else return false;

}
