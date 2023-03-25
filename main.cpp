#include "Network.h"

int main(){
    Network manager = Network();
    Graph network = manager.getTrainNetwork();
    for (auto c : network.getVertexSet()) cout << c->getId() << "," << manager.IDtoStation(c->getId()) << "\n";
    return 0;
}