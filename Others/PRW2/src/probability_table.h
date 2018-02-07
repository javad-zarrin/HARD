/*
 * Probability_Table .h
 *
 *  Created on: Mar 7, 2013
 *      Author: jzarrin
 */

#ifndef Probability_Table_H_
#define Probability_Table_H_

#include <map>
#include <string>
#include <vector>

using namespace std;

typedef struct rec{
    rec() : PF(1.0){}
    int nid; // neighbor id for the neighboring QMS or an_node
//    std::string an_key;
    double PF; //probe factor
    double probability; // the probability to find a resource of type T in the neighboring QMS with id of nid

} an_record;

typedef struct sor_rec{
    sor_rec() : psor(-1), sor_latency(0), sor_size(0) {}
    int psor; // prefered source of resource
    double sor_latency; // estimated latency to access the preffered sor
    int sor_size; // number of available resource in the preffered sor

} sor_record;


typedef map < unsigned int, std::vector<an_record> > pt_type; // sq_type_id and probability table per each sq_type_id
typedef map < unsigned int, std::vector<an_record> >::iterator it_pt_type;
typedef map<unsigned int , sor_record> preference_map; // sq_type_id, prefered_vnode
class Probability_Table {

public:
    pt_type p_table;
    preference_map p_map; // sq_type_id, prefered_vnode
    Probability_Table ();
    virtual ~Probability_Table ();

};

#endif /* Probability_Table _H_ */
