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

channel Channel extends ned.DelayChannel
{
    delay = 1ms;
}

channel Channel1 extends ned.DelayChannel
{
    delay = 1ms;
}

channel Channel2 extends ned.DelayChannel
{
    delay = 2ms;
}

channel Channel3 extends ned.DelayChannel
{
    delay = 3ms;
}

channel Channel4 extends ned.DelayChannel
{
    delay = 3.2ms;
}

channel Channel5 extends ned.DelayChannel
{
    delay = 1.5ms;
}

channel Channel6 extends ned.DelayChannel
{
    delay = 2.4ms;
}
channel Channel7 extends ned.DelayChannel
{
    delay = 3.9ms;
}
channel Channel8 extends ned.DelayChannel
{
    delay = 1.9ms;
}
channel Channel9 extends ned.DelayChannel
{
    delay = 2.6ms;
}
channel Channel10 extends ned.DelayChannel
{
    //  delay = 6ms;
    delay = 6ms;
}








//
// Generated network with random topology (12 nodes, 20 edges, seed=100).
//
network Network12
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
    connections:
        node0.gate++ <--> Channel10 <--> node1.gate++;
        node0.gate++ <--> Channel10 <--> node2.gate++;
        node0.gate++ <--> Channel10 <--> node4.gate++;
        node0.gate++ <--> Channel10 <--> node6.gate++;
        node0.gate++ <--> Channel10 <--> node11.gate++;
        node1.gate++ <--> Channel10 <--> node2.gate++;
        node1.gate++ <--> Channel10 <--> node3.gate++;
        node1.gate++ <--> Channel10 <--> node5.gate++;
        node1.gate++ <--> Channel10 <--> node8.gate++;
        node2.gate++ <--> Channel10 <--> node4.gate++;
        node2.gate++ <--> Channel10 <--> node8.gate++;
        node3.gate++ <--> Channel10 <--> node5.gate++;
        node3.gate++ <--> Channel10 <--> node7.gate++;
        node3.gate++ <--> Channel10 <--> node10.gate++;
        node4.gate++ <--> Channel10 <--> node11.gate++;
        node5.gate++ <--> Channel10 <--> node9.gate++;
        node6.gate++ <--> Channel10 <--> node10.gate++;
        node6.gate++ <--> Channel10 <--> node11.gate++;
        node7.gate++ <--> Channel10 <--> node9.gate++;
        node8.gate++ <--> Channel10 <--> node9.gate++;
}
