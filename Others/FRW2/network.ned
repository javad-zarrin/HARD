//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2010 Andras Varga, Rudolf Hornig
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


//
// Same as nodetoc12
//
network disNetwork
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 1ms;
        }
    submodules:
        node[12]: rdNode;
    connections:
        node[0].gate++ <--> Channel <--> node[1].gate++;
        node[1].gate++ <--> Channel <--> node[2].gate++;
        node[1].gate++ <--> Channel <--> node[4].gate++;
        node[3].gate++ <--> Channel <--> node[4].gate++;
        node[4].gate++ <--> Channel <--> node[6].gate++;
        node[4].gate++ <--> Channel <--> node[5].gate++;
        node[6].gate++ <--> Channel <--> node[7].gate++;
        node[7].gate++ <--> Channel <--> node[8].gate++;
        node[5].gate++ <--> Channel <--> node[10].gate++;
        node[9].gate++ <--> Channel <--> node[10].gate++;
        node[10].gate++ <--> Channel <--> node[11].gate++;

        node[7].gate++ <--> Channel <--> node[11].gate++;



}

simple rdNode
{
    
    
    
    
    parameters:
		@node;
		int RH_DRQ;
		int Desired_Number_Of_Resources;
		int application_scale;
	//	double channeldelay;
   //     @signal[finishSelfDeployment](type="long int");
//        @statistic[num_inc_msg](title="num_inc_msg"; source="finishSelfDeployment"; record=mean; interpolationmode=none);

        @display("i=misc/node2,white;is=vs");
    gates:
        inout gate[];
}

