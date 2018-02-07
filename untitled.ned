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

channel Chanel extends ned.DatarateChannel
{
    parameters:
        int cost = default(0);
}

//
// Generated network with random topology (50 nodes, 80 edges, seed=100).
//
network disNetwork2
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
        node24: rdNode;
        node25: rdNode;
        node26: rdNode;
        node27: rdNode;
        node28: rdNode;
        node29: rdNode;
        node30: rdNode;
        node31: rdNode;
        node32: rdNode;
        node33: rdNode;
        node34: rdNode;
        node35: rdNode;
        node36: rdNode;
        node37: rdNode;
        node38: rdNode;
        node39: rdNode;
        node40: rdNode;
        node41: rdNode;
        node42: rdNode;
        node43: rdNode;
        node44: rdNode;
        node45: rdNode;
        node46: rdNode;
        node47: rdNode;
        node48: rdNode;
        node49: rdNode;
    connections:
        node0.gate++ <--> Chanel <--> node1.gate++;
        node0.gate++ <--> Chanel <--> node21.gate++;
        node0.gate++ <--> Chanel <--> node6.gate++;
        node0.gate++ <--> Chanel <--> node22.gate++;
        node0.gate++ <--> Chanel <--> node9.gate++;
        node0.gate++ <--> Chanel <--> node11.gate++;
        node1.gate++ <--> Chanel <--> node16.gate++;
        node1.gate++ <--> Chanel <--> node19.gate++;
        node1.gate++ <--> Chanel <--> node2.gate++;
        node1.gate++ <--> Chanel <--> node3.gate++;
        node1.gate++ <--> Chanel <--> node5.gate++;
        node2.gate++ <--> Chanel <--> node4.gate++;
        node2.gate++ <--> Chanel <--> node8.gate++;
        node2.gate++ <--> Chanel <--> node41.gate++;
        node3.gate++ <--> Chanel <--> node7.gate++;
        node3.gate++ <--> Chanel <--> node10.gate++;
        node4.gate++ <--> Chanel <--> node18.gate++;
        node4.gate++ <--> Chanel <--> node24.gate++;
        node4.gate++ <--> Chanel <--> node27.gate++;
        node4.gate++ <--> Chanel <--> node46.gate++;
        node5.gate++ <--> Chanel <--> node33.gate++;
        node5.gate++ <--> Chanel <--> node12.gate++;
        node5.gate++ <--> Chanel <--> node14.gate++;
        node6.gate++ <--> Chanel <--> node32.gate++;
        node6.gate++ <--> Chanel <--> node18.gate++;
        node6.gate++ <--> Chanel <--> node41.gate++;
        node6.gate++ <--> Chanel <--> node13.gate++;
        node7.gate++ <--> Chanel <--> node34.gate++;
        node7.gate++ <--> Chanel <--> node17.gate++;
        node7.gate++ <--> Chanel <--> node16.gate++;
        node7.gate++ <--> Chanel <--> node9.gate++;
        node7.gate++ <--> Chanel <--> node26.gate++;
        node8.gate++ <--> Chanel <--> node35.gate++;
        node8.gate++ <--> Chanel <--> node9.gate++;
        node8.gate++ <--> Chanel <--> node28.gate++;
        node9.gate++ <--> Chanel <--> node35.gate++;
        node9.gate++ <--> Chanel <--> node37.gate++;
        node9.gate++ <--> Chanel <--> node12.gate++;
        node10.gate++ <--> Chanel <--> node16.gate++;
        node10.gate++ <--> Chanel <--> node31.gate++;
        node12.gate++ <--> Chanel <--> node15.gate++;
        node13.gate++ <--> Chanel <--> node26.gate++;
        node14.gate++ <--> Chanel <--> node49.gate++;
        node14.gate++ <--> Chanel <--> node38.gate++;
        node15.gate++ <--> Chanel <--> node16.gate++;
        node16.gate++ <--> Chanel <--> node29.gate++;
        node17.gate++ <--> Chanel <--> node42.gate++;
        node17.gate++ <--> Chanel <--> node25.gate++;
        node17.gate++ <--> Chanel <--> node40.gate++;
        node17.gate++ <--> Chanel <--> node29.gate++;
        node18.gate++ <--> Chanel <--> node45.gate++;
        node19.gate++ <--> Chanel <--> node32.gate++;
        node19.gate++ <--> Chanel <--> node33.gate++;
        node19.gate++ <--> Chanel <--> node20.gate++;
        node19.gate++ <--> Chanel <--> node44.gate++;
        node20.gate++ <--> Chanel <--> node48.gate++;
        node20.gate++ <--> Chanel <--> node43.gate++;
        node22.gate++ <--> Chanel <--> node23.gate++;
        node22.gate++ <--> Chanel <--> node45.gate++;
        node23.gate++ <--> Chanel <--> node32.gate++;
        node23.gate++ <--> Chanel <--> node47.gate++;
        node24.gate++ <--> Chanel <--> node35.gate++;
        node24.gate++ <--> Chanel <--> node46.gate++;
        node26.gate++ <--> Chanel <--> node36.gate++;
        node26.gate++ <--> Chanel <--> node31.gate++;
        node27.gate++ <--> Chanel <--> node38.gate++;
        node27.gate++ <--> Chanel <--> node29.gate++;
        node28.gate++ <--> Chanel <--> node30.gate++;
        node29.gate++ <--> Chanel <--> node40.gate++;
        node30.gate++ <--> Chanel <--> node42.gate++;
        node31.gate++ <--> Chanel <--> node45.gate++;
        node32.gate++ <--> Chanel <--> node33.gate++;
        node32.gate++ <--> Chanel <--> node39.gate++;
        node33.gate++ <--> Chanel <--> node49.gate++;
        node34.gate++ <--> Chanel <--> node43.gate++;
        node35.gate++ <--> Chanel <--> node39.gate++;
        node37.gate++ <--> Chanel <--> node46.gate++;
        node39.gate++ <--> Chanel <--> node44.gate++;
        node41.gate++ <--> Chanel <--> node47.gate++;
        node47.gate++ <--> Chanel <--> node48.gate++;
}
