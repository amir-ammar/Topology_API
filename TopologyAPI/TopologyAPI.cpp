// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "TopologyAPI.h"
#include <fstream>
#include <iomanip>
namespace TopologyLibrary
{
	// Result subclass

	int Topology::Result::cntDevices() {
		return sz(this->components);
	}

	string Topology::Result::getID() {
		return this->id;
	}

	DeviceList Topology::Result::getDevices() {
		return this->components;
	}

	json Topology::Result::toJSON() {
		json j;
		j["id"] = this->id;
		j["components"] = this->components;
		return j;
	}

	void Topology::Result::print() {
		cout << setw(4) << this->toJSON() << endl;
	}

	Topology::Result::Result(string id, DeviceList components) {
		this->id = id;
		this->components = components;
	}

	bool Topology::Result::operator==(const Result& other) {
		return other.id == this->id;
	}

	// TopologyList subclass

	int Topology::TopologyList::cntTopologies() {
		return sz(this->topologies);
	}

	vector<Topology::Result> Topology::TopologyList::getTopologies() {
		return this->topologies;
	}

	void Topology::TopologyList::addTopology(Result topo) {
		this->topologies.push_back(topo);
	}

	Topology::Result Topology::TopologyList::findTopology(string topologyID) {
		for (auto topo : this->topologies) {
			if (topo.getID() == topologyID) {
				return topo;
			}
		}
		string message = "No topology with id (" + topologyID + ")!";
		perror(message.c_str());
		exit(1);
	}

	Topology::Result Topology::TopologyList::deleteTopology(string topologyID) {
		Result topo = this->findTopology(topologyID);
		this->topologies.erase(remove(all(this->topologies), topo), this->topologies.end());
		return topo;
	}

	void Topology::TopologyList::print() {
		for (auto topology : this->topologies) {
			topology.print();
		}
	}

	// Topology Class

	Topology::Topology() {
		this->memory = unique_ptr<TopologyList>(new TopologyList());
	}

	// Read a topology from a given JSON file and store it in the memory.
	Topology::Result Topology::readJSON(string FileName) {
		ifstream i(FileName);
		json j;
		i >> j;
		try
		{
			string topologyID = j["id"];
			DeviceList components = j["components"];
			Result r(topologyID, components);
			this->memory->addTopology(r);
			return r;
		}
		catch (const std::exception&)
		{
			perror("JSON file doesn't meet the requirements!");
			exit(1);
		}
	}

	// Write a given topology from the memory to a JSON file.
	Topology::Result Topology::writeJSON(string TopologyID) {
		Result topo = this->memory->findTopology(TopologyID);
		std::ofstream o(topo.getID()+".json");
		o << setw(4) << topo.toJSON() << std::endl;
		return topo;
	}

	// Query about which topologies are currently in the memory.
	Topology::TopologyList Topology::queryTopologies() {
		return *(this->memory);
	}

	// Delete a given topology from memory.
	Topology::Result Topology::deleteTopology(string TopologyID) {
		return this->memory->deleteTopology(TopologyID);
	}

	// Query about which devices are in a given topology.
	DeviceList Topology::queryDevices(string TopologyID) {
		Result topo = this->memory->findTopology(TopologyID);
		return topo.getDevices();
	}

	// Query about which devices are connected to a given netlist node in a given topology.
	DeviceList Topology::queryDevicesWithNetlistNode(string TopologyID, string NetlistNodeID) {
		DeviceList devices = this->queryDevices(TopologyID);
		DeviceList result;
		for (auto device : devices) {
			string netlist = device["netlist"].dump();
			if (netlist.find(NetlistNodeID) != string::npos) {
				result.push_back(device);
			}
		}
		return result;
	}
}