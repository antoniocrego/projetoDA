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
    ///@brief Empty Constructor.
    Network();
    /**
     * @brief Store the information about the Stations from a Data File into a graph.
     */
    void readStations();
    /**
     * @brief Store the information about the connections between Stations from a Data File into a graph.
     */
    void readNetwork();
    /**
     * @brief Function that returns the graph related to the connections between Stations
     * @return Graph
     */
    Graph getTrainNetwork();
    /**
     * @brief Function that returns the Station related to the given id passed in the parameter.
     * @param id
     * @return The Station.
     */
    string IDtoStation(int id);
    /**
     * @brief Function that returns information about the Station given the name.
     * @param name The name of the Station.
     * @return The Station.
     */
    Station getStationInfo(string name);
    /**
     * @brief Function that returns the id of the Station given the name.
     * @param name The name of the Station.
     * @return The Station ID.
     */
    int getStationID(const string& name);
    /**
     * @brief Function that takes two strings as parameters and convert them into id before calling the Edmonds Karp Algorithm.
     * @param source The source Station.
     * @param dest The destination Station.
     * @return The Edmonds Karp function with these two parameters.
     */
    double maxFlow(const std::string& source, const std::string& dest);
    /**
     * @brief Function that calculates the maximum maxflow in the entire railway.
     * @param stationPairs The vector that is going to store our return.
     * @return The vector stationPairs with the names of the Stations where flow is max.
     */
    double maxFlowPairs(vector<pair<std::string, std::string>>& stationPairs);
    vector<pair<int,string>> multiMaxFlow();
    double reducedEdgesMaxFlow(const std::string& source, const std::string& dest, unordered_set<Edge *> segments);
    vector<pair<int,pair<double,double>>> segmentFailureEvaluation(const unordered_set<Edge *>& segments);
    double maxArrival(const std::string& station);
private:
    ///brief Bidirection Graph that represents the connections between Stations.
    Graph trainNetwork;
    Graph bdTrainNetwork;
    ///brief A map where the first parameter is the name of the Station and the second one is a Station Object.
    unordered_map<string,Station> stationInfo;
    ///brief A map where the first parameter is the name of the Station and the second one is the Station ID.
    unordered_map<string,int> stationToID;
};


#endif //PROJETODA_NETWORK_H
