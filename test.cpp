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

  printf("[test] tmTool:nodeToPosition <cleared>\n");

  //Test Move Method
  point_t point;
  point.now_node=1; tool->move(&point,-1);
  assert(point.now_node==3 || point.now_node==10 || point.now_node==9);

  point.now_node=1; tool->move(&point,-2);
  assert( point.now_node==2 || point.now_node==3 || point.now_node==9 || point.now_node==10 || (point.now_node>=17 && point.now_node>=19) );

  point.now_node=16; tool->move(&point,-1);
  assert(point.now_node==3 || point.now_node==10 || point.now_node==9);


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
