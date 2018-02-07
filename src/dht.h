
/*
 *
 *  
 *      Author: jzarrin
 */



#include <stdio.h>

#include <iostream>
#include <cstdlib>
#include <stdlib.h>



#include <vector>
#include <algorithm>
#include <utility>
#include "math.h"


#include <string.h>
#include <strings.h>
#include <string>
#include <vector>
#include <map>
#include "rdp.h"



const unsigned int single_attribute_bitsize=16; //bits
const unsigned int multi_attribute_bitsize=64;  //bits
typedef std::pair<int, std::string> PAIR;

bool sort_pred(const PAIR& left, const PAIR& right){
    return left.second < right.second;
}


void show_finger_table(int rid, finger_table ft){
    EV <<"--Resource ID="<< rid<< endl;
    for (unsigned int j=0;j< multi_attribute_bitsize ; j++ )
      EV <<"--Finger Record--"<< j<< "---" << ft.get_start_id(j).c_str()<< "---" <<  ft.get_successor_id(j)<< endl;

}





