/*
 * query.h
 *
 *  Created on: Sep 22, 2014
 *      Author: jzarrin
 */

#ifndef QUERY_H_
#define QUERY_H_

#include <vector>
#include <map>
#include <string>
#include "probability_table.h"

typedef std::string  MainCT;

typedef std::vector<long int> rlist;

struct strtype{

        std::string description; // minimal string class that wraps a const char*


        } ;


const struct strtype DEFULT_STC = { // or maybe FOO_DEFAULT or something
        ""
};

typedef struct {
    long main_query_id;
    unsigned int sub_query_id;
    int parent_sender;
    int destination;
}qr_type;

/*typedef struct sor_rec{
    sor_rec() : psor(-1), sor_source_time_stamp(0.0), sor_size(0) {}
    int psor; // prefered source of resource
    double sor_source_time_stamp; // estimated latency to access the preffered sor
    int sor_size; // number of available resource in the preffered sor

} query_sor_record;
*/

typedef struct {
unsigned int sub_query_id;
long int thread_group_id;
unsigned int nrr; // number of requested resources
std::vector<long int> drs; // IDS of discovered resources
unsigned int ndr; // number of discovered resources
double sq_status; // status of a sub query= 100*ndr/nrr
unsigned int nmsg; // number of messages required to resolve the sub query;
double total_time; // total consumed time for a sub query
unsigned int state; // 0 not completed 1 completed


}Sub_Query_Status;



typedef struct {
long int thread_group_id;
std::vector<long int> drs; // IDS of discovered resources
}Light_SQ_Status;



typedef struct {
long main_query_id;
double mq_status; // status of a main query , i.e. fully resolved , partially resolved, not resolved, resolving rate
long int tnmsg; // total number of message to resolve the main query
double main_query_total_time ;// ms
unsigned int quering_period; // quering period of time t1 t2 t3 t4
std::vector<Light_SQ_Status> sqs;
}Light_MQ_Status ;



typedef struct {
long main_query_id;
int source;
unsigned int nsq; // number of sub queries
double mq_status; // status of a main query , i.e. fully resolved , partially resolved, not resolved, resolving rate
double TTL; // time to live, main query life time
long int tnmsg; // total number of message to resolve the main query
double main_query_total_time ;// ms
unsigned int quering_period; // quering period of time t1 t2 t3 t4
std::vector<Sub_Query_Status> sqs;


}Main_Query_Des ;

typedef struct {
    long int homog_id; // homogeneous group
    std::string qls;
    std::string qas;
    std::string qss;
    unsigned int nRR; //NumberOfRequestedResources
    std::string  inconst; // inter ho group communication constraints
} HOGroup;

typedef struct {
    unsigned int heteg_id; // heterogeneous group
    std::vector<long int> homog_ids;
    std::string igconst; // inter-groups min max latency bandwidth

}HEGroup;

class mainQuery {
public:
    mainQuery() {

    };




        long main_query_id;
        double ttl; // time to live or expiry time
        unsigned int nhogs; // number of hogroups;
        unsigned int nhegs; // number of hegroups;
        unsigned int quering_period;
        std::vector<HOGroup> hogroups;
        std::vector<HEGroup> hegroups;



};


class subQuery {
public:
    subQuery() {
 //   sub_query_id=0;
  //  main_query_id=0;
    nRR=0;
    nDR=0;
    TTL=0;
    nMS=0;
    UDWT=0; // 0: normal upward or downward, 1: call back upward or downward
    UPT=0; // update type
 //   prefered_vnode=-1;
    quering_period=0; // quering period of time t1 t2 t3 t4
    latency=0; // Mill second , time to complete a sub query
    qls.assign("");
    qas.assign("");
    qss.assign("");
    ins.assign("");
    };




    unsigned int sub_query_id;
    long main_query_id;
    std::vector<unsigned int> sq_type_ids;
    long int thread_group_id;
    int original_qms_id;

    sor_record prefered_vnode ;
    unsigned int quering_period; // quering period of time t1 t2 t3 t4

    std::vector<int> visited_qms_ids;

    std::vector<int> visited_sqms_ids;

    std::string qls;
    std::string qas;
    std::string qss;
    std::string  ins; // inter ho group communication constraints

    unsigned int nRR; //NumberOfRequestedResources
    unsigned int nDR; //NumberOfDiscoveredResources
    unsigned int nMS; // number of transacted messages to resolve the query
    double TTL; // time to live sq expiration , number of hops, start time
    double latency;

    unsigned int UDWT; // upward/downward type
    unsigned int UPT; // update type
    rlist DRs;

};


#endif /* QUERY_H_ */
