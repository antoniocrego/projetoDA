//
// Created by António Rego on 3/21/2023.
//

#ifndef PROJETODA_NETWORK_H
#define PROJETODA_NETWORK_H


#include "data_structures/Graph.h"
#include "Station.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Network {
public:
    Network();
    void readStations();
    void readNetwork();
    Graph getTrainNetwork();
    string IDtoStation(int id);

    double maxFlow(const std::string& source, const std::string& dest);
private:
    Graph trainNetwork;
    unordered_map<string,Station> stationInfo;
    unordered_map<string,int> stationToID;
};


#endif //PROJETODA_NETWORK_H
