#include "tmRandom.h"

int randomWith( int max_num ){
    srand((unsigned)time(NULL));
    return ( (int)rand()%max_num+1 );
}
