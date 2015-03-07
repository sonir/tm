#include <stdio.h>
#include <cassert>
#include "tmManager.h"
#include "gtest/gtest.h"
#include "lineController.h"


//Function prototypes
bool test(void);
void testTool(void);

//Global Variables
tmManager* tm = new tmManager();
tmTool *tool = new tmTool(tm, COLUMN, ROW, NODE_NUM,POINT_NUM);

using namespace std;

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
  point.now_node=12;point.pre_node=20;
  tool->moveManual(&point, 3, UP);
  std::cout << "TRY4c new position is: " << point.now_node << std::endl;
  assert( (point.now_node==2 || point.now_node<=6) || (point.now_node==18||point.now_node==22) );


  // point.now_node=29;point.pre_node=21;
  // tool->move(&point,-4);
  // std::cout << "TRY4c new position is: " << point.now_node << std::endl;

  printf("<test> tmTool:move is working correctlly. <cleared>\n");
  #endif

}


void testLine(void){

  cout << "-- testLine() --" << endl;

  cout << "numCHK" << endl;
  int foo = (3-1)^2;
  cout << foo << endl;

  LineController *line = new LineController(3); //grid 3^2
  LineController *line2 = new LineController(5); //grid 5^2
  //Chk calculation the numbers of lines
  assert( line->vline_num==6 );
  assert( line->hline_num==6 );
  assert( line->pDLines_num==4 );
  assert( line->nDLines_num==4 );

  // cout << "line2" << endl;
  // LineController *line2 = new LineController(5); //grid 3^2
  // assert( line2->getLineID(8,UP)==3 );


  //Test Get lineID
  // cout << "5:" << line->getLineID(5,DRIGHT) << endl;
  assert( line->getLineID(5,UP)==1 );
  assert( line->getLineID(5,DOWN)==4 );
  assert( line->getLineID(5,LEFT)==2 );
  assert( line->getLineID(5,RIGHT)==3 );
  assert( line->getLineID(5,ULEFT)==0 );
  assert( line->getLineID(5,URIGHT)==1 );
  assert( line->getLineID(5,DLEFT)==2 );
  assert( line->getLineID(5,DRIGHT)==3 );
  assert( line->getLineID(6,UP)==2 );
  assert( line->getLineID(6,DOWN)==5 );
  assert( line->getLineID(6,LEFT)==3);
  assert( line->getLineID(6,ULEFT)==1 );
  assert( line->getLineID(6,DLEFT)==3 );

  assert( line2->getLineID(9,UP)==3 );
  assert( line2->getLineID(9,DOWN)==8 );
  assert( line2->getLineID(9,LEFT)==6 );
  assert( line2->getLineID(9,RIGHT)==7 );
  assert( line2->getLineID(9,ULEFT)==2 );
  assert( line2->getLineID(9,URIGHT)==3 );
  assert( line2->getLineID(9,DLEFT)==6 );
  assert( line2->getLineID(9,DRIGHT)==7 );
  cout << "<test:lineController> [ getLineID() ] is working correctlly. <cleared>" << endl;

  cout << "print pDlines array" << line->pDLines_num << endl;
  for(int i=0; i<line->pDLines_num ; i++){

    cout << i << ": uid= " << line->pDLines[i].uid << "active=" << line->pDLines[i].active << "property:" << line->pDLines[i].property << endl;

  }


  //Test Get Line
  line_t l = line->getLine(8,UP); assert( l.uid==4 && l.property==VERTICAL ); //Test Get Line
  l = line->getLine(1,DOWN); assert( l.uid==0 && l.property==VERTICAL ); //Test Get Line
  l = line->getLine(9,LEFT); assert( l.uid==5 && l.property==HORIZONTAL ); //Test Get Line
  l = line->getLine(7,RIGHT); assert( l.uid==4 && l.property==HORIZONTAL ); //Test Get Line
  l = line->getLine(4,URIGHT); assert( l.uid==0 && l.property==POSI_DIAGONAL ); //Test Get Line
  l = line->getLine(6,ULEFT); assert( l.uid==1 && l.property==NEGA_DIAGONAL ); //Test Get Line
  l = line->getLine(2,DLEFT); assert( l.uid==0 && l.property==POSI_DIAGONAL ); //Test Get Line
  l = line->getLine(5,DRIGHT); cout<<l.property<<endl;  assert( l.uid==3 && l.property==NEGA_DIAGONAL ); //Test Get Line



  cout << "<test:lineController> [ getLine() ] is working correctlly. <cleared>" << endl;

  // Test SetLine
  l = line->getLine(8, URIGHT);
  assert( l.active==false );
  line->setLine(8, URIGHT); //SetLine with gid, direction
  l = line->getLine(8, URIGHT);
  // cout << l.uid << "," << l.property << endl;
  assert( l.uid==3 && l.active==true && l.property==POSI_DIAGONAL );
  cout << "<test:lineController> [ setLine() ] is working correctlly. <cleared>" << endl;
  //

  //Test Line ID

}


void testSync(){

  // tm->move(0);
  // assert(tm->line->vLines[1].active==true);
  // tm->move(1);
  // assert(tm->line->pDLines[1].active==true);
  // tm->move(2);
  // assert(tm->line->nDLines[2].active==true);
  // tm->move(3);
  // assert(tm->line->hLines[5].active==true);

}

bool test (void) {

  testTool();
  testLine();
  testSync();
  return true;

}



int main (void){

  // tmManager* tm = new tmManager();

  //TestCode
  test();

}
