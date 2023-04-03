#include "Network.h"

int main(){
    Network manager = Network();
    Graph network = manager.getTrainNetwork();
    cout << manager.maxFlow("Porto São Bento", "Braga");
    return 0;
}