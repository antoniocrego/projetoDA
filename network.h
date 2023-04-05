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
#include <unordered_set>
using namespace std;

class Network {
public:
    Network();
    void readStations();
    void readNetwork();
    Graph getTrainNetwork();
    string IDtoStation(int id);
    Station getStationInfo(string name);
    int getStationID(const string& name);

    double maxFlow(const std::string& source, const std::string& dest);
    double maxFlowPairs(vector<pair<std::string, std::string>>& stationPairs);
    vector<pair<int,string>> multiMaxFlow();
    double reducedEdgesMaxFlow(const std::string& source, const std::string& dest, unordered_set<Edge *> segments);
    vector<pair<int,pair<double,double>>> segmentFailureEvaluation(const unordered_set<Edge *>& segments);
    double maxArrival(const std::string& station);
private:
    Graph trainNetwork;
    Graph bdTrainNetwork;
    unordered_map<string,Station> stationInfo;
    unordered_map<string,int> stationToID;
};


#endif //PROJETODA_NETWORK_H
