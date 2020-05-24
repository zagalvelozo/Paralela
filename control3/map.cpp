#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

#include "map.h"
#include "debug.h"

Map::Map(int verticesCount) : weights(verticesCount)
{
    for (int i = 0; i < verticesCount; ++i)
    {
        weights[i].resize(verticesCount);
    }
}

Map Map::fromFile(const std::string &str, const char delimiter)
{
    return fromFile(std::ifstream(str.c_str()), delimiter);
}

Map Map::fromFile(std::ifstream &&istream, const char delimiter)
{
    std::string header;

    if (std::getline(istream, header, ':') && header == "vertices" && std::getline(istream, header))
    {
        int verticesCount = std::stoi(header);

        Map m(verticesCount);

        for (auto i = 0; i < verticesCount; ++i)
        {
            std::string line;
            std::getline(istream, line);

            std::stringstream linestream(line);
            for (auto j = 0; j < verticesCount; ++j)
            {
                std::string numstr;
                std::getline(linestream, numstr, delimiter);

                // the `i` node has no edge to `j`
                if (numstr.find("-") != std::string::npos)
                    m.weights[i][j] = NO_EDGE;

                else
                    m.weights[i][j] = std::stoi(numstr);
            }
        }

        for (auto i = 0; i < verticesCount; ++i)
        {
            char nodeName[2] = {0};
            nodeName[0] = i;
            m.nodesNames.push_back(i);
        }

        return m;
    }

    throw std::runtime_error("Wrong map file format");
}

void Map::printWeights() const
{
    for (auto i = 0u; i < getSize(); ++i)
    {
        for (auto j = 0u; j < getSize(); ++j)
            if (weights[i][j] != -1)
            {
                continue;
            }
            //std::cout << std::setw(4) << weights[i][j] << " ";
            else
            {
                continue;
            }
        //std::cout << std::setw(4) << "-" << " ";

        //std::cout << std::endl;
    }
}
