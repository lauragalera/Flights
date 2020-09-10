//Laura Galera Alfaro
//u1959173
//practica final


#include "Route.h"

Route::Route(const vector<string> &dataRead) {
    
    _IATAICAOAirline = dataRead[IATAICAOAirline];
    _destinationAirport = dataRead[IATAICAOAirportD];
    _sourceAirport = dataRead[IATAICAOAirportS];
    _stops = stoi(dataRead[stops]);
    
    if (dataRead[IDAirline] == "\\N") _airlineID = -1;
    else _airlineID = stoi(dataRead[IDAirline]);
    
    if (dataRead[IDAirportS] == "\\N") _IDsourceAirport = -1;
    else _IDsourceAirport = stoi(dataRead[IDAirportS]);
    
    if (dataRead[IDAirportD] == "\\N") _IDdestinationAirport = -1;
    else _IDdestinationAirport = stoi(dataRead[IDAirportD]);
    
    if (dataRead[codeShare] == "Y") _codeShare = true;
    else _codeShare = false;
 
    string tmp;
    stringstream load(dataRead[flightsUsed]); 
    while (load >> tmp) { //guardem els IATA dels avions a una list de strings.
        if (!tmp.empty()) _equipment.push_back(tmp);
    }
}

int Route::getIDAirline() const {
    
    return _airlineID;
}

string Route::getIATAICAOAirline() const {
    
    return _IATAICAOAirline;
}

int Route::getIDAirport(char type) const {
    
    if (type == 'D') return _IDsourceAirport;
    else return _IDdestinationAirport;
}

string Route::getIATAICAOAirport(char type) const {
    
    if (type == 'D') return _sourceAirport;
    return _destinationAirport;
}

list<string> Route::getEquipment() const {
    
    return _equipment;
}


