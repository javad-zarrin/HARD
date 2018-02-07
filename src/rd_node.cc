/* rd3
 *
 *  
 *      Author: jzarrin
 */
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <string>
#include <omnetpp.h>
#include "rd_message_m.h"
#include "signal_m.h"
#include "discovery_reply_m.h"
#include "query_registry.h"
#include <algorithm>
#include "probability_table.h"
#include "rd_tools.h"
#include "rdp.h"
#include "dht.h"
#include "discovery.h"
#include "discovery_m.h"
#include "subquery_m.h"
#include "query.h"
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream
#include "rd_node.h"
#include <iostream>
#include <fstream>
//#include <random>


using namespace std;
unsigned int total_number_of_qms_in_the_system=0;
time_t experiment_id=time(NULL);

std::map<int,std::string> anycast_adress_list;

bool are_all_the_gates_registerd(map<int, int> neigbours_group, int gateSize) {
    map<int, int>::iterator it;
    int n = 0;
    for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it)
        n++;
    if (n == gateSize)
        return true;
    else
        return false;
}



/*
class rdNode: public cSimpleModule {
private:
//	simsignal_t finishSD;
    int module_role;
    int status;
    pair<std::string, int> reservation_status; //pair(reservation status, thread id)
    int vnode_id, qms_id, sqms_id;
    Routing_Table routing_table;
    map<int, int> neigbours_group;
    map<int, int> AN_Options;
    vector<int> agroup_members;
    vector<int> sgroup_members;
    std::vector<std::pair<int, std::string> > DHTvector;
    unsigned int maxRank;
    std::string maxKey;
    finger_table ft;

    int number_of_FTC_confirmations;
    unsigned int a_members_size;
    vector<int> list_of_possible_aggregate_nodes;
    unsigned int voters;
    unsigned int tnc;
    QueryRegistery QREG;
    //long  num_in_msg;
    unsigned int esd_repetition;
    unsigned int efr_repetition;
    ProbabilityTable PT;
    cModuleType *discoveryProcType;
    long numSent;
    long numReceived;
    long numPRouting_Messages;
    long group_size;
    long valid;
    long count;

// discovery phase
    struct global_stamp {
        std::string lstamp;
        std::string astamp;
        std::string sstamp;
    } resource_key;

protected:
    void forwardMessage(rdMessage *msg);
    void sendMessage(Dmsg *msg);
    void send_message_to_a_random_neigbour(rdMessage *msg);
    void send_to_a_random_neigbour(Dmsg *msg);
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
*/
Define_Module(rdNode);
//Register_Class(rdNode);


/*
 rdNode::rdNode(){
 module_role=_null;


 }*/

rdNode::rdNode() {
    module_role = -1;
    vnode_id = -1;
    sibling_vnode_id=-1;
    sqms_id = -1;
    qms_id = -1;
    querying_iteration=1;


}

void rdNode::initialize() {
    total_number_of_qms_in_the_system=0;
    anycast_adress_list.clear();

    num_rec_overlay_msg=0;
    num_rec_routing_msg=0;
    num_rec_discovery_msg=0;
    num_rec_dis_routing_msg=0;

    overal_transcated_data_overlay=0.0;
    overal_transcated_data_routing=0.0;
    overal_transcated_data_discovery=0.0;
    overal_transcated_data_dis_routing=0.0;

    cTopology topo("topo");
    // extract topology
    topo.extractByProperty("node");
//   EV << "cTopology found " << topo.getNumNodes() << " nodes\n";

    numReceived = 0;
    numSent = 0;
    numPRouting_Messages = 0;

    group_size = 0;
    valid = 0;
    count = 1;

   // WATCH(numReceived);
  //  WATCH(numSent);
  //  WATCH(numPRouting_Messages);

 //   WATCH(group_size);
   // WATCH(valid);
   // WATCH(count);

    status = 0;
   // reservation_status.first="free";
    discoveryProcType = cModuleType::find("discoveryProcess");
    //  num_in_msg=0;
    efr_repetition = 0;
    esd_repetition = 0;
    a_members_size = 0;
    //   finishSD = registerSignal("finishSelfDeployment");

    vnode_id = getId() - 2; //getIndex();

    resource_status temp_res;

 /*   for(int i=0; i<nhor_per_vnode; i++){
        temp_res.resource_id=(unsigned int) vnode_id*nhor_per_vnode+i;
        temp_res.thread_group_id=-1;
        resources.push_back(temp_res);

    }*/

    unsigned int upper=((vnode_id % 10)+1)*10;
    for(unsigned int i=0; i<upper; i++){
            temp_res.resource_id=(long int) vnode_id*100+i;
            temp_res.thread_group_id=-1;
            resources.push_back(temp_res);

        }

    resource_key.lstamp = set_ln_key(vnode_id, (unsigned int) par("RH_DRQ"));
    EV << resource_key.lstamp << endl;

//    EV << "Resource ID=" << vnode_id << "SIM_TIME=" << simTime()  << "--------------"<< endl;


    agroup_members.push_back(vnode_id);


    sgroup_members.push_back(vnode_id);

    voters = 1;
    tnc = 0;
    //  module_role=_null;
    //simtime_t start_time;

    //start_time=getIndex();

    if (vnode_id == 0) {

        rdMessage *msg = new rdMessage("Start_ID_Request");
        msg->setMtype(Start_ID_Request);
        //  scheduleAt(getIndex()/10.,msg);
        scheduleAt(simTime(), msg);
    }

//}

    /*
     // Module 0 sends the first message
     if (getIndex()==4) {
     char msgname[20];
     sprintf(msgname, "Test");
     rdMessage *msg = new rdMessage(msgname);
     msg->setSource(vnode_id);
     msg->setDestination(0);2
     msg->setMtype(100);

     scheduleAt(0.45, msg);
     }
     */

//if (getIndex()==4) {
    simtime_t wake_up_time;
    wake_up_time = 1.0 + uniform(0, Max_Startup_Time) / 10000.0;

    // EV << "wT=" << wake_up_time << endl;

    rdMessage *wmsg = new rdMessage("Wake up");
    wmsg->setMtype(WakeUp);
    scheduleAt(wake_up_time, wmsg);


    rdMessage *efrmsg = new rdMessage("Ending First Round");
    efrmsg->setMtype(EndingFR);
    scheduleAt(simTime() + 1 + (Max_Startup_Time) / 10000.0, efrmsg);
}
//   } forwardMessage(ttmsg);

/*void rdNode::activity(){
 while(1) {
 */

void rdNode::handleMessage(cMessage *omsg) {

    char msgname[20];
    if (dynamic_cast<rdMessage*>(omsg) != NULL) {
        //      rdMessage *ttmsg = check_and_cast<rdMessage *>(omsg);
        rdMessage *ttmsg = static_cast<rdMessage *>(omsg);

        /*  int n = gateSize("gate");
         EV << "\n Start: resource Id =" << vnode_id << "--   ";
         for (int i=0;i<=n-1;i++) {
         int a=gate("gate$o", i)->getIndex();
         EV << "gate name= " << a << ", ";
         }
         EV << "\n";
         */
        switch (ttmsg->getMtype()) {

        case Start_ID_Request: {
          //  num_rec_overlay_msg++;
            //    num_in_msg++;
            delete ttmsg;
            int n = gateSize("gate");
            for (int i = 0; i <= n - 1; i++) {
                if (!is_it_a_registerd_gate(i)) {

                    rdMessage *reqmsg = new rdMessage("ID_Request");

                    reqmsg->setMtype(ID_Request);
                    reqmsg->setSource(vnode_id);
                    //                  reqmsg->setOriginSource(vnode_id);
                    reqmsg->setIntContent(vnode_id);
                    send(reqmsg, "gate$o", i);
                }
            }

            break;
        }
        case ID_Request: {
            if (ttmsg->getSource()!=vnode_id) { num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
            EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;
            EV<< "sizeof(rdMessage)=" << 2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool) << endl;

            }
            //   num_in_msg++;
            numReceived++;
            cGate * ingate = ttmsg->getArrivalGate();

            neigbours_group.insert(
                    pair<int, int>(ttmsg->getIntContent(), ingate->getIndex()));
            Route route;
            route.destination = ttmsg->getIntContent();
            route.next = ttmsg->getIntContent();
            route.hop = 1;
            routing_table.push_back(route);

            //         if (vnode_id==8)
            //           EV << "\n node 8:-- received msg from = " <<  ttmsg->getOriginSource() << " msg_type= ID_Request" << "\n" ;

            delete ttmsg;

            rdMessage *repmsg = new rdMessage("ID_Reply");
            repmsg->setMtype(ID_Reply);
            //           repmsg->setOriginSource(vnode_id);
            repmsg->setSource(vnode_id);
            repmsg->setIntContent(vnode_id);
            repmsg->setKind(1);

            send(repmsg, "gate$o", ingate->getIndex());
            numSent++;
            if (status == 0) {
                int n = gateSize("gate");
                for (int i = 0; i <= n - 1; i++) {
                    if (!is_it_a_registerd_gate(i)) {

                        rdMessage *reqmsg = new rdMessage("ID_Request");
                        reqmsg->setSource(vnode_id);

                        reqmsg->setMtype(ID_Request);
                        //             reqmsg->setOriginSource(vnode_id);
                        reqmsg->setIntContent(vnode_id);
                        send(reqmsg, "gate$o", i);
                        numSent++;
                    }
                }
                status = 2;
            }

            /*         if (are_all_the_gates_registerd(neigbours_group, gateSize("gate")) && (status!=1)) {
             EV << "Mode Request- Status is changing in Node=" << vnode_id <<  " at time=" << simTime() << endl;

             }

             */
            if (are_all_the_gates_registerd(neigbours_group,
                    gateSize("gate"))) {
//                EV << "gs" << gateSize("gate") <<  "ns" << neigbours_group.size() <<  "\n" << endl;
                status = 1;
                //               EV << "Node" << vnode_id <<  " is entering to the state 1 rq\n" << endl;
            }

            break;
        }

        case ID_Reply: {
            if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
            EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

            }
            //    num_in_msg++;

            numReceived++;
            cGate * ingate = ttmsg->getArrivalGate();

            neigbours_group.insert(
                    pair<int, int>(ttmsg->getIntContent(), ingate->getIndex()));

            Route route;
            route.destination = ttmsg->getIntContent();
            route.next = ttmsg->getIntContent();
            route.hop = 1;
            routing_table.push_back(route);

            //    if (vnode_id==8)
            //            EV << "\n node 8:-- received msg from = " <<  ttmsg->getOriginSource() << " msg_type= ID_Reply" << "\n" ;

            delete ttmsg;

            if (are_all_the_gates_registerd(neigbours_group, gateSize("gate"))
                    && (status != 1)) {
//                EV << "Mode Reply- Status is changing in Node=" << vnode_id <<  " at time=" << simTime() << endl;

            }

            if (are_all_the_gates_registerd(neigbours_group,
                    gateSize("gate"))) {
                status = 1;
//             EV << "gs=" << gateSize("gate") <<  "n_of_ne=" << neigbours_group.size();
                //           EV << "in Node=" << vnode_id <<  " is entering to the state 1 \n" << endl;
            }

            break;

        }


        case SStamp2Ns: {

            if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
            EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

            }
            //    num_in_msg++;

            numReceived++;
            int sender = ttmsg->getSource();
            strtype anycast_address= ttmsg->getMainContent();


            neigbours_group_anycast.insert(pair<int, std::string>(sender,  anycast_address.description));




            delete ttmsg;

            break;







        }




        case WakeUp: {

            //num_in_msg++;
            if (module_role == -1) {
                bubble("Start Sending Join Requests");
                EV << "Start Sending Join Requests"<< endl;
                //   int n = gateSize("gate");

                rdMessage *jrmsg;
                map<int, int>::iterator it;
                for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                    jrmsg = new rdMessage("JoinRequest");
                    jrmsg->setMtype(JoinRequest);
                    jrmsg->setSource(vnode_id);
                    //               jrmsg->setOriginSource(vnode_id);
                    jrmsg->setDestination(it->first);
                    EV << "destination for JoinRequest msg is " << it->first<< endl;
                    forwardMessage(jrmsg);
                    numSent++;
                }

                /*      for (int k =0;k<=n-1;k++) {
                 jrmsg = new rdMessage(msgname);
                 jrmsg->setMtype(JoinRequest);
                 jrmsg->setSource(vnode_id);

                 send(jrmsg, "gate$o", k);
                 }
                 */

            }
            delete ttmsg;
            break;
        }
        case JoinRequest: {
            if (ttmsg->getDestination() == vnode_id) {

                if (ttmsg->getSource()!=vnode_id) { num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //     num_in_msg++;
                numReceived++;
                if (module_role == -1) {
                    module_role = LN;
                    qms_id = ttmsg->getSource();
                    rdMessage *jamsg;

                    jamsg = new rdMessage("JoinAccept");
                    jamsg->setMtype(JoinAccept);
                    jamsg->setSource(vnode_id);
                    jamsg->setDestination(qms_id);
                    jamsg->setKind(2);
                    forwardMessage(jamsg);
                    numSent++;
                    delete ttmsg;

                } else if (module_role == LN) {
                    ttmsg->setDestination(qms_id);
                    forwardMessage(ttmsg);
                    numSent++;

                } else {
                    bool poss = check_local_lgroup_joining_possibility();
                    if (poss) {

                        rdMessage *uqmsg;
                        uqmsg = new rdMessage("Update QMS ID");
                        uqmsg->setMtype(UpdateQmsId);
                        uqmsg->setSource(vnode_id);
                        uqmsg->setDestination(ttmsg->getSource());

                        agroup_members.push_back(ttmsg->getSource());

                        forwardMessage(uqmsg);
                        numSent++;

                    } else {
                        list_of_possible_aggregate_nodes.push_back(
                                ttmsg->getSource());
                    }
                    delete ttmsg;

                }

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }

            break;

        }
        case UpdateQmsId: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //   num_in_msg++;
                numReceived++;
                if (module_role == -1) {
                    module_role = LN;
                    qms_id = ttmsg->getSource();
                    delete ttmsg;

                } else if (module_role == LN) {

                    rdMessage *dumsg;
                    dumsg = new rdMessage("Deny Update");
                    dumsg->setMtype(DenyUpdate);
                    dumsg->setSource(vnode_id);
                    dumsg->setDestination(ttmsg->getSource());
                    forwardMessage(dumsg);
                    numSent++;
                    delete ttmsg;

                } else {

                    rdMessage *dumsg;
                    dumsg = new rdMessage("Deny Update");
                    dumsg->setMtype(DenyUpdate);
                    dumsg->setSource(vnode_id);
                    dumsg->setDestination(ttmsg->getSource());
                    forwardMessage(dumsg);
                    numSent++;
                    list_of_possible_aggregate_nodes.push_back(
                            ttmsg->getSource());
                    delete ttmsg;

                }

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }

            break;
        }
        case DenyUpdate: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //   num_in_msg++;
                numReceived++;
                if (module_role == -1) {

                } else if (module_role == LN) {

                } else {
                    vector<int>::iterator It;
                    It = find(agroup_members.begin(), agroup_members.end(),
                            ttmsg->getSource());
                    if (It != agroup_members.end()) {
                        agroup_members.erase(It);
                    }

                }
                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }
            break;
        }
        case JoinAccept: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //  num_in_msg++;
                numReceived++;
                if (module_role == -1) {
                    module_role = AN;
                    qms_id = vnode_id;

                    agroup_members.push_back(ttmsg->getSource());

                    delete ttmsg;

                } else if (module_role == LN) {
                    int sender_id;
                    sender_id = ttmsg->getSource();
                    if (sender_id == qms_id) {
                        module_role = AN;
                        qms_id = vnode_id;

                        delete ttmsg;

                    } else {
                        ttmsg->setDestination(qms_id);
                        ttmsg->setIntContent(JoinAccept);
                        forwardMessage(ttmsg);
                        numSent++;

                    }

                } else {
                    bool poss = check_local_lgroup_joining_possibility();
                    if (poss) {
                        agroup_members.push_back(ttmsg->getSource());
                        if (ttmsg->getIntContent() == JoinAccept) { // if the arrived message is a forwarded JoinAccept message

                            rdMessage *cqmsid;
                            cqmsid = new rdMessage("Change QMS ID");
                            cqmsid->setMtype(ChangeQmsId);
                            cqmsid->setSource(vnode_id);
                            cqmsid->setDestination(ttmsg->getSource());
                            cqmsid->setKind(7);
                            forwardMessage(cqmsid);
                            numSent++;
                        }

                    } else {
                        rdMessage *fgp_msg;
                        fgp_msg = new rdMessage("FilledGroup");

                        fgp_msg->setMtype(FilledGroup);
                        fgp_msg->setSource(vnode_id);
                        fgp_msg->setDestination(ttmsg->getSource());
                        forwardMessage(fgp_msg);
                        numSent++;

                        list_of_possible_aggregate_nodes.push_back(
                                ttmsg->getSource());

                    }
                    delete ttmsg;
                }
            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }

            break;
        }

        case FilledGroup: {

            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //      num_in_msg++;
                numReceived++;
                if (module_role == -1) {
                    delete ttmsg;
                } else if (module_role == LN) {
                    module_role = -1;
                    qms_id = -1;
                    //jflag=0;
                    delete ttmsg;
                } else {
                    delete ttmsg;

                }

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case ChangeQmsId: {

            if (ttmsg->getDestination() == vnode_id) {

                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //      num_in_msg++;
                numReceived++;
                if (module_role == -1) {
                    delete ttmsg;
                } else if (module_role == LN) {

                    qms_id = ttmsg->getSource();
                    //jflag=0;
                    delete ttmsg;
                } else {
                    delete ttmsg;

                }

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case Confirm_Q_Merging: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //  num_in_msg++;
                numReceived++;

                if (module_role == AN) {
                    vector<int> invec;
                    string instr;

                    instr = ttmsg->getMainContent().description;
                    invec = convert_string_vector(instr);
                    agroup_members.insert(agroup_members.end(), invec.begin(),
                            invec.end());

                }

                delete ttmsg;
            } else {

                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case Reject_Q_Merging: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //     num_in_msg++;
                numReceived++;
                if (module_role == AN) {
                    a_members_size = a_members_size - ttmsg->getIntContentSD();

                }

                delete ttmsg;
            } else {

                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case New_QMS_Alert: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //     num_in_msg++;
                numReceived++;

                qms_id = ttmsg->getIntContentSD();

                cDisplayString& dispStr = getDisplayString();
                char xbuf[14];//old value=7
                sprintf(xbuf, "#%06x", (qms_id + 1) * 10000);
                char qms_id_buf[10];//old value=5
                sprintf(qms_id_buf, "q=%d", qms_id);
                dispStr.setTagArg("i", 1, xbuf);
                dispStr.setTagArg("t", 0, qms_id_buf);

                delete ttmsg;
            } else {

                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case Accept_QMS_Merging: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //     num_in_msg++;
                numReceived++;

                if ((module_role == AN) && (a_members_size == 0)) {
                    module_role = LN;
                    qms_id = ttmsg->getSource();


                    rdMessage *cqmsg;

                    cqmsg = new rdMessage("Confirm_Q_Merging");

                    cqmsg->setMtype(Confirm_Q_Merging);
                    cqmsg->setSource(vnode_id);
                    cqmsg->setIntContent(vnode_id);

                    cqmsg->setDestination(ttmsg->getSource());

                    string str = convert_vector_string(agroup_members);
                    strtype st;
                    st.description = str;
                    cqmsg->setMainContent(st);
                    forwardMessage(cqmsg);
                    numSent++;


                    for (unsigned i = 0; i < agroup_members.size(); i++) {
                        rdMessage *nqamsg;
                        nqamsg = new rdMessage("New_QMS_Alert");
                        nqamsg->setMtype(New_QMS_Alert);
                        nqamsg->setSource(vnode_id);
                        nqamsg->setIntContentSD(qms_id);
                        nqamsg->setDestination(agroup_members[i]);

                        forwardMessage(nqamsg);
                        numSent++;

                    }

                    sprintf(msgname, "AN-Merging-Options_Info-Upgrade");
                    rdMessage *anmoimsg;
                    map<int, int>::iterator it;
                    vector<int> neigbours_amembers;
                    vector<int> neigbours_vector;
                    vector<int>::iterator itrt;

                    for (it = neigbours_group.begin();
                            it != neigbours_group.end(); ++it) {
                        neigbours_vector.push_back(it->first);
                    }

                    vector<int>::iterator ip;
                    for (vector<int>::size_type i = 0;
                            i < neigbours_vector.size(); i++) {
                        neigbours_amembers.push_back(neigbours_vector.at(i));
                    }

                    for (vector<int>::size_type i = 0;
                            i < agroup_members.size(); i++) {
                        ip = find(neigbours_vector.begin(),
                                neigbours_vector.end(), agroup_members.at(i));
                        if (ip == neigbours_vector.end()) {
                            neigbours_amembers.push_back(agroup_members.at(i));
                        }
                    }

                    //      ip=std::set_union (neigbours_vector.begin(), neigbours_vector.end(),agroup_members.begin(), agroup_members.end(), neigbours_amembers);

                    int bigger_an_size = ttmsg->getIntContent()
                            + agroup_members.size();
                    for (vector<int>::size_type i = 0;
                            i < neigbours_amembers.size(); ++i) {
                        anmoimsg = new rdMessage("AN_MOptions_Info_Upgrade");
                        anmoimsg->setHopCount(0);
                        anmoimsg->setMtype(AN_MOptions_Info_Upgrade);
                        anmoimsg->setSource(vnode_id);
                        anmoimsg->setDestination(neigbours_amembers.at(i));
                        anmoimsg->setIntContent(bigger_an_size);
                        anmoimsg->setIntContentSD(qms_id);
                        forwardMessage(anmoimsg);
                        numSent++;

                    }

                    agroup_members.clear();

                } else {

                    rdMessage *rqmmsg;
                    rqmmsg = new rdMessage("Reject_Q_Merging");

                    rqmmsg->setMtype(Reject_Q_Merging);
                    rqmmsg->setSource(vnode_id);
                    rqmmsg->setDestination(ttmsg->getSource());
                    rqmmsg->setIntContent(vnode_id);
                    rqmmsg->setIntContentSD(ttmsg->getIntContentSD());
                    forwardMessage(rqmmsg);
                    numSent++;

                }

                delete ttmsg;
            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case QMS_Merging_Req: {
            /*   if (ttmsg->getHopCount()>Max_QMS_Merging_Hop) {
             delete ttmsg;
             break;
             }*/
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                cout << "\n A receive qms merging req msg from "
                        << ttmsg->getSource() << " in " << vnode_id
                        << " ans size=" << ttmsg->getIntContent();
                //          num_in_msg++;
                numReceived++;
                if (module_role == LN) {
                    if (qms_id == ttmsg->getSource()) {
                        delete ttmsg;
                    } else {

                        ttmsg->setSource(vnode_id);
                        ttmsg->setDestination(qms_id);

                        forwardMessage(ttmsg);
                        numSent++;
                    }
                } else if (module_role == AN) {
                    cout << "\n B receive qms merging req msg from "
                            << ttmsg->getSource() << " in " << vnode_id
                            << " ans size=" << ttmsg->getIntContent();
                    unsigned int n_members = ttmsg->getIntContent()
                            + agroup_members.size() + a_members_size;
                    if (n_members <= Max_Number_of_Members_in_AGroup) {


                        rdMessage *aqmmsg;
                        aqmmsg = new rdMessage("Accept_QMS_Merging");

                        aqmmsg->setMtype(Accept_QMS_Merging);
                        aqmmsg->setSource(vnode_id);
                        aqmmsg->setDestination(ttmsg->getIntContentSD());
                        aqmmsg->setIntContent(agroup_members.size());
                        a_members_size = a_members_size
                                + ttmsg->getIntContent();
                        aqmmsg->setIntContentSD(ttmsg->getIntContent());
                        forwardMessage(aqmmsg);
                        numSent++;

                    }
                    delete ttmsg;
                }

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case AN_MOptions_Info: {

            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //          num_in_msg++;
                numReceived++;
                AN_Options.insert(pair<int, int>(ttmsg->getIntContentSD(), ttmsg->getIntContent()));
//------------------------------------------------------------------------------------------------
                if (ttmsg->getFlag()){
                    map<int, int>::iterator it;
                    vector<int> neigbours_vector, am;
                    am=convert_string_vector(ttmsg->getMainContent().description);

                    for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                        neigbours_vector.push_back(it->first);
                    }



                    vector<int>::iterator ip;
                    for (unsigned int i = 0; i < neigbours_vector.size(); i++) {
                        ip = find(am.begin(), am.end(), neigbours_vector[i]);
                        if (ip == am.end()) {
                            rdMessage *newanmoimsg;
                            EV<< "extendin AN_MOptions_Info from vnode_id="<< vnode_id << " to " << neigbours_vector[i] <<" hop count=" << ttmsg->getHopCount()<< endl;
                            newanmoimsg = new rdMessage("AN-Merging-Options_Info");
                            newanmoimsg->setHopCount(ttmsg->getHopCount());
                            newanmoimsg->setFlag(false);
                            newanmoimsg->setMtype(AN_MOptions_Info);

                            newanmoimsg->setSource(ttmsg->getSource());

                            newanmoimsg->setIntContent(ttmsg->getIntContent());
                           //------------------------------------------------------------------------------------------------
                            newanmoimsg->setMainContent(ttmsg->getMainContent());
                           //------------------------------------------------------------------------------------------------
                            newanmoimsg->setIntContentSD(ttmsg->getIntContentSD());


                            newanmoimsg->setDestination(neigbours_vector.at(i));
                            forwardMessage(newanmoimsg);

                        }


                    }

                }

//------------------------------------------------------------------------------------------------
                delete ttmsg;
            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }

            break;
        }

        case AN_MOptions_Info_Upgrade: {

            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //       num_in_msg++;
                numReceived++;
                int entry_to_be_removed;
                entry_to_be_removed = ttmsg->getSource();

                map<int, int>::iterator it = AN_Options.find(
                        entry_to_be_removed);
                map<int, int>::iterator pt, at;
                if (it != AN_Options.end()) {
                    AN_Options.erase(it);

                }

                AN_Options.insert(
                        pair<int, int>(ttmsg->getIntContentSD(),
                                ttmsg->getIntContent()));

                delete ttmsg;
            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }

            break;
        }

        case Start_QMS_Merging_Req: {

            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //        num_in_msg++;
                numReceived++;
                if (module_role == AN) {
                    cout << "\n receive msg from " << ttmsg->getSource()
                            << " in " << vnode_id << " finaldes="
                            << ttmsg->getIntContent();

                    rdMessage *aqmmsg;
                    aqmmsg = new rdMessage("QMS_Merging_Request");
                    aqmmsg->setMtype(QMS_Merging_Req);
                    aqmmsg->setSource(vnode_id);
                    aqmmsg->setDestination(ttmsg->getIntContent());
                    aqmmsg->setIntContent(agroup_members.size());
                    aqmmsg->setIntContentSD(vnode_id);
                    cout << "\n send qms merging req msg from " << vnode_id
                            << " to " << ttmsg->getIntContent() << " asize="
                            << agroup_members.size();
                    forwardMessage(aqmmsg);
                    numSent++;


                }
                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case ANM_Checking_Time: {

            EV << "\n-ANM Checking-----------------       " << vnode_id
                    << "   ----------------\n";
            if (AN_Options.size() > 1) {
                bubble("Merging Spot ....");
                EV << "*********     \n Spot Node!!!  at " << vnode_id  << "    ******* \n";
                EV << "\nAN_ID      " << "Number of Resources";
                for (map<int, int>::iterator i = AN_Options.begin();
                        i != AN_Options.end(); i++) {

                    EV << "\n  " << i->first << "  " << i->second << " size="<< AN_Options.size() << "\n";

                }

                vector<int> candidate_ans_for_merging;

                int largest_an;
                map<int, int>::iterator it = AN_Options.find(qms_id);
                map<int, int>::iterator pt, at;
                if (it != AN_Options.end()) {
                    int number_of_current_an_members = it->second;
                    unsigned int final_size = number_of_current_an_members;
                    int size_of_largest_an, vnode_id_of_largest_an;
                    AN_Options.erase(it);
                    candidate_ans_for_merging.push_back(qms_id);
                    EV << "\n insert in candidate list " << qms_id;

                    largest_an = qms_id;
                    int ps, qs;

                    do {
                        at = AN_Options.begin();
                        size_of_largest_an = at->second;
                        //          cout << "\n  rid=" << at->first << "size_of_largest_an=" <<size_of_largest_an;
                        for (pt = AN_Options.begin(); pt != AN_Options.end();
                                pt++) {
                            ps = pt->second;
                            qs = pt->first;
                            EV << "\n  AN_Option=" << qs << " size=" << ps
                                    << " size_of_largest_an="
                                    << size_of_largest_an;

                            if (ps >= size_of_largest_an) {
                                size_of_largest_an = ps;
                                vnode_id_of_largest_an = qs;
                                EV << "\n vnode_id_of_largest_an="
                                        << vnode_id_of_largest_an
                                        << "  size_of_largest_an="
                                        << size_of_largest_an;

                            }
                        }
                        EV << "\n  final_size=" << final_size;

                        final_size = final_size + size_of_largest_an;
                        EV << "\n  final_size=" << final_size;
                        if (final_size <= Max_Number_of_Members_in_AGroup) {

                            candidate_ans_for_merging.push_back(
                                    vnode_id_of_largest_an);

                            int entry_to_be_removed;
                            entry_to_be_removed = vnode_id_of_largest_an;

                            map<int, int>::iterator it = AN_Options.find(
                                    entry_to_be_removed);

                            if (it != AN_Options.end()) {
                                AN_Options.erase(it);

                            }

                            EV << "\n insert in candidate list "
                                    << vnode_id_of_largest_an;

                            if (size_of_largest_an
                                    >= number_of_current_an_members) {
                                largest_an = vnode_id_of_largest_an;
                            }

                        }

                    } while ((final_size <= Max_Number_of_Members_in_AGroup)
                            && (AN_Options.size() != 0));


                    rdMessage *aqmmsg;

                    EV << " \n vnode_id= " << vnode_id << "  size="<< candidate_ans_for_merging.size() << " --\n";
                    if (candidate_ans_for_merging.size() > 1) {
                        for (std::vector<int>::size_type i = 0;
                                i != candidate_ans_for_merging.size(); i++) {
                            EV << " \n candidate_id= "
                                    << candidate_ans_for_merging.at(i)
                                    << " largest_an= " << largest_an
                                    << "   size of largest an= "
                                    << size_of_largest_an << "--\n";
                            if (candidate_ans_for_merging.at(i) != largest_an) {
                                if (vnode_id
                                        != candidate_ans_for_merging.at(i)) {
                                    EV << "\n send msg from " << vnode_id
                                            << " to "
                                            << candidate_ans_for_merging.at(i)
                                            << " finaldes=" << largest_an;
                                    aqmmsg = new rdMessage("Start_QMS_Merging_Request");
                                    aqmmsg->setMtype(Start_QMS_Merging_Req);
                                    aqmmsg->setSource(vnode_id);
                                    aqmmsg->setDestination(
                                            candidate_ans_for_merging.at(i));
                                    aqmmsg->setIntContent(largest_an);

                                    forwardMessage(aqmmsg);
                                    numSent++;

                                } else {

                                    aqmmsg = new rdMessage("Start_QMS_Merging_Request");
                                    aqmmsg->setMtype(Start_QMS_Merging_Req);
                                    aqmmsg->setSource(vnode_id);
                                    aqmmsg->setDestination(
                                            candidate_ans_for_merging.at(i));
                                    aqmmsg->setIntContent(largest_an);
                                    scheduleAt(simTime(), aqmmsg);

                                }
                            }

                        }
                    }

                } else {

                }

            }

            delete ttmsg;
            break;
        }

        case EndingFR: {
            //  num_in_msg++;
            efr_repetition++;

            if (module_role == -1) {

                module_role = AN;
                qms_id = vnode_id;
                //           EV << "Create a too small AGroup... " << endl;

            }

            if ((module_role == AN)
                    && (agroup_members.size() < Min_Number_of_Members_in_AGroup)
                    && (efr_repetition <= Max_efr_Repetition)) {

                //             EV << "efr repetition=" << efr_repetition << endl;
                AN_Options.insert(pair<int, int>(vnode_id, agroup_members.size()));


                rdMessage *anmoimsg;
                map<int, int>::iterator it;
                vector<int> neigbours_amembers;
                vector<int> neigbours_vector;
                vector<int>::iterator itrt;

                for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                    neigbours_vector.push_back(it->first);
                }

                vector<int>::iterator ip;
                for (vector<int>::size_type i = 0; i < neigbours_vector.size();
                        i++) {
                    neigbours_amembers.push_back(neigbours_vector.at(i));
                }

                for (vector<int>::size_type i = 0; i < agroup_members.size();
                        i++) {
                    ip = find(neigbours_vector.begin(), neigbours_vector.end(),
                            agroup_members.at(i));
                    if (ip == neigbours_vector.end()) {
                        neigbours_amembers.push_back(agroup_members.at(i));
                    }
                }

                //      ip=std::set_union (neigbours_vector.begin(), neigbours_vector.end(),agroup_members.begin(), agroup_members.end(), neigbours_amembers);

//------------------------------------------------------------------------------------------------
             /*   for (vector<int>::size_type i = 0;i < neigbours_amembers.size(); ++i) {
                    anmoimsg = new rdMessage("AN-Merging-Options_Info");
                    anmoimsg->setHopCount(0);
                    anmoimsg->setMtype(AN_MOptions_Info);
                    anmoimsg->setSource(vnode_id);
                    anmoimsg->setDestination(neigbours_amembers.at(i));
                    anmoimsg->setIntContent(agroup_members.size());
                    anmoimsg->setIntContentSD(qms_id);
                    forwardMessage(anmoimsg);
                    numSent++;

                }*/
//------------------------------------------------------------------------------------------------
                string st_temp;
                strtype strt;
                st_temp=convert_vector_string(agroup_members);
                strt.description=st_temp;
//------------------------------------------------------------------------------------------------

                for (vector<int>::size_type i = 0; i < agroup_members.size(); ++i) {
                    anmoimsg = new rdMessage("AN-Merging-Options_Info");
                    anmoimsg->setHopCount(0);
                    anmoimsg->setMtype(AN_MOptions_Info);
                    anmoimsg->setSource(vnode_id);
                    anmoimsg->setFlag(true);
                    anmoimsg->setDestination(agroup_members.at(i));
                    anmoimsg->setIntContent(agroup_members.size());
//------------------------------------------------------------------------------------------------
                    anmoimsg->setMainContent(strt);
//------------------------------------------------------------------------------------------------
                    anmoimsg->setIntContentSD(qms_id);
                    forwardMessage(anmoimsg);
                    numSent++;

                }
//------------------------------------------------------------------------------------------------

                simtime_t anm_checking_time;
                anm_checking_time = simTime()
                        + uniform(1000, Max_Startup_Time - 1000) / 10000.0;

                EV << "wT=" << anm_checking_time << endl;

                rdMessage *anmctmsg = new rdMessage("ANM_Checking_Time");
                anmctmsg->setMtype(ANM_Checking_Time);
                scheduleAt(anm_checking_time, anmctmsg);


                rdMessage *efrmsg = new rdMessage("Ending First Round");
                efrmsg->setMtype(EndingFR);
                scheduleAt(simTime() + (Max_Startup_Time) / 10000.0, efrmsg);

                delete ttmsg;
                break;
            }

            cDisplayString& dispStr = getDisplayString();
            char xbuf[14];//old value=7
            sprintf(xbuf, "#%06x", (qms_id + 1) * 10000);
            char qms_id_buf[10];//old value=5
            sprintf(qms_id_buf, "q=%d", qms_id);
            //sprintf(xbuf, "#123456");

            if (module_role == 1) {
                dispStr.setTagArg("i", 1, "red");
                //          EV<< "this is it:"<< dispStr.str()<< endl;

                simtime_t a_wake_up_time;
                a_wake_up_time = simTime()
                        + uniform(0, Max_Startup_Time) / 1000.0;

                //             EV << "a_wt=" << a_wake_up_time << endl;

                rdMessage *awmsg = new rdMessage("AN Wake up");
                awmsg->setMtype(AN_WakeUp);
                scheduleAt(a_wake_up_time, awmsg);


                rdMessage *esdmsg = new rdMessage("Ending Second Round");
                esdmsg->setMtype(EndingSD);
                scheduleAt(simTime() + 2+ (Max_Startup_Time) / 1000.0, esdmsg);

            } else if (module_role == 0) {
                dispStr.setTagArg("i", 1, xbuf);
                dispStr.setTagArg("t", 0, qms_id_buf);

                //           EV<< "this is it:"<< dispStr.str()<< endl;

            } else {
                //  dispStr.set("i=red/routing");
                dispStr.setTagArg("i", 1, "white");
                //         EV<< "this resource is not belonged to a group :"<< dispStr.str()<< endl;
            }

            if (efr_repetition <= Max_efr_Repetition) {

                simtime_t anm_checking_time;
                anm_checking_time = simTime()
                        + uniform(1000, Max_Startup_Time - 1000) / 10000.0;

                //      EV << "wT=" << anm_checking_time << endl;

                rdMessage *anmctmsg = new rdMessage("ANM_Checking_Time");
                anmctmsg->setMtype(ANM_Checking_Time);
                scheduleAt(anm_checking_time, anmctmsg);


                rdMessage *efrmsg = new rdMessage("Ending First Round");
                efrmsg->setMtype(EndingFR);
                scheduleAt(simTime() + (Max_Startup_Time) / 10000.0, efrmsg);

            }

            delete ttmsg;
            break;
        }

            // second phase: sqms election
        case AN_WakeUp: {
            EV << endl<< "JX: vnode="<<vnode_id<< " An AN_WakeUp from " << ttmsg->getSource() << " (ms="<< ttmsg->getIntContent()<< ") "<< " sqms=" << sqms_id << " qms_id=" << qms_id << endl;

            //  num_in_msg++;

                //   if (list_of_possible_aggregate_nodes.empty()) {
                //         EV << "Empty LPAN in qms_id=" << qms_id << endl;



//rep11111111111111111111111111111111111111111111111111111111111111111111111
            map<int, int>::iterator it;
            vector<int>::iterator ip;
            if (sqms_id == -1) {
                rdMessage *emsg;
                for (unsigned int i=0; i< agroup_members.size(); i++) {
                    if (agroup_members[i]!=vnode_id){
                        emsg = new rdMessage("SuperNodeElection");
                        emsg->setMtype(SuperNodeElection);
                        emsg->setSource(vnode_id);
                        emsg->setDestination(agroup_members[i]);
                        emsg->setIntContent(vnode_id);
                        emsg->setID(vnode_id);
                        emsg->setFlag(true);
                        strtype st;
                        st.description=convert_vector_string(agroup_members);
                        emsg->setMainContent(st);
                        emsg->setIntContentSD((int) agroup_members.size());

                        EV << endl<< "JX: Sent a SuperNodeElection from vnode="<<vnode_id<< " (ms="<< vnode_id<< ") to " << agroup_members[i] << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;

                        forwardMessage(emsg);
                        numSent++;
                    }
                }
            }

//rep111111111111111111111111111111111111111111111111111111111111111111111111





                for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                   /* if (sqms_id == -1) { //rep1
                        emsg = new rdMessage("SuperNodeElection");
                        emsg->setMtype(SuperNodeElection);
                        emsg->setSource(vnode_id);
                        emsg->setDestination(it->first);
                        emsg->setIntContent(vnode_id);
                        emsg->setID(vnode_id); //emsg->setID(rqms_id);
                        emsg->setIntContentSD((int) agroup_members.size());
                        forwardMessage(emsg);
                        numSent++;
                    }*/


//===============================================================================
                    ip = find(agroup_members.begin(), agroup_members.end(), it->first);
                    if (ip == agroup_members.end()) {
                        rdMessage *lsrpmsg;
                        lsrpmsg = new rdMessage("QMS_Neighbour");
                        lsrpmsg->setDestination(it->first);
                        lsrpmsg->setSource(vnode_id);
                        lsrpmsg->setMtype(QMS_Neighbour);
                        lsrpmsg->setIntContent(qms_id);
                        forwardMessage(lsrpmsg);
                    }
//===============================================================================






                /*               }
                 else {

                 EV << "Here it is ...\n" ;

                 for (unsigned int i=0;i<list_of_possible_aggregate_nodes.size();i++) {
                 rdMessage * emsg;
                 emsg = new rdMessage(msgname);
                 emsg->setMtype(SuperNodeElection);
                 emsg->setSource(vnode_id);
                 emsg->setDestination(list_of_possible_aggregate_nodes[i]);
                 emsg->setIntContent(qms_id);

                 forwardMessage(emsg);*/
                //   }
            }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                for (unsigned int i = 1; i < agroup_members.size(); i++) {
                    //start to build FT
                    rdMessage *ftcmsg;
                    strtype st;
                    ftcmsg = new rdMessage("Find_QMS_Neighbour");
                    ftcmsg->setDestination(agroup_members[i]);
                    ftcmsg->setSource(vnode_id);
                    ftcmsg->setMtype(Find_QMS_Neighbour);
                    ftcmsg->setIntContent(qms_id);
                    string list;
                    list = convert_vector_string(agroup_members);
                    st.description = list;
                    ftcmsg->setMainContent(st);
                    forwardMessage(ftcmsg);

                }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

            delete ttmsg;
            break;

        }

        case SuperNodeElection: {

            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }

                EV << endl<< "JX: vnode="<<vnode_id<< " A SuperNodeElection from " << ttmsg->getSource() << " (ms="<< ttmsg->getIntContent()<< ") "<< " sqms=" << sqms_id << " qms_id=" << qms_id << endl;
                //      num_in_msg++;
                numReceived++;
                if (QREG.isMQueryRegistered(ttmsg->getID())) {
                    //           EV << "Already Registered msg=" << ttmsg->getId() << " ID=" << ttmsg->getID() << endl;
                    delete ttmsg;
                    break;
                } else {

                    //           EV << "Register msg=" << ttmsg->getId() << " ID=" << ttmsg->getID() << endl;
                    QREG.QRegister(ttmsg);

                }

                //          EV << "Super Node Selection Procedure " << endl;
                if (qms_id == ttmsg->getIntContent()) {

//rep2222222222222222222222222222222222222222222222222222222222222222
                    rdMessage *emsg; // rep2
                    map<int, int>::iterator it;
                    int des;
                    vector<int> am;
                    am=convert_string_vector(ttmsg->getMainContent().description);
                    for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                        des = it->first;
                        if (find(am.begin(),am.end(), des)==am.end()){
                            if (des!=ttmsg->getIntContent()){

                            emsg = new rdMessage("SuperNodeElection");
                            emsg->setMtype(SuperNodeElection);
                            emsg->setSource(vnode_id);
                            emsg->setDestination(des);
                            emsg->setIntContent(ttmsg->getIntContent());
                            emsg->setID(ttmsg->getID());
                            emsg->setIntContentSD(ttmsg->getIntContentSD());
                            emsg->setMainContent(ttmsg->getMainContent());

                            EV << endl<< "JX: Sent a SuperNodeElection from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << des << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                            forwardMessage(emsg);
                            numSent++;
                            }

                        }




                    }

//rep2222222222222222222222222222222222222222222222222222222222222222

                 /*   rdMessage *emsg; // rep2
                    map<int, int>::iterator it;
                    int des;
                    for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                        des = it->first;
                        if ((des != qms_id) && (des != ttmsg->getSource())) {
                            emsg = new rdMessage("SuperNodeElection");
                            emsg->setMtype(SuperNodeElection);
                            emsg->setSource(vnode_id);
                            emsg->setDestination(des);
                            emsg->setIntContent(ttmsg->getIntContent());
                            emsg->setID(ttmsg->getID());
                            emsg->setIntContentSD(ttmsg->getIntContentSD());
                            forwardMessage(emsg);
                            numSent++;

                        }

                    }
                    */
                    delete ttmsg;
                } else {
                    if (module_role == LN) {
                        //         EV << "LN Recived SNE" <<endl;

                        ttmsg->setSource(vnode_id); //emsg->setSource(ttmsg->getSource());
                        ttmsg->setDestination(qms_id);

                        EV << endl<< "JX: MR=LN Forwarded a SuperNodeElection from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << qms_id << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                        forwardMessage(ttmsg);
                        numSent++;

                    } else if ((module_role == AN) && (sqms_id == -1)) {
                        //              EV << "AN -1 Recived SNE" <<endl;
                        EV << endl<< "JX: vnode="<<vnode_id<< "MR=AN sqms_id="<< sqms_id << endl;
                        sqms_id = ttmsg->getIntContent();

                        rdMessage *vymsg;

                        vymsg = new rdMessage("VoteYes");
                        vymsg->setIntContent(vnode_id);
                        vymsg->setMtype(VoteYes);
                        vymsg->setSource(vnode_id);
                        vymsg->setDestination(sqms_id);
                        vymsg->setIntContent(vnode_id);
                        vymsg->setIntContentSD((int) agroup_members.size());

                        EV << endl<< "JX: SQMS-Change Sent a VoteYes from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << sqms_id << " new sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;

                        forwardMessage(vymsg);
                        numSent++;
                        delete ttmsg;
                    } else if ((module_role == AN) && (sqms_id > 0)) {
                        //         EV << "AN >0 Recived SNE" <<endl;

                        ttmsg->setSource(vnode_id); //emsg->setSource(ttmsg->getSource());

                        ttmsg->setDestination(sqms_id);

                        EV << endl<< "JX: MR=AN sqms_id>0 Forwarded a SuperNodeElection from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << sqms_id << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                        forwardMessage(ttmsg);
                        numSent++;

                    } else if (module_role == SN) {
                        //          EV << "SN Received SNE" <<endl;
                        //int poss=check_local_agroup_joining_possibility();
                        bool poss = check_local_agroup_joining_possibility();
                        if (poss) {

                            rdMessage *usmsg;
                            usmsg = new rdMessage("UpdateSqmsId");
                            usmsg->setDestination(ttmsg->getIntContent());
                            usmsg->setSource(vnode_id);
                            usmsg->setMtype(UpdateSqmsId);
                            usmsg->setIntContent(vnode_id);

                            EV << endl<< "JX: Sent a UpdateSqmsId from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << ttmsg->getIntContent() << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                            forwardMessage(usmsg);
                            numSent++;

                            EV << endl<< "JX before: "<<vnode_id << " sgroup_members=";
                            for (unsigned int i=0; i<sgroup_members.size();i++)
                                EV << sgroup_members[i]<< ",";
                            EV<< endl;

                            if (std::find(sgroup_members.begin(),sgroup_members.end(),ttmsg->getIntContent())==sgroup_members.end()){
                                voters++;
                                sgroup_members.push_back(ttmsg->getIntContent()); //sgroup_members.push_back(ttmsg->getSource());
                                tnc = tnc + ttmsg->getIntContentSD();
                            }

                            EV << endl<< "JX after: "<<vnode_id << " sgroup_members=";
                            for (unsigned int i=0; i<sgroup_members.size();i++)
                                EV << sgroup_members[i]<< ",";
                            EV<< endl;
                        }
                        delete ttmsg;
                    } else {
                        delete ttmsg;
                    }

                }

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }

            break;
        }

        case VoteYes: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }

                EV << endl<< "JX: vnode="<<vnode_id<< " A VoteYes from " << ttmsg->getSource() << " (ms="<< ttmsg->getIntContent()<< ") "<< " sqms=" << sqms_id << " qms_id=" << qms_id << endl;
                //     num_in_msg++;
                numReceived++;
                if ((module_role == AN) && (sqms_id == -1)) {

                    EV << endl<< "JX: vnode_id="<<vnode_id <<" before MR=AN sqms_id="<< sqms_id ;
                    sqms_id = vnode_id;
                    module_role = SN;


                    EV << endl<< "JX: vnode_id="<<vnode_id <<" after MR=SN sqms_id="<< sqms_id ;


                    EV << endl<< "JX before: "<<vnode_id << " sgroup_members=";
                    for (unsigned int i=0; i<sgroup_members.size();i++)
                        EV << sgroup_members[i]<< ",";
                    EV<< endl;


                    if (std::find(sgroup_members.begin(),sgroup_members.end(),ttmsg->getIntContent())==sgroup_members.end()){
                        voters++;
                        sgroup_members.push_back(ttmsg->getIntContent()); //sgroup_members.push_back(ttmsg->getSource());
                        tnc = tnc + ttmsg->getIntContentSD();

                    }

                    EV << endl<< "JX after: "<<vnode_id << " sgroup_members=";
                    for (unsigned int i=0; i<sgroup_members.size();i++)
                        EV << sgroup_members[i]<< ",";
                    EV<< endl;


                    delete ttmsg;
                } else if ((module_role == AN) && (sqms_id > 0)) {

                    int sender_id;
                    sender_id = ttmsg->getIntContent(); //sender_id=ttmsg->getSource();

                    if (sender_id == vnode_id) {

                        EV << endl<< "JX: vnode_id="<<vnode_id <<" before MR=AN sqms_id="<< sqms_id ;
                        module_role = SN;
                        sqms_id = vnode_id;

                        EV << endl<< "JX: vnode_id="<<vnode_id <<" after MR=SN sqms_id="<< sqms_id ;

                        EV << "#Check it out! VOTEYES sender=resource-id#"
                                  << endl;
                        delete ttmsg;
                    } else {

                        ttmsg->setSource(vnode_id); //vymsg->setSource(ttmsg->getSource());

                        ttmsg->setDestination(sqms_id);

                        ttmsg->setIntContentSD(vnode_id);


                        EV << endl<< "JX: MR=AN sqms_id>0 Forwarded a VoteYes from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << sqms_id << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                        forwardMessage(ttmsg);
                        numSent++;

                    }

                } else if (module_role == SN) {
                    bool poss = check_local_agroup_joining_possibility();
                    if (poss) {


                        EV << endl<< "JX MR=SN before: "<<vnode_id << " sgroup_members=";
                        for (unsigned int i=0; i<sgroup_members.size();i++)
                            EV << sgroup_members[i]<< ",";
                        EV<< endl;


                        if (std::find(sgroup_members.begin(),sgroup_members.end(),ttmsg->getIntContent())==sgroup_members.end()){
                            voters++;
                            sgroup_members.push_back(ttmsg->getIntContent());
                            tnc = tnc + ttmsg->getIntContentSD();

                        }


                        EV << endl<< "JX after: "<<vnode_id << " sgroup_members=";
                        for (unsigned int i=0; i<sgroup_members.size();i++)
                            EV << sgroup_members[i]<< ",";
                        EV<< endl;



                        rdMessage *usmsg;
                        usmsg = new rdMessage("UpdateSqmsId2");
                        usmsg->setDestination(ttmsg->getIntContent());
                        //           EV << "Destination is : " << ttmsg->getIntContent() << endl;
                        usmsg->setSource(vnode_id);
                        usmsg->setMtype(UpdateSqmsId2);
                        usmsg->setIntContent(vnode_id);

                        EV << endl<< "JX: Sent a UpdateSqmsId2 from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << ttmsg->getIntContent() << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                        forwardMessage(usmsg);
                        numSent++;

                    } else {

                        rdMessage *rsmsg;
                        rsmsg = new rdMessage("RemoveSqmsId");
                        rsmsg->setDestination(ttmsg->getIntContent());
                        //               EV << "Destination is : " << ttmsg->getIntContent() << endl;
                        rsmsg->setSource(vnode_id);
                        rsmsg->setMtype(RemoveSqmsId);
                        rsmsg->setIntContent(vnode_id);


                        EV << endl<< "JX: Sent a RemoveSqmsId from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << ttmsg->getIntContent() << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                        forwardMessage(rsmsg);
                        numSent++;

                    }
                    delete ttmsg;
                }

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }

            break;
        }

        case UpdateSqmsId2: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //      num_in_msg++;

                EV << endl<< "JX: vnode="<<vnode_id<< " A UpdateSqmsId2 from " << ttmsg->getSource() << " (ms="<< ttmsg->getIntContent()<< ") "<< " sqms=" << sqms_id << " qms_id=" << qms_id << endl;
                numReceived++;
                if ((module_role == AN)&& (sqms_id>0)) {

                    EV << endl<< "JX: vnode_id="<<vnode_id <<" before MR=AN sqms_id="<< sqms_id ;
                    sqms_id =ttmsg->getIntContent() ;
                    //          EV << " SQMS updated to -1" << endl;
                    EV << endl<< "JX: vnode_id="<<vnode_id <<" after MR=AN sqms_id="<< sqms_id ;

                }
                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }
            break;
        }


        case RemoveSqmsId: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //      num_in_msg++;

                EV << endl<< "JX: vnode="<<vnode_id<< " A RemoveSqmsId from " << ttmsg->getSource() << " (ms="<< ttmsg->getIntContent()<< ") "<< " sqms=" << sqms_id << " qms_id=" << qms_id << endl;
                numReceived++;
                if ((module_role == AN)
                        && (sqms_id == ttmsg->getIntContent())) {
                    EV << endl<< "JX: vnode_id="<<vnode_id <<" before MR=AN sqms_id="<< sqms_id ;
                    sqms_id = -1;
                    EV << endl<< "JX: vnode_id="<<vnode_id <<" after MR=AN sqms_id="<< sqms_id ;
                    //          EV << " SQMS updated to -1" << endl;

                }
                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }
            break;
        }

        case UpdateSqmsId: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++; overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //     num_in_msg++;

                EV << endl<< "JX: vnode="<<vnode_id<< " A UpdateSQMSId from " << ttmsg->getSource() << " (ms="<< ttmsg->getIntContent()<< ") "<< " sqms=" << sqms_id << " qms_id=" << qms_id << endl;
                numReceived++;
                if ((module_role == AN) && (sqms_id == -1)) {
                    EV << endl<< "JX: vnode_id="<<vnode_id <<" before MR=AN sqms_id="<< sqms_id ;
                    //          EV << " -1 Update SQMS ID" << endl;
                    sqms_id = ttmsg->getIntContent();
                    EV << endl<< "JX: vnode_id="<<vnode_id <<" after MR=AN sqms_id="<< sqms_id ;

                    delete ttmsg;
                } else if (((module_role == AN) && (sqms_id > 0))) {

                    //           EV << "  >0 Update SQMS ID" << endl;

                    if (ttmsg->getIntContent() == sqms_id) {
                        //sqms_id=ttmsg->getIntContent();
                        //        EV << " changed >0 Update SQMS ID" << endl;
                        EV << endl<< "JX: vnode_id="<<vnode_id <<" no change MR=AN sqms_id="<< sqms_id ;
                        delete ttmsg;

                    } else {
                        //       EV << " 1- Deny Update SQMS ID" << endl;
                        //           EV << "Destination is : " << ttmsg->getDestination() << endl;

                        rdMessage *dsmsg;
                        dsmsg = new rdMessage("DenySQMSUpdate");

                        dsmsg->setDestination(ttmsg->getIntContent());
                        dsmsg->setSource(vnode_id);
                        dsmsg->setMtype(DenySQMSUpdate);
                        dsmsg->setIntContent(vnode_id);
                        dsmsg->setIntContentSD((int) agroup_members.size());

                        EV << endl<< "JX: MR=AN Sent a DenySQMSUpdate from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << ttmsg->getIntContent() << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                        forwardMessage(dsmsg);
                        numSent++;
                        delete ttmsg;
                        //         EV << " 2- Deny Update SQMS ID" << endl;

                    }

                } else if (module_role == SN) {

                    //          EV << "  SN Update SQMS ID" << endl;


                    rdMessage *dsmsg;
                    dsmsg = new rdMessage("DenySQMSUpdate");

                    dsmsg->setDestination(ttmsg->getIntContent());
                    dsmsg->setSource(vnode_id);
                    dsmsg->setMtype(DenySQMSUpdate);
                    dsmsg->setIntContent(vnode_id);
                    dsmsg->setIntContentSD((int) agroup_members.size());

                    EV << endl<< "JX: MR=SN Sent a DenySQMSUpdate from vnode="<<vnode_id<< " (ms="<< ttmsg->getIntContent()<<") to " << ttmsg->getIntContent() << " sender's sqms=" << sqms_id << " sender's qms_id=" << qms_id << endl;
                    forwardMessage(dsmsg);
                    numSent++;
                    delete ttmsg;
                } else {
                    delete ttmsg;
                }
            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;
            }
            break;
        }

        case DenySQMSUpdate: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                //        num_in_msg++;

                EV << endl<< "JX: vnode="<<vnode_id<< ", time=" << simTime().dbl()*10000<< " A DenySQMSUpdate from " << ttmsg->getSource() << " (ms="<< ttmsg->getIntContent()<< ") "<< " sqms=" << sqms_id << " qms_id=" << qms_id << endl;
                numReceived++;

                EV << endl<< "JX before: "<<vnode_id << ", time=" << simTime().dbl()*10000<<" sgroup_members=";
                for (unsigned int i=0; i<sgroup_members.size();i++)
                    EV << sgroup_members[i]<< ",";
                EV<< endl;


                if (module_role == SN) {
                    vector<int>::iterator It;
                    It = find(sgroup_members.begin(), sgroup_members.end(), ttmsg->getIntContent());
                    if (It != sgroup_members.end()) {
                        sgroup_members.erase(It);
                    }

                    voters--;
                    tnc = tnc - ttmsg->getIntContentSD();
                } else if (module_role==AN){

                    vector<int>::iterator It;
                    It = find(sgroup_members.begin(), sgroup_members.end(), ttmsg->getIntContent());
                    if (It != sgroup_members.end()) {
                        sgroup_members.erase(It);
                    }

                    voters--;
                    tnc = tnc - ttmsg->getIntContentSD();

                }


                EV << endl<< "JX after: "<<vnode_id << ", " << simTime().dbl()*1000<< " sgroup_members=";
                for (unsigned int i=0; i<sgroup_members.size();i++)
                    EV << sgroup_members[i]<< ",";
                EV<< endl;

                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                numPRouting_Messages++;

            }
            break;
        }

//---------------------------------------------------------------------------------------------------------
        case LS_Request: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }

                rdMessage *lsrpmsg;
                lsrpmsg = new rdMessage("LS_Reply");
                lsrpmsg->setDestination(ttmsg->getIntContent());
                lsrpmsg->setSource(vnode_id);
                lsrpmsg->setMtype(LS_Reply);
                lsrpmsg->setIntContent(vnode_id);
                strtype st;
                st.description = resource_key.lstamp;
                lsrpmsg->setMainContent(st);
                forwardMessage(lsrpmsg);
                delete ttmsg;
            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
            }
            break;
        }

//---------------------------------------------------------------------------------------------------------
        case LS_Reply: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
               string tempstr;
                tempstr = ttmsg->getMainContent().description;
               DHTvector.push_back(make_pair(ttmsg->getIntContent(), tempstr));
              if (agroup_members.size() == DHTvector.size()) {


                    sort(DHTvector.begin(), DHTvector.end(), sort_pred);

                    for (unsigned int i = 0; i < DHTvector.size(); i++)
                        EV << "[" << i << "]--" << DHTvector[i].first << "   "
                                  << DHTvector[i].second << endl; //rem2

                    maxRank = DHTvector[DHTvector.size() - 1].first;
                    maxKey.assign(DHTvector[DHTvector.size() - 1].second);
                    EV << "--maxKey=" << maxKey.c_str() << "  maxRank="
                              << maxRank << endl;


                    std::string temp;

                    std::pair<int, std::string> successor;
                    temp.assign(resource_key.lstamp);
                   for (unsigned int i = 0; i < multi_attribute_bitsize; i++) {
                        string exp = hex_str_2pown(i, 16);
                        string start = hex_str_add2str(temp, exp, 16);
                        successor = find_successor(DHTvector, start);
                       int sid = int(successor.first);
                      ft.put(i, start, sid);

                    }



                   show_finger_table(vnode_id, ft);
                   QREG.resetRegistry();

                   for (unsigned int i=0; i< type_ids_length; i++){ // first time configuration for the probability table

                   }

                   number_of_FTC_confirmations=1;
             //      int preceding_node_id;
                    vector<int> succlist;
                    int temp_sibling_vnode_id, temp_index, sibling_index;
                    for (unsigned int i = 0; i < agroup_members.size(); i++) {
                        temp_sibling_vnode_id=-1;
                        temp_index=0;


                        for (unsigned int k = 0; k < DHTvector.size(); k++)
                            if (DHTvector[k].first ==  agroup_members[i]){ // i
                                temp.assign(DHTvector[k].second);
                                temp_index=k;
                            }

                        sibling_index=temp_index+1;
                        if (sibling_index< (int) DHTvector.size()) {
                            if (DHTvector[sibling_index].second==temp) {
                                temp_sibling_vnode_id=DHTvector[sibling_index].first;
                            }

                        }

                        if (i==0){
                            sibling_vnode_id= temp_sibling_vnode_id;

                        }
                        else {

                            succlist.clear();
                            for (unsigned int j = 0; j < multi_attribute_bitsize; j++) {
                                string exp = hex_str_2pown(j, 16);
                                string start = hex_str_add2str(temp, exp, 16);
                                successor = find_successor(DHTvector, start);
                                int sid = int(successor.first);
                                succlist.push_back(sid);
                            }


                            //start to build FT
                            rdMessage *ftcmsg;
                            ftcmsg = new rdMessage("FTC");
                            ftcmsg->setDestination(agroup_members[i]);
                            ftcmsg->setSource(vnode_id);
                            ftcmsg->setMtype(FTC);
                            ftcmsg->setIntContent(vnode_id);
                            string list;
                            list = convert_vector_string(succlist);
                            strtype st;
                            st.description = list;
                            ftcmsg->setMainContent(st);
                            st.description=maxKey;
                            ftcmsg->setStringContent(st);
                            ftcmsg->setIntContentSD(maxRank);
                            ftcmsg->setIntValue(temp_sibling_vnode_id);
                            forwardMessage(ftcmsg);


                        }


                    }




                }


                delete ttmsg;
            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
            }
            break;
        }

//---------------------------------------------------------------------------------------------------------
        case QMS_Neighbour:{
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }
                rdMessage *lsrpmsg;
                lsrpmsg = new rdMessage("Confirm_QMS_Neighbour");
                lsrpmsg->setDestination(ttmsg->getIntContent());
                lsrpmsg->setSource(vnode_id);
                lsrpmsg->setMtype(Confirm_QMS_Neighbour);
                lsrpmsg->setIntContent(qms_id);

                forwardMessage(lsrpmsg);
                delete ttmsg;
            }
            else{
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
            }


            break;

        }

//---------------------------------------------------------------------------------------------------------
        case Confirm_QMS_Neighbour:{
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }

                if (an_neigbors.find((unsigned int) ttmsg->getIntContent())==an_neigbors.end()){
                    an_neigbors[(unsigned int) ttmsg->getIntContent()]=1;
                }

                delete ttmsg;
            }
            else{
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
            }


            break;

        }
//---------------------------------------------------------------------------------------------------------
        case Find_QMS_Neighbour: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }

//=========================================================
                vector<int> am=convert_string_vector(ttmsg->getMainContent().description);
                map<int, int>::iterator it;
                vector<int>::iterator ip;
                for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                    ip = find(am.begin(), am.end(), it->first);
                    if (ip == am.end()) {
                        rdMessage *lsrpmsg;
                        lsrpmsg = new rdMessage("QMS_Neighbour");
                        lsrpmsg->setDestination(it->first);
                        lsrpmsg->setSource(vnode_id);
                        lsrpmsg->setMtype(QMS_Neighbour);
                        lsrpmsg->setIntContent(qms_id);
                        forwardMessage(lsrpmsg);


                    }

                }

//=========================================================
                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
            }
            break;
        }
//---------------------------------------------------------------------------------------------------------
        case FTC: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }

                QREG.resetRegistry();
                string tempstr;
                sibling_vnode_id=ttmsg->getIntValue();

                maxRank=ttmsg->getIntContentSD();
                maxKey=ttmsg->getStringContent().description;

                tempstr = ttmsg->getMainContent().description;
                vector<int> sids;

                std::string temp;
                std::string sm;
                std::pair<int, std::string> successor;
                temp.assign(resource_key.lstamp);

                sids = convert_string_vector(tempstr);
                for (unsigned int i = 0; i < multi_attribute_bitsize; i++) {
                    string exp = hex_str_2pown(i, 16);
                    string start = hex_str_add2str(temp, exp, 16);
                    ft.put(i, start, sids[i]);
                }
                show_finger_table(vnode_id, ft);

                rdMessage *cftcmsg;
                cftcmsg = new rdMessage("Confirm_FTC");
                cftcmsg->setDestination(qms_id);
                cftcmsg->setSource(vnode_id);
                cftcmsg->setMtype(Confirm_FTC);
                forwardMessage(cftcmsg);


                //   ft.put(ttmsg->getIntContent(),tempstr,ttmsg->getIntContentSD());

                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
            }
            break;
        }
//
//---------------------------------------------------------------------------------------------------------
        case Confirm_FTC: {
                    if (ttmsg->getDestination() == vnode_id) {
                        if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                        EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                        }

                        number_of_FTC_confirmations++;
                        EV<< "in "<< vnode_id <<"--->"<< "incoming C-FTC from "<< ttmsg->getSource() << " number of C-FTC=" << number_of_FTC_confirmations << endl;
                        if (DHTvector.size()==(unsigned) number_of_FTC_confirmations){
                            rdMessage *idpmsg;
                            idpmsg = new rdMessage("Discovery_Activation");
                            idpmsg->setDestination(vnode_id);
                            idpmsg->setSource(vnode_id);
                            idpmsg->setMtype(Discovery_Activation);
                            scheduleAt(simTime(), idpmsg);

                            for (unsigned int i = 1; i < agroup_members.size(); i++) {

                                rdMessage *idpmsg;
                                idpmsg = new rdMessage("Discovery_Activation");
                                idpmsg->setDestination(agroup_members[i]);
                                idpmsg->setSource(vnode_id);
                                idpmsg->setMtype(Discovery_Activation);
                                forwardMessage(idpmsg);
                            }



                        }



                        delete ttmsg;

                    } else {
                        forwardMessage(ttmsg);
                        if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                    }
                    break;
                }

//---------------------------------------------------------------------------------------------------------
        case SG_Members: {
            if (ttmsg->getDestination() == vnode_id) {
                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);
                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                }

                sgroup_members=convert_string_vector(ttmsg->getMainContent().description);


                EV << endl <<"JXY: SG-Members for vnode_id=" << vnode_id << " sgroup_members=";

                for (unsigned int i=0; i < sgroup_members.size();i++){
                    EV<<sgroup_members[i]<<",";
                }

                EV << endl <<"JXY: SG-Members Start vnode_id=" << vnode_id << " an_neighbours=";

                for(std::map<unsigned int,double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it){
                    EV<< it->first<< ",";

                }


                std::map<unsigned int, double> temp;

                EV << endl <<"JXY: SG-Members Before vnode_id=" << vnode_id << " an_neighbours=";

                for( unsigned int i=0; i<  sgroup_members.size(); i++){
                    std::map<unsigned int,double>::iterator it=an_neigbors.find(sgroup_members[i]);
                    if (it!=an_neigbors.end()){
                        EV<< it->first<< ",";
                        temp[it->first]=-2;
                        it->second=-2;

                    }

                }

                EV << endl <<"JXY: SG-Members Mid vnode_id=" << vnode_id << " an_neighbours=";



                for(std::map<unsigned int,double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it){
                    EV<< it->first<< ",";

                    if (it->second!=-2){ //scenario-HARD3
                        EV<< "("<< it->first <<" is removed!),";
                        an_neigbors.erase(it); ///scenario-HARD3

                    }
                }

                EV << endl <<"JXY: SG-Members After vnode_id=" << vnode_id << " an_neighbours=";

                for(std::map<unsigned int,double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it){
                    EV<< it->first<< ",";

                }

                an_neigbors.clear();
                an_neigbors.insert(temp.begin(), temp.end());
                temp.clear();


                EV << endl <<"JXY: SG-Members After2 vnode_id=" << vnode_id << " an_neighbours=";

                for(std::map<unsigned int,double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it){
                    EV<< it->first<< ",";

                }

                //an_neighbors_cleanup();





                delete ttmsg;

            } else {
                forwardMessage(ttmsg);
                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
            }
            break;
        }


//---------------------------------------------------------------------------------------------------------
                case Discovery_Activation: {
                            if (ttmsg->getDestination() == vnode_id) {
                                if (ttmsg->getSource()!=vnode_id) {num_rec_overlay_msg++;overal_transcated_data_overlay+=2*sizeof(strtype)+7*sizeof(int)+sizeof(unsigned int)+sizeof(bool);

                                EV<< "overal_transcated_data_overlay="<< overal_transcated_data_overlay << endl;

                                }

                            /*    if (module_role==SN) {

                                    anycast_adress_list.insert(pair<int,std::string>(vnode_id, resource_key.sstamp));

                                }*/


                                if (ttmsg->getTotalMessageCount()>2000) ttmsg->resetMessageCounters();
                             //   unsigned int ccr = 1800, l1s = 128, l2s = 128, l1l = 1;
                             //   unsigned int pc=4, intp=3, isa=8, nc=7; // 0004000300080007,0008000A00070029
                             //   unsigned int ms=8,  nb=10, dc=7,  tnc=41;



                                if (vnode_id %number_of_requesters_factor==0) {



                                    mainQuery original_main_query;
                                    unsigned int thread_group_index=0;  ///0003000F00030004
                                    // Type A=1300,128,15,1024---Type B=1500,64,20,512
                                    // Type C=2800,16,1,2048------Type D=2000,32,5,256 -------Type E=2600,16,10,128
                                    HOGroup hogtemp;
                                    Specific_QL1P specific_l1q_par;

                                    Specific_QL3P specific_l3q_par;

                                    /*
                                    for (unsigned int i=1; i<=(unsigned int) par("RH_DRQ"); i++){
                                        specific_l1q_par=get_specific_query_parameters(i);
                                        thread_group_index=i-1;



                                        original_main_query.hogroups.push_back(hogtemp);


                                    }
                                */
                                  unsigned int tmdrq=(unsigned int) par("RH_DRQ");
                         //         unsigned int rhdrq= intuniform(1,tmdrq,0);

                                  unsigned int dnr=(unsigned int) par("Desired_Number_Of_Resources");
                            //      unsigned int dnrfinal=(unsigned int) normal(dnr,30.0,0);


                                  for (unsigned int i=1; i<=tmdrq; i++){
                                      specific_l1q_par=get_specific_query_parameters(i);
                                      specific_l3q_par=get_specific_anycast_query_parameters(i);

                                      thread_group_index=i-1;


                                      hogtemp=create_ho_group(vnode_id*100+thread_group_index,dnr ,   specific_l1q_par.first,specific_l1q_par.second,specific_l1q_par.third,specific_l1q_par.fourth,  /* 4,10,8,9 */ 0,0,0,0   , /*8,10,7,41*/ /*0,0,0,0 */ specific_l3q_par.first , specific_l3q_par.second ,0,0   ,1,100,20,80); // query generation

                                      EV << "main query: thread_gid="<< hogtemp.homog_id << " nRR="<< hogtemp.nRR<<" lstr=" << hogtemp.qls << " astr=" <<hogtemp.qas << " sstr=" <<hogtemp.qss<< endl;

                                      original_main_query.hogroups.push_back(hogtemp);


                                  }


                       ////////////////////////////////// add one more sub query
                           //         thread_group_index++;
                           //         hogtemp=create_ho_group(vnode_id*nhor_per_vnode+thread_group_index,1,   1800,128,10,512,   4,0,0,0,  /*32,1000,5,44*/  0,0,0,0  ,10,60,50,120);
                            //        EV << "main query: thread_gid="<< hogtemp.homog_id << " nRR="<< hogtemp.nRR<<" lstr=" << hogtemp.qls << " astr=" <<hogtemp.qas << " sstr=" <<hogtemp.qss<< endl;
                            //        original_main_query.hogroups.push_back(hogtemp);
                         //////////////////////////////////
                                    original_main_query.nhogs=original_main_query.hogroups.size();
                                    original_main_query.quering_period=querying_iteration;


                                    Dmsg *mqmsg;

                                    mqmsg = new Dmsg("Main_Query");
                                    mqmsg->setDestination(qms_id);
                                    mqmsg->setSource(vnode_id);
                                    mqmsg->setMtype(Main_Query);
                                    original_main_query.main_query_id=mqmsg->getId();
                                    mqmsg->setMq(original_main_query);
                                    sendMessage(mqmsg);
                                    EV << " iteration="<<  querying_iteration << " mqid="<< original_main_query.main_query_id<< " main query from requester=" <<vnode_id << " has been sent to "<< qms_id << " at the time of "<< simTime()<< endl;


                                }




                                delete ttmsg;


                                if (vnode_id %number_of_requesters_factor==0) {

                                    querying_iteration++;
                                    if (querying_iteration <= Max_Querying_Iterations){
                                        rdMessage *idpmsg;
                                        idpmsg = new rdMessage("Discovery_Activation");
                                        idpmsg->setDestination(vnode_id);
                                        idpmsg->setSource(vnode_id);

                                        idpmsg->setMtype(Discovery_Activation);


                                       // int random_interval = intuniform(2000,6000,0);
                                        double random_interval=exponential(4000,0);
                                        double raninter=random_interval/1000.0;
                                        scheduleAt(simTime() + raninter, idpmsg);

                                    }



                                }


                            } else {
                                forwardMessage(ttmsg);
                                if (ttmsg->getSource()!=vnode_id) num_rec_routing_msg++;
                            }
                            break;
                        }



//---------------------------------------------------------------------------------------------------------
        case EndingSD: {
            //  num_in_msg++;
            delete ttmsg;

            esd_repetition++;
            tnc = tnc + (int) agroup_members.size();
            EV << endl<< "JX ESD before: "<<vnode_id << " time="<< simTime().dbl()*10000 <<" sgroup_members=";
            for (unsigned int i=0; i<sgroup_members.size();i++)
                EV << sgroup_members[i]<< ",";
            EV<< endl;

            if ((module_role == AN) && (sqms_id == -1)) {

                sqms_id = vnode_id;
                module_role = SN;
                //     voters++;

                //       EV << "Create a too small SGroup... " << endl;

                /*               if (a_wakeup_repetition==2) {
                 sqms_id= vnode_id;
                 module_role=SN;
                 voters++;
                 EV << "222-AA- vnode_id=" << vnode_id << " a_wakeup_repetition=" << a_wakeup_repetition << endl;

                 }
                 else {

                 sprintf(msgname, "AN Wake up");
                 rdMessage *awmsg = new rdMessage(msgname);
                 awmsg->setMtype(AN_WakeUp);
                 scheduleAt(simTime()  , awmsg);
                 EV << "111-AA- vnode_id=" << vnode_id << " a_wakeup_repetition=" << a_wakeup_repetition << endl;

                 sprintf(msgname, "Ending Second Round");
                 rdMessage *esdmsg = new rdMessage(msgname);
                 esdmsg->setMtype(EndingSD);
                 scheduleAt(simTime()+10+(Max_Startup_Time)/ 1000.0  , esdmsg);
                 delete ttmsg;



                 break;

                 }*/

            }



            if (module_role == SN) {
                rdMessage *smsmsg;
                strtype st;
                for(unsigned int i=0;i<sgroup_members.size();i++){
                  //  if (sgroup_members[i]!=vnode_id){
                    smsmsg=new rdMessage("SG_Members");
                    smsmsg->setMtype(SG_Members);
                    smsmsg->setDestination(sgroup_members[i]);
                    st.description=convert_vector_string(sgroup_members);
                    smsmsg->setMainContent(st);
                    smsmsg->setSource(vnode_id);
                    forwardMessage(smsmsg);
                   // }


                }


            }

            DHTvector.push_back(make_pair(vnode_id, resource_key.lstamp));

            for (unsigned int i = 1; i < agroup_members.size(); i++) {
                EV << " mem " << i << "=" << agroup_members[i] << endl;
  //July 9 Debug
                rdMessage *lsrmsg;
                lsrmsg = new rdMessage("LS_Request");
                lsrmsg->setDestination(agroup_members[i]);
                lsrmsg->setSource(vnode_id);
                lsrmsg->setMtype(LS_Request);
                lsrmsg->setIntContent(vnode_id);
                forwardMessage(lsrmsg);
 // July 9 Debug
            }

            cDisplayString& dispStr = getDisplayString();
            /*  char xbuf[7];
             sprintf(xbuf,"#%06x",(qms_id+1)*10000);*/

            std::ostringstream stream;
            stream << "sq=" << sqms_id << ", q="<< qms_id << ", SNm#="<< (int) sgroup_members.size() << ",ANm#="<< (int) agroup_members.size()<< ", tnc=" <<tnc;


            //sprintf(xbuf, "#123456");

            if ((module_role==AN)||(module_role==SN)) total_number_of_qms_in_the_system++;
            if (module_role == SN) {
                dispStr.setTagArg("i", 1, "black");
                dispStr.setTagArg("t", 0, stream.str().c_str());
                //           EV<< "this is it:"<< dispStr.str()<< endl;
                resource_key.astamp = set_an_key(vnode_id,(unsigned int) agroup_members.size(), (unsigned int) par("RH_DRQ"));
                EV << resource_key.astamp << endl;
                resource_key.sstamp = set_sn_key(vnode_id,(unsigned int) sgroup_members.size(),(unsigned int) tnc, (unsigned int) par("RH_DRQ"));
                EV << resource_key.sstamp << endl;

                anycast_adress_list.insert(pair<int,std::string>(vnode_id, resource_key.sstamp));

     /*           rdMessage *jrmsg;

                strtype st;
                st.description=resource_key.sstamp;

                map<int, int>::iterator it;
                for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
                    jrmsg = new rdMessage("Send_sstamp_to_neigbours");
                    jrmsg->setMtype(SStamp2Ns);
                    jrmsg->setSource(vnode_id);
                    //               jrmsg->setOriginSource(vnode_id);
                    jrmsg->setMainContent(st);
                    jrmsg->setDestination(it->first);
                    EV << "destination for SStamp2Ns msg is " << it->first<< endl;
                    forwardMessage(jrmsg);
                    numSent++;
                }*/





            } else {
                //  dispStr.set("i=red/routing");
               stream.str("");
               stream << "sq=" << sqms_id << ", q="<< qms_id << ",ANm#="<< (int) agroup_members.size();
                dispStr.setTagArg("t", 0, stream.str().c_str());
                //             EV<< "this resource is not belonged to a group :"<< dispStr.str()<< endl;
                resource_key.astamp = set_an_key(vnode_id,  (unsigned int) agroup_members.size(), (unsigned int) par("RH_DRQ") );
                EV << resource_key.astamp << endl;
            }

            EV << endl<< "JX ESD after: "<<vnode_id<< " time="<< simTime().dbl()*10000 <<" sgroup_members=";
            for (unsigned int i=0; i<sgroup_members.size();i++)
                EV << sgroup_members[i]<< ",";
            EV<< endl;


            break;
        }

        default: {
            if (ttmsg->getDestination() == vnode_id) {
                //    num_in_msg++;
                numReceived++;
                delete ttmsg;
                bubble("ARRIVED in destination");

            } else {
                forwardMessage(ttmsg);
                numPRouting_Messages++;

            }

            break;
        }

        }
        //  delete omsg;

        /*
         if (ttmsg->getDestination()==getIndex())
         {
         // Message arrived
         int hopcount = ttmsg->getHopCount();
         // send a signal
         emit(arrivalSignal, hopcount);

         EV << "Message " << ttmsg << " arrived after " << hopcount << " hops.\n";
         bubble("ARRIVED, starting new one!");

         delete ttmsg;

         // Generate another one.
         EV << "Generating another message: ";
         rdMessage *newmsg = generateMessage();
         EV << newmsg << endl;
         forwardMessage(newmsg);
         }
         else
         {
         // We need to forward the message.
         forwardMessage(ttmsg);
         }

         */

        // if (ev.isGUI())  updateDisplay();
    }

    else if (dynamic_cast<Dmsg*>(omsg) != NULL) {

        //      Dmsg *ddmsg = check_and_cast<Dmsg *>(omsg);
        Dmsg *ddmsg = static_cast<Dmsg *>(omsg);
        // normal customers ...
        EV << "Main Query message is arrived" << endl;

        switch (ddmsg->getMtype()) {
//---------------------------------------------------------------------------------------------------------

        case Main_Query: {
            if (ddmsg->getDestination() == (unsigned int) vnode_id) {

                if ((int) ddmsg->getSource()!= (int) vnode_id) {num_rec_discovery_msg++;  overal_transcated_data_discovery+=sizeof(mainQuery)+3*sizeof(unsigned int);
                EV<< "Dmsg: overal_transcated_data_discovery="<< overal_transcated_data_discovery << endl;
                EV<< "Dmsg-test: overal_transcated_data_discovery="<< sizeof(mainQuery)+3*sizeof(unsigned int) << endl;

                }

               an_neighbors_cleanup();

               EV << "a main query (mqid="<< ddmsg->getMq().main_query_id << ") from " << ddmsg->getSource() << " has arrived in "<< vnode_id<< endl;
               Main_Query_Des temp_mq;
               Sub_Query_Status temp_sq;


               temp_mq.main_query_id=ddmsg->getMq().main_query_id;
               temp_mq.source=ddmsg->getSource();
               temp_mq.TTL= simTime().dbl();
               EV<<temp_mq.main_query_id<< " start time by ms " << temp_mq.TTL<<endl;
               temp_mq.tnmsg=0;
               temp_mq.mq_status=0;
               temp_mq.quering_period=ddmsg->getMq().quering_period;


               for(unsigned int i=0; i< ddmsg->getMq().nhogs; i++ ){
                   temp_sq.thread_group_id=ddmsg->getMq().hogroups[i].homog_id;
                   temp_sq.sub_query_id=i;
                 //  if ((int) ddmsg->getSource()==vnode_id) temp_sq.nmsg=0; else temp_sq.nmsg=2;
                   temp_sq.nmsg=0;
                   temp_sq.ndr=0;
                   temp_sq.state=0;
                   temp_sq.nrr=ddmsg->getMq().hogroups[i].nRR;
                   temp_sq.sq_status=100*(temp_sq.ndr/temp_sq.nrr);// rate of sub query resolution
                   temp_mq.sqs.push_back(temp_sq);
               }

               QREG.Register(ddmsg->getMq().main_query_id, temp_mq);


               subQuery sub_query;
               int destination_id;


               // Query Analyzer --- Start  ( i.e. generating sub queries ... )
               EV << "Starting Query Analyzer ..."<<endl;
               for(unsigned int i=0; i< ddmsg->getMq().nhogs; i++ ){
                   sub_query.qls=ddmsg->getMq().hogroups[i].qls;
                   sub_query.qas=ddmsg->getMq().hogroups[i].qas;
                   sub_query.qss=ddmsg->getMq().hogroups[i].qss;
                   sub_query.ins=ddmsg->getMq().hogroups[i].inconst;
                   sub_query.TTL=temp_mq.TTL;
               //    if ((int) ddmsg->getSource()==vnode_id) sub_query.nMS=0; else sub_query.nMS=2;
                   sub_query.nMS=0;
                   sub_query.main_query_id=ddmsg->getMq().main_query_id;
                   sub_query.sub_query_id=i;
                   sub_query.thread_group_id=ddmsg->getMq().hogroups[i].homog_id;
                   sub_query.nRR=ddmsg->getMq().hogroups[i].nRR;
                   sub_query.nDR=0;
                   sub_query.original_qms_id=vnode_id;

                   EV << " Identifying the query type IDs... qls="<<sub_query.qls << " and qas=" << sub_query.qas<< endl;
                   sub_query.sq_type_ids=get_sub_query_type_ids(sub_query.qls, sub_query.qas);
                   EV << "qid="<< sub_query.main_query_id << ":" << sub_query.sub_query_id << " list of query type ids= ";
                   for (unsigned int i=0;i<sub_query.sq_type_ids.size();i++){
                       EV << sub_query.sq_type_ids[i] << " , ";
                   }


                   for(unsigned int i=0;i<sub_query.sq_type_ids.size();i++){EV<<" type_ids="<< sub_query.sq_type_ids[i];}
                   EV<< endl;
                   sub_query.quering_period=temp_mq.quering_period;

                   EV <<" starting SOR at main query" << endl;
                   show_sors_status("Main-Start", vnode_id, sub_query);
                   sub_query.prefered_vnode.psor= calculate_absolute_preference(sub_query);
                   EV <<" ending SOR at main query" << endl;
                   show_sors_status("Main-End", vnode_id, sub_query);

                   EV << "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << " Preferred vnode="<< sub_query.prefered_vnode.psor << endl;

                   if ((sub_query.qas=="n") && (sub_query.qss=="n")){

                       SQM *lmsg;
                       lmsg = new SQM("Lookup");
                       destination_id=DHTvector[0].first;
                       lmsg->setDestination(destination_id);
                       lmsg->setSource(vnode_id);
                       lmsg->setMtype(Lookup);

                       //@@@@@@@@@@
        //               if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
        //               sub_query.visited_qms_ids.push_back(vnode_id);
                       //@@@@@@@@@@

                       if (destination_id!=vnode_id) sub_query.nMS=1; //1
                       lmsg->setSq(sub_query);

                       QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-2,-1); // if parent_sender==-2: current qms= original_qms
                       // if destination_id==-1 : a local qms lookup has been done

                       sendMessage(lmsg);
                       EV << "a sub_query (lookup request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;

                   }
                   else if ((sub_query.qas!="n") && (sub_query.qss=="n")){
                       if (key_checking(sub_query.qas,resource_key.astamp)) {

                           SQM *lmsg;
                           lmsg = new SQM("Lookup");
                           destination_id=DHTvector[0].first;
                           lmsg->setDestination(destination_id);
                           lmsg->setSource(vnode_id);
                           lmsg->setMtype(Lookup);


                           //@@@@@@@@@@
            //               if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
             //              sub_query.visited_qms_ids.push_back(vnode_id);
                           //@@@@@@@@@@

                           if (destination_id!=vnode_id) sub_query.nMS=1; //1
                           lmsg->setSq(sub_query);


                           QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-2,-1); // if parent_sender==-2: current qms= original_qms
                           // if destination_id==-1 : a local qms lookup has been done

                           sendMessage(lmsg);
                           EV << "a sub_query (lookup request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;

                       }
                       else { // invoking probability tables in order to determine the next QMS

                               //@@@@@@@@@@
                               if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                               sub_query.visited_qms_ids.push_back(vnode_id);
                               //@@@@@@@@@@


                               int next_qms=next_qms_selection(sub_query);

                               if (next_qms==-2){




                                   SQM *lmsg;
                                   lmsg = new SQM("Upward");
                                   destination_id=sqms_id;
                                   lmsg->setDestination(destination_id);
                                   lmsg->setSource(vnode_id);
                                   lmsg->setMtype(Upward);
                                   sub_query.prefered_vnode.psor=-1; // optional

                                   //@@@@@@@@@@
                         //          if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                         //          sub_query.visited_qms_ids.push_back(vnode_id);
                                   //@@@@@@@@@@

                                   if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                       sub_query.visited_qms_ids.push_back(vnode_id);

                                   if (destination_id!=vnode_id) sub_query.nMS=1; //1
                                   lmsg->setSq(sub_query);


                                   EV<< " A-Before.." << endl;
                                   QROUT.print_qrout();

                                   QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-2,destination_id);

                                   EV<< " A-After.." << endl;

                                   QROUT.print_qrout();



                                   sendMessage(lmsg);
                                   EV << "a sub_query (forward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;


/*//anycasting to be changed
                                   SQM *lmsg;
                                   lmsg = new SQM("Upward");
                                   destination_id=sqms_id;
                                   lmsg->setDestination(destination_id);
                                   lmsg->setSource(vnode_id);
                                   lmsg->setMtype(Upward);

                                   sub_query.visited_qms_ids.clear(); // removing all the visited an nodes in the current layer when the query is directed to the upper layer

                                   if (destination_id!=vnode_id) sub_query.nMS=1; //1
                                   lmsg->setSq(sub_query);

                                   QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-2,destination_id);

                                   sendMessage(lmsg);
                                   EV << "a sub_query (upward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
*/


                               }
                               else if (next_qms==-3){

                                   EV << "*** System Error No.1! *** "<<endl;

                               }
                               else {

                                   SQM *lmsg;
                                   lmsg = new SQM("Downward");
                                   destination_id=next_qms;
                                   lmsg->setDestination(destination_id);
                                   lmsg->setSource(vnode_id);
                                   lmsg->setMtype(Downward);
                                   sub_query.UDWT=0;


                                   if (destination_id!=vnode_id) sub_query.nMS=1; //1
                                   lmsg->setSq(sub_query);

                                   QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-2,destination_id); // if parent_sender==-2: current qms= original_qms

                                   sendMessage(lmsg);
                                   EV << "a sub_query (downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;



                               }


//----------------------------------------------------------------

                       }

                   }
                   else { // forwarding the sub query to the upper layer - SQMS level



                       SQM *lmsg;
                       lmsg = new SQM("Forward");
                       destination_id=sqms_id;
                       lmsg->setDestination(destination_id);
                       lmsg->setSource(vnode_id);
                       lmsg->setMtype(Forward);

                       sub_query.prefered_vnode.psor=-1;

                       //@@@@@@@@@@
             //          if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
             //          sub_query.visited_qms_ids.push_back(vnode_id);
                       //@@@@@@@@@@

                       if (destination_id!=vnode_id) sub_query.nMS=1; //1
                       lmsg->setSq(sub_query);

                       EV<< " Before.." << endl;
                       QROUT.print_qrout();

                       QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-2,destination_id);

                       EV<< " After.." << endl;

                       QROUT.print_qrout();

                       sendMessage(lmsg);
                       EV << "a sub_query (forward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;

                   }


               }

               // Query Analyzer --- End



                delete ddmsg;
            } else {
                sendMessage(ddmsg);

                if ((int) ddmsg->getSource()!=(int) vnode_id) num_rec_dis_routing_msg++;
            }
            break;
        }




        }
    }
//---------------------------------------------------------------------------------------------------------

    else if (dynamic_cast<SQM*>(omsg) != NULL) {

        //      SQM *subq = check_and_cast<SQM *>(omsg);
        SQM *sqmsg = static_cast<SQM *>(omsg);
        // normal customers ...
        EV << "Sub-Query message is arrived" << endl;

        switch (sqmsg->getMtype()) {


//---------------------------------------------------------------------------------------------------------


                case Lookup: {
                    if (sqmsg->getDestination() == (unsigned int) vnode_id) {
                        if ((int) sqmsg->getSource()!=(int) vnode_id) {num_rec_discovery_msg++; overal_transcated_data_discovery+=sizeof(subQuery)+4*sizeof(unsigned int);
                        EV<< "SQM: overal_transcated_data_discovery="<< overal_transcated_data_discovery << endl;
                        EV<< "SQM-test: overal_transcated_data_discovery="<< sizeof(subQuery)+4*sizeof(unsigned int) << endl;

                        }


                        EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id <<" a lookup request from " << sqmsg->getSource() << " has been arrived in "<< vnode_id<< endl;

                        show_sors_status("Lookup", vnode_id, sqmsg->getSq()); // optional debug
//===================================================
                        subQuery temp_query_request=sqmsg->getSq();

                        temp_query_request.nRR=sqmsg->getSq().nRR-sqmsg->getSq().nDR;
                        temp_query_request.nDR=0;


                        int idx=ft.get_entry_index2(sqmsg->getSq().qls);
                        unsigned int number_of_matched_resources;

                        if (resource_key.lstamp==sqmsg->getSq().qls){
//------------------------------------------------------------------------
                            unsigned number_of_available_resources=0;
                            for (unsigned i=0; i<resources.size(); i++) {
                                if(resources[i].thread_group_id==-1) number_of_available_resources++;
                            }

                          //  if (reservation_status.first=="free") {
                            if (number_of_available_resources>0) {
                                //---------------------------------
                               number_of_matched_resources=0;
                                for (unsigned i=0; i<resources.size(); i++) {
                                    if ((resources[i].thread_group_id==-1) && (temp_query_request.nRR>number_of_matched_resources)) {
                                        number_of_matched_resources++;
                                        temp_query_request.DRs.push_back(resources[i].resource_id);
                                        resources[i].thread_group_id=temp_query_request.thread_group_id;
                                    }
                                }

                                //---------------------------------


                                temp_query_request.UPT=1; //1=QMSUpdate;
                                temp_query_request.nDR=number_of_matched_resources;

                          //      reservation_status.first="reserved";
                           //     reservation_status.second=-1;
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " part 1 number of matched resources=" << number_of_matched_resources<< " nRR="<< temp_query_request.nRR << " number of available resources="<< number_of_available_resources<< endl;
                            }
                            else {
                                temp_query_request.UPT=1; //1=QMSUpdate; Original QMS update=2;
                                temp_query_request.nDR=0;
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " part 2 " << endl;

                            }

                            if ((sibling_vnode_id!=-1)&&(temp_query_request.nDR<temp_query_request.nRR)){

                                sqmsg->setDestination(sibling_vnode_id);
                                sqmsg->setSource(vnode_id);

                                if (sibling_vnode_id!=vnode_id) temp_query_request.nMS=sqmsg->getSq().nMS+1;

                                temp_query_request.nRR=sqmsg->getSq().nRR;
                                temp_query_request.nDR=temp_query_request.nDR+sqmsg->getSq().nDR;

                                sqmsg->setSq(temp_query_request);

                                sendMessage(sqmsg);
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a sibling lookup request from " << vnode_id << " has been sent to "<< sibling_vnode_id<< endl;



                            }
                            else {

                                unsigned number_of_available_resources=0;
                                for (unsigned i=0; i<resources.size(); i++) {
                                    if(resources[i].thread_group_id==-1) number_of_available_resources++;
                                }
                                if (number_of_available_resources>0) {

                                    temp_query_request.prefered_vnode.psor=qms_id;
                                    temp_query_request.prefered_vnode.sor_size=number_of_available_resources;
                                    temp_query_request.prefered_vnode.sor_latency=simTime().dbl();
                                    EV<< " Note: number_of_available_resources="<< number_of_available_resources << " for "<<  temp_query_request.thread_group_id<< endl;

                                }
                                else {
                                    if (sqmsg->getSq().prefered_vnode.psor==qms_id ) temp_query_request.prefered_vnode.psor=-1;
                                    EV<< " Note: number_of_available_resources="<< number_of_available_resources<< " for "<<  temp_query_request.thread_group_id<< endl;
                                }
                                SQM *dumsg;
                                dumsg = new SQM("DUpdate");
                                dumsg->setDestination(qms_id);
                                dumsg->setSource(vnode_id);
                                dumsg->setMtype(DUpdate);

                                temp_query_request.nRR=sqmsg->getSq().nRR;
                                temp_query_request.nDR=temp_query_request.nDR+sqmsg->getSq().nDR;

                                if (qms_id!=vnode_id) temp_query_request.nMS=sqmsg->getSq().nMS+1;

                                if (std::find(temp_query_request.visited_qms_ids.begin(), temp_query_request.visited_qms_ids.end(), qms_id )==temp_query_request.visited_qms_ids.end()){
                                    EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " qms "<< qms_id << " is visited after a lookup" << endl;
                                    temp_query_request.visited_qms_ids.push_back(qms_id);
                                }

                                dumsg->setSq(temp_query_request);
                                show_sors_status("succ-Lookup", vnode_id, temp_query_request); // optional debug
                                sendMessage(dumsg);
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a d-update message from " << vnode_id << " has been sent to "<< qms_id<< endl;


                                delete sqmsg;

                            }


//------------------------------------------------------------
                        }
                        else if ((resource_key.lstamp!=sqmsg->getSq().qls) && (idx==-1)) {
                            temp_query_request.UPT=1; //QMSUpdate;
                            temp_query_request.nDR=0;
                            SQM *dumsg;
                            dumsg = new SQM("DUpdate");
                            dumsg->setDestination(qms_id);
                            dumsg->setSource(vnode_id);
                            dumsg->setMtype(DUpdate);

                            temp_query_request.nRR=sqmsg->getSq().nRR;
                            temp_query_request.nDR=temp_query_request.nDR+sqmsg->getSq().nDR;

                            if (qms_id!=vnode_id) temp_query_request.nMS=sqmsg->getSq().nMS+1;

                            if (std::find(temp_query_request.visited_qms_ids.begin(), temp_query_request.visited_qms_ids.end(), qms_id )==temp_query_request.visited_qms_ids.end()){
                                EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " qms "<< qms_id << " is visited after a lookup" << endl;
                                temp_query_request.visited_qms_ids.push_back(qms_id);
                            }

                            dumsg->setSq(temp_query_request);
                            sendMessage(dumsg);
                            EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a d-update message from " << vnode_id << " has been sent to "<< qms_id<< endl;
                            EV << " part 3 " << endl;
                            delete sqmsg;

                        }
                        else {

                            if (((unsigned int) vnode_id==maxRank) || ( maxKey<sqmsg->getSq().qls)) {

                                temp_query_request.UPT=1; //QMSUpdate;
                                temp_query_request.nDR=0;
                                SQM *dumsg;
                                dumsg = new SQM("DUpdate");
                                dumsg->setDestination(qms_id);
                                dumsg->setSource(vnode_id);
                                dumsg->setMtype(DUpdate);


                                temp_query_request.nRR=sqmsg->getSq().nRR;
                                temp_query_request.nDR=temp_query_request.nDR+sqmsg->getSq().nDR;

                                if (qms_id!=vnode_id) temp_query_request.nMS=sqmsg->getSq().nMS+1;

                                if (std::find(temp_query_request.visited_qms_ids.begin(), temp_query_request.visited_qms_ids.end(), qms_id )==temp_query_request.visited_qms_ids.end()){
                                    EV<< " qms "<< qms_id << " is visited after a lookup" << endl;
                                    temp_query_request.visited_qms_ids.push_back(qms_id);
                                }

                                dumsg->setSq(temp_query_request);
                                sendMessage(dumsg);
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a d-update message from " << vnode_id << " has been sent to "<< qms_id<< endl;
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " part 4 " << endl;
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " resource-id=" << vnode_id << " maxRank="<< maxRank<< " maxKey="<< maxKey << " sqmsg->getSq().qls=" << sqmsg->getSq().qls << endl;
                                delete sqmsg;

                            }
                            else {
                                int nextPoint=ft.get_successor_id(idx);
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " idx= " << idx << " nextpoint= " << nextPoint << endl;
                             //   int index=0;

                                if (nextPoint==vnode_id) {

                                    EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "part 666" << endl;




                                }

                                sqmsg->setDestination(nextPoint);
                                sqmsg->setSource(vnode_id);

                                temp_query_request=sqmsg->getSq();

                                if (nextPoint!=vnode_id) temp_query_request.nMS=sqmsg->getSq().nMS+1;

                                sqmsg->setSq(temp_query_request);

                                sendMessage(sqmsg);
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a lookup request from " << vnode_id << " has been sent to "<< nextPoint<< endl;
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << " part 5 " << endl;


                            };

                        };


//===================================================

                    } else {
                        sendMessage(sqmsg);
                        if ((int) sqmsg->getSource()!=(int) vnode_id) num_rec_dis_routing_msg++;
                    }
                    break;
                }

//---------------------------------------------------------------------------------------------------------




                case DUpdate: {
                    if (sqmsg->getDestination() == (unsigned int) vnode_id) {
                        if ((int) sqmsg->getSource()!=(int) vnode_id) {num_rec_discovery_msg++; overal_transcated_data_discovery+=sizeof(subQuery)+4*sizeof(unsigned int);
                        EV<< "SQM: overal_transcated_data_discovery="<< overal_transcated_data_discovery << endl;
                        EV<< "SQM-test: overal_transcated_data_discovery="<< sizeof(subQuery)+4*sizeof(unsigned int) << endl;

                        }


                        EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a d-update message from " << sqmsg->getSource() << " has been arrived in "<< vnode_id<< endl;

                        show_sors_status("Update", vnode_id, sqmsg->getSq()); //optional debug

                        if (sqmsg->getSq().UPT==1) { //QMS update



                            double current_time=simTime().dbl();
                            double living_time= (current_time - sqmsg->getSq().TTL)*1000.0;
                            EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "qid="<< sqmsg->getSq().main_query_id<<":"<< sqmsg->getSq().sub_query_id<< " => living time (ms) =" <<  living_time << endl;
                            EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "CT="<<current_time<< "  and  ST="<< sqmsg->getSq().TTL << endl;

                            if ((sqmsg->getSq().nDR < sqmsg->getSq().nRR) && (living_time < MAX_TTL )){

                                subQuery sub_query=sqmsg->getSq();


                                int next_qms=next_qms_selection(sub_query); // if next_qms=-2 : current sqms has fully explored, the sub query must be directed to the upper layer i.e. sqms layer
                                // return=-3: call back to the parent-sender
                                EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "DUpdate=QMS Update --> next_qms="<< next_qms<< " in qmid="<< sub_query.main_query_id<< ":"<<sub_query.sub_query_id<< endl;
                                if (next_qms==-3){

                                    SQM *lmsg;
                                    lmsg = new SQM("Downward");
                                    int destination_id=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);
                                    if (destination_id==-2) {EV <<" j-debug code 15 -->"<< endl;}
                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Downward);

                                    sub_query.UDWT=1; // call back downward
                                    //@@@@@@@@@@
                                    if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                        sub_query.visited_qms_ids.push_back(vnode_id);
                                    //@@@@@@@@@@

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);


                                    if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    sendMessage(lmsg);
                                    EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a sub_query (call back downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                                }
                                else if (next_qms==-2){



                                    SQM *lmsg;
                                    lmsg = new SQM("Upward");
                                    int destination_id=sqms_id;
                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Upward);
                                  //  sub_query.prefered_vnode.psor=-1; // optional

                                    //@@@@@@@@@@
                          //          if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                          //          sub_query.visited_qms_ids.push_back(vnode_id);
                                    //@@@@@@@@@@



                                    if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                        sub_query.visited_qms_ids.push_back(vnode_id);

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);



                                    int main_source=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);

                                    if (destination_id!=vnode_id){


                                        QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                        QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, main_source ,destination_id);




                                    }

                                    if ((vnode_id!=sqms_id)&&(QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id)!=sqms_id)) upward_qrout_cleanup(sub_query);
                                    sendMessage(lmsg);
                                    EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query ( Upward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;










                                }
                                else if (next_qms==-1){

                                }
                                else {
                                    SQM *lmsg;
                                    lmsg = new SQM("Downward");
                                    int destination_id=next_qms;
                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Downward);
                                    sub_query.UDWT=0;

                                    //@@@@@@@@@@
                                    if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                        sub_query.visited_qms_ids.push_back(vnode_id);
                                    //@@@@@@@@@@

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);

                                    int main_source=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);
                                    if (main_source==-2) {EV <<" j-debug code 16 -->"<< endl;}

                                    if (destination_id!=vnode_id) {
                                        QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                        QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, main_source ,destination_id);

                                    }

                                    sendMessage(lmsg);
                                    EV << "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "a sub_query (downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                                }






///---------------------------------------------------






                            }
                            else {
//-----------------------------------------------------------
                                subQuery sub_query=sqmsg->getSq();

                                int destination_id=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);

                                if (QREG.isMQueryRegistered(sub_query.main_query_id))  {

                                    subQuery sub_query;
                                    sub_query=sqmsg->getSq();

                                    double current_time=simTime().dbl();
                                    double consumed_time= (current_time - sqmsg->getSq().TTL)*1000.0;
                                    double living_time= (current_time - QREG.registry[sub_query.main_query_id].TTL)*1000.0;

                                    sub_query.latency=consumed_time; // by ms

                          //          sub_query_pta_update(sub_query, sqmsg->getSource(), 2);

                                    sub_query_registry_update(sub_query);



                                    QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    bool self_mq_msg_flag;
                                    if ((QREG.Discovery_is_Completed(sub_query.main_query_id)) ||(living_time>= MAX_TTL) || (QREG.MQ_Resolution_State(sub_query.main_query_id) )) {
                                        int destination_id=QREG.MainQueryResults(sub_query.main_query_id).source;
                                        if (destination_id==vnode_id) self_mq_msg_flag=true; else self_mq_msg_flag=false;

                                        Light_MQ_Status final_main_query_status=QREG.LightResults(sub_query.main_query_id, living_time,self_mq_msg_flag);

                                        LSM *lmsg;
                                        lmsg = new LSM("Main_Reply");

                                        lmsg->setDestination(destination_id);
                                        lmsg->setSource(vnode_id);
                                        lmsg->setMtype(Main_Reply);
                                        lmsg->setMq_result(final_main_query_status);

                                        QROUT.remove_mq_entry(final_main_query_status.main_query_id);

                                        EV << "a sub_query (main reply with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                                        EV << " main query status=%" << final_main_query_status.mq_status << endl;
                                        QREG.removeEntry(final_main_query_status.main_query_id); //remove the remark 1
                                        EV << " main query with id="<< final_main_query_status.main_query_id << " has been removed from QREG..."<< endl;

                                        sendMessage(lmsg);

                                    } //------to do


                                }
                                else if ((destination_id==-5)&&(!QREG.isMQueryRegistered(sub_query.main_query_id))) {


                                    sub_query.UPT=6; // no update


                                    SQM *lmsg;
                                    lmsg = new SQM("DUpdate");
                                    sub_query.prefered_vnode.psor=-1;

                                    lmsg->setDestination(sub_query.original_qms_id);

                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(DUpdate);

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);

                                    if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    sendMessage(lmsg);
                                    EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (-5 original QMS update no DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< sub_query.original_qms_id<< endl;



                                }
                                else if ((destination_id==-2)&&(!QREG.isMQueryRegistered(sub_query.main_query_id))){

                                    EV <<" ERROR - logical mistake"<< endl;

                                }
                                else {

                                    if (living_time >= MAX_TTL) sub_query.UPT=6; // no update
                                    else sub_query.UPT=2; // original qms update

                                    SQM *lmsg;
                                    lmsg = new SQM("DUpdate");
                                    if (sqmsg->getSq().prefered_vnode.psor!=vnode_id) sub_query.prefered_vnode.psor=-1;

                                    lmsg->setDestination(destination_id);

                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(DUpdate);

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);

                                    if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    sendMessage(lmsg);
                                    EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (original QMS update DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;



                                }

                                if ((living_time < MAX_TTL)&&(sqmsg->getSq().prefered_vnode.psor==vnode_id))
                                for (std::map<unsigned int, double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it ){
                                    if ((int) it->first !=destination_id){

                                        int des_id=(int) it->first;
                                        sub_query.UPT=4; // Neighbor_PT_Update

                                        SQM *lmsg;
                                        lmsg = new SQM("DUpdate");


                                        lmsg->setDestination(des_id);

                                        lmsg->setSource(vnode_id);
                                        lmsg->setMtype(DUpdate);


                                        lmsg->setSq(sub_query);



                                        sendMessage(lmsg);
                                        EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (neighbor pt update DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< des_id<< endl;




                                    }


                                }
//-------------------------------------------------------------------------

                            }


                        }
                        else if ((sqmsg->getSq().UPT==2)||(sqmsg->getSq().UPT==6)) { //Original QMS update or no update
                            EV <<"j-debug code 53 type of update="<< sqmsg->getSq().UPT<< endl;
                            subQuery sub_query;
                            sub_query=sqmsg->getSq();

                            an_neighbors_cleanup();

                            if (sqmsg->getSq().UPT==2) sub_query_pta_update(sub_query, sqmsg->getSource(), 2);

//===================================================

                            sub_query.UPT=sqmsg->getSq().UPT; // original qms update or no update
                            int destination_id=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);

                            EV << "j-debug code 54"<< " destination_id=" << destination_id;

                            if (QREG.isMQueryRegistered(sub_query.main_query_id)){

//----------------

                                double current_time=simTime().dbl();
                                double consumed_time= (current_time - sqmsg->getSq().TTL)*1000.0;
                                double living_time= (current_time - QREG.registry[sub_query.main_query_id].TTL)*1000.0;

                                sub_query.latency=consumed_time; // by ms

                      //          sub_query_pta_update(sub_query, sqmsg->getSource(), 2);

                                sub_query_registry_update(sub_query);



                                QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                bool self_mq_msg_flag;
                                if ((QREG.Discovery_is_Completed(sub_query.main_query_id)) ||(living_time>= MAX_TTL) || (QREG.MQ_Resolution_State(sub_query.main_query_id) )) {
                                    int destination_id=QREG.MainQueryResults(sub_query.main_query_id).source;
                                    if (destination_id==vnode_id) self_mq_msg_flag=true; else self_mq_msg_flag=false;

                                    Light_MQ_Status final_main_query_status=QREG.LightResults(sub_query.main_query_id, living_time,self_mq_msg_flag);

                                    LSM *lmsg;
                                    lmsg = new LSM("Main_Reply");

                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Main_Reply);
                                    lmsg->setMq_result(final_main_query_status);

                                    QROUT.remove_mq_entry(final_main_query_status.main_query_id);

                                    EV << "a sub_query (main reply with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                                    EV << " main query status=%" << final_main_query_status.mq_status << endl;
                                    QREG.removeEntry(final_main_query_status.main_query_id); //remove the remark 2
                                    EV << " main query with id="<< final_main_query_status.main_query_id << " has been removed from QREG..."<< endl;

                                    sendMessage(lmsg);

                                } //------to do




//-----------------------



                            }
                            else if ((destination_id==-5)&&(!QREG.isMQueryRegistered(sub_query.main_query_id))) {


                                sub_query.UPT=6; // no update

                                EV << "Info->"<< sqmsg->getSq().main_query_id << ":"<< sqmsg->getSq().sub_query_id << "->"<< " destination_id==-5" << endl;

                                SQM *lmsg;
                                lmsg = new SQM("DUpdate");
                                sub_query.prefered_vnode.psor=-1;

                                lmsg->setDestination(sub_query.original_qms_id);

                                lmsg->setSource(vnode_id);
                                lmsg->setMtype(DUpdate);

                                if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                lmsg->setSq(sub_query);

                                if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                sendMessage(lmsg);
                                EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (-5 original QMS update no DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< sub_query.original_qms_id<< endl;



                            }
                            else if ((destination_id==-2)&&(!QREG.isMQueryRegistered(sub_query.main_query_id)) ){
                                EV<< "ERROR 2- logical mistake"<< endl;
                            }
                            else {

                                SQM *lmsg;
                                lmsg = new SQM("DUpdate");


                                lmsg->setDestination(destination_id);

                                lmsg->setSource(vnode_id);
                                lmsg->setMtype(DUpdate);

                                if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                lmsg->setSq(sub_query);

                                if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                sendMessage(lmsg);
                                EV << "a sub_query (original QMS update DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;



                            }


//===================================================




                        }
                        else if (sqmsg->getSq().UPT==4) { // Neighbor PT Update

                            EV << "Info->"<< sqmsg->getSq().main_query_id << ":"<< sqmsg->getSq().sub_query_id << "->"<< "update upt=4" << endl;
                            subQuery sub_query;
                            sub_query=sqmsg->getSq();

                            an_neighbors_cleanup();

                            sub_query_pta_update(sub_query, sqmsg->getSource(), 4);

                        }

                        EV << " a dupdate termination "<< endl;

                        delete sqmsg;
                        EV << " b dupdate termination "<< endl;
                    } else {
                        sendMessage(sqmsg);
                        if ((int) sqmsg->getSource()!=(int) vnode_id) num_rec_dis_routing_msg++;
                    }
                    break;
                }

//---------------------------------------------------------------------------------------------------------
                case Forward: {
                    if (sqmsg->getDestination() == (unsigned int) vnode_id) {
                        if ((int) sqmsg->getSource()!=(int) vnode_id) {num_rec_discovery_msg++; overal_transcated_data_discovery+=sizeof(subQuery)+4*sizeof(unsigned int);
                        EV<< "SQM: overal_transcated_data_discovery="<< overal_transcated_data_discovery << endl;
                        EV<< "SQM-test: overal_transcated_data_discovery="<< sizeof(subQuery)+4*sizeof(unsigned int) << endl;
                        }

                        EV << "a forward message from " << sqmsg->getSource() << " has been arrived in "<< vnode_id<< endl;

                        subQuery sub_query=sqmsg->getSq();

                        if (key_checking(sub_query.qss,resource_key.sstamp)) {

                            sub_query.prefered_vnode.psor= calculate_absolute_preference(sub_query);
                            sub_query.visited_qms_ids.clear();

                            SQM *lmsg;
                            lmsg = new SQM("Downward");
                            int destination_id=vnode_id;
                            lmsg->setDestination(destination_id);
                            lmsg->setSource(vnode_id);
                            lmsg->setMtype(Downward);
                            sub_query.UDWT=0;


                          //  if (destination_id!=vnode_id) sub_query.nMS=sub_query.nMS +1; //optional

                            lmsg->setSq(sub_query);

                            if (!QROUT.the_route_is_existed_for(sub_query.main_query_id, sub_query.sub_query_id)) {

                                EV<< " In SQMS- Before.." << endl;
                                QROUT.print_qrout();

                                QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-5,destination_id); // if parent_sender==-5: current qms is a sqms which is not the original_qms

                                EV<< " IN SQMS- After.." << endl;

                                QROUT.print_qrout();

                            }
                            else {
                                QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id,-5,destination_id); // if parent_sender==-5: current qms is a sqms which is not the original_qms


                            }
                            scheduleAt(simTime(), lmsg);
                            EV << "a sub_query (downward request (from a SQMS) with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;






                            delete sqmsg;

                        } else {


                            double current_time=simTime().dbl();
                            double living_time= (current_time - sqmsg->getSq().TTL)*1000.0;
                            EV << "In SQMS qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "qid="<< sqmsg->getSq().main_query_id<<":"<< sqmsg->getSq().sub_query_id<< " => living time (ms) =" <<  living_time << endl;
                            EV << "IN SQMS qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "CT="<<current_time<< "  and  ST="<< sqmsg->getSq().TTL << endl;



                            if (std::find(sub_query.visited_sqms_ids.begin(), sub_query.visited_sqms_ids.end(), vnode_id )==sub_query.visited_sqms_ids.end())
                            sub_query.visited_sqms_ids.push_back(vnode_id);

                            if (living_time < MAX_TTL ){

                                sub_query.prefered_vnode.psor=-1;

                                sub_query.nMS=sub_query.nMS+1;

                                sqmsg->setMtype(Forward);

                                sqmsg->setSq(sub_query);

                                sqmsg->setSource(vnode_id);




                                int sqms_decision=anycastMessage(sqmsg);
                                if (sqms_decision>0) {
                                    EV << "Anycasting : from "<< vnode_id<< " IN SQMS qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "CT="<<current_time<< "  and  ST="<< sqmsg->getSq().TTL << endl;
                                }
                                else {
                                    EV << "Anycasting (alternative: original QMS-Update) was not successful..in "<< vnode_id << " for " << sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id<< endl;


                                    sub_query.UPT=6; // no update


                                    SQM *lmsg;
                                    lmsg = new SQM("DUpdate");
                                    sub_query.prefered_vnode.psor=-1;

                                    int destination_id=sub_query.original_qms_id;
                                    lmsg->setDestination(destination_id);

                                    lmsg->setSource(vnode_id);

                                    lmsg->setMtype(DUpdate);


                                    lmsg->setSq(sub_query);

                                    if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    sendMessage(lmsg);
                                    EV<< "In SQMS qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (-5 original QMS update no DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< sub_query.original_qms_id<< endl;

                                    delete sqmsg;


                                }



                            }
                            else {


                                sub_query.UPT=6; // no update


                                SQM *lmsg;
                                lmsg = new SQM("DUpdate");
                                sub_query.prefered_vnode.psor=-1;
                                int destination_id=sub_query.original_qms_id;
                                lmsg->setDestination(destination_id);

                                lmsg->setSource(vnode_id);
                                lmsg->setMtype(DUpdate);

                                if (sub_query.original_qms_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                lmsg->setSq(sub_query);

                                if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                sendMessage(lmsg);
                                EV<< "In SQMS - sq time out - qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (-5 original QMS update no DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< sub_query.original_qms_id<< endl;

                                delete sqmsg;
                            }





                        }






                    }
                    else{
                        sendMessage(sqmsg);

                        if ((int) sqmsg->getSource()!=(int) vnode_id) num_rec_dis_routing_msg++;


                    }

                    break;

                }







//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
                                case Upward: {
                                    if (sqmsg->getDestination() == (unsigned int) vnode_id) {
                                        if ((int) sqmsg->getSource()!=(int) vnode_id) {num_rec_discovery_msg++; overal_transcated_data_discovery+=sizeof(subQuery)+4*sizeof(unsigned int);
                                        EV<< "SQM: overal_transcated_data_discovery="<< overal_transcated_data_discovery << endl;
                                        EV<< "SQM-test: overal_transcated_data_discovery="<< sizeof(subQuery)+4*sizeof(unsigned int) << endl;
                                        }

                                        EV << "an upward message from " << sqmsg->getSource() << " has been arrived in "<< vnode_id<< endl;

                                        subQuery sub_query=sqmsg->getSq();




                                        double current_time=simTime().dbl();
                                        double living_time= (current_time - sqmsg->getSq().TTL)*1000.0;
                                        EV << "In SQMS qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "qid="<< sqmsg->getSq().main_query_id<<":"<< sqmsg->getSq().sub_query_id<< " => living time (ms) =" <<  living_time << endl;
                                        EV << "IN SQMS qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "CT="<<current_time<< "  and  ST="<< sqmsg->getSq().TTL << endl;



                                        if (std::find(sub_query.visited_sqms_ids.begin(), sub_query.visited_sqms_ids.end(), vnode_id )==sub_query.visited_sqms_ids.end())
                                            sub_query.visited_sqms_ids.push_back(vnode_id);

                                        if (living_time < MAX_TTL ){

                                            sub_query.prefered_vnode.psor=-1;

                                            sub_query.nMS=sub_query.nMS+1;

                                            sqmsg->setMtype(Forward);

                                            sqmsg->setSq(sub_query);

                                            sqmsg->setSource(vnode_id);




                                            int sqms_decision=anycastMessage(sqmsg);
                                            if (sqms_decision>0) {
                                                EV << "Anycasting : from "<< vnode_id<< " IN SQMS - upward qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id << "CT="<<current_time<< "  and  ST="<< sqmsg->getSq().TTL << endl;
                                            }
                                            else {
                                                EV << "Anycasting (alternative: original QMS-Update) was not successful..in upward "<< vnode_id << " for " << sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id<< endl;


                                                sub_query.UPT=6; // no update


                                                SQM *lmsg;
                                                lmsg = new SQM("DUpdate");
                                                sub_query.prefered_vnode.psor=-1;

                                                int destination_id=sub_query.original_qms_id;
                                                lmsg->setDestination(destination_id);

                                                lmsg->setSource(vnode_id);

                                                lmsg->setMtype(DUpdate);

                                             //   if (sub_query.original_qms_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                                lmsg->setSq(sub_query);

                                                if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                                sendMessage(lmsg);
                                                EV<< "In SQMS qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (-5 original QMS update no DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< sub_query.original_qms_id<< endl;

                                                delete sqmsg;


                                            }



                                        }
                                        else {


                                            sub_query.UPT=6; // no update


                                            SQM *lmsg;
                                            lmsg = new SQM("DUpdate");
                                            sub_query.prefered_vnode.psor=-1;
                                            int destination_id=sub_query.original_qms_id;
                                            lmsg->setDestination(destination_id);

                                            lmsg->setSource(vnode_id);
                                            lmsg->setMtype(DUpdate);

                                            if (sub_query.original_qms_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                            lmsg->setSq(sub_query);

                                            if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                            sendMessage(lmsg);
                                            EV<< "In SQMS - sq time out - qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (-5 original QMS update no DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< sub_query.original_qms_id<< endl;

                                            delete sqmsg;

                                        }




                                    }
                                    else{
                                        sendMessage(sqmsg);

                                        if ((int) sqmsg->getSource()!=(int) vnode_id) num_rec_dis_routing_msg++;


                                    }

                                    break;

                                }







//---------------------------------------------------------------------------------------------------------


                case Downward: {
                    if (sqmsg->getDestination() == (unsigned int) vnode_id) {
                        if ((int) sqmsg->getSource()!=(int) vnode_id) {num_rec_discovery_msg++; overal_transcated_data_discovery+=sizeof(subQuery)+4*sizeof(unsigned int);
                        EV<< "SQM: overal_transcated_data_discovery="<< overal_transcated_data_discovery << endl;
                        EV<< "SQM-test: overal_transcated_data_discovery="<< sizeof(subQuery)+4*sizeof(unsigned int) << endl;

                        }


                        EV << "a downward message from " << sqmsg->getSource() << " has been arrived in "<< vnode_id<< endl;
                        show_sors_status("Downward", vnode_id, sqmsg->getSq()); //optional debug

//===================================================
                        subQuery sub_query;
                        sub_query=sqmsg->getSq(); //call back checking...
                        an_neighbors_cleanup();

                        if (sub_query.UDWT==1) sub_query_pta_update(sub_query, sqmsg->getSource(), 3);



                        if (!QROUT.the_route_is_existed_for(sub_query.main_query_id, sub_query.sub_query_id)){

                            if (sub_query.qas=="n") {

                                SQM *lmsg;
                                lmsg = new SQM("Lookup");
                                int destination_id=DHTvector[0].first;
                                lmsg->setDestination(destination_id);
                                lmsg->setSource(vnode_id);
                                lmsg->setMtype(Lookup);

                                //@@@@@@@@@@
                    //            if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                     //           sub_query.visited_qms_ids.push_back(vnode_id);
                                //@@@@@@@@@@

                                if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                lmsg->setSq(sub_query);

                                QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, sqmsg->getSource(),-1); // if parent_sender==-2: current qms= original_qms
                                // if destination_id==-1 : a local qms lookup has been done

                                sendMessage(lmsg);
                                EV << "a sub_query (lookup request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;



                            }
                            else {
                                if (key_checking(sub_query.qas,resource_key.astamp)) {

                                    SQM *lmsg;
                                    lmsg = new SQM("Lookup");
                                    int destination_id=DHTvector[0].first;
                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Lookup);

                                    //@@@@@@@@@@
                      //              if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                      //              sub_query.visited_qms_ids.push_back(vnode_id);
                                    //@@@@@@@@@@

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);

                                    QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, sqmsg->getSource(),-1); // if parent_sender==-2: current qms= original_qms
                                    // if destination_id==-1 : a local qms lookup has been done

                                    sendMessage(lmsg);
                                    EV << "a sub_query (lookup request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;

                                }
                                else{

                                    int next_qms=next_qms_selection(sub_query); // if next_qms=-2 : current sqms has fully explored, the sub query must be directed to the upper layer i.e. sqms layer
                                    // return=-3: call back to the parent-sender
                                    if (next_qms==-3){
                                        EV<< "j-debug code 4" << endl;
                                        SQM *lmsg;
                                        lmsg = new SQM("Downward");
                                        int destination_id=sqmsg->getSource();
                                        EV << "j-debug code 1 --> destination-id=" << destination_id;
                                        lmsg->setDestination(destination_id);
                                        lmsg->setSource(vnode_id);
                                        lmsg->setMtype(Downward);

                                        sub_query.UDWT=1; // call back downward
                                        //@@@@@@@@@@
                                        if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                            sub_query.visited_qms_ids.push_back(vnode_id);
                                        //@@@@@@@@@@

                                        if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                        lmsg->setSq(sub_query);


                                        if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id); //optional

                                        sendMessage(lmsg);
                                        EV << "a sub_query (call back downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                                    }
                                    else if (next_qms==-2){



                                        // Upwarding is the right decision here..

                                        SQM *lmsg;
                                        lmsg = new SQM("Upward");
                                        int destination_id=sqms_id;
                                        lmsg->setDestination(destination_id);
                                        lmsg->setSource(vnode_id);
                                        lmsg->setMtype(Upward);
                                        sub_query.prefered_vnode.psor=-1; // optional

                                        //@@@@@@@@@@
                              //          if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                              //          sub_query.visited_qms_ids.push_back(vnode_id);
                                        //@@@@@@@@@@



                                        if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                            sub_query.visited_qms_ids.push_back(vnode_id);

                                        if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                        lmsg->setSq(sub_query);




                                        QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, sqmsg->getSource() ,destination_id);

                                        if ((vnode_id!=sqms_id)&&(QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id)!=sqms_id)) upward_qrout_cleanup(sub_query);
                                        sendMessage(lmsg);
                                        EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query ( Upward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;










                          /*              int destination_id=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);

                                        if (destination_id==-2) {destination_id=vnode_id;  EV <<" j-debug code 13 -->"<< endl;}
                                        sub_query.UPT=6; // no update

                                        SQM *lmsg;
                                        lmsg = new SQM("DUpdate");
                                        sub_query.prefered_vnode.psor=-1; //optional

                                        lmsg->setDestination(destination_id);

                                        lmsg->setSource(vnode_id);
                                        lmsg->setMtype(DUpdate);

                                        if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                        lmsg->setSq(sub_query);

                                        QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                        sendMessage(lmsg);
                                        EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (original QMS update DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;

                        */

                                    }
                                    else if (next_qms==-1){


                                    }
                                    else {
                                        SQM *lmsg;
                                        lmsg = new SQM("Downward");
                                        int destination_id=next_qms;
                                        lmsg->setDestination(destination_id);
                                        lmsg->setSource(vnode_id);
                                        lmsg->setMtype(Downward);
                                        sub_query.UDWT=0;
                                        //@@@@@@@@@@
                                        if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                            sub_query.visited_qms_ids.push_back(vnode_id);
                                        //@@@@@@@@@@

                                        if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                        lmsg->setSq(sub_query);

                                        QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, sqmsg->getSource() ,destination_id);

                                        sendMessage(lmsg);
                                        EV << "a sub_query (downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                                    }

                                }
                                //-------------------------------

                            }



                        }
                        else {

                            an_neighbors_cleanup();

                            int next_qms=next_qms_selection(sub_query); // if next_qms=-2 : current sqms has fully explored, the sub query must be directed to the upper layer i.e. sqms layer
                            // return=-3: call back to the parent-sender
                            if (next_qms==-3){
                                EV<< "j-debug code 3" << endl;
                                int destination_id;
                                destination_id=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);
                                if ((destination_id!=-2)&& (destination_id!=-5)){
                                    EV << "j-debug code 2--> destination-id=" << destination_id;

                                    SQM *lmsg;
                                    lmsg = new SQM("Downward");

                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Downward);

                                    sub_query.UDWT=1; // call back downward
                                    //@@@@@@@@@@
                                    if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                        sub_query.visited_qms_ids.push_back(vnode_id);
                                    //@@@@@@@@@@

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);


                                    if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    sendMessage(lmsg);
                                    EV << "a sub_query (call back downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;

                                }
                                else if ((destination_id==-2)&&(sub_query.qss!="n")&&(sqmsg->getSq().UDWT==0)) {
                                    destination_id=sqmsg->getSource();

                                    EV << "j-debug code 22--> destination-id=" << destination_id;

                                    SQM *lmsg;
                                    lmsg = new SQM("Downward");

                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Downward);

                                    sub_query.UDWT=1; // call back downward
                                    //@@@@@@@@@@
                                    if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                        sub_query.visited_qms_ids.push_back(vnode_id);
                                    //@@@@@@@@@@

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);


                                    if (destination_id!=vnode_id) QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    sendMessage(lmsg);
                                    EV << "a sub_query (call back downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;



                                }
                                else {

                                    EV <<" j-debug code 9"<< endl;



                                    // Upwarding is the right decision here..

                                    SQM *lmsg;
                                    lmsg = new SQM("Upward");
                                    int destination_id=sqms_id;
                                    lmsg->setDestination(destination_id);
                                    lmsg->setSource(vnode_id);
                                    lmsg->setMtype(Upward);
                                    sub_query.prefered_vnode.psor=-1; // optional

                                    //@@@@@@@@@@
                          //          if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                          //          sub_query.visited_qms_ids.push_back(vnode_id);
                                    //@@@@@@@@@@



                                    if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                        sub_query.visited_qms_ids.push_back(vnode_id);

                                    if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                    lmsg->setSq(sub_query);



                                    int main_source=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);

                                    if (destination_id!=vnode_id){

                                        QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                        QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, main_source ,destination_id);
                                    }

                                    if ((vnode_id!=sqms_id)&&(QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id)!=sqms_id)) upward_qrout_cleanup(sub_query);
                                    sendMessage(lmsg);
                                    EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query ( Upward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;


                                    EV <<" j-debug code 52"<< endl;

                                }


                            }
                            else if (next_qms==-2){


                                // Upwarding is the right decision here..

                                SQM *lmsg;
                                lmsg = new SQM("Upward");
                                int destination_id=sqms_id;
                                lmsg->setDestination(destination_id);
                                lmsg->setSource(vnode_id);
                                lmsg->setMtype(Upward);
                                sub_query.prefered_vnode.psor=-1; // optional

                                //@@@@@@@@@@
                      //          if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                      //          sub_query.visited_qms_ids.push_back(vnode_id);
                                //@@@@@@@@@@



                                if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                    sub_query.visited_qms_ids.push_back(vnode_id);

                                if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                lmsg->setSq(sub_query);



                                int main_source=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);

                                if (destination_id!=vnode_id){

                                    QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                    QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, main_source ,destination_id);
                                }

                                if ((vnode_id!=sqms_id)&&(QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id)!=sqms_id)) upward_qrout_cleanup(sub_query);
                                sendMessage(lmsg);
                                EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query ( Upward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;




                               /*

                                int destination_id=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);
                                if (destination_id==-2) {destination_id=vnode_id; EV <<" j-debug code 17 -->"<< endl;}
                                sub_query.UPT=6; // no update

                                SQM *lmsg;
                                lmsg = new SQM("DUpdate");
                                sub_query.prefered_vnode.psor=-1;//optional

                                lmsg->setDestination(destination_id);

                                lmsg->setSource(vnode_id);
                                lmsg->setMtype(DUpdate);

                                if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                lmsg->setSq(sub_query);

                                QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                sendMessage(lmsg);
                                EV<< "qid="<< sqmsg->getSq().main_query_id << ":" << sqmsg->getSq().sub_query_id  << "a sub_query (original QMS update DUpdate request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                                   */


                            }
                            else if (next_qms==-1){

                                EV<< "j-debug code 51" << endl;

                            }
                            else {//  -*-*----call-back downward vs normal downward    --->sqmsg->getSq()
                                int downward_type=sqmsg->getSq().UDWT;
                                int current=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);
                                bool change_source_flag=false;
                                if ((downward_type==0)&&(current==-2)) change_source_flag=true;

                                SQM *lmsg;
                                lmsg = new SQM("Downward");
                                int destination_id=next_qms;
                                lmsg->setDestination(destination_id);
                                lmsg->setSource(vnode_id);
                                lmsg->setMtype(Downward);
                                sub_query.UDWT=0;

                                //@@@@@@@@@@
                                if (std::find(sub_query.visited_qms_ids.begin(), sub_query.visited_qms_ids.end(), vnode_id )==sub_query.visited_qms_ids.end())
                                    sub_query.visited_qms_ids.push_back(vnode_id);
                                //@@@@@@@@@@

                                if (destination_id!=vnode_id) sub_query.nMS=sqmsg->getSq().nMS+1;
                                lmsg->setSq(sub_query);

                                int main_source=QROUT.get_parent_sender_id(sub_query.main_query_id, sub_query.sub_query_id);

                                if (destination_id!=vnode_id){
                                    QROUT.remove_entry(sub_query.main_query_id, sub_query.sub_query_id);

                                   if (change_source_flag==true)
                                       QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, sqmsg->getSource() ,destination_id); //-----
                                   else
                                       QROUT.add_entry(sub_query.main_query_id, sub_query.sub_query_id, main_source ,destination_id); //-----
                                }

                                sendMessage(lmsg);
                                EV << "a sub_query (downward request with "<< "mq_id="<< sub_query.main_query_id <<", sq_id="<< sub_query.sub_query_id << ")"<<" from " << vnode_id << " has been sent to "<< destination_id<< endl;
                            }






                        }


//===================================================
                        delete sqmsg;
                    } else {
                        sendMessage(sqmsg);

                        if ((int) sqmsg->getSource()!=(int) vnode_id) num_rec_dis_routing_msg++;
                    }
                    break;
                }

//---------------------------------------------------------------------------------------------------------









        }





    }

    else if (dynamic_cast<Signal*>(omsg) != NULL) {
        //      SQM *subq = check_and_cast<SQM *>(omsg);
        Signal *sigmsg = static_cast<Signal *>(omsg);
        // normal customers ...
        EV << "a signal is arrived" << endl;

        switch (sigmsg->getMtype()) {

        case Upward_QROUT_Cleanup:{

            if (sigmsg->getDestination() == (unsigned int) vnode_id) {
                EV << endl<< sigmsg->getValue()<< ":"<< sigmsg->getValue2()<< "an upward-cleanup signal from " << sigmsg->getSource() << " has arrived in "<< vnode_id<< endl;
                long int mq=sigmsg->getValue();
                unsigned int sq=sigmsg->getValue2();

                if (QROUT.the_route_is_existed_for(mq,sq)){
                    QROUT.remove_entry(mq,sq);
                    EV<<endl<< " in vnode_id=" << vnode_id << " the rout for "<< mq << ":"<< sq << " has been removed in QROUT"<< endl;
                }


                delete sigmsg;

            }
            else {
                sendMessage(sigmsg);

            }



            break;

        }

        case Release_Resources : {
            if (sigmsg->getDestination() == (unsigned int) vnode_id) {
                EV << "a resource_release signal from " << sigmsg->getSource() << " has arrived in "<< vnode_id<< endl;
                int tg_id=sigmsg->getValue();
                for (unsigned int i=0; i< resources.size();i++){
                    if (resources[i].thread_group_id==tg_id) resources[i].thread_group_id=-1;
                }

                delete sigmsg;

            }
            else {
                sendMessage(sigmsg);

            }



            break;

        }


        }

    }
    else if (dynamic_cast<LSM*>(omsg) != NULL) {
           //
           LSM *lsmsg = static_cast<LSM *>(omsg);
           // normal customers ...
           EV << "a LSM (Light Discovery Reply) is arrived" << endl;

           switch (lsmsg->getMtype()) {

           case Ending_Excution : {
               if (lsmsg->getDestination() == (unsigned int) vnode_id) {

                   Light_MQ_Status mq_reply=lsmsg->getMq_result();

                   std::vector<int> signaled_des;
                   EV << "qid="<< mq_reply.main_query_id << " an Ending_Execution from " << lsmsg->getSource() << " has been arrived in "<< vnode_id<< endl;

                   for (unsigned int i=0; i<mq_reply.sqs.size();i++){

                       Light_SQ_Status lsq;
                       lsq=mq_reply.sqs[i];

                       for (unsigned int j=0; j<lsq.drs.size();j++ ){
                           EV << "jdid="<<lsq.drs[j]  << endl;
                          // int destination_id=(int) lsq.drs[j] /10;
                           int destination_id=(int) lsq.drs[j] /100;
                           EV << "jdid="<<destination_id << endl;
                           if (std::find(signaled_des.begin(),signaled_des.end(), destination_id)== signaled_des.end()) {

                               Signal *smsg;
                               smsg = new Signal("Release_Resources");

                               long int value=lsq.thread_group_id;
                               smsg->setValue(value);
                               smsg->setDestination(destination_id);
                               smsg->setSource(vnode_id);
                               smsg->setMtype(Release_Resources);
                               sendMessage(smsg);
                               EV << "qid="<< mq_reply.main_query_id << " a release_resources signal (tg_id or value="<< value<<  ") from " << vnode_id << " has been sent to "<< destination_id<< endl;
                               signaled_des.push_back(destination_id);

                           }


                       }

                       signaled_des.clear();


                   }

                   delete(lsmsg);

               }
               else {
                   sendMessage(lsmsg);

               }



               break;

           }


           case Main_Reply : {
               if (lsmsg->getDestination() == (unsigned int) vnode_id) {

                   if ((int) lsmsg->getSource()!=(int) vnode_id) {num_rec_discovery_msg++;overal_transcated_data_discovery+=3*sizeof(unsigned int)+sizeof(Light_MQ_Status);



                   EV<< "LSM: overal_transcated_data_discovery="<< overal_transcated_data_discovery << endl;
                   EV<< "LSM-test: overal_transcated_data_discovery="<< 3*sizeof(unsigned int)+sizeof(Light_MQ_Status) << endl;

                   }



                   cTopology topo("topo");
                   topo.extractByProperty("node");
                   EV << " a main reply message is arrived in "<< vnode_id << endl;
                   Light_MQ_Status mq_reply=lsmsg->getMq_result();

                   subQuery sub_query;

                  // unsigned int app_scale=(unsigned int) par("application_scale");

                  double qrecord_time=simTime().dbl();
                  qrecord_time=qrecord_time*1000.0; // by ms
                  double query_homogenity_rate=100.0*1.0/(unsigned int) par("RH_DRQ");
                  double rate_of_requesters=100.0/(number_of_requesters_factor*10.0);

                 /* July9 Debug
                  recordScalar("rate_of_requesters", rate_of_requesters);
                 // recordScalar("number_of_resources", 10*topo.getNumNodes());
                  recordScalar("number_of_resources", 55*topo.getNumNodes());
                  recordScalar("time_period", mq_reply.quering_period);
                   recordScalar("number_of_messages", mq_reply.tnmsg);
                  recordScalar("discovery_latency",mq_reply.main_query_total_time );
                  recordScalar("number_of_desired_resources",(unsigned int) par("Desired_Number_Of_Resources"));
                  recordScalar("query_homogenity_rate",query_homogenity_rate);
                  recordScalar("qrecord_time",qrecord_time);
                  recordScalar("discovery_resolution_rate",mq_reply.mq_status);
                   */ // July9 Debug

                  result_record temp_res;
                 // temp_res.number_of_resources=10*topo.getNumNodes();
                  temp_res.number_of_resources=55*topo.getNumNodes();
                  temp_res.time_period=  mq_reply.quering_period;
                  temp_res.number_of_messages=mq_reply.tnmsg;
                  temp_res.discovery_latency=mq_reply.main_query_total_time;
                  temp_res.discovery_resolution_rate=mq_reply.mq_status;




                  stringstream ss, hh;

                  ss << temp_res.number_of_resources;

                  hh << experiment_id;



                  string name1 = "Test-"+ss.str()+ "-Hard3-" + hh.str()+".data";
                  string name2 = "Test-"+ss.str()+ "-Hard3-" + hh.str()+".txt";



              /*    ofstream bin_result_file (name1.c_str(), ios::app|ios::binary);
                  bin_result_file.write((char*)&temp_res, sizeof(temp_res) );
                  bin_result_file.close();*///optional

                  ofstream txt_result_file (name2.c_str(),  ios::app|ios::ate);
                   if (txt_result_file.is_open())
                   {
                       txt_result_file << vnode_id << ","<< rate_of_requesters<< "," << (unsigned int) par("Desired_Number_Of_Resources")<< "," <<  query_homogenity_rate << "," << qrecord_time << "," << temp_res.number_of_resources << "," << temp_res.time_period << ","<< temp_res.number_of_messages<< ","<<  temp_res.discovery_latency << "," << temp_res.discovery_resolution_rate<< endl ;
                       txt_result_file.close();
                   }
                   else EV << "Unable to open file";


          /*         cOutVector  v1, v2, v3,v4;
                   cLongHistogram v_stats;
                   v1.setName("number_of_resources");
                   v1.record(10*topo.getNumNodes());

                   v2.setName("time_period");
                   v2.record(sqmsg->getExtra());

                   v3.setName("number_of_messages");
                   v3.record(sub_query.nMS);

                   v4.setName("discovery_latency");
                   v4.record(sub_query.latency);*/

                 //  v_stats.collect(sub_query.nMS);





               //    int release_time = intuniform( app_scale*2000-2000, app_scale*2000,0);
                //   double sraninter=release_time/1000.0;
                   double release_time= weibull(3.58033497,2.40799318,0);
                   double sraninter=release_time;



                   LSM *newmsg;
                   newmsg = new LSM("Ending_Execution");


                   newmsg->setSource(vnode_id);
                   newmsg->setMtype(Ending_Excution);
                   newmsg->setMq_result(mq_reply);



                   lsmsg->setDestination(vnode_id);
                   scheduleAt(simTime() + sraninter, newmsg);







                   delete lsmsg;



               }
               else {
                   sendMessage(lsmsg);

                   if ((int) lsmsg->getSource()!=(int) vnode_id) num_rec_dis_routing_msg++;

               }



               break;

           }


           }


    }



}


void rdNode::sub_query_pta_update(subQuery sub_query, int updater, unsigned int utype){

    an_neighbors_cleanup();

   // utype=2 : DUpdate // Original QMS DUpdate or OQMS_DUpdate
    //utype=3 : Downward //Call Back Downward or CB_Downward
    // utype=4 : DUpdate // Neighbor PT Update

    srand(time(NULL));

    double landa;
    landa= ((double) rand()+1) / ((double) 1+RAND_MAX);


    for(unsigned int i=0; i<sub_query.sq_type_ids.size();i++){

        it_pt_type ita;
        ita=PTA.p_table.find(sub_query.sq_type_ids[i]);

        if (ita==PTA.p_table.end()){
            for (std::map<unsigned int,double>::iterator itm=an_neigbors.begin(); itm!=an_neigbors.end(); ++itm) {
                an_record ar;

                ar.nid=(int) itm->first;
                ar.PF=1.0;
                ar.probability=0.0;
                if ((int) itm->first==updater) {

                    if (utype==2) {
                        //-----------------------------------
                        double current_time=simTime().dbl();
                        double pr_latency;

                        if(sub_query.prefered_vnode.psor>=0)
                            pr_latency=(current_time-sub_query.prefered_vnode.sor_latency)*5.0;
                        else
                            pr_latency=1.0;
                        //----------------------------------
                        if ((sub_query.nRR==sub_query.nDR)&& (sub_query.prefered_vnode.psor>=0))
                            ar.PF=ar.PF-landa*ar.PF+landa/pr_latency;   // increase the probability
                        else
                            ar.PF=landa*ar.PF; // decrease the probability



                    }
                    else if (utype==3) { // utype==3;

                        ar.PF=landa*ar.PF; // decrease the probability

                    }
                    else if (utype==4){
                        //-----------------------------------
                        double current_time=simTime().dbl();
                        double pr_latency;

                        if(sub_query.prefered_vnode.psor>=0)
                            pr_latency=(current_time-sub_query.prefered_vnode.sor_latency)*5.0;
                        else
                            pr_latency=1.0;
                        //----------------------------------


                        ar.PF=ar.PF-landa*ar.PF+landa/pr_latency;;   // increase the probability

                    }



                }

                PTA.p_table[sub_query.sq_type_ids[i]].push_back(ar);
            }

            if (utype==2){
                double current_time=simTime().dbl();
                double pr_latency=(current_time-sub_query.prefered_vnode.sor_latency)*1000.0;

                if ((sub_query.nRR==sub_query.nDR)&& (sub_query.prefered_vnode.psor>=0)) {

                    PTA.p_map[sub_query.sq_type_ids[i]].psor=sub_query.prefered_vnode.psor;
                    PTA.p_map[sub_query.sq_type_ids[i]].sor_latency=pr_latency;
                    PTA.p_map[sub_query.sq_type_ids[i]].sor_size=sub_query.prefered_vnode.sor_size;
                }
                else {

                    PTA.p_map[sub_query.sq_type_ids[i]].psor=-1;
                    PTA.p_map[sub_query.sq_type_ids[i]].sor_latency=0.0;
                    PTA.p_map[sub_query.sq_type_ids[i]].sor_size=0;
                }


            }


        }
        else {

            unsigned int sq_type_id_temp;
            sq_type_id_temp=ita->first;

            for (unsigned int j=0 ; j< PTA.p_table[sub_query.sq_type_ids[i]].size(); j++){
                an_record ar;
                if (PTA.p_table[sub_query.sq_type_ids[i]][j].nid==updater){
                    ar=PTA.p_table[sub_query.sq_type_ids[i]][j];

                    if (utype==2){
                        //-----------------------------------
                        double current_time=simTime().dbl();
                        double pr_latency;

                        if(sub_query.prefered_vnode.psor>=0)
                            pr_latency=(current_time-sub_query.prefered_vnode.sor_latency)*5.0;
                        else
                            pr_latency=1.0;
                        //----------------------------------

                        if ((sub_query.nRR==sub_query.nDR)&& (sub_query.prefered_vnode.psor>=0))
                            ar.PF=ar.PF-landa*ar.PF+landa/pr_latency; // increase the probability
                        else
                            ar.PF=landa*ar.PF; // decrease the probability

                    }
                    else if (utype==3) {
                        ar.PF=landa*ar.PF; // decrease the probability
                    }
                    else if (utype==4){
                        //-----------------------------------
                        double current_time=simTime().dbl();
                        double pr_latency;

                        if(sub_query.prefered_vnode.psor>=0)
                            pr_latency=(current_time-sub_query.prefered_vnode.sor_latency)*5.0;
                        else
                            pr_latency=1.0;
                        //----------------------------------
                        ar.PF=ar.PF-landa*ar.PF+landa/pr_latency;   // increase the probability

                    }



                    PTA.p_table[sub_query.sq_type_ids[i]].erase(PTA.p_table[sub_query.sq_type_ids[i]].begin()+j);
                    PTA.p_table[sub_query.sq_type_ids[i]].push_back(ar);
                    break;
                }

            }

            if (utype==2){


                if ((sub_query.nRR==sub_query.nDR)&& (sub_query.prefered_vnode.psor>=0)){

                    double current_time=simTime().dbl();
                    double pr_latency=(current_time-sub_query.prefered_vnode.sor_latency)*1000.0;




                    if (PTA.p_map[sq_type_id_temp].psor>=0){
                        if ((pr_latency<=PTA.p_map[sq_type_id_temp].sor_latency)&&(sub_query.prefered_vnode.sor_size>=PTA.p_map[sq_type_id_temp].sor_size)){
                            PTA.p_map[sq_type_id_temp].psor=sub_query.prefered_vnode.psor;
                            PTA.p_map[sq_type_id_temp].sor_latency=pr_latency;
                            PTA.p_map[sq_type_id_temp].sor_size=sub_query.prefered_vnode.sor_size;
                        }

                    }
                    else {

                    PTA.p_map[sq_type_id_temp].psor=sub_query.prefered_vnode.psor;
                    PTA.p_map[sq_type_id_temp].sor_latency=pr_latency;
                    PTA.p_map[sq_type_id_temp].sor_size=sub_query.prefered_vnode.sor_size;
                    }


                }

                else{

                    if (PTA.p_map[sq_type_id_temp].psor==sub_query.prefered_vnode.psor ) {
                        PTA.p_map[sq_type_id_temp].psor=-1;
                        PTA.p_map[sq_type_id_temp].sor_latency=0.0;
                        PTA.p_map[sq_type_id_temp].sor_size=0;

                    }

                }

            }


        }








    }





}

analyse_result rdNode::registry_analyse(){

    long int counter=0;
    long int sum_nmsg=0;
    double sum_latency=0.0;
    for (std::map<unsigned int,Main_Query_Des>::iterator it=QREG.registry.begin(); it!=QREG.registry.end(); ++it) {

        Main_Query_Des temp_mq;
        temp_mq=QREG.MainQueryResults(it->first);
        unsigned int mid=temp_mq.main_query_id;


        for (unsigned int i=0; i<QREG.registry[mid].sqs.size();i++){
            Sub_Query_Status temp_sq=QREG.registry[mid].sqs[i];
            if (temp_sq.sq_status==100.0) {
                counter++;
                sum_nmsg=sum_nmsg+temp_sq.nmsg;
                sum_latency=sum_latency+temp_sq.total_time;

            }

        }


    }

    analyse_result result;

    if (counter>0){
        result.average_number_of_discovery_messages=(double) sum_nmsg/counter;
        result.average_discovery_latency=(double) sum_latency/counter;
        result.total_number_of_fully_resolved_sub_queries=counter;

    }
    else {
        result.average_number_of_discovery_messages=0.0;
        result.average_discovery_latency=0.0;
        result.total_number_of_fully_resolved_sub_queries=0;


    }

    return result;



}

void rdNode::show_registry(){
    EV <<"========================================================================================================"<< endl;
    EV << "Results:"<< endl;
    unsigned int counter=0;
    for (std::map<unsigned int,Main_Query_Des>::iterator it=QREG.registry.begin(); it!=QREG.registry.end(); ++it) {
        counter++;
        Main_Query_Des temp_mq;
        temp_mq=QREG.MainQueryResults(it->first);
        unsigned int mid=temp_mq.main_query_id;
        EV << "................................................."<< endl;
        EV<< endl;
        int source_id=QREG.MainQueryResults(mid).source;

        EV << counter << ": from "<< source_id << endl;
        EV<< endl;
        for (unsigned int i=0; i<QREG.registry[mid].sqs.size();i++){
            Sub_Query_Status temp_sq=QREG.registry[mid].sqs[i];
            if (temp_sq.sq_status==100.0) {
            EV << "mqid="<< mid<<":"<< temp_sq.sub_query_id << ",  nrr="<< temp_sq.nrr << ",  ndr="<< temp_sq.ndr << ",  status=%" << temp_sq.sq_status << ",  number of messages="<< temp_sq.nmsg << ",  discovery latency=" << temp_sq.total_time << " ms"<< endl;
            EV<< endl;
            EV << " thread_group_id="<< temp_sq.thread_group_id << ",  discovered resources= " ;
            for (unsigned int j=0; j< temp_sq.drs.size();j++){
                EV << temp_sq.drs[j] << " , ";
            }
            EV << endl;
            EV << "................................................."<< endl;
            EV<< endl;
            }

        }


    }

    EV <<"========================================================================================================"<< endl;


}
void rdNode::sub_query_registry_update(subQuery sub_query){

//    if (sub_query.nDR!=0){
        if (QREG.isMQueryRegistered(sub_query.main_query_id)){
            //       QREG.registry[sqmsg->getSq().main_query_id].sqs[sqmsg->getSq().sub_query_id].drs.insert( QREG.registry[sqmsg->getSq().main_query_id].sqs[0].drs.end(),sqmsg->getSq().DRs.begin(),sqmsg->getSq().DRs.end());
            if (sub_query.nDR!=0) QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].drs.insert( QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].drs.end(),sub_query.DRs.begin(),sub_query.DRs.end());
            QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].ndr=sub_query.nDR;

            if (sub_query.nDR==0){sub_query.nMS=0; sub_query.latency=0;}
            QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].nmsg=sub_query.nMS;
            QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].total_time=sub_query.latency;

            QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].sq_status=100*( (double) sub_query.nDR/ (double) sub_query.nRR);
            QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].state=1;
            unsigned int sum_ndr, sum_nrr;
            sum_ndr=0;
            sum_nrr=0;

            for (unsigned int i=0; i< QREG.registry[sub_query.main_query_id].sqs.size();i++){
                sum_ndr=sum_ndr+QREG.registry[sub_query.main_query_id].sqs[i].ndr;
                sum_nrr=sum_nrr+QREG.registry[sub_query.main_query_id].sqs[i].nrr;
            }
            QREG.registry[sub_query.main_query_id].mq_status=(double) 100*sum_ndr/sum_nrr;


        }

        EV<< " qid=" << sub_query.main_query_id << ":"<< sub_query.sub_query_id<<" => from " << QREG.MainQueryResults(sub_query.main_query_id).source << " has been resolved in the following resource-ids by transacting "<< QREG.MainQueryResults(sub_query.main_query_id).sqs[sub_query.sub_query_id].nmsg<<  endl;
        //       for (unsigned int i=0; i< sqmsg->getSq().DRs.size(); i++)
        //          EV<< ", resource_id="<<sqmsg->getSq().DRs[i];
        //      EV<< endl;
        for(unsigned int i=0; i< QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].drs.size(); i++){
            EV<< "resource_id="<<QREG.registry[sub_query.main_query_id].sqs[sub_query.sub_query_id].drs[i];

            EV<< endl;
        }

 //   }
 /*   else {

        EV<< " sub query (" << sub_query.qls << ") with mq_id="<< sub_query.main_query_id << ", sq_id="<<sub_query.sub_query_id <<" from " << QREG.MainQueryResults(sub_query.main_query_id).source << " can't be resolved in the system." << endl;

    }*/


}
void rdNode::show_sors_status(std::string etype ,int vid, subQuery sub_query){

    if (sub_query.thread_group_id==902){

    string name1 = "debug-set.txt";

    ofstream txt_result_file (name1.c_str(),  ios::app|ios::ate);
     if (txt_result_file.is_open())
     {

         txt_result_file<< "===================================================================="<<etype << endl;
         txt_result_file<< "SOR Status in " << vid << "  querying iteration="<< sub_query.quering_period << " thread-group-id="<< sub_query.thread_group_id<< endl;
         txt_result_file<< "mqid="<< sub_query.main_query_id<<":" <<sub_query.sub_query_id << " nrr="<< sub_query.nRR << "ndr="<< sub_query.nDR << " nMsg="<< sub_query.nMS<< endl;
         txt_result_file<< "sub-query==> sor:" << sub_query.prefered_vnode.psor << ", sor-size:"<< sub_query.prefered_vnode.sor_size << ", sor-latency:"<< sub_query.prefered_vnode.sor_latency << endl;
         txt_result_file<< "sub-query_type_ids=[";
         for (unsigned int i=0;i<sub_query.sq_type_ids.size(); i++){
             if (i!=0) txt_result_file<< ",";
                 txt_result_file<< sub_query.sq_type_ids[i];
         }
         txt_result_file << "]"<< endl;

        EV<< " QMS SOR Preferences are:" << endl;
         for (map<unsigned int , sor_record>::iterator it=PTA.p_map.begin(); it!=PTA.p_map.end(); ++it){

             txt_result_file<<"res-typeid:"<< it->first <<"==> sor-id:" << it->second.psor << ", sor-size:"<< it->second.sor_size <<", sor-latency:" <<it->second.sor_latency << endl;
         }



         txt_result_file<< "===================================================================="<< endl;
         txt_result_file.close();
     }
     else EV << "Unable to open file";


    }


}

int rdNode::calculate_absolute_preference(subQuery sub_query){
    int max_val, max_count;

    vector<int> prefered_vnodes;

    for (unsigned int i=0;i<sub_query.sq_type_ids.size(); i++){
        if (PTA.p_map.find(sub_query.sq_type_ids[i])!=PTA.p_map.end()){
            prefered_vnodes.push_back(PTA.p_map[sub_query.sq_type_ids[i]].psor);

        }
    }

    if (prefered_vnodes.size()>0) {
        max_val=prefered_vnodes[0];
        max_count=1;
        for (unsigned int i=0;i<prefered_vnodes.size(); i++){
            if ( std::count (prefered_vnodes.begin(), prefered_vnodes.end(), prefered_vnodes[i]) > max_count){
                max_val=prefered_vnodes[i];
                max_count=std::count (prefered_vnodes.begin(), prefered_vnodes.end(), prefered_vnodes[i]);


            }


        }

        if (max_count>1) return max_val; else return -2; // -2: the preference is not absolute

    }
    else
        return -3; // there is no record for preferences


}

int rdNode::next_qms_selection(subQuery sub_query){

/*

// log file ---------------------------

std::string name4="SimLog.txt";

ofstream txt_log_file (name4.c_str(),  ios::app|ios::ate);
 if (txt_log_file.is_open())
 {
     txt_log_file << "Step 1: vnode_id="<< vnode_id<< ", qid="<< sub_query.main_query_id << ":" << sub_query.sub_query_id << endl;
     txt_log_file << " SG Members = ";
     for(unsigned int i=0; i < sgroup_members.size(); i++){
         txt_log_file << sgroup_members[i]<< ",";
     }
     txt_log_file << endl << " NBs = ";

     typedef std::map<unsigned int,double>::iterator it_type;
     for(it_type iterator = an_neigbors.begin(); iterator != an_neigbors.end(); iterator++) {
         txt_log_file <<  iterator->first << ",";
     }




    // txt_log_file.close();
 }
 else EV << "Unable to open file";

 // log file ---------------------------

*/

an_neighbors_cleanup();
an_neighbors_cleanup();


/*
// log file ---------------------------



 if (txt_log_file.is_open())
 {
     txt_log_file << "Step 2: vnode_id="<< vnode_id<< ", qid="<< sub_query.main_query_id << ":" << sub_query.sub_query_id << endl;
     txt_log_file << " SG Members = ";
     for(unsigned int i=0; i< sgroup_members.size(); i++){
         txt_log_file << sgroup_members[i]<< ",";
     }
     txt_log_file << endl << " NBs = ";

     typedef std::map<unsigned int,double>::iterator it_type;
     for(it_type iterator = an_neigbors.begin(); iterator != an_neigbors.end(); iterator++) {
         txt_log_file <<  iterator->first << ",";
     }




    // txt_log_file.close();
 }
 else EV << "Unable to open file";

 // log file ---------------------------
*/

map<unsigned int, double> temp_an_neigbors, temp_an_probabilities, t_a_n;

temp_an_neigbors.clear(); temp_an_probabilities.clear(); t_a_n.clear();


for(unsigned int i=0; i<sgroup_members.size();i++){
    if (an_neigbors.find(sgroup_members[i])!=an_neigbors.end()) {
        t_a_n[sgroup_members[i]]=0.0;

    }

}





temp_an_neigbors.insert(t_a_n.begin(),t_a_n.end());
temp_an_probabilities.insert(t_a_n.begin(),t_a_n.end());

/*
// log file ---------------------------


 if (txt_log_file.is_open())
 {
     txt_log_file << "Step 3: vnode_id="<< vnode_id<< ", qid="<< sub_query.main_query_id << ":" << sub_query.sub_query_id << endl;
     txt_log_file << " SG Members = ";
     for(unsigned int i=0; i<sgroup_members.size();i++){
         txt_log_file << sgroup_members[i]<< ",";
     }
     txt_log_file << endl << " TAN-NBs = ";

     typedef std::map<unsigned int,double>::iterator it_type;
     for(it_type iterator = t_a_n.begin(); iterator != t_a_n.end(); iterator++) {
         txt_log_file <<  iterator->first << ",";
     }

     txt_log_file << endl << " Temp-NBs = ";

     typedef std::map<unsigned int,double>::iterator it_type;
     for(it_type iterator = temp_an_neigbors.begin(); iterator != temp_an_neigbors.end(); iterator++) {
         txt_log_file <<  iterator->first << ",";
     }



     txt_log_file.close();
 }
 else EV << "Unable to open file";

 // log file ---------------------------

*/

unsigned int total_number_of_qms_nodes_in_current_sqms=  (unsigned int ) sgroup_members.size();///scenario-HARD3 //total_number_of_qms_in_the_system  scenario-HARD2 ;
unsigned int total_number_of_visited_qms_nodes=sub_query.visited_qms_ids.size();
EV << "j-debug code 11 -->"<< " total_number_of_visited_qms_nodes="<<total_number_of_visited_qms_nodes<< endl;
EV << " total_number_of_qms_nodes_in_current_sqms"<< total_number_of_qms_nodes_in_current_sqms<< endl;
if (total_number_of_visited_qms_nodes==total_number_of_qms_nodes_in_current_sqms) return -2; // the sub query must be directed to the upper layer
// i.e. all the qms nodes in the current sqms have been explored

EV << "visited nodes are: " ;
EV << "-----"<< sub_query.main_query_id<<"-" << sub_query.sub_query_id<< " qms_id="<< qms_id << ">>" << "number of visited nodes="<< total_number_of_visited_qms_nodes << " sqms.size="<< total_number_of_qms_nodes_in_current_sqms << endl;
for (unsigned int i=0; i< sub_query.visited_qms_ids.size() ; i++)
 EV << sub_query.visited_qms_ids[i] <<  endl;

// invoking probability tables in order to determine the next QMS
    double max_pf;
    int next_qms;
    std::vector<int> next_qms_cans;


    for (std::map<unsigned int,double>::iterator itm=temp_an_neigbors.begin(); itm!=temp_an_neigbors.end(); ++itm) {

        itm->second=0.0;
    }


    unsigned int counter=0;

    for (unsigned j=0; j< sub_query.sq_type_ids.size(); j++){
        std::map< unsigned int, std::vector<an_record> >::iterator it=PTA.p_table.find(sub_query.sq_type_ids[j]);
        if (it!=PTA.p_table.end()){
            counter++;
            for (unsigned int k=0; k< it->second.size(); k++) {
                an_record arc;
                arc=it->second[k];

                if (find(sgroup_members.begin(), sgroup_members.end(), arc.nid)!=sgroup_members.end()){ //scenario-HARD3
                    temp_an_neigbors[arc.nid]=temp_an_neigbors[arc.nid]+arc.PF;
                    temp_an_probabilities[arc.nid]=temp_an_probabilities[arc.nid]+arc.probability;
                }

            }

        }

    }

    EV << "qid="<< sub_query.main_query_id << ":"<< sub_query.sub_query_id <<"----> debug- before cleanup - neighbor table is: " << endl;
    for (std::map<unsigned int,double>::iterator pt=temp_an_neigbors.begin(); pt!=temp_an_neigbors.end(); ++pt){

           EV << "neighbor="<< pt->first<<"   pf="<< pt->second << " probability="<<temp_an_probabilities[pt->first] << endl;

    }


    EV << "qid="<< sub_query.main_query_id << ":"<< sub_query.sub_query_id << "  neighbors examination:"<<endl;
    /*
    for (std::map<unsigned int,double>::iterator itn=temp_an_neigbors.begin(); itn!=temp_an_neigbors.end(); ++itn){
        if (std::find(sub_query.visited_qms_ids.begin(),sub_query.visited_qms_ids.end(),(int)itn->first)!=sub_query.visited_qms_ids.end()){

            EV<< itn->first << " has already been visited => " << "this element will be removed"<< endl;
            temp_an_neigbors.erase(itn->first);
        }
        else {
            EV<< itn->first << " has not been visited yet" <<endl;
        }

    }*/

    for(unsigned int i=0; i<sub_query.visited_qms_ids.size();i++ ){
        std::map<unsigned int,double>::iterator itn=temp_an_neigbors.find(sub_query.visited_qms_ids[i]);
        if (itn!=temp_an_neigbors.end()) {
            EV<< itn->first << " has already been visited => " << "this element which is "<< sub_query.visited_qms_ids[i] <<" will be removed"<< endl;
            temp_an_neigbors.erase(itn->first);
            unsigned int tempn=itn->first;
            temp_an_probabilities.erase(tempn);


        }
    }



    EV << "qid="<< sub_query.main_query_id << ":"<< sub_query.sub_query_id <<"----> debug- after cleanup - neighbor table is: " << endl;
    for (std::map<unsigned int,double>::iterator pt=temp_an_neigbors.begin(); pt!=temp_an_neigbors.end(); ++pt){
        EV << "neighbor="<< pt->first<<"   pf="<< pt->second << " probability="<<temp_an_probabilities[pt->first] << endl;
    }


        EV<< temp_an_neigbors.size()<<" before return -3 " << total_number_of_qms_nodes_in_current_sqms <<endl;



    if (temp_an_neigbors.size()==0) return -3;

    EV<< "qid="<< sub_query.main_query_id << ":"<< sub_query.sub_query_id <<"---->number of query type ids which have been found in PTA=" << counter << endl;

    if (counter!=0) {


        max_pf=temp_an_neigbors.rbegin()->second/(double)counter;
        next_qms=temp_an_neigbors.rbegin()->first;

        EV << "qid="<< sub_query.main_query_id << ":"<< sub_query.sub_query_id <<"----> neighbor table is: " << endl;
        for (std::map<unsigned int,double>::reverse_iterator itm=temp_an_neigbors.rbegin(); itm!=temp_an_neigbors.rend(); ++itm) {
            itm->second=itm->second/(double)counter;
            if (itm->second > max_pf) {max_pf=itm->second; next_qms=itm->first;}
            EV << "neighbor="<< itm->first<<"   pf="<< itm->second << " probability="<<temp_an_probabilities[itm->first] << endl;

        }

        EV<< endl;

        EV<< "qid="<< sub_query.main_query_id << ":"<< sub_query.sub_query_id <<"----> in"<<" qms_id="<<qms_id << " max_pf="<< max_pf<<endl;

        for (std::map<unsigned int,double>::iterator itn=temp_an_neigbors.begin(); itn!=temp_an_neigbors.end(); ++itn) {
            if (itn->second==max_pf) {

                    next_qms_cans.push_back((int)itn->first);
            }

        }

        if (next_qms_cans.size()==0) return -3; else { // return=-3: call back to the parent-sender
            EV << "1- the sor is "<< sub_query.prefered_vnode.psor<< endl;


            if (sub_query.prefered_vnode.psor>=0){
                if (temp_an_neigbors.find(sub_query.prefered_vnode.psor)!=temp_an_neigbors.end()) {
                    EV<< " the preferred vnode is " <<  sub_query.prefered_vnode.psor << endl;
                    return sub_query.prefered_vnode.psor;
                }

            }

            int nextsor=calculate_absolute_preference(sub_query);
            if (nextsor>=0) {
                if (temp_an_neigbors.find(nextsor)!=temp_an_neigbors.end()){
                EV<< " there is a next-sor which is "<< nextsor << endl;
                return nextsor;
                }
                else
                    EV << " next-sor is not existed" << endl;
            }
            else {
                EV << " next-sor is not existed" << endl;
            }



            int randomIndex = rand() % next_qms_cans.size();
            next_qms=next_qms_cans[randomIndex];
            return next_qms;

        }


//-----------------------------------

    }
    else {

        for (std::map<unsigned int,double>::iterator itn=temp_an_neigbors.begin(); itn!=temp_an_neigbors.end(); ++itn)
            next_qms_cans.push_back((int)itn->first);

        if (next_qms_cans.size()==0) return -3; else { // return=-3: call back to the parent-sender
            EV << "2- the sor is "<< sub_query.prefered_vnode.psor<< endl;

            if (sub_query.prefered_vnode.psor>=0){
                if (temp_an_neigbors.find(sub_query.prefered_vnode.psor)!=temp_an_neigbors.end()) {
                    EV<< " the preferred vnode is " <<  sub_query.prefered_vnode.psor << endl;
                    return sub_query.prefered_vnode.psor;
                }

            }

            int nextsor=calculate_absolute_preference(sub_query);
            if (nextsor>=0) {
                if (temp_an_neigbors.find(nextsor)!=temp_an_neigbors.end()){
                EV<< " there is a next-sor which is "<< nextsor << endl;
                return nextsor;
                }
                else
                    EV << " next-sor is not existed" << endl;
            }
            else {
                EV << " next-sor is not existed" << endl;
            }


            int randomIndex = rand() % next_qms_cans.size();
            next_qms=next_qms_cans[randomIndex];
            return next_qms;

        }

    }


    EV << " j-debug code 12 -- Unknown error in qms-selection" << endl;
    return -1;
}


void rdNode::an_neighbors_cleanup() {

    for(std::map<unsigned int,double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it){

        //scenario-HARD2 leave this block empty.. no erase condition ..
        if (find(sgroup_members.begin(), sgroup_members.end(), it->first)==sgroup_members.end()){ //scenario-HARD3
            an_neigbors.erase(it); ///scenario-HARD3
        }  ///scenario-HARD3
    }
}

bool rdNode::key_checking( std::string query_string, std::string key_string){
    EV << "query stamp="<< query_string<< ", key stamp="<< key_string << endl;

    string zero;
    zero.assign("0000");

    for (unsigned int i=0;i<query_string.length(); i+=4){
        EV <<  i<< "=" << query_string.substr(i,4)<< " -- " << key_string.substr(i,4) << endl;
        if ((query_string.substr(i,4)!=zero)&&(query_string.substr(i,4)!=key_string.substr(i,4))) return false;


    }



    EV<< endl;
    return true;
}

void rdNode::finish() {


    //int a=par("RH_DRQ");


   // EV << "RHDRQ="<< a<< endl;

    cTopology topo("topo");

    topo.extractByProperty("node");



    if (module_role != LN) {

        group_size = agroup_members.size();

        if ((group_size < 25) && (group_size > 3)) {
            valid = 1;

        }

    }

  //  EV << "vnode_id=" << vnode_id << " and sibling_vnode_id="<< sibling_vnode_id << " List of local occupied resources= ";

    bool flag=false;

    for (unsigned int i=0; i< resources.size();i++){
        if (resources[i].thread_group_id!=-1) {flag=true; break;}
    }

    if (flag){
        EV << endl<< "vnode_id=" << vnode_id << " List of local occupied resources= ";
        for (unsigned int i=0; i< resources.size();i++){
            if (resources[i].thread_group_id!=-1) EV << resources[i].resource_id << " , ";
        }
    }


    EV<< endl;



    if (module_role == AN) {

      //  EV << "vnode_id=" << vnode_id << " and sibling_vnode_id="<< sibling_vnode_id << endl;
        EV << "-----------------------------------\n";
        EV << "QMS-Start\n";
        EV<< "total_number of_qms_in_the_system="<<total_number_of_qms_in_the_system << endl;
        EV << "Number of Members:" << agroup_members.size() << endl;
        EV << "vnode_id: " << vnode_id << endl;
        EV<< "DHT Entry="<< DHTvector[0].first << endl;
        EV << "astamp=" << resource_key.astamp << endl;

        EV << "Module Role:     " << module_role << endl;
        EV << "qms_id:    " << qms_id << endl;
        EV << "sqms_id:    " << sqms_id << endl;

        EV << "LN members are: ";
        for (unsigned i = 0; i < agroup_members.size(); i++)
            EV << agroup_members[i] << ", ";

        EV << "Family members are: ";
        for (unsigned i = 0; i < sgroup_members.size(); i++)
            EV << sgroup_members[i] << ", ";
        EV << endl;

        EV << endl<< "Neighbor QMSs members are: ";
        for(std::map<unsigned int,double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it)
            EV << it->first << ", ";
        EV << endl;

       // show_registry(); //July 9 Debug
       // analyse_result tempr=registry_analyse(); //July 9 Debug
       // EV << " Registry Result:" << endl;
     //   EV << "average_number_of_discovery_messages="<< tempr.average_number_of_discovery_messages << endl; //July 9 Debug
     //   EV << "average_discovery_latency=" << tempr.average_discovery_latency << endl; // July 9 Debug
    //    EV << "total_number_of_fully_resolved_sub_queries=" << tempr.total_number_of_fully_resolved_sub_queries << endl; //July 9 Debug


       EV<< endl;




        EV << "End\n";
    }



    else if (module_role == SN) {
        EV << "-----------------------------------\n";
        EV << "SQMS- Start\n";
        EV << "Number of LN Members:" << agroup_members.size() << endl;
        EV << "Number of AN Members:" << voters << " , "
                  << sgroup_members.size() << endl;
        EV << "vnode_id: " << vnode_id << endl;
        EV<< "DHT Entry="<< DHTvector[0].first << endl;
        EV << "astamp=" << resource_key.astamp << endl;
        EV << "sstamp=" << resource_key.sstamp << endl;
        EV << "TNC=" << tnc << endl;

        EV << "Module Role:     " << module_role << endl;
        EV << "qms_id:    " << qms_id << endl;
        EV << "sqms_id:    " << sqms_id << endl;

        EV << "LN members are: ";
        for (unsigned i = 0; i < agroup_members.size(); i++)
            EV << agroup_members[i] << ", ";
        EV << endl;

        EV << "AN members are: ";
        for (unsigned i = 0; i < sgroup_members.size(); i++)
            EV << sgroup_members[i] << ", ";
        EV << endl;


        EV << "Neighbor QMSs members are: ";
        for(std::map<unsigned int,double>::iterator it=an_neigbors.begin(); it!=an_neigbors.end(); ++it)
            EV << it->first << ", ";
        EV << endl;

    //    show_registry();
    //    analyse_result tempr=registry_analyse();
    //    EV << " Registry Result:" << endl;
     //   EV << "average_number_of_discovery_messages="<< tempr.average_number_of_discovery_messages << endl;
      //  EV << "average_discovery_latency=" << tempr.average_discovery_latency << endl;
   //     EV << "total_number_of_fully_resolved_sub_queries=" << tempr.total_number_of_fully_resolved_sub_queries << endl;


        EV << "End\n";
    }



    //================================Storing the traffic information per node



   stringstream ss, hh;

   ss << 55*topo.getNumNodes();
   unsigned int numres= (unsigned int) 55*topo.getNumNodes();
   hh << experiment_id;


   string name3 = "Test-"+ss.str()+ "-Hard3-Traffic" + hh.str()+".txt";



   ofstream txt_result_file (name3.c_str(),  ios::app|ios::ate);
    if (txt_result_file.is_open())
    {
        txt_result_file << numres << "," <<vnode_id<< "," << num_rec_overlay_msg<< "," << overal_transcated_data_overlay<< "," <<  num_rec_discovery_msg << "," << overal_transcated_data_discovery << "," << num_rec_routing_msg << "," << num_rec_dis_routing_msg << endl ;
        txt_result_file.close();
    }
    else EV << "Unable to open file";






    //=====================================================================================

 /*   //showing the anycast list
    EV<< "showing the anycast list-----" << endl;
    std::map<int, std::string>::iterator it;
    for (it = anycast_adress_list.begin(); it != anycast_adress_list.end(); ++it) {

        EV<< "vnode_id=" << it->first << "  anycast address=" << it->second << endl;

    }

*/


}
bool rdNode::check_local_lgroup_joining_possibility() {

    if (agroup_members.size() < Max_Number_of_Members_in_AGroup)
        return true;
    else
        return false;

}

bool rdNode::check_local_agroup_joining_possibility() {

    if (voters < Max_Number_of_Members_in_SGroup)
        return true;
    else
        return false;

}

bool rdNode::is_it_a_registerd_gate(int gateNumber) {
    map<int, int>::iterator it;

    for (it = neigbours_group.begin(); it != neigbours_group.end(); ++it) {
        if (it->second == gateNumber)
            return true;
    }

    return false;
}

void rdNode::updateDisplay() {
    char buf[80];//old value=40
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}


//---------------------------------------anycast forwarding


void rdNode::anycast_to_a_random_neigbour(SQM  *msg) {
    int n = gateSize("gate");
    int k = intuniform(0, n - 1);
    send(msg, "gate$o", k);


}

int rdNode::anycastMessage(SQM  *msg) {

    std::map<int, std::string>::iterator it;

    double distance=0;
    double min_distance=0;
    int count;

    subQuery sub_query= msg->getSq();
    std::string anycast_address=sub_query.qss;
    cTopology topo("topo");
    cTopology::Node *targetnode;
    cTopology::Node *node;

    bool conditions;

    int sender= msg->getSource();
    int final_destination;

    // extract topology
    topo.extractByProperty("node");

    if (anycast_adress_list.size()<=1) return -1; // the whole search space has been explored. There exisit no other SQMS to search







    count=0;

    for (it = anycast_adress_list.begin(); it != anycast_adress_list.end(); ++it) {

        if (anycast_address=="n")
            {conditions=((it->first!=sender)&& (std::find(sub_query.visited_sqms_ids.begin(), sub_query.visited_sqms_ids.end(), it->first )==sub_query.visited_sqms_ids.end()));}
        else
            {conditions=((key_checking(anycast_address,it->second))&&(it->first!=sender)&& (std::find(sub_query.visited_sqms_ids.begin(), sub_query.visited_sqms_ids.end(), it->first )==sub_query.visited_sqms_ids.end()));}

        if (conditions) {
            count++;

            int d = it->first;
            targetnode = topo.getNode(d);
            topo.calculateUnweightedSingleShortestPathsTo(targetnode);
            node = topo.getNodeFor(this);
            distance=node->getDistanceToTarget();
            if (count==1) {min_distance=distance; final_destination=d;}
            if (distance<min_distance) {min_distance=distance; final_destination=d;}

        }

    }

    if (count==0) {
        return -2; // all the super nodes in the system have already been visited.
    }
    else {

        targetnode = topo.getNode(final_destination);
        topo.calculateUnweightedSingleShortestPathsTo(targetnode);
        node = topo.getNodeFor(this);
        msg->setDestination((unsigned int) final_destination);

        if ((node == NULL) || (node->getNumPaths() == 0)) {
                //ev < "We (" << getFullPath() << ") are not included in the topology.\n";

            if (neigbours_group.count(final_destination) > 0) {
                send(msg, "gate$o", neigbours_group.find(final_destination)->second);
            } else {
                anycast_to_a_random_neigbour(msg);
            }
        } else {

            cTopology::LinkOut *path = node->getPath(0);
            int gateNumber = path->getLocalGate()->getIndex();
            send(msg, "gate$o", gateNumber);

        }

    }









return 1;
}


void rdNode:: upward_qrout_cleanup(subQuery sub_query){
    EV << endl<< " upward_cleanup in "<< vnode_id << " for"<< sub_query.main_query_id << ":"<< sub_query.sub_query_id << " QMSs for cleanup are ";
    for(unsigned int i=0; i<sub_query.visited_qms_ids.size();i++ ){
        if ((sub_query.visited_qms_ids[i]!=sub_query.original_qms_id)&&(sub_query.visited_qms_ids[i]!=sqms_id)) {
            EV<< sub_query.visited_qms_ids[i]<< ",";
        }
    }

    EV<< endl;

    for(unsigned int i=0; i<sub_query.visited_qms_ids.size();i++ ){
        if ((sub_query.visited_qms_ids[i]!=sub_query.original_qms_id)&&(sub_query.visited_qms_ids[i]!=sqms_id)&&(sub_query.visited_qms_ids[i]!=vnode_id)) {

            Signal *smsg;
            smsg = new Signal("Upward_QROUT_Cleanup");


            smsg->setValue(sub_query.main_query_id);
            smsg->setValue2(sub_query.sub_query_id);

            smsg->setDestination(sub_query.visited_qms_ids[i]);
            smsg->setSource(vnode_id);
            smsg->setMtype(Upward_QROUT_Cleanup);
            sendMessage(smsg);

        }
    }


}


//------------------------------------------------end anycast forwarding





