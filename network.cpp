#include "Network.h"

Network::Network(){
    readStations();
    readNetwork();
}

void Network::readNetwork() {
    ifstream in("../data/network.csv");
    string aLine, origin, dest, capacity, service, trash;
    getline(in, aLine);
    while (getline(in, aLine))
    {
        istringstream inn(aLine);
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, origin, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, origin, ',');
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, dest, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, dest, ',');
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, capacity, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, capacity, ',');
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, service, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, service, ',');
        double gordo = stod(capacity);
        trainNetwork.addBidirectionalEdge(stationToID.at(origin),stationToID.at(dest),gordo, service);
    }
}

void Network::readStations() {
    ifstream in("../data/stations.csv");
    string aLine, name, district, municipality, township, line, trash;
    getline(in, aLine);
    while (getline(in, aLine))
    {
        istringstream inn(aLine);
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, name, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, name, ',');
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, district, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, district, ',');
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, municipality, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, municipality, ',');
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, township, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, township, ',');
        if (inn.peek()=='\"'){
            getline(inn, trash, '\"');
            getline(inn, line, '\"');
            getline(inn,trash,',');
        }
        else getline(inn, line, ',');
        Station station = Station(name,district,municipality,township,line);
        stationInfo.insert({name,station});
        stationToID.insert({name,stationToID.size()});
        trainNetwork.addVertex(stationToID.size()-1);
    }
}

Graph Network::getTrainNetwork() {
    return trainNetwork;
}

string Network::IDtoStation(int id) {
    for(const auto& c : stationToID){
        if (c.second==id) return c.first;
    }
    return "Notfound";
}

double Network::maxFlow(const std::string& source, const std::string& dest){
    double maxFlow = 0;
    int srcID;
    int destID;
    try {
        srcID = stationToID.at(source);
        destID = stationToID.at(dest);
    }
    catch (const std::out_of_range& oor){
        cout << "Invalid source or destination stations.\n";
        return -1;
    }
    return trainNetwork.edmondsKarp(srcID, destID);
}

Station Network::getStationInfo(string name){
    auto iter = stationInfo.find(name);
    if(iter == stationInfo.end()){
        cout << "Notfound";
        return Station();
    }
    return iter->second;
}

double Network::maxFlowPairs(vector<pair<std::string, std::string>>& stationPairs){
    double currentMax = 0;
    double iterationFlow;
    for (int i = 0; i<stationToID.size(); i++){
        for (int j=i; j<stationToID.size(); j++){
            if (i==j) continue;
            iterationFlow= maxFlow(IDtoStation(i), IDtoStation(j));
            if (iterationFlow>currentMax){
                currentMax=iterationFlow;
                stationPairs.clear();
                stationPairs.emplace_back(IDtoStation(i), IDtoStation(j));
            }
            else if (iterationFlow==currentMax) stationPairs.emplace_back(IDtoStation(i), IDtoStation(j));
        }
    }
    return currentMax;
}