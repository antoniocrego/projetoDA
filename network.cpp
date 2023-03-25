#include "Network.h"

Network::Network(){
    readStations();
    readNetwork();
}

void Network::readNetwork() {
    ifstream in("../data/network.csv");
    string aLine, origin, dest, capacity, service;
    getline(in, aLine);
    while (getline(in, aLine))
    {
        istringstream inn(aLine);
        getline(inn, origin, ',');
        getline(inn, dest, ',');
        getline(inn, capacity, ',');
        getline(inn, service, ',');
        double gordo = stod(capacity);
        trainNetwork.addEdge(stationToID.at(origin),stationToID.at(dest),gordo, service);
    }
}

void Network::readStations() {
    ifstream in("../data/stations.csv");
    string aLine, name, district, municipality, township, line;
    getline(in, aLine);
    while (getline(in, aLine))
    {
        istringstream inn(aLine);
        getline(inn, name, ',');
        getline(inn, district, ',');
        getline(inn, municipality, ',');
        getline(inn, township, ',');
        getline(inn, line, ',');
        Station station = Station(name,district,municipality,township,line);
        stationToID.insert({name,stationToID.size()});
        trainNetwork.addVertex(stationToID.size()-1);
    }
}

Graph Network::getTrainNetwork() {
    return trainNetwork;
}

string Network::IDtoStation(int id) {
    for(auto c : stationToID){
        if (c.second==id) return c.first;
    }
    return "Notfound";
}
