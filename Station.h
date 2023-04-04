//
// Created by António Rego on 3/21/2023.
//

#ifndef PROJETODA_STATION_H
#define PROJETODA_STATION_H

#include <string>
using namespace std;

class Station {
public:
    Station();
    Station(string name, string district, string municipality, string township, string line);
    string getName();
    string getDistrict();
    string getMunicipality();
    string getTownship();
    string getLine();
    bool operator<(Station s1) const;
private:
    string name;
    string district;
    string municipality;
    string township;
    string line;
};


#endif //PROJETODA_STATION_H
