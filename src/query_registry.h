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

#include "rd_message_m.h"

#ifndef QUERYREGISTERY_H_
#define QUERYREGISTERY_H_

#include "query.h"



class Query_Registry {




public:
    Query_Registry();
    virtual ~Query_Registry();
    std::map<unsigned int,Main_Query_Des> registry;
    bool Register(unsigned int,Main_Query_Des );
    void QRegister(rdMessage * rdm);
    bool isMQueryRegistered(unsigned int);
    bool Discovery_is_Completed(unsigned int);
    void removeEntry(unsigned int);
    void resetRegistry();
    Main_Query_Des MainQueryResults(unsigned int);
    Light_MQ_Status LightResults(unsigned int, double, bool );
    bool MQ_Resolution_State(unsigned int);
/*  std::vector<found_t> get_discovered_resourcesIDs(int){};
    void add_to_discovered_resources(int ,nodeID, int){};
*/


};

#endif /* QUERYREGISTERY_H_ */
