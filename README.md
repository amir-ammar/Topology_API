# TopologyAPI

## An API library which does the following

**1. Read and write topologies to and from disk.**

**2. Stores multiple topologies in memory.**

**3. Execute operations on topologies.**

### Topology Specification

    A topology is a set of electronic components that are connected together.

![example topology](/images/topology.png)

### Provided Functionality

**1. Read a topology from a given JSON file and store it in the memory.**

**2. Write a given topology from the memory to a JSON file.**

**3. Query about which topologies are currently in the memory.**

**4. Delete a given topology from memory.**

**5. Query about which devices are in a given topology.**

**6. Query about which devices are connected to a given netlist node in a given topology.**
