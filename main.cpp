#include "Network.h"
#include "Program.h"

int main(){
    Network manager = Network();
    Graph network = manager.getTrainNetwork(); //39
    unordered_set<Edge *> temp;
    for (auto e : network.getVertexSet().at(0)->getIncoming()){
        temp.insert(e);
    }
    auto result = manager.segmentFailureEvaluation(temp);
    for (auto c : result){
        cout << manager.IDtoStation(c.first) << endl;
        cout << "\t" << c.second.first << "\\" << c.second.second << endl;
    }
    cout << manager.maxArrival("Porto Campanhã");

    network.Dijsktra(0,83);
    /*string input;
    cout << "Introduz 1 para ver todas as Stations.\nIntroduz 2 para ver todas as Edges da station 3.\n--";
    cin >> input;
    if(input == "1") {
        for (auto c: network.getVertexSet()) cout << c->getId() << "," << manager.IDtoStation(c->getId()) << "\n";
    }
    else{
        Vertex *vertex = network.findVertex(1);
        for(auto edge : vertex->getAdj()){
            cout << manager.IDtoStation(edge->getOrig()->getId()) << "->" << manager.IDtoStation(edge->getDest()->getId()) << "-" << edge->getWeight() << "\n";
        }
    }*/
    //Program p = Program();
    //p.run();

    return 0;
}