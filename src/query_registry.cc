//
// Author: jzarrin
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "query_registry.h"

Query_Registry::Query_Registry() {
    // TODO Auto-generated constructor stub

}

Query_Registry::~Query_Registry() {
    // TODO Auto-generated destructor stub
}


void Query_Registry::QRegister(rdMessage * rdm) {

    EV << "inside QRegister qid="<< rdm->getID() << endl;
    Main_Query_Des temp;
//    registery.insert(rdm->getID());
    registry.insert ( std::pair<unsigned int ,Main_Query_Des>(rdm->getID(),temp) );




}
bool Query_Registry::isMQueryRegistered(unsigned int mqid) {
    EV << "inside isMQueryRegistered mqid="<< mqid << endl;
    std::map<unsigned int,Main_Query_Des >::iterator it;
    it=registry.find(mqid);
    if (it==registry.end()) {
        EV << " False mqid=" << mqid << " is not registered." << endl;
        return false;
    }
    else {
        EV << " True mqid=" << mqid << " is registered." << endl;
        return true;
    }


}

Main_Query_Des Query_Registry::MainQueryResults(unsigned int mqid){

 /*   std::map<unsigned int,Main_Query_Des >::iterator it;
    it=registry.find(mqid);
    return it->second;
*/
  //  return registry.at(mqid);

    return registry.find(mqid)->second;

}

Light_MQ_Status Query_Registry::LightResults(unsigned int mqid, double latency,  bool self_msg_flag ){

   // Main_Query_Des mq=registry.at(mqid);
    Main_Query_Des mq=registry.find(mqid)->second;
    Light_MQ_Status result;

    result.mq_status=mq.mq_status;
    result.main_query_id=mq.main_query_id;
    result.main_query_total_time=latency;

    long int sum_nmsg=0;
    for (unsigned int i=0; i<mq.sqs.size();i++){
        Sub_Query_Status sq;
        Light_SQ_Status lsq;

        sq=mq.sqs[i];
        sum_nmsg=sum_nmsg+sq.nmsg;
        lsq.thread_group_id= sq.thread_group_id;
        lsq.drs=sq.drs;

        result.sqs.push_back(lsq);
    }

    result.quering_period=mq.quering_period;
    if (self_msg_flag==true) result.tnmsg=sum_nmsg; else result.tnmsg=sum_nmsg+2;

    return result;

}

bool Query_Registry::MQ_Resolution_State(unsigned int mid){
    Main_Query_Des mq=registry.find(mid)->second;
    bool result=true;

    for (unsigned int i=0; i<mq.sqs.size();i++){
        Sub_Query_Status temp_sq=mq.sqs[i];

        if (temp_sq.state!=1) return false;

    }

    return result;

}
bool Query_Registry::Register(unsigned int main_query_id,Main_Query_Des main_query_description){
    std::pair<std::map<unsigned int,Main_Query_Des>::iterator,bool> ret;
      ret = registry.insert ( std::pair<unsigned int,Main_Query_Des>(main_query_id, main_query_description) );
      if (ret.second==false) {
        std::cout << "element"<< main_query_id <<"already existed" << '\n';
      }
      return ret.second;
}
bool Query_Registry::Discovery_is_Completed(unsigned int mqid) {
    if (registry.find(mqid)->second.mq_status==100.0)
        return true;
    else
        return false;
}
void Query_Registry::removeEntry(unsigned int mqid) {

      std::map<unsigned int,Main_Query_Des>::iterator it;
      it=registry.find(mqid);
      registry.erase (it);


}
void Query_Registry::resetRegistry(){
    //registry.erase (registry.begin(), registry.end());
    registry.clear();
}

