//This header defines structure files for TM.
#ifndef STTM
#define STTM

typedef enum {UP,DOWN,LEFT,RIGHT, ULEFT, URIGHT, DLEFT, DRIGHT} EDirection;
typedef enum {HORIZONTAL, VERTICAL, POSI_DIAGONAL, NEGA_DIAGONAL} EProperty;
typedef enum {STRAIGHT, ARC} ELine_type;


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
  bool isULeftConnected;
  bool isURightConnected;
  bool isDLeftConnected;
  bool isDRightConnected;



} grid_t;



//Structure of point
typedef struct point {

  int point_id;
  int now_node;
  int pre_node;
  position_t position;

} point_t;


typedef struct line{

    EProperty property;
    int uid;
    bool active;
    int st_gid;
    int ed_gid;
    ELine_type line_type;

} line_t;

#endif
