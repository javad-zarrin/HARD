/*
 * rd_node.h
 *
 *  Created on: Oct 30, 2014
 *      Author: jzarrin
 */

#ifndef RD_NODE_H_
#define RD_NODE_H_
#include "rdp.h"
static const int nhor_per_vnode = 10; // number of homogeneous resources in each virtual node
static const int LN = 0; //instant role leaf node
static const int AN = 1; //instant role aggregate node
static const int SN = 2; //instant role super node

// Startup Events
static const int JoinRequest = 5006; //event_Type
static const int JoinAccept = 5007; //event_Type
static const int UpdateQmsId = 5008; //event_Type
static const int FilledGroup = 5009; //event_Type
static const int DenyUpdate = 5010; //event_Type
static const int SuperNodeElection = 5011; //event_type
static const int VoteYes = 5012; //event_type
static const int UpdateSqmsId = 5013; //event_Type
static const int RemoveSqmsId = 5014; //event_Type
static const int QMS_Merging_Req = 5015; //event_Type
static const int Accept_QMS_Merging = 5016; //event_Type
static const int Confirm_Q_Merging = 5017; //event_Type
static const int Reject_Q_Merging = 5018; //event_Type
static const int New_QMS_Alert = 5019; //event_Type
static const int AN_MOptions_Info = 5020; //event_Type
static const int ANM_Checking_Time = 5021; //event_Type
static const int Start_QMS_Merging_Req = 5022; //event_Type
static const int AN_MOptions_Info_Upgrade = 5023; //event_Type
static const int ChangeQmsId = 5024; //event_Type
static const int UpdateSqmsId2 = 5025; //event_Type

static const int LS_Request = 6001;
static const int LS_Reply = 6002;
static const int FTC = 6003; //finger table construction
static const int Confirm_FTC=6004; //confirmation of FT construction
static const int Discovery_Activation=6005; // enabling resource discovery capability for a requester
static const int QMS_Neighbour=6006;
static const int Confirm_QMS_Neighbour=6007;
static const int Find_QMS_Neighbour=6008;
static const int SG_Members=6009;
static const int SStamp2Ns=6010; // sending sstamp to the node neighbors for the purpose of anycasting in future
//-----------------------------------------------------------------------------------------------
//Discovery Eventswith
static const int Main_Query = 7001; //finger table construction
static const int Lookup=7002;
static const int DUpdate=7003; // discovery update
static const int Forward=7004; // forward sub query --- traversing the nodes in the same layer
static const int Upward=7005; // sub query--- traversing the nodes in from the lower layer to the upper layer
static const int Downward=7006; // sub query--- traversing the nodes in from the upper layer to the lower layer
static const int Main_Reply=7007;
static const int Release_Resources=7008;
static const int Ending_Excution=7009;
static const int Upward_QROUT_Cleanup=7010;
//-----------------------------------------------------------------------------------------------

static const int DenySQMSUpdate = 514; //event_type
static const int Start_ID_Request = 515; //event_type
static const int ID_Request = 516; //event_type
static const int ID_Reply = 517; //event_type
static const int Max_Startup_Time = 3000;//3000;
//static const int Max_QMS_Merging_Hop=7;

static const int WakeUp = 518;
static const int EndingFR = 519;
static const int AN_WakeUp = 520;
static const int EndingSD = 521;

//static const int _null=-1;
static const unsigned int Max_Number_of_Members_in_AGroup = 100;
static const unsigned int Max_Number_of_Members_in_SGroup = 50;
static const unsigned int Min_Number_of_Members_in_AGroup = 50;
static const unsigned int Max_efr_Repetition = 1;

static const double MAX_TTL=6000;

static const unsigned int Max_Querying_Iterations=10;//10;//4;
//static const unsigned int Desired_Number_Of_Resources=1; //number of target resources of the same type to be discovered 1-6

static const unsigned int number_of_requesters_factor=10;//10; // A=percentage of requesters,  B=100/number_of_requesters_factor, A=B/10


typedef struct {

 unsigned  number_of_resources;
 unsigned int time_period;
 long int number_of_messages;
 double discovery_latency;
 double discovery_resolution_rate;
} result_record;


typedef struct {
    double average_number_of_discovery_messages;
    double average_discovery_latency;
    long int total_number_of_fully_resolved_sub_queries;
} analyse_result;


typedef struct {
    int destination;
    int next;
    int hop;
} Route;

typedef vector<Route> Routing_Table;

typedef struct {
    long int resource_id;
    long int thread_group_id; // resource_id , reserved for thread_group_id

}resource_status;

class rdNode: public cSimpleModule {



private:
//  simsignal_t finishSD;
    int module_role;
    int status;
 //   pair<std::string, int> reservation_status; //pair(reservation status, thread id)
    int vnode_id, qms_id, sqms_id, sibling_vnode_id;
    unsigned int querying_iteration;
    std::vector<resource_status> resources;
    Routing_Table routing_table;
    map<int, int> neigbours_group;
    map<int, std::string> neigbours_group_anycast;

    map<int, int> AN_Options;
    vector<int> agroup_members;
    map<unsigned int, double> an_neigbors; // QMS host neighbor nodes
    map<unsigned int, std::string> sn_neigbors; // SQMS host neighbor nodes
    vector<int> sgroup_members;
    std::vector<std::pair<int, std::string> > DHTvector;
    unsigned int maxRank;
    unsigned int closest_preceding_node;
    std::string maxKey;
    finger_table ft;

    int number_of_FTC_confirmations;
    unsigned int a_members_size;
    vector<int> list_of_possible_aggregate_nodes;
    unsigned int voters;
    unsigned int tnc;
    Query_Registry QREG;
    QueryRouter QROUT;

    //long  num_in_msg;
    unsigned int esd_repetition;
    unsigned int efr_repetition;
    Probability_Table PTA;
    cModuleType *discoveryProcType;
    long numSent;
    long numReceived;
    long numPRouting_Messages;
    long group_size;
    long valid;
    long count;
    long num_rec_overlay_msg;
    long num_rec_routing_msg;
    long num_rec_dis_routing_msg;
    long num_rec_discovery_msg;

    double overal_transcated_data_overlay;
    double overal_transcated_data_routing;
    double overal_transcated_data_dis_routing;
    double overal_transcated_data_discovery;



// discovery phase
    struct global_stamp {
        std::string lstamp;
        std::string astamp;
        std::string sstamp;
    } resource_key;

protected:

    void upward_qrout_cleanup(subQuery sub_query);

    void forwardMessage(rdMessage *msg);
    void show_registry();
    analyse_result registry_analyse();
    void send_message_to_a_random_neigbour(rdMessage *msg);
    bool key_checking( std::string query_string, std::string key_string);

    int next_qms_selection(subQuery sub_query);
    int calculate_absolute_preference(subQuery sub_query);
    void show_sors_status(std::string etype, int vid, subQuery sub_query);

    void sub_query_registry_update(subQuery sub_query);
    void sub_query_pta_update(subQuery sub_query, int updater, unsigned int utype); // utype=2: OQMS_DUpdate or utype=3: CB_Downward

    void an_neighbors_cleanup();

    template<class T> void sendMessage(T *msg);
    template<class T> void send_to_a_random_neigbour(T *msg);

    int anycastMessage(SQM *msg);
    void anycast_to_a_random_neigbour(SQM *msg);

    bool check_local_lgroup_joining_possibility();
    bool check_local_agroup_joining_possibility();
    bool is_it_a_registerd_gate(int gateNumber);
    virtual void initialize();
    //virtual void activity();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    virtual void updateDisplay();

public:
    rdNode();
    //   virtual ~rdNode();

};



template<class T> void rdNode::send_to_a_random_neigbour(T *msg) {
    int n = gateSize("gate");
    int k = intuniform(0, n - 1);
    send(msg, "gate$o", k);


}

template<class T> void rdNode::sendMessage(T *msg) {

    cTopology topo("topo");
    // extract topology
    topo.extractByProperty("node");
    int d = msg->getDestination();
    cTopology::Node *targetnode = topo.getNode(d);
    topo.calculateUnweightedSingleShortestPathsTo(targetnode);
    cTopology::Node *node = topo.getNodeFor(this);

    if ((node == NULL) || (node->getNumPaths() == 0)) {
        //ev < "We (" << getFullPath() << ") are not included in the topology.\n";

        if (neigbours_group.count(msg->getDestination()) > 0) {
            send(msg, "gate$o",
                    neigbours_group.find(msg->getDestination())->second);
        } else {
            send_to_a_random_neigbour(msg);
        }
    } else {

        cTopology::LinkOut *path = node->getPath(0);
        int gateNumber = path->getLocalGate()->getIndex();
        send(msg, "gate$o", gateNumber);

    }

}



void rdNode::send_message_to_a_random_neigbour(rdMessage *msg) {
    int n = gateSize("gate");
    int k = intuniform(0, n - 1);
    send(msg, "gate$o", k);

}
/*
 void rdNode::forwardMessage(rdMessage *msg)
 {

 msg->setHopCount(msg->getHopCount()+1);
 if (neigbours_group.count(msg->getDestination())>0) {
 send(msg, "gate$o", neigbours_group.find(msg->getDestination())->second);
 }
 else {
 send_message_to_a_random_neigbour(msg);
 }
 }
 */


void rdNode::forwardMessage(rdMessage *msg) {
    msg->setHopCount(msg->getHopCount() + 1);
    cTopology topo("topo");
    // extract topology
    topo.extractByProperty("node");
    int d = msg->getDestination();
    cTopology::Node *targetnode = topo.getNode(d);
    topo.calculateUnweightedSingleShortestPathsTo(targetnode);
    cTopology::Node *node = topo.getNodeFor(this);

    if ((node == NULL) || (node->getNumPaths() == 0)) {
        //ev < "We (" << getFullPath() << ") are not included in the topology.\n";

        if (neigbours_group.count(msg->getDestination()) > 0) {
            send(msg, "gate$o",
                    neigbours_group.find(msg->getDestination())->second);
        } else {
            send_message_to_a_random_neigbour(msg);
        }
    } else {

        cTopology::LinkOut *path = node->getPath(0);
        int gateNumber = path->getLocalGate()->getIndex();
        send(msg, "gate$o", gateNumber);

    }

}



#endif /* RD_NODE_H_ */
