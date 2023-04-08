#include "Program.h"

Program::Program() {
    this->currentMenuPage=0;
    createMenu();
    this->network=Network();
}

/**Functionality: Make the program wait until the user wants it to continue
 *
 * Description: This is an auxiliary function, it will create a string and ask the user to insert anything when he wants to continue the program. That
 * way the program will be on hold until the user tells it to continue.
 */
void Program::wait() const {
    cout<<"\nEnter anything to go back:";
    string wait;
    cin>>wait;
}

void Program::clear() const {
    for(int i = 0; i < 20; i++){
        cout << endl;
    }
}

void Program::createMenu() {
    this->menus.push_back(Menu("../menu/files/mainMenu.txt", "Train Network"));//Initialize main menu
    /*this->menus.push_back(Menu("../Menus/scheduleSubMenu.txt"));// Initialize schedule submenu
    this->menus.push_back(Menu("../Menus/requestsMenu"));*/

}

int Program::getCurrentPage() const {
    return this->currentMenuPage;
}

/**
 *
 * @param newCurrentPage
 * This function receive the index of the new menu page we are in and set it as the current menu page
 */
void Program::setCurrentPage(int newCurrentPage)  {
    this->currentMenuPage=newCurrentPage;
}

/**Functionality: draw the current page of the menu we are in
 * Description: Take the attribute menus get the current menu and use the method draw of the menu to draw it
 */
void Program::draw(){
    this->menus[this->currentMenuPage].draw(); //draw the current menu
}

void Program:: run() {
    while (this->currentMenuPage != -1) {
        menu();
// runs until quit option is selected
    }
}

void Program::menu() {
    draw(); //draw the current menu
    int option = menus.at(currentMenuPage).getOption();
    string station1 = "";
    string station2 = "";
    vector<pair<string, string>> pairs;
    unordered_set<Edge *> segments;
    vector<Edge *> segments2;
    Edge * segment;
    double returnValue;
    vector<pair<int,pair<double,double>>> specialReturn;
    vector<pair<int,double>> temp;
    pair<int,double> dijkstra;
    vector<pair<double,string>> flowByDistrict;
    switch (this->currentMenuPage) {
        case 0: // Is on main menu
            switch (option) {
                case 1:
                    station1 = chooseStation(false);
                    station2 = chooseStation(false);
                    clear();
                    returnValue = network.maxFlow(station1,station2);
                    cout << "The maximum flow between " << station1 << " and " << station2 << " is " << returnValue << ".\n";
                    this->wait();
                    currentMenuPage=0;
                    break;
                case 2: //option show was selected, changing to submenu show
                    station1 = chooseStation(false);
                    clear();
                    returnValue = this->network.maxArrival(station1);
                    cout << station1 << " Max Arrival: " << returnValue << endl;
                    this->wait();
                    currentMenuPage = 0;
                    break;
                case 3:
                    clear();
                    returnValue = this->network.maxFlowPairs(pairs);
                    cout << "The highest flow between stations in the network is " << returnValue << " for the following stations:\n";
                    for (auto pair: pairs) {
                        cout << "\t" << pair.first << " & " << pair.second << endl;
                    }
                    this->wait();
                    currentMenuPage = 0;
                    break;
                case 4:
                    clear();
                    flowByDistrict = this->network.multiMaxFlowDistricts();
                    std::sort(flowByDistrict.begin(), flowByDistrict.end(), [](const pair<double,string>& a, const pair<double,string>& b) -> bool{return a.first<b.first;});
                    cout << "From highest transportation need (lowest flow), to lowest need (highest flow):" << endl;
                    for (int i = 1; i<=flowByDistrict.size(); i++){
                        cout << "\t[" << i << "] " << flowByDistrict.at(i-1).second << " - " << flowByDistrict.at(i-1).first << endl;
                    }
                    this->wait();
                    currentMenuPage = 0;
                    break;
                case 5:
                    station1 = chooseDistrict(false);
                    clear();
                    flowByDistrict = this->network.multiMaxFlowMunicipalities(station1);
                    std::sort(flowByDistrict.begin(), flowByDistrict.end(), [](const pair<double,string>& a, const pair<double,string>& b) -> bool{return a.first<b.first;});
                    cout << "From highest transportation need (lowest flow), to lowest need (highest flow) in the district of " << station1 << ":" << endl;
                    for (int i = 1; i<=flowByDistrict.size(); i++){
                        cout << "\t[" << i << "] " << flowByDistrict.at(i-1).second << " - " << flowByDistrict.at(i-1).first << endl;
                    }
                    this->wait();
                    currentMenuPage = 0;
                    break;
                case 6:
                    station1 = chooseStation(false);
                    station2 = chooseStation(false);
                    while (true){
                        segment = chooseEdge(true);
                        if(segment == NULL) break;
                        segments.insert(segment);
                    }
                    clear();
                    returnValue = this->network.reducedEdgesMaxFlow(station1, station2, segments);
                    cout << "The maximum flow between " << station1 << " and " << station2 << " without the selected edges is" << returnValue << "." << endl;
                    this->wait();
                    currentMenuPage = 0;
                    break;
                case 7:
                    while (true){
                        segment = chooseEdge(true);
                        if(segment == NULL) break;
                        segments2.push_back(segment);
                    }
                    clear();
                    specialReturn = this->network.segmentFailureEvaluation(segments2);
                    for (int i = 0; i<segments2.size();i++) {
                        for (int j = i; j < specialReturn.size(); j += segments2.size()) {
                            temp.emplace_back(specialReturn.at(j).first,
                                              specialReturn.at(j).second.first - specialReturn.at(j).second.second);
                        }
                        cout << "For the failure of segment: " << network.IDtoStation(segments2.at(i)->getOrig()->getId()) << " <-> " << network.IDtoStation(segments2.at(i)->getDest()->getId()) << endl;
                        std::sort(temp.begin(), temp.end(), [](const pair<int,double>& a, const pair<int,double>& b) -> bool{return a.second>b.second;});
                        for (int cnt = 1; cnt<=10; cnt++){
                            cout << "\t[" << cnt << "]" << network.IDtoStation(temp.at(cnt-1).first) << " - " << temp.at(cnt-1).second << endl;
                        }
                        temp.clear();
                        cout << endl;
                    }
                    this->wait();
                    currentMenuPage=0;
                    break;
                case 8:
                    station1 = chooseStation(false);
                    station2 = chooseStation(false);
                    clear();
                    dijkstra = network.getTrainNetwork().Dijsktra(network.getStationID(station1),network.getStationID(station2));
                    cout << "For the cheapest cost of " << dijkstra.first << "€, there is a maximum flow of " << dijkstra.second << " in between " << station1 << " and " << station2 << ".\n";
                    this->wait();
                    currentMenuPage=0;
                    break;
                case 9:
                    this->network = Network();
                    break;
                case 0:
                    this->currentMenuPage = -1;
                    break;
            }
            break;
    }
}

string Program::chooseDistrict(bool addStopButton){
    int previousMenuPage = currentMenuPage;
    this->menus.push_back(Menu(network.getDistricts(), "Districts"));// Initialize districts submenu
    currentMenuPage = menus.size() - 1;
    if(addStopButton) menus.at(currentMenuPage).addButton("Stop");
    draw();
    int option = menus.at(currentMenuPage).getOption();
    if((option-1) == this->network.getDistricts().size()) return "quit";
    string district = this->network.getDistricts().at(option-1);
    currentMenuPage = previousMenuPage;
    menus.pop_back();
    return district;
}

string Program::chooseMunicipality(bool addStopButton) {
    string district = chooseDistrict(false);
    int previousMenuPage = currentMenuPage;
    vector<string> municipalities;
    for(pair<string,string> pair : this->network.getMunicipalities()){
        if(pair.first == district){
            municipalities.push_back(pair.second);
        }
    }
    this->menus.push_back(Menu(municipalities, "Municipalities"));// Initialize districts submenu
    currentMenuPage = menus.size() - 1;
    if(addStopButton) menus.at(currentMenuPage).addButton("Stop");
    draw();
    int option = menus.at(currentMenuPage).getOption();
    if((option-1) == municipalities.size()) return "quit";
    string municipality = municipalities.at(option-1);
    currentMenuPage = previousMenuPage;
    menus.pop_back();
    return municipality;
}

string Program::chooseStation(bool addStopButton) {
    string municipality = chooseMunicipality(false);
    int previousMenuPage = currentMenuPage;
    vector<string> stations;
    for(auto pair : this->network.getStations()){
        Station station = pair.second;
        if(station.getMunicipality() == municipality){
            stations.push_back(station.getName());
        }
    }
    menus.push_back(Menu(stations, "Stations"));
    currentMenuPage = menus.size()-1;
    if(addStopButton) menus.at(currentMenuPage).addButton("Stop");
    draw();
    int option = menus.at(currentMenuPage).getOption();
    if((option-1) == stations.size()) return "quit";
    string stationName = stations.at(option-1);
    currentMenuPage = previousMenuPage;
    menus.pop_back();
    return stationName;
}

Edge * Program::chooseEdge(bool addStopButton) {
    string source = chooseStation(false);
    int sourceId = this->network.getStationID(source);
    int previousMenuPage = currentMenuPage;
    vector<string> destStations;
    Vertex * sourceVertex = this->network.getTrainNetwork().getVertexSet().at(sourceId);
    for(auto edge : sourceVertex->getAdj()){
        string destStation = this->network.IDtoStation(edge->getDest()->getId());
        destStations.push_back(destStation);
    }
    menus.push_back(Menu(destStations, "Adjacent Stations"));
    currentMenuPage = menus.size()-1;
    if(addStopButton) menus.at(currentMenuPage).addButton("Stop");
    draw();
    int option = menus.at(currentMenuPage).getOption();
    if((option - 1) == destStations.size()){
        return NULL;
    }
    Edge * edge = sourceVertex->getAdj().at(option - 1);
    currentMenuPage = previousMenuPage;
    menus.pop_back();
    return edge;
}

