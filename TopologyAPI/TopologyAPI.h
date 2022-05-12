// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include <iostream>
#include <json.hpp>
using json = nlohmann::json;
using namespace std;

#define sz(v) (int)v.size()
#define all(v) v.begin(),v.end()
#define DeviceList vector<json>


namespace TopologyLibrary
{
	class Topology
	{
		// single topology
		class Result {
			string id;
			DeviceList components;
		public:
			Result(string id, DeviceList components);
			int cntDevices();
			string getID();
			DeviceList getDevices();
			json toJSON();
			void print();
			bool operator==(const Result& other);
		};

		// multiple topologies
		class TopologyList {
			vector<Result> topologies;
		public:
			int cntTopologies();
			vector<Result> getTopologies();
			void addTopology(Result topo);
			Result findTopology(string topologyID);
			Topology::Result deleteTopology(string topologyID);
			void print();
		};

		unique_ptr<TopologyList> memory;

	public:

		Topology();

		// Read a topology from a given JSON file and store it in the memory.
		Result readJSON(string FileName);

		// Write a given topology from the memory to a JSON file.
		Result writeJSON(string TopologyID);

		// Query about which topologies are currently in the memory.
		TopologyList queryTopologies();

		// Delete a given topology from memory.
		Result deleteTopology(string TopologyID);

		// Query about which devices are in a given topology.
		DeviceList queryDevices(string TopologyID);

		// Query about which devices are connected to a given netlist node in a given topology.
		DeviceList queryDevicesWithNetlistNode(string TopologyID, string NetlistNodeID);
	};
}