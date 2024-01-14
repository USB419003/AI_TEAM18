#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

// Perform Breadth-First Search (BFS) to find a path
bool bfs(char start, char end, const std::vector<std::vector<char>>& graph, std::ofstream& outputFile) {
    std::queue<char> queue;
    std::unordered_set<char> visited;
    std::unordered_map<char, char> parent;

    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        char current = queue.front();
        queue.pop();

        if (current == end) {
            // Reconstruct the path
            std::vector<char> path;
            char node = end;
            while (node != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(start);

            // Write the path to the output file
            outputFile << "Path found: ";
            for (int i = path.size() - 1; i >= 0; --i) {
                outputFile << path[i];
                if (i > 0) outputFile << " -> ";
            }
            outputFile << std::endl;

            return true;
        }

        for (char neighbor : graph[current - 'A']) {
            if (visited.find(neighbor) == visited.end()) {
                queue.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = current;

                // Write step information to the output file
                outputFile << "Step: ";
                outputFile << "Current node: " << current << ", ";
                outputFile << "Next node: " << neighbor << std::endl;

                // Uncomment the line below to see the steps in the console
                // std::cout << "Step: " << "Current node: " << current << ", " << "Next node: " << neighbor << std::endl;
            }
        }
    }

    return false; // No path found
}

int main() {
    std::string inputFileName = "input(1).txt";   // Change this to your input file name
    std::string outputFileName = "output(1).txt"; // Change this to your output file name

    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile) {
        std::cerr << "Error: Could not open input file " << inputFileName << std::endl;
        return 1;
    }

    if (!outputFile) {
        std::cerr << "Error: Could not open output file " << outputFileName << std::endl;
        return 1;
    }

    int numNodes, numEdges;
    inputFile >> numNodes >> numEdges;

    std::vector<std::vector<char>> graph(numNodes); // Assuming nodes are labeled with characters (A, B, C, ...)
    char u, v;

    for (int i = 0; i < numEdges; ++i) {
        inputFile >> u >> v;
        graph[u - 'A'].push_back(v);
        graph[v - 'A'].push_back(u); // Assuming an undirected graph
    }

    char start, end;
    inputFile >> start >> end;

    // Perform BFS to find a path from start to end
    bool pathFound = bfs(start, end, graph, outputFile);

    // Write the result to the output file
    if (!pathFound) {
        outputFile << "No path found." << std::endl;
    }

    // Close files
    inputFile.close();
    outputFile.close();

    std::cout << "BFS search completed. Output written to " << outputFileName << std::endl;

    return 0;
}

