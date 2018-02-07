# HARD
HARD Simulation in OMNET++

<h2> C++ code for HARD simulation using OMNET++ </h2>

Hybrid Adaptive Resource Discovery (HARD) is a highly scalable and efficent resource-discovery protocol which is built upon a virtual hierarchical overlay based on self-organization and self-adaptation of processing resources in the system, where the computing resources are organized into distributed hierarchies according to a hierarchical multi-layered resource description model. HARD supports distributed query processing within and across hierarchical layers by deploying various distributed resource discovery services and functionalities in the system which are implemented using different adapted algorithms and mechanisms in each level of hierarchy. It addresses the requirements for resource discovery in very large scale manycore environments such as high-hierarchy, high-heterogeneity, high-scalability and dynamicity.


To read more about HARD, check out our paper here:
https://doi.org/10.1016/j.jnca.2017.04.014


<h2> Code Layout </h2>

HARD/src (hard3 source directory)

HARD/others (the code for simulation of other approaches)

<h2>Simulation </h2>

see simrun0, simrun1, simrun2

./Hard3 -u Cmdenv -c net100  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net200  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net300  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net400  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net500  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net600  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net700  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net800  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net900  -f omnetpp.ini -r 2

./Hard3 -u Cmdenv -c net1000  -f omnetpp.ini -r 2



