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

package src;

module Node
{
    parameters:
        @display("i=abstract/router_vs");
    gates:
        inout g[];
    connections allowunconnected:
}

channel Link extends ned.DatarateChannel
{
    parameters:
        int cost = default(0);
}

//
// Generated network with random topology (8 nodes, 14 edges, seed=100).
//
network Network
{
    submodules:
        node0: Node;
        node1: Node {
            @display("p=100,14");
        }
        node2: Node {
            @display("p=169,96");
        }
        node3: Node;
        node4: Node;
        node5: Node;
        node6: Node {
            @display("p=198,25");
        }
        node7: Node {
            @display("p=85,125");
        }
    connections:
        node0.g++ <--> Link <--> node1.g++;
        node0.g++ <--> Link <--> node4.g++;
        node0.g++ <--> Link <--> node6.g++;
        node1.g++ <--> Link <--> node2.g++;
        node1.g++ <--> Link <--> node3.g++;
        node1.g++ <--> Link <--> node4.g++;
        node1.g++ <--> Link <--> node5.g++;
        node1.g++ <--> Link <--> node6.g++;
        node1.g++ <--> Link <--> node7.g++;
        node2.g++ <--> Link <--> node4.g++;
        node2.g++ <--> Link <--> node6.g++;
        node2.g++ <--> Link <--> node7.g++;
        node3.g++ <--> Link <--> node7.g++;
        node4.g++ <--> Link <--> node7.g++;
}
