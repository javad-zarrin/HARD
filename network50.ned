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

//
// Generated network with random topology (50 nodes, 80 edges, seed=5).
//
network Network50
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
        node0.gate++ <--> Channel10 <--> node35.gate++;
        node0.gate++ <--> Channel10 <--> node1.gate++;
        node0.gate++ <--> Channel10 <--> node2.gate++;
        node0.gate++ <--> Channel10 <--> node25.gate++;
        node0.gate++ <--> Channel10 <--> node9.gate++;
        node0.gate++ <--> Channel10 <--> node11.gate++;
        node1.gate++ <--> Channel10 <--> node5.gate++;
        node1.gate++ <--> Channel10 <--> node7.gate++;
        node1.gate++ <--> Channel10 <--> node10.gate++;
        node2.gate++ <--> Channel10 <--> node17.gate++;
        node2.gate++ <--> Channel10 <--> node32.gate++;
        node2.gate++ <--> Channel10 <--> node33.gate++;
        node2.gate++ <--> Channel10 <--> node3.gate++;
        node2.gate++ <--> Channel10 <--> node4.gate++;
        node2.gate++ <--> Channel10 <--> node11.gate++;
        node3.gate++ <--> Channel10 <--> node32.gate++;
        node3.gate++ <--> Channel10 <--> node49.gate++;
        node3.gate++ <--> Channel10 <--> node18.gate++;
        node3.gate++ <--> Channel10 <--> node39.gate++;
        node3.gate++ <--> Channel10 <--> node23.gate++;
        node3.gate++ <--> Channel10 <--> node12.gate++;
        node4.gate++ <--> Channel10 <--> node39.gate++;
        node4.gate++ <--> Channel10 <--> node14.gate++;
        node5.gate++ <--> Channel10 <--> node6.gate++;
        node5.gate++ <--> Channel10 <--> node22.gate++;
        node5.gate++ <--> Channel10 <--> node10.gate++;
        node5.gate++ <--> Channel10 <--> node27.gate++;
        node5.gate++ <--> Channel10 <--> node28.gate++;
        node6.gate++ <--> Channel10 <--> node21.gate++;
        node6.gate++ <--> Channel10 <--> node8.gate++;
        node6.gate++ <--> Channel10 <--> node31.gate++;
        node6.gate++ <--> Channel10 <--> node45.gate++;
        node7.gate++ <--> Channel10 <--> node18.gate++;
        node8.gate++ <--> Channel10 <--> node19.gate++;
        node8.gate++ <--> Channel10 <--> node43.gate++;
        node8.gate++ <--> Channel10 <--> node9.gate++;
        node8.gate++ <--> Channel10 <--> node41.gate++;
        node8.gate++ <--> Channel10 <--> node15.gate++;
        node9.gate++ <--> Channel10 <--> node34.gate++;
        node9.gate++ <--> Channel10 <--> node22.gate++;
        node11.gate++ <--> Channel10 <--> node23.gate++;
        node11.gate++ <--> Channel10 <--> node25.gate++;
        node11.gate++ <--> Channel10 <--> node13.gate++;
        node12.gate++ <--> Channel10 <--> node35.gate++;
        node13.gate++ <--> Channel10 <--> node17.gate++;
        node13.gate++ <--> Channel10 <--> node16.gate++;
        node13.gate++ <--> Channel10 <--> node49.gate++;
        node13.gate++ <--> Channel10 <--> node37.gate++;
        node13.gate++ <--> Channel10 <--> node47.gate++;
        node14.gate++ <--> Channel10 <--> node17.gate++;
        node15.gate++ <--> Channel10 <--> node27.gate++;
        node15.gate++ <--> Channel10 <--> node29.gate++;
        node16.gate++ <--> Channel10 <--> node37.gate++;
        node17.gate++ <--> Channel10 <--> node20.gate++;
        node19.gate++ <--> Channel10 <--> node43.gate++;
        node19.gate++ <--> Channel10 <--> node45.gate++;
        node20.gate++ <--> Channel10 <--> node24.gate++;
        node20.gate++ <--> Channel10 <--> node26.gate++;
        node20.gate++ <--> Channel10 <--> node29.gate++;
        node20.gate++ <--> Channel10 <--> node30.gate++;
        node21.gate++ <--> Channel10 <--> node32.gate++;
        node22.gate++ <--> Channel10 <--> node33.gate++;
        node22.gate++ <--> Channel10 <--> node41.gate++;
        node23.gate++ <--> Channel10 <--> node28.gate++;
        node24.gate++ <--> Channel10 <--> node37.gate++;
        node24.gate++ <--> Channel10 <--> node47.gate++;
        node25.gate++ <--> Channel10 <--> node48.gate++;
        node25.gate++ <--> Channel10 <--> node26.gate++;
        node26.gate++ <--> Channel10 <--> node36.gate++;
        node27.gate++ <--> Channel10 <--> node43.gate++;
        node27.gate++ <--> Channel10 <--> node45.gate++;
        node28.gate++ <--> Channel10 <--> node46.gate++;
        node28.gate++ <--> Channel10 <--> node31.gate++;
        node29.gate++ <--> Channel10 <--> node42.gate++;
        node29.gate++ <--> Channel10 <--> node44.gate++;
        node32.gate++ <--> Channel10 <--> node39.gate++;
        node33.gate++ <--> Channel10 <--> node40.gate++;
        node34.gate++ <--> Channel10 <--> node48.gate++;
        node37.gate++ <--> Channel10 <--> node38.gate++;
        node37.gate++ <--> Channel10 <--> node39.gate++;
}
