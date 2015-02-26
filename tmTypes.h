//This header defines structure files for TM.

#ifndef STTM
#define STTM


typedef enum {UP,DOWN,LEFT,RIGHT, ULEFT, URIGHT, DLEFT, DRIGHT} EDirection;

//Structure for position
typedef struct position {

  float x;
  float y;

} position_t;



//Structure for each grid
typedef struct grid {
  int grid_id; //Unique ID
  //To Store the connected nodes
  bool isUpConnected;
  bool isDownConnected;
  bool isLeftConnected;
  bool isRightConnected;
} grid_t;



//Structure of point
typedef struct point {

  int point_id;
  int now_node;
  int pre_node;
  position_t position;

} point_t;

#endif
