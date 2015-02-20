#include "tmRandom.h"

//Constructor
tmRandom::tmRandom(){

  srand((unsigned)time(NULL));


};


//Generate random number with Max
int tmRandom::randomWith( int max_num ){
    return ( (int)rand()%max_num+1 );
}
