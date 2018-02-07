/*
 * File:   rdp.h
 * Author: jzarrin
 *
 * Created on 28 November 2012, 15:37
 */

#ifndef RDP_H
#define RDP_H

#include <stdio.h>

#include <iostream>
#include <stdlib.h>


#include <fstream>

#include <sstream>
#include <bitset>


#include <cstdlib>
#include <string.h>
#include <strings.h>
#include <string>
#include <vector>
#include <map>
#include "query.h"




using namespace std;



typedef std::vector<std::string> conditions; // At_ID:Op_ID:At_VA:La_ID:At_TY , At_ID:Op_ID$
typedef std::pair<int,conditions> HO_Resource_Collection; // Number of Homegenous Resources$
typedef std::vector<HO_Resource_Collection> HE_Resource_Collection;
static const int key_size=64;//bits - 160 bits; 4 attributes , 16 chars - 16 bytes key
static const int id_char_size=16;//40;//key_size\4 //convert the binary string to a hexadecimal string;

static const unsigned int type_ids_length=10; //maximum number of predefined sq-types

static const unsigned int CCR=6;
static const unsigned int L1S=7;
static const unsigned int L1L=8;
static const unsigned int L2S=9;

static const unsigned int PC=30; //Processor Type CPU=0, GPU=1, FPGA=2, N/A=4
static const unsigned int NC=34; //number of cores
static const unsigned int  INT=25; //Interconnection Network Bus=0, Ring=1, NOC=2, Crossbar=3, PointToPoint=4, HierarchicalNOC=5, Hypercube=6, Mesh=7, QsNet(Quadrics)=8 ,
// Infiniband=9, Myrinet=10, SCI(Scalable Coherent Interface)=11, GE( Gigabit Ethernet)=12, NUMAlink=13, SP Switch=13, Proprietary=14, Cray Interconnect=15, Mixed=16, N/A=17
static const unsigned int ISA=23;// X86=0, SPARC=1, ARM=2, XCORE=3, RISC=4, CISC=5, Legacy=6 , N/A=7 , Instruction Set Architecture

static const unsigned int DC=38; //Die Count
static const unsigned int MS=36 ; // Memory Size
static const unsigned int NB=39 ; // Network Bandwidth MBits/s
static const unsigned int TNC=37 ; // total number of cores in the node

//static const unsigned int RH_DRQ=1; //rate_of_homogeneity_for_the_desired_resources_in_each_query; 1-5
//static const unsigned int Min_Number_of_Members_in_SGroup=2;



// ----------VP---------------------


map<string, char> hexcharmap;

void initMap()
{
    hexcharmap.insert(std::pair<string, char>("1111", 'F'));
    hexcharmap.insert(std::pair<string, char>("1110", 'E'));
    hexcharmap.insert(std::pair<string, char>("1101", 'D'));
    hexcharmap.insert(std::pair<string, char>("1100", 'C'));
    hexcharmap.insert(std::pair<string, char>("1011", 'B'));
    hexcharmap.insert(std::pair<string, char>("1010", 'A'));
    hexcharmap.insert(std::pair<string, char>("1001", '9'));
    hexcharmap.insert(std::pair<string, char>("1000", '8'));
    hexcharmap.insert(std::pair<string, char>("0111", '7'));
    hexcharmap.insert(std::pair<string, char>("0110", '6'));
    hexcharmap.insert(std::pair<string, char>("0101", '5'));
    hexcharmap.insert(std::pair<string, char>("0100", '4'));
    hexcharmap.insert(std::pair<string, char>("0011", '3'));
    hexcharmap.insert(std::pair<string, char>("0010", '2'));
    hexcharmap.insert(std::pair<string, char>("0001", '1'));
    hexcharmap.insert(std::pair<string, char>("0000", '0'));
    hexcharmap.insert(std::pair<string, char>("111", '7'));
    hexcharmap.insert(std::pair<string, char>("110", '6'));
    hexcharmap.insert(std::pair<string, char>("101", '5'));
    hexcharmap.insert(std::pair<string, char>("100", '4'));
    hexcharmap.insert(std::pair<string, char>("011", '3'));
    hexcharmap.insert(std::pair<string, char>("010", '2'));
    hexcharmap.insert(std::pair<string, char>("001", '1'));
    hexcharmap.insert(std::pair<string, char>("000", '0'));
    hexcharmap.insert(std::pair<string, char>("11", '3'));
    hexcharmap.insert(std::pair<string, char>("10", '2'));
    hexcharmap.insert(std::pair<string, char>("01", '1'));
    hexcharmap.insert(std::pair<string, char>("00", '0'));
    hexcharmap.insert(std::pair<string, char>("1", '1'));
    hexcharmap.insert(std::pair<string, char>("0", '0'));
}

char getHexCharacter(std::string str)
{
    return hexcharmap.find(str)->second;


}
std::string getHexRowFails(string input)
{
    string rowresult;
    rowresult.assign("");
    std::string endresult = "";
    int m=input.size() % 4;
    int e=4-m;
    if (m != 0) {
        rowresult.append(e , '0');
        rowresult.append(input);
        }else rowresult.append(input);



    for(unsigned int i = 4; i<= rowresult.size() ;  i = i+4)
    {
        string s=rowresult.substr(rowresult.size()-i,4);
        endresult = getHexCharacter(s)+endresult;


    }

    return endresult;
}



std::pair<int,string> find_successor(vector<pair<int,string> > w , string s) {
pair<int,string> result;
for(unsigned int i=0; i < w.size(); i++) {
    result=w[i];
    if ( s <= result.second) return result;
}


return w[0];

}

string hex_str_2pown(int n, int fixed_size){
initMap();
string resultp,resultf, resultm;
resultp.assign("1");
resultp.append(n,'0');
resultm= getHexRowFails(resultp);
int st= fixed_size - resultm.size();
if (st>0){
    resultf.append(st,'0');
    resultf.append(resultm);

    } else resultf.append(resultm);



return resultf;

}


int hex_char_to_dec( char c ){

switch (c) {
    case '0' : {return 0; break;}
    case '1' : {return 1; break;}
    case '2' : {return 2; break;}
    case '3' : {return 3; break;}
    case '4' : {return 4; break;}
    case '5' : {return 5; break;}
    case '6' : {return 6; break;}
    case '7' : {return 7; break;}
    case '8' : {return 8; break;}
    case '9' : {return 9; break;}
    case 'A' : {return 10; break;}
    case 'B' : {return 11; break;}
    case 'C' : {return 12; break;}
    case 'D' : {return 13; break;}
    case 'E' : {return 14; break;}
    case 'F' : {return 15; break;}

    }
return -1;
}


char dec_to_hex_char( int d ){

switch (d) {
        case 0 : {return '0'; break;}
        case 1 : {return '1'; break;}
        case 2 : {return '2'; break;}
        case 3 : {return '3'; break;}
        case 4 : {return '4'; break;}
        case 5 : {return '5'; break;}
        case 6 : {return '6'; break;}
        case 7 : {return '7'; break;}
        case 8 : {return '8'; break;}
        case 9 : {return '9'; break;}
        case 10 : {return 'A'; break;}
        case 11 : {return 'B'; break;}
        case 12 : {return 'C'; break;}
        case 13 : {return 'D'; break;}
        case 14 : {return 'E'; break;}
        case 15 : {return 'F'; break;}

        }
return 'X';
}




string  hex_str_add2str( string str1, string str2, int fixed_size) {

string res1,res2;

res1.assign("");
res2.assign("");

int st= fixed_size - str1.size();
if (st>0){
        res1.append(st,'0');
        res1.append(str1);

        } else res1.append(str1);

st= fixed_size - str2.size();
if (st>0){
        res2.append(st,'0');
        res2.append(str2);

        } else res2.append(str2);

int value, overhead=0;
string result;
div_t divresult;

for (int i= fixed_size -1 ; i>=0 ; i--) {

    value=overhead+ hex_char_to_dec(res1[i]) + hex_char_to_dec(res2[i]);

    divresult = div (value,16);
    overhead= divresult.quot;
    value=divresult.rem;
    result=dec_to_hex_char(value) + result;

}
int dif=result.size() - fixed_size;
if (dif > 0)  return result.substr(dif,fixed_size); else return result;



}




//-----------VP--------------------------

//--------------------SR------------

struct nodeID {
    std::string networkIP;
        unsigned int cpuID;
        unsigned int coreID;
        };

typedef std::string MCAST_ADDR;
typedef std::pair<nodeID,int> found_t;





class subQueryTemp {
public:
    subQueryTemp() {
    query_id=0;
    NumberOfRequestedResources=0;
    NumberOfDiscoveredResources=0;
    QID=0;
    TST=0;
    UWT=0;
    UPT=0;
    ls.assign("");
    as.assign("");
    ss.assign("");
    };



    unsigned int message_type;
    unsigned int query_id;
        std::string ls;
        std::string as;
        std::string ss;
        unsigned int NumberOfRequestedResources;
        unsigned int NumberOfDiscoveredResources;
        unsigned int QID;
        unsigned int TST;
        unsigned int UWT;
        unsigned int UPT;
        nodeID DiscoveredResourceID;
        std::vector<found_t> resources;
        int signal_int;


};







struct probability_table {

    probability_table(): count() {}

    unsigned count;




};




struct neigbour_table {

    neigbour_table(): count() {}
    unsigned count;


};

/*
class QueryRegistery {



public:
    QueryRegistery();
    ~QueryRegistery();
    void QRegister(subQueryTemp){};
    bool isTheQueryRegistered(int) {}
    bool isTheDiscoveryCompleted(int) {}
    void removeEntry(int) {};
    std::vector<found_t> get_discovered_resourcesIDs(int){};
    void add_to_discovered_resources(int ,nodeID, int){};


};
*/



class QueryRouter {

private:
    std::vector<qr_type> q_router;


public:
    QueryRouter(){};
    ~QueryRouter(){};

   void add_entry(long main_query_id, unsigned int sub_query_id, int parent_sender, int destination){
       qr_type temp;

       temp.main_query_id=main_query_id;
       temp.sub_query_id=sub_query_id;
       temp.parent_sender=parent_sender;
       temp.destination=destination;
      if (!the_route_is_existed_for(main_query_id, sub_query_id))    q_router.push_back(temp);

      return;
   }

   bool the_route_is_existed_for(long main_query_id, unsigned int sub_query_id){
       bool result=false;

       for(unsigned int i=0;i<q_router.size();i++){
           if ((q_router[i].main_query_id==main_query_id)&& (q_router[i].sub_query_id==sub_query_id)) { result=true; return result;}
       }

       return result;

   }

   void print_qrout(){

       EV << "j-debug code 61  "<<  endl;
       for(unsigned int i=0;i<q_router.size();i++){
           EV << q_router[i].main_query_id << "," << q_router[i].sub_query_id << "," << q_router[i].parent_sender <<endl;
       }
       EV << "j-debug code 81"<< endl;
   }

   /*
    * Sub-Query message is arrived
SQM: overal_transcated_data_discovery=173132
SQM-test: overal_transcated_data_discovery=248
qid=30578:0a d-update message from 520 has been arrived in 797
j-debug code 53
j-debug code 6  qid=30578:0
30999,2,128
35215,2,520
51608,0,-2
j-debug code 8
j-debug code 55
    *
    *
    *
    */

   int get_parent_sender_id (long main_query_id, unsigned int sub_query_id){
       int result=-1;
       EV << "j-debug code 6  "<< "qid="<< main_query_id<< ":"<< sub_query_id<< endl;
       for(unsigned int i=0;i<q_router.size();i++){
           EV << q_router[i].main_query_id << "," << q_router[i].sub_query_id << "," << q_router[i].parent_sender <<endl;
       }
       EV << "j-debug code 8"<< endl;
       for(unsigned int i=0;i<q_router.size();i++){
           if ((q_router[i].main_query_id==main_query_id)&& (q_router[i].sub_query_id==sub_query_id)) {
               result=q_router[i].parent_sender;
               EV << "j-debug code 7 result="<< result<< endl;
               return result;
           }
       }

       EV <<"j-debug code 55"<< endl;
       return result;

   }

   int get_destination_id (long main_query_id, unsigned int sub_query_id){
       int result=-1;

       for(unsigned int i=0;i<q_router.size();i++){
           if ((q_router[i].main_query_id==main_query_id)&& (q_router[i].sub_query_id==sub_query_id)) { result=q_router[i].destination; return result;}
       }

       return result;


   }

   void remove_mq_entry(long main_query_id){

       for(unsigned int i=0;i<q_router.size();i++){
           if (q_router[i].main_query_id==main_query_id) { q_router.erase(q_router.begin()+i); return;}
       }

       return;

   }

   void remove_entry(long main_query_id, unsigned int sub_query_id){

       for(unsigned int i=0;i<q_router.size();i++){
           if ((q_router[i].main_query_id==main_query_id)&& (q_router[i].sub_query_id==sub_query_id)) { q_router.erase(q_router.begin()+i); return;}
       }

       return;

   }



};


std::vector<subQueryTemp> QueryBroker(subQueryTemp) {
    std::vector<subQueryTemp> result;
    //....
    return result;

};


bool checkQueryValidation(int) {
    bool result;
    result=true;
    //....
    return result;

};





void IgnoreTheEvent() {

}
void stop_discovery() {

    }

double ctimer() {
    double ftimer=5.33;
    return ftimer;

}

int listening(int *message_type, nodeID *sender_coreID){
    int flg=1;
    return flg;
};

subQueryTemp  receive(nodeID sender, int message_type){
        subQueryTemp messageStr;

        return messageStr;
}


void send(subQueryTemp msg, nodeID receiver, int message_type){
//..
}

void forward( subQueryTemp msg, nodeID original_sender_id, nodeID destination_id, int message_type) {

 //..
};

void broadcast( subQueryTemp msg, MCAST_ADDR multicast_address, int message_type) {
//..
    return ;
};


MCAST_ADDR create_multicast_group(std::vector<nodeID> group_of_nodes) {
    MCAST_ADDR result;
    //create a multicast address
    return result;

};


void sync(){


}

//  ------------SR----------

HE_Resource_Collection translateQuery(string  input)  {HE_Resource_Collection hecol; return hecol;}

//----------------------DHT----------


class  finger_table
{
private:
    struct finger_record {
    std::string start_id;    //
    int successor_rank_id;   //
    };
        finger_record  ft[key_size] ;


public:
    finger_table(){
    };


    void    put (int i, std::string sta_id , int  suc_rank_id  ){//char sta_id[id_char_size],char suc_id[id_char_size] ){
        ft[i].start_id.assign(sta_id);
        ft[i].successor_rank_id=suc_rank_id;
        };

    int     get_successor_id(int i){
        return ft[i].successor_rank_id;
        };

    string  get_start_id(int i){
            return ft[i].start_id;
            };

    int  get_entry_index1(char local_id[id_char_size],char sta_id[id_char_size]){   // sta_id (hex)  = local_id (hex)  + 2 pow ( index )
            int index=0;
        char temp1[id_char_size], temp2[id_char_size];
        strcpy(temp1, sta_id);
        strcpy(temp2, local_id);
        return index;
            };

    int  get_entry_index2(string  msg){

            string key=msg;
        int index;
        for(int i=0; i< key_size ; i++ ) {
            if (ft[i].start_id==key) {
                index= i;
                return index;
                };

            };
        for(int i=0; i< key_size ; i++ ) {
            index=i-1;


                        if (key < ft[i].start_id ) {

                return index;
                                };

                        };


        return key_size -1  ;

        };


};







//-----------------DHT-------------

typedef struct {
   unsigned int first;
   unsigned int second;
   unsigned int third;
   unsigned int fourth;


} Specific_QL1P;


typedef struct {
   unsigned int first;
   unsigned int second;



} Specific_QL3P;



Specific_QL3P get_specific_anycast_query_parameters(unsigned int specific_type){
    Specific_QL3P result;
    // Type A=1300,128,15,1024---Type B=1500,64,20,512
                                       // Type C=2800,16,1,2048------Type D=2000,32,5,256 -------Type E=2600,16,10,128
    switch (specific_type) {
    case 1: { // Type A=1300,128,15,1024
        result.first=8;
        result.second=100;

        return result;
        break;
    }
    case 2: { //Type B=1500,64,20,512
         result.first=16;
         result.second=1000;

         return result;
         break;
     }
    case 3: { //Type C=2800,16,1,2048
        result.first=32;
        result.second=10000;

        return result;
        break;
    }



    }

    result.first=64;
    result.second=100;

    return result;
}




Specific_QL1P get_specific_query_parameters(unsigned int specific_type){
    Specific_QL1P result;
    // Type A=1300,128,15,1024---Type B=1500,64,20,512
                                       // Type C=2800,16,1,2048------Type D=2000,32,5,256 -------Type E=2600,16,10,128
    switch (specific_type) {
    case 1: { // Type A=1300,128,15,1024
        result.first=1300;
        result.second=128;
        result.third=15;
        result.fourth=1024;
        return result;
        break;
    }
    case 2: { //Type B=1500,64,20,512
         result.first=1500;
         result.second=64;
         result.third=20;
         result.fourth=512;
         return result;
         break;
     }
    case 3: { //Type C=2800,16,1,2048
        result.first=2800;
        result.second=16;
        result.third=1;
        result.fourth=2048;
        return result;
        break;
    }
    case 4: { //Type D=2000,32,5,256
        result.first=2000;
        result.second=32;
        result.third=5;
        result.fourth=256;
        return result;
        break;
     }
    case 5: { //Type E=2600,16,10,128
         result.first=2600;
         result.second=16;
         result.third=10;
         result.fourth=128;
         return result;
         break;
     }


    }

    result.first=1300;
    result.second=128;
    result.third=15;
    result.fourth=1024;
    return result;
}




unsigned int set_random_value(unsigned int attribute_id, unsigned int rndcore, unsigned int RH_DRQ){

    srand(rndcore);

//    if (((rndcore==33)||(rndcore==63)||(rndcore==93)||(rndcore==22)||(rndcore==52)||(rndcore==82)||(rndcore==11)||(rndcore==41)||(rndcore==71)||(rndcore==0))&&(attribute_id<10)){
 //type A     Type A=1300,128,15,1024
    if ((rndcore>=0)&& (rndcore<30) &&(attribute_id<10)){
        switch (attribute_id) {
        //  case 6: { return  ((unsigned int[]) {1000, 1200, 1500, 1800, 2000, 2200, 2400, 2500, 2600, 2800, 3000})[rand() % 11]; break;} //CCR by MHz
          case 6: { return  1300 ; break;} //CCR by MHz
        //  case 7: { return  ((unsigned  int[]) {16, 32, 64, 128})[rand() % 4]; break;} //L1S by KB
          case 7: { return  128; break;} //L1S by KB
         // case 8: { return  ((unsigned  int[]) {1, 2, 5, 10, 20})[rand() % 5]; break;} //L1L by NS
          case 8: { return  15; break;} //L1L by NS
        //  case 9: { return  ((unsigned  int[]) {128, 256, 512, 1024, 2048})[rand() % 5]; break;} //L2S by KB
          case 9: { return  1024; break;} //L2S by KB
        }
    }

    //type B     Type B=1500,64,20,512
       if ((rndcore>=30)&& (rndcore<60) &&(attribute_id<10) &&(RH_DRQ>=2) ){
           switch (attribute_id) {
           //  case 6: { return  ((unsigned int[]) {1000, 1200, 1500, 1800, 2000, 2200, 2400, 2500, 2600, 2800, 3000})[rand() % 11]; break;} //CCR by MHz
             case 6: { return  1500 ; break;} //CCR by MHz
           //  case 7: { return  ((unsigned  int[]) {16, 32, 64, 128})[rand() % 4]; break;} //L1S by KB
             case 7: { return  64; break;} //L1S by KB
            // case 8: { return  ((unsigned  int[]) {1, 2, 5, 10, 20})[rand() % 5]; break;} //L1L by NS
             case 8: { return  20; break;} //L1L by NS
           //  case 9: { return  ((unsigned  int[]) {128, 256, 512, 1024, 2048})[rand() % 5]; break;} //L2S by KB
             case 9: { return  512; break;} //L2S by KB
           }
       }

       //type C  Type C=2800,16,1,2048
          if ((rndcore>=60)&& (rndcore<90) &&(attribute_id<10)&&(RH_DRQ>=3)){
              switch (attribute_id) {
              //  case 6: { return  ((unsigned int[]) {1000, 1200, 1500, 1800, 2000, 2200, 2400, 2500, 2600, 2800, 3000})[rand() % 11]; break;} //CCR by MHz
                case 6: { return  2800 ; break;} //CCR by MHz
              //  case 7: { return  ((unsigned  int[]) {16, 32, 64, 128})[rand() % 4]; break;} //L1S by KB
                case 7: { return  16; break;} //L1S by KB
               // case 8: { return  ((unsigned  int[]) {1, 2, 5, 10, 20})[rand() % 5]; break;} //L1L by NS
                case 8: { return  1; break;} //L1L by NS
              //  case 9: { return  ((unsigned  int[]) {128, 256, 512, 1024, 2048})[rand() % 5]; break;} //L2S by KB
                case 9: { return  2048; break;} //L2S by KB
              }
          }


          //type D   Type D=2000,32,5,256
             if ((rndcore>=90)&& (rndcore<120) &&(attribute_id<10)&&(RH_DRQ>=4)){
                 switch (attribute_id) {
                 //  case 6: { return  ((unsigned int[]) {1000, 1200, 1500, 1800, 2000, 2200, 2400, 2500, 2600, 2800, 3000})[rand() % 11]; break;} //CCR by MHz
                   case 6: { return  2000 ; break;} //CCR by MHz
                 //  case 7: { return  ((unsigned  int[]) {16, 32, 64, 128})[rand() % 4]; break;} //L1S by KB
                   case 7: { return  32; break;} //L1S by KB
                  // case 8: { return  ((unsigned  int[]) {1, 2, 5, 10, 20})[rand() % 5]; break;} //L1L by NS
                   case 8: { return  5; break;} //L1L by NS
                 //  case 9: { return  ((unsigned  int[]) {128, 256, 512, 1024, 2048})[rand() % 5]; break;} //L2S by KB
                   case 9: { return  256; break;} //L2S by KB
                 }
             }



             //type E    Type E=2600,16,10,128
                if ((rndcore>=120)&& (rndcore<150) &&(attribute_id<10)&&(RH_DRQ>=5)){
                    switch (attribute_id) {
                    //  case 6: { return  ((unsigned int[]) {1000, 1200, 1500, 1800, 2000, 2200, 2400, 2500, 2600, 2800, 3000})[rand() % 11]; break;} //CCR by MHz
                      case 6: { return  2600 ; break;} //CCR by MHz
                    //  case 7: { return  ((unsigned  int[]) {16, 32, 64, 128})[rand() % 4]; break;} //L1S by KB
                      case 7: { return  16; break;} //L1S by KB
                     // case 8: { return  ((unsigned  int[]) {1, 2, 5, 10, 20})[rand() % 5]; break;} //L1L by NS
                      case 8: { return  10; break;} //L1L by NS
                    //  case 9: { return  ((unsigned  int[]) {128, 256, 512, 1024, 2048})[rand() % 5]; break;} //L2S by KB
                      case 9: { return  128; break;} //L2S by KB
                    }
                }




                //type E    Type E=2600,16,10,128
                for(unsigned int k=0;k<=20 ; k+=4){
                   if ((rndcore>=k*50)&& (rndcore<((k+1)*50)) &&(attribute_id>35)){
                       switch (attribute_id) {

                         case 36: { return  8 ; break;} //MS  {8,16,32,64,128}

                         case 39: { return  100; break;} //NB  {10, 100, 1000, 10000, 20000}
                       }
                   }
                }

                for(unsigned int k=1;k<=20 ; k+=4){
                   if ((rndcore>=k*50)&& (rndcore<((k+1)*50)) &&(attribute_id>35)){
                       switch (attribute_id) {

                         case 36: { return  16 ; break;} //MS  {8,16,32,64,128}

                         case 39: { return  1000; break;} //NB  {10, 100, 1000, 10000, 20000}
                       }
                   }
                }

                for(unsigned int k=2;k<=20 ; k+=4){
                   if ((rndcore>=k*50)&& (rndcore<((k+1)*50)) &&(attribute_id>35)){
                       switch (attribute_id) {

                         case 36: { return  32 ; break;} //MS  {8,16,32,64,128}

                         case 39: { return  10000; break;} //NB  {10, 100, 1000, 10000, 20000}
                       }
                   }
                }


    switch (attribute_id) {
  //  case 6: { return  ((unsigned int[]) {1000, 1200, 1500, 1800, 2000, 2200, 2400, 2500, 2600, 2800, 3000})[rand() % 11]; break;} //CCR by MHz
    case 6: { return  ((unsigned int[]) {1000, 1800, 2500})[rand() % 3]; break;} //CCR by MHz
  //  case 7: { return  ((unsigned  int[]) {16, 32, 64, 128})[rand() % 4]; break;} //L1S by KB
    case 7: { return  ((unsigned  int[]) {32, 128})[rand() % 2]; break;} //L1S by KB
   // case 8: { return  ((unsigned  int[]) {1, 2, 5, 10, 20})[rand() % 5]; break;} //L1L by NS
    case 8: { return  ((unsigned  int[]) {1, 10, 20})[rand() % 3]; break;} //L1L by NS
  //  case 9: { return  ((unsigned  int[]) {128, 256, 512, 1024, 2048})[rand() % 5]; break;} //L2S by KB
    case 9: { return  ((unsigned  int[]) {128, 512, 2048})[rand() % 3]; break;} //L2S by KB



    case 30:  { return  ((unsigned  int[]) {1, 2, 3, 4})[rand() % 4]; break;}  //Processor Type CPU=1, GPU=2, FPGA=3, N/A=4
  //  case 30:  { return  ((unsigned  int[]) { 4})[rand() % 1]; break;}  //Processor Type CPU=1, GPU=2, FPGA=3, N/A=4
    case 34:  { return  ((unsigned  int[]) {8, 16, 32, 64, 128})[rand() % 5]; break;} //number of cores
    case 25:  { return  ((unsigned  int[]) {1, 2, 3, 4, 5, 6 , 7, 8 , 9, 10, 11, 12, 13, 14, 15, 16, 17,18,19})[rand() % 19]; break;}  //Interconnection Network
   // case 25:  { return  ((unsigned  int[]) {10})[rand() % 1]; break;}  //Interconnection Network Bus=1, Ring=2, NOC=3, Crossbar=4, PointToPoint=5, HierarchicalNOC=6, Hypercube=7, Mesh=8, QsNet(Quadrics)=9 ,
    // Infiniband=10, Myrinet=11, SCI(Scalable Coherent Interface)=12, GE( Gigabit Ethernet)=13, NUMAlink=14, SP Switch=15, Proprietary=16, Cray Interconnect=17, Mixed=18, N/A=19
    case 23:  { return  ((unsigned  int[]) {1, 2, 3, 4,5,6,7,8})[rand() % 8]; break;} //  SPARC=1, ARM=2, XCORE=3, RISC=4, CISC=5, Legacy=6 , N/A=7 ,X86=8 , Instruction Set Architecture
  //  case 23:  { return  ((unsigned  int[]) {8})[rand() % 1]; break;} //  SPARC=1, ARM=2, XCORE=3, RISC=4, CISC=5, Legacy=6 , N/A=7 ,X86=8 , Instruction Set Architecture


    case 38:  { return  ((unsigned  int[]) {1,2, 4, 8,16,24})[rand() % 6]; break;} //Die Count
    case 36:  { return  ((unsigned  int[]) {8,16,32,64,128})[rand() % 5]; break;}// Memory Size by GB
    case 39:  { return  ((unsigned  int[]) {10, 100, 1000, 10000, 20000})[rand() % 5]; break;}// Network Bandwidth MBits/s
    case 37:  { return  ((unsigned  int[]) {200, 1000, 2000, 10000,20000})[rand() % 5]; break;} // total number of cores in the node





    }

return 1;
}

std::vector<unsigned int> get_sub_query_type_ids( std::string ls, std::string as){
    std::vector<unsigned int> type_ids;
    //PC-- Processor Type CPU=1, GPU=2, FPGA=3, N/A=4
    //INT --//Interconnection Network Bus=1, Ring=2, NOC=3, Crossbar=4, PointToPoint=5, HierarchicalNOC=6, Hypercube=7, Mesh=8, QsNet(Quadrics)=9 ,
    // Infiniband=10, Myrinet=11, SCI(Scalable Coherent Interface)=12, GE( Gigabit Ethernet)=13, NUMAlink=14, SP Switch=15, Proprietary=16, Cray Interconnect=17, Mixed=18, N/A=19
    // ISA -- SPARC=1, ARM=2, XCORE=3, RISC=4, CISC=5, Legacy=6 , X86=7 ,N/A=8 , Instruction Set Architecture



    // type_id=0  CCR < 1500
    // type_id=1  1500 <=CCR < 2500
    // type_id=2  2500 <= CCR

    // type_id=3  L1S < 64
    // type_id=4  64 <= L1S

    // type_id=5  L1L <10
    // type_id=6  10<= L1L

    // type_id=7  L2S < 512
    // type_id=8  512 <= L2S < 2048
    // type_id=9  2048 <= L2S

    //type_id=10  PC< 3
    //type_id=11  3 <= PC


    //type_id=12 INT <7
    //type_id=13 7 <= INT < 13
    //type_id=14 13 <= INT


    //type_id=15 ISA < 5
    //type_id=16  5<= ISA



    string CCR, L1S,L1L,L2S;
    CCR=ls.substr(0,4);
    L1S=ls.substr(4,4);
    L1L=ls.substr(8,4);
    L2S=ls.substr(12,4);
    unsigned int CCRi, L1Si,L1Li,L2Si;


    std::istringstream iss1, iss2, iss3, iss4;

    iss1.str(CCR);
    iss1 >> std::hex >> CCRi;

    iss2.str(L1S);
    iss2 >> std::hex >> L1Si;

    iss3.str(L1L);
    iss3 >> std::hex >> L1Li;

    iss4.str(L2S);
    iss4 >> std::hex >> L2Si;

    if (CCRi>0){
        if (CCRi<1500) type_ids.push_back(0);// type_id=0  CCR < 1500
        else if ((CCRi>=1500)&&(CCRi<2500))  type_ids.push_back(1); // type_id=1  1500 <=CCR < 2500
        else   type_ids.push_back(2); // type_id=2  2500 <= CCR




    }




    if (L1Si>0){

        if (L1Si<64) type_ids.push_back(3);// type_id=3  L1S < 64
        else  type_ids.push_back(4);  // type_id=4  64 <= L1S





    }





    if (L1Li>0){
        if (L1Li<10) type_ids.push_back(5);// type_id=5  L1L <10
        else type_ids.push_back(6);// type_id=6  10<= L1L




    }





    if (L2Si>0){
        if (L2Si<512) type_ids.push_back(7);// type_id=7  L2S < 512
        else if ((L2Si>=512)&&(L2Si<2048))  type_ids.push_back(8); // type_id=8  512 <= L2S < 2048
        else  type_ids.push_back(9); // type_id=9  2048 <= L2S

    }


    std::string tempstr;
    tempstr.assign("n");

    if (as!=tempstr){


        string PC, INT,ISA;
        PC=as.substr(0,4);
        INT=as.substr(4,4);
        ISA=as.substr(8,4);

        unsigned int PCi, INTi,ISAi;


        std::istringstream iss5, iss6, iss7;

        iss5.str(PC);
        iss5 >> std::hex >> PCi;

        iss6.str(INT);
        iss6 >> std::hex >> INTi;

        iss7.str(ISA);
        iss7 >> std::hex >> ISAi;


        if (PCi>0){
            if (PCi<3) type_ids.push_back(10);  //type_id=10  PC< 3
            else  type_ids.push_back(11);   //type_id=11  3 <= PC

        }




        if (INTi>0){
            if (INTi<7) type_ids.push_back(12);  //type_id=12 INT <7
            else if ((INTi>=7)&&(INTi<13))  type_ids.push_back(13);  //type_id=13 7 <= INT < 13
            else   type_ids.push_back(14);  //type_id=14 13 <= INT

        }





        if (ISAi>0){
            if (ISAi<5) type_ids.push_back(15); //type_id=15 ISA < 5
            else type_ids.push_back(16); //type_id=16  5<= ISA


        }

        EV<< "Values for "<< as << "(" << PC<<INT<<ISA<<")"<< " = "<< PCi<< ", "<< INTi<< ", " << ISAi <<  endl;

    }










    EV<< "Values for "<< ls << "(" << CCR<<L1S<<L1L<<L2S<< ")"<< " = "<< CCRi<< ", "<< L1Si<< ", " << L1Li << ", " << L2Si << endl;


    return type_ids;



}


std::string set_ln_key(int rdcore, unsigned int RH_DRQ){

    unsigned int CCR_value, L1S_value, L1L_value, L2S_value;
    CCR_value=set_random_value(CCR,rdcore, RH_DRQ );
    L1S_value=set_random_value(L1S, rdcore, RH_DRQ);
    L1L_value=set_random_value(L1L, rdcore, RH_DRQ);
    L2S_value=set_random_value(L2S, rdcore, RH_DRQ);
    EV << "CCR="<<CCR_value << "   L1S="<<L1S_value << "    L2S="<<L2S_value << "   L1L="<<L1L_value << endl;

    size_t st;
            string strResult,temp;
            strResult.clear();
            ostringstream str;
            char buf[3];
            std::bitset<16>  CCRb,L1Sb,L1Lb,L2Sb;
                    CCRb=CCR_value;
                    L1Sb=L1S_value;
                    L1Lb=L1L_value;
                    L2Sb=L2S_value;
                    sprintf(buf,"%lX",CCRb.to_ulong());
                    //str << hex ;
                    //str << CCRb.to_ulong();
                    //temp=str.str();
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;
                    //cout << s1 << "=" << CCR << endl;
                    //cout << s2 << "=" << L1S << endl;
                    //cout << s3 << "=" << L1L << endl;
                    //cout << s4 << "=" << L2S << endl;
                    sprintf(buf,"%lX",L1Sb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

             sprintf(buf,"%lX",L1Lb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                   // cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

                    sprintf(buf,"%lX",L2Sb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

return strResult;
}




std::string set_an_key(int rdcore, unsigned int nc, unsigned int RH_DRQ){

    unsigned int PC_value, INT_value, ISA_value, NC_value;
    PC_value=set_random_value(PC,rdcore, RH_DRQ );
    INT_value=set_random_value(INT, rdcore, RH_DRQ);
    ISA_value=set_random_value(ISA, rdcore, RH_DRQ);
    NC_value=nc;
    EV << "PC="<<PC_value << "   INT="<<INT_value << "    ISA="<<ISA_value << "   NC="<<NC_value << endl;

    size_t st;
            string strResult,temp;
            strResult.clear();
            ostringstream str;
            char buf[3];
            std::bitset<16>  PCb,INTb,ISAb,NCb;
                    PCb=PC_value;
                    INTb=INT_value;
                    ISAb=ISA_value;
                    NCb=NC_value;
                    sprintf(buf,"%lX",PCb.to_ulong());
                    //str << hex ;
                    //str << CCRb.to_ulong();
                    //temp=str.str();
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;
                    //cout << s1 << "=" << CCR << endl;
                    //cout << s2 << "=" << L1S << endl;
                    //cout << s3 << "=" << L1L << endl;
                    //cout << s4 << "=" << L2S << endl;
                    sprintf(buf,"%lX",INTb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

             sprintf(buf,"%lX",ISAb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                   // cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

                    sprintf(buf,"%lX",NCb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

return strResult;
}


std::string set_sn_key(int rdcore, unsigned int dc, unsigned int tnc, unsigned int RH_DRQ){


    unsigned int MS_value, NB_value, DC_value, TNC_value;
    MS_value=set_random_value(MS,rdcore , RH_DRQ);
    NB_value=set_random_value(NB, rdcore, RH_DRQ);
    DC_value=dc;
    TNC_value=tnc;
    EV << "MS="<<MS_value << "   NB="<<NB_value << "    DC="<<DC_value << "   TNC="<<TNC_value << endl;

    size_t st;
            string strResult,temp;
            strResult.clear();
            ostringstream str;
            char buf[3];
            std::bitset<16>  MSb,NBb,DCb,TNCb;
                    MSb=MS_value;
                    NBb=NB_value;
                    DCb=DC_value;
                    TNCb=TNC_value;
                    sprintf(buf,"%lX",MSb.to_ulong());
                    //str << hex ;
                    //str << CCRb.to_ulong();
                    //temp=str.str();
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;
                    //cout << s1 << "=" << CCR << endl;
                    //cout << s2 << "=" << L1S << endl;
                    //cout << s3 << "=" << L1L << endl;
                    //cout << s4 << "=" << L2S << endl;
                    sprintf(buf,"%lX",NBb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

             sprintf(buf,"%lX",DCb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                   // cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

                    sprintf(buf,"%lX",TNCb.to_ulong());
                    temp.assign(buf);
                    st= 4- temp.size();
                    strResult.append(st,'0');
                    strResult.append(temp);
                    //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

return strResult;
}




string convert_args_qstring(unsigned int CCR, unsigned int L1S, unsigned int L1L, unsigned int L2S ) {




       size_t st;
       string strResult,temp;
       strResult.clear();
       ostringstream str;
       char buf[4];
       std::bitset<16>  CCRb,L1Sb,L1Lb,L2Sb;
               CCRb=CCR;
               L1Sb=L1S;
               L1Lb=L1L;
               L2Sb=L2S;
               sprintf(buf,"%lX",CCRb.to_ulong());
               //str << hex ;
               //str << CCRb.to_ulong();
               //temp=str.str();
               temp.assign(buf);
               st= 4- temp.size();
               strResult.append(st,'0');
               strResult.append(temp);
               //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;
               //cout << s1 << "=" << CCR << endl;
               //cout << s2 << "=" << L1S << endl;
               //cout << s3 << "=" << L1L << endl;
               //cout << s4 << "=" << L2S << endl;
               sprintf(buf,"%lX",L1Sb.to_ulong());
               temp.assign(buf);
               st= 4- temp.size();
               strResult.append(st,'0');
               strResult.append(temp);
               //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

        sprintf(buf,"%lX",L1Lb.to_ulong());
               temp.assign(buf);
               st= 4- temp.size();
               strResult.append(st,'0');
               strResult.append(temp);
              // cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;

               sprintf(buf,"%lX",L2Sb.to_ulong());
               temp.assign(buf);
               st= 4- temp.size();
               strResult.append(st,'0');
               strResult.append(temp);
               //cout << "-" << temp << "-" << strResult << "-" <<  strResult.size() << endl;






       return strResult;
}


HOGroup create_ho_group(long int thread_group_id, unsigned int nRR, unsigned int ccr, unsigned int l1s, unsigned int l1l, unsigned int l2s, unsigned int pc, unsigned int intp, unsigned int isa, unsigned int nc, unsigned int ms, unsigned int nb, unsigned int dc, unsigned int tnc, unsigned int mil, unsigned int mal, unsigned int mib, unsigned int mab  ){

    HOGroup hog_temp;
    string qlstr = convert_args_qstring(ccr, l1s, l1l, l2s);

    string qastr = convert_args_qstring(pc, intp, isa, nc);
    if ((pc==0) && (intp==0) && (isa==0) && (nc==0)) qastr="n";


    string qsstr = convert_args_qstring(ms, nb, dc, tnc);
    if ((ms==0) && (nb==0) && (dc==0) && (tnc==0)) qsstr="n";




    string inconst = convert_args_qstring(mil, mal, mib, mab);
    hog_temp.homog_id=thread_group_id;
    hog_temp.nRR=nRR;
    hog_temp.qls=qlstr;
    hog_temp.qas=qastr;
    hog_temp.qss=qsstr;
    hog_temp.inconst=inconst;
    return hog_temp;




}


#endif  /* RDP_H */

