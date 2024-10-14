#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

void visit_node(std::queue<int>& q, std::unordered_map<int, bool>& visited, std::unordered_map<int, int>& predecessor, std::string& world, int node, int next_node)
{
    if(node > 0 && node < world.size() && !visited[node])
    if(world[node] == '.' || world[node] == 'E')
    {
        q.push(node);
        visited[node] = true;
        predecessor[node] = next_node; 
    }
}

int main()
{
    std::vector<std::string> paths = { "../test1.txt", "../test2.txt", "../test3.txt"};
    for(auto path : paths)
    {
        std::ifstream file(path);
        if (!file) 
        {
            std::cerr << "Error opening file!" << std::endl;
            return 1;
        }

        int row = 0;
        int col = 0;
        std::string world;
        std::string line;
        while (std::getline(file, line)) 
        {
            if(col == 0)
                col = line.size();
            std::cout << line << std::endl;
            world += line;
            row ++;
        }
        file.close();

        std::cout << "Col: " << col << std::endl;
        std::cout << "Row: " << row << std::endl;

        int start = world.find('S'); 
        int found = -1;
        std::queue<int> q;
        std::unordered_map<int, bool> visited;
        std::unordered_map<int, int> predecessor;
        
        q.push(start);
        visited[start] = true;

        while (!q.empty()) 
        {
            if(q.empty())
                break;

            int currentNode = q.front();
            q.pop();

            if (currentNode == world.find('E')) 
            {
                std::cout << "FOUND :)" << std::endl;
                found = currentNode;
                break;
            }

            if(currentNode - col > 0) visit_node(q, visited, predecessor, world, currentNode - col, currentNode);
            if(currentNode + col < world.size()) visit_node(q, visited, predecessor, world, currentNode + col, currentNode);
            if(((currentNode % col) != (col - 1))) visit_node(q, visited, predecessor, world, currentNode + 1, currentNode);
            if((currentNode % col) != 0) visit_node(q, visited, predecessor, world, currentNode - 1, currentNode);
        }

        if(found == -1)
            std::cout << "Not Found :(\n" << std::endl;
        else {
            int node = found;
            std::string path;
            while(node != start)
            {
                int pred = predecessor[node];
                if(node == pred + 1)        path = "RIGHT\n" + path;
                else if(node == pred - 1)   path = "LEFT\n" + path;
                else if(node == pred + col) path = "BOTTOM\n" + path;
                else if(node == pred - col) path = "TOP\n" + path;        
                node = pred;
            }
            std::cout << path;
        }
    }
    return 0;
}