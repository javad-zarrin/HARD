//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


//
// Same as TictocMsg11
//
cplusplus {{ 
    #include "query.h"
    #include <vector>
    #include <string>
 //   typedef opp_string strt;
    
    
    }} // C++ typedef
struct strtype;
//class noncobject strt;


 
message rdMessage
{
   unsigned int ID=0; 
   bool flag=true;
    int source=0;
    int destination=0;
    int hopCount = 0;
    int mtype=0;
    int intContent=0;
    int intContentSD=0;
    int intValue=0;
  // strtype  mainContent;
  	strtype mainContent=DEFULT_STC;
  	strtype stringContent=DEFULT_STC;
 //	int originSource;
  
}
