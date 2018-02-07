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

import rdNode;

import Channel10;

//
// Generated network with random topology (24 nodes, 40 edges, seed=100).
//
network Network24
{
    submodules:
        node0: rdNode;
        node1: rdNode;
        node2: rdNode;
        node3: rdNode;
        node4: rdNode;
        node5: rdNode;
        node6: rdNode;
        node7: rdNode;
        node8: rdNode;
        node9: rdNode;
        node10: rdNode;
        node11: rdNode;
        node12: rdNode;
        node13: rdNode;
        node14: rdNode;
        node15: rdNode;
        node16: rdNode;
        node17: rdNode;
        node18: rdNode;
        node19: rdNode;
        node20: rdNode;
        node21: rdNode;
        node22: rdNode;
        node23: rdNode;
    connections:
        node0.gate++ <--> Channel10 <--> node1.gate++;
        node0.gate++ <--> Channel10 <--> node21.gate++;
        node0.gate++ <--> Channel10 <--> node5.gate++;
        node0.gate++ <--> Channel10 <--> node6.gate++;
        node0.gate++ <--> Channel10 <--> node22.gate++;
        node0.gate++ <--> Channel10 <--> node11.gate++;
        node1.gate++ <--> Channel10 <--> node16.gate++;
        node1.gate++ <--> Channel10 <--> node19.gate++;
        node1.gate++ <--> Channel10 <--> node2.gate++;
        node1.gate++ <--> Channel10 <--> node3.gate++;
        node1.gate++ <--> Channel10 <--> node5.gate++;
        node2.gate++ <--> Channel10 <--> node4.gate++;
        node2.gate++ <--> Channel10 <--> node8.gate++;
        node2.gate++ <--> Channel10 <--> node13.gate++;
        node3.gate++ <--> Channel10 <--> node7.gate++;
        node3.gate++ <--> Channel10 <--> node10.gate++;
        node4.gate++ <--> Channel10 <--> node17.gate++;
        node4.gate++ <--> Channel10 <--> node11.gate++;
        node5.gate++ <--> Channel10 <--> node18.gate++;
        node5.gate++ <--> Channel10 <--> node12.gate++;
        node5.gate++ <--> Channel10 <--> node13.gate++;
        node5.gate++ <--> Channel10 <--> node14.gate++;
        node6.gate++ <--> Channel10 <--> node18.gate++;
        node6.gate++ <--> Channel10 <--> node13.gate++;
        node7.gate++ <--> Channel10 <--> node17.gate++;
        node7.gate++ <--> Channel10 <--> node9.gate++;
        node7.gate++ <--> Channel10 <--> node10.gate++;
        node8.gate++ <--> Channel10 <--> node17.gate++;
        node8.gate++ <--> Channel10 <--> node9.gate++;
        node10.gate++ <--> Channel10 <--> node16.gate++;
        node12.gate++ <--> Channel10 <--> node20.gate++;
        node12.gate++ <--> Channel10 <--> node15.gate++;
        node13.gate++ <--> Channel10 <--> node18.gate++;
        node17.gate++ <--> Channel10 <--> node22.gate++;
        node18.gate++ <--> Channel10 <--> node19.gate++;
        node18.gate++ <--> Channel10 <--> node23.gate++;
        node19.gate++ <--> Channel10 <--> node20.gate++;
        node19.gate++ <--> Channel10 <--> node22.gate++;
        node21.gate++ <--> Channel10 <--> node22.gate++;
        node22.gate++ <--> Channel10 <--> node23.gate++;
}
