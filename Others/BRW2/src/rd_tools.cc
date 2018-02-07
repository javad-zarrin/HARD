//
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



#include "rd_tools.h"

string convert_vector_string(vector<int> vin){
    string res;

    std::stringstream result;


    std::copy(vin.begin(),vin.end(),std::ostream_iterator<int>(result, " "));

    res= result.str();
    res = res.substr(0, res.length()-1);  // get rid of the trailing space

    return res;

}

vector<int> convert_string_vector(string sin) {
    vector<int> res;

    istringstream ist(sin);
    int n;
    while( ist >> n ) {
            res.push_back( n );
    }

    return res;

}

