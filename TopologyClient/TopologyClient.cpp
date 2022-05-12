#include "TopologyAPI.h"
#include<iostream>

int main() {

	TopologyLibrary::Topology topo;

	topo.readJSON("topology.json");
	topo.queryTopologies().print();
	/*topo.deleteTopology("top1");
	topo.queryTopologies().print();*/
	cout << topo.queryDevices("top1") << endl;
	cout << topo.queryDevicesWithNetlistNode("top1", "n1") << endl;
	cout << topo.queryDevicesWithNetlistNode("top1", "vdd") << endl;

	return 0;
}