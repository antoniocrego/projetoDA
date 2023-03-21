//
// Created by António Rego on 3/21/2023.
//

#ifndef PROJETODA_NETWORK_H
#define PROJETODA_NETWORK_H


#include "data_structures/Graph.h"
#include "Station.h"
#include <unordered_map>
using namespace std;

class Network {
public:
    void readStations();
    void readNetwork();
private:
    Graph trainNetwork;
    unordered_map<string,Station> stationInfo;

};


#endif //PROJETODA_NETWORK_H
