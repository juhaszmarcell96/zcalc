#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

struct Node {
    std::string name;
    bool visited = false;
    bool start = false;
};

struct Edge {
    std::string designator;
    std::size_t node_0_index;
    std::size_t node_1_index;
    bool visited = false;
};

class Network {
private:
    std::vector<Node> m_nodes;
    std::vector<Edge> m_edges;

    void node_cycle (std::size_t node_index, std::vector<std::string> path, std::vector<std::vector<std::string>>& cycles)
    {
        /* if this is the starting node but this node was not yet visited by the algorithm -> this is the starting node */
        /* mark this node as visited */
        /* put it in the path */
        /* go through every unvisited edge of this node, set them to visited, add them to the path and call the cycle to their other node */
        if (!m_nodes[node_index].visited) {
            m_nodes[node_index].visited = true;                                     /* set the node to visited */
            path.push_back(m_nodes[node_index].name);                               /* put the node into the path */
            for (Edge& edge : m_edges) {                                            /* go through every unvisited edge */
                if (edge.visited == false) {
                    std::vector<std::string> own_path = path;                       /* clone the path */
                    edge.visited = true;                                            /* set the edge to visited */
                    own_path.push_back(edge.designator);                            /* add the edge to the path */
                    if (edge.node_0_index == node_index) {                          /* if one end of the edge is connected to this node */
                        node_cycle(edge.node_1_index, own_path, cycles);            /* call the node cycle */
                    }
                    else if (edge.node_1_index == node_index) {
                        node_cycle(edge.node_0_index, own_path, cycles);
                    }
                    edge.visited = false;
                }
            }
            m_nodes[node_index].visited = false;
        }
        /* if the node was already visited */
        else {
            if (m_nodes[node_index].start) {                                        /* if it is the starting node -> cycle */
                //path.push_back(m_nodes[node_index].name);
                cycles.push_back(path);
            }
        }
    }
public:
    void add_node (const std::string& node_name) {
        for (const Node& node : m_nodes) {
            if (node_name.compare(node.name) == 0) {
                std::cout << "ERROR : node already exists" << std::endl;
                return;
            }
        }
        Node n;
        n.name = node_name;
        n.visited = false;
        n.start = false;
        m_nodes.push_back(n);
    }
    void add_edge (const std::string& designator, const std::string& node_0_name, const std::string& node_1_name) {
        for (const Edge& edge : m_edges) {
            if (designator.compare(edge.designator) == 0) {
                std::cout << "ERROR : edge already exists" << std::endl;
                return;
            }
        }
        Edge e;
        e.designator = designator;
        bool node_0_exists = false;
        bool node_1_exists = false;
        for (std::size_t i = 0; i < m_nodes.size(); ++i) {
            if (node_0_name.compare(m_nodes[i].name) == 0) {
                node_0_exists = true;
                e.node_0_index = i;
            }
            if (node_1_name.compare(m_nodes[i].name) == 0) {
                node_1_exists = true;
                e.node_1_index = i;
            }
        }
        if (!node_0_exists || !node_1_exists) {
            std::cout << "ERROR : edge endnode does not exists" << std::endl;
            return;
        }
        m_edges.push_back(std::move(e));
    }
    void print () {
        std::cout << "nodes" << std::endl;
        for (const Node& node : m_nodes) {
            std::cout << "    " << node.name << std::endl;
        }
        std::cout << "edges" << std::endl;
        for (const Edge& edge : m_edges) {
            std::cout << "    " << m_nodes[edge.node_0_index].name << " - " << edge.designator << " - " << m_nodes[edge.node_1_index].name << std::endl;
        }
    }
    void print_cycles () {
        std::vector<std::vector<std::string>> cycles;
        for (std::size_t i = 0; i < m_nodes.size(); ++i) {
            std::vector<std::string> path;
            for (Node& node_tmp : m_nodes) {
                node_tmp.start = false;
                node_tmp.visited = false;
            }
            for (Edge& edge_tmp : m_edges) {
                edge_tmp.visited = false;
            }
            m_nodes[i].start = true;
            node_cycle(i, path, cycles);
        }
        for (const std::vector<std::string>& cycle : cycles) {
            for (const std::string& element : cycle) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main () {
    Network network;
    network.add_node("gnd");
    network.add_node("input");
    network.add_node("a");
    network.add_node("b");
    network.add_node("output");
    network.add_edge("U", "input", "gnd");
    network.add_edge("500ohm", "input", "a");
    network.add_edge("10mH", "a", "b");
    network.add_edge("1kohm", "b", "gnd");
    network.add_edge("800ohm", "b", "output");
    network.add_edge("600ohm", "output", "gnd");
    network.add_edge("120nF", "output", "gnd");
    network.print();
    network.print_cycles();

    return 0;
}