#include <stdio.h>
#include <cassert>
#include "tmManager.h"
#include "gtest/gtest.h"


//Function prototypes
bool test(void);
void testTool(void);

//Global Variables
tmManager* tm = new tmManager();
tmTool *tool = new tmTool(tm, COLUMN, ROW, NODE_NUM,POINT_NUM);



void testTool(void){

  //Test Conversion nodeToPosition
  position_t p;

  p=tool->nodeToPosition(1);
  assert(p.x==0. && p.y==0.);

  p=tool->nodeToPosition(3);
  assert(p.x==2. && p.y==0.);

  p=tool->nodeToPosition(8);
  assert(p.x==7. && p.y==0.);

  p=tool->nodeToPosition(9);
  assert(p.x==0. && p.y==1.);

  p=tool->nodeToPosition(12);
  assert(p.x==3. && p.y==1.);

  p=tool->nodeToPosition(16);
  assert(p.x==7. && p.y==1.);

  p=tool->nodeToPosition(17);
  assert(p.x==0. && p.y==2.);

  p=tool->nodeToPosition(20);
  assert(p.x==3. && p.y==2.);

  p=tool->nodeToPosition(24);
  assert(p.x==7. && p.y==2.);

  printf("<test> tmTool:nodeToPosition <cleared>\n");


  //Test isGridActive
  assert(tool->isGridActive(1,UP)==false);
  assert(tool->isGridActive(1,LEFT)==false);
  assert(tool->isGridActive(1,RIGHT)==true);
  assert(tool->isGridActive(1,DOWN)==true);
  assert(tool->isGridActive(1,DLEFT)==false);
  assert(tool->isGridActive(1,DRIGHT)==true);
  assert(tool->isGridActive(1,URIGHT)==false);
  assert(tool->isGridActive(1,ULEFT)==false);
  assert(tool->isGridActive(64,UP)==true);
  assert(tool->isGridActive(64,LEFT)==true);
  assert(tool->isGridActive(64,RIGHT)==false);
  assert(tool->isGridActive(64,DOWN)==false);
  assert(tool->isGridActive(64,DLEFT)==false);
  assert(tool->isGridActive(64,DRIGHT)==false);
  assert(tool->isGridActive(64,URIGHT)==false);
  assert(tool->isGridActive(64,ULEFT)==true);
  printf("<test> tmTool:isGridActive is working correctlly. <cleared>\n");


  point_t point;

  //Test doStep
  point.now_node = 10; point.pre_node=0;
  // std::cout << "1" << std::endl;
  assert( tool->doStep(UP,&point)==2);
  // std::cout << "2" << std::endl;
  assert( tool->doStep(ULEFT,&point)==1);
  // std::cout << "3" << std::endl;
  assert( tool->doStep(LEFT,&point)==9);
  // std::cout << "4" << std::endl;
  assert( tool->doStep(DLEFT,&point)==17);
  // std::cout << "5" << std::endl;
  assert( tool->doStep(DOWN,&point)==18);
  // std::cout << "6" << std::endl;
  assert( tool->doStep(DRIGHT,&point)==19);
  // std::cout << "7" << std::endl;
  assert( tool->doStep(RIGHT,&point)==11);
  // Force error code
  // point.now_node = 1; point.pre_node=0;
  // assert( tool->doStep(LEFT,&point)==0);
  printf("<test> tmTool:doStep is working correctlly. <cleared>\n");


  #ifndef STRAIGHT_MOVE
  // Test Avoit ReturnPath
  point.now_node = 1; point.pre_node=0;
  assert(tool->isDestinationReturnPath(&point,0)==true);
  printf("<test>tmTool:isDestinationNotReturnPath is working correctlly. <cleared>\n");

  //Test Move Method
  point.now_node=1; tool->move(&point,-1);
  std::cout << "TRY1 new position is: " << point.now_node << std::endl;
  assert(point.now_node==2 || point.now_node==10 || point.now_node==9);

  point.now_node=1; tool->move(&point,-2);
  std::cout << "TRY2 new position is: " << point.now_node << std::endl;
  assert( point.now_node<=2 || point.now_node==3 || ( point.now_node>=9 && point.now_node<=11) || (point.now_node>=17 && point.now_node<=19) );

  point.now_node=64; tool->move(&point,-1);
  std::cout << "TRY3 new position is: " << point.now_node << std::endl;
  assert(point.now_node==63 || point.now_node==56 || point.now_node==55);

  point.now_node=1; tool->move(&point,-5);
  std::cout << "TRY4 new position is: " << point.now_node << std::endl;
  assert(point.now_node<5 || ( point.now_node%8<=8 && point.now_node< ((8+1)*5+1) ));
  printf("<test> tmTool:move is working correctlly. <cleared>\n");
  #endif

  #ifdef STRAIGHT_MOVE
  point.now_node=29; point.pre_node=21;
  tool->move(&point,-3);
  std::cout << "TRY4b new position is: " << point.now_node << std::endl;
  assert( point.now_node!=5 || point.now_node==2 || point.now_node==26 || point.now_node==50 || point.now_node==53 || point.now_node==56 || point.now_node==32 || point.now_node==8 );
  point.now_node=29;point.pre_node=21;
  tool->move(&point,-4);
  std::cout << "TRY4c new position is: " << point.now_node << std::endl;
  printf("<test> tmTool:move is working correctlly. <cleared>\n");
  #endif

}



bool test (void) {

  testTool();
  return true;

}



int main (void){

  // tmManager* tm = new tmManager();

  //TestCode
  test();

}
