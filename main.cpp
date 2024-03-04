//
// Created by rayminn on 24-3-3.
//

#include <iostream>
#include "DATA_MAKER.hpp"

using namespace DATA_MAKER;

#define dm DATA_MAKER

signed main()
{
    long long a = dm::RND();
    double b = dm::RND.doub();
    int c = dm::RND(1,10);
    printf("%lld %lf %d\n",a,b,c);
    
    dm::IO io("data",1,".in",".out");

    io.input_write(1,2,3,4,5);
    

    return 0;
}