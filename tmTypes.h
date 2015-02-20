//This header defines structure files for TM.

#ifndef STTM
#define STTM

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

  position_t position;

} point_t;

#endif
