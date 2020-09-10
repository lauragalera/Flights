//Laura Galera Alfaro
//u1959173
//practica final

#include "Airline.h"

Airline::Airline(const vector<string> &dataRead) {
    
    _ID = stoi(dataRead[ID]);
    _name = dataRead[name];
    _alias = dataRead[alias];
    _callsign = dataRead[callsign];
    _country = dataRead[country];
    
    if (dataRead[IATA].empty() or dataRead[IATA] == "-" or dataRead[IATA].size()!=2)
        _IATACode = "\\N";
    else _IATACode = dataRead[IATA];
    
    if (dataRead[ICAO] == "N/A" or dataRead[ICAO].empty() or dataRead[ICAO].size()!=3)
        _ICAOCode = "\\N";
    else _ICAOCode = dataRead[ICAO];
    
    if (dataRead[active] == "Y") _isActive = true;
    else _isActive = false;
}

int Airline::getID() const {
    
    return _ID;
}

bool Airline::knownIATA() const {
    
    return (_IATACode != "\\N");
}

bool Airline::knownICAO() const {
    
    return (_ICAOCode != "\\N");
}

string Airline::getIATA() const {
    
    return _IATACode;
}

string Airline::getICAO() const {
    
    return _ICAOCode;
}

string Airline::getCountry() const{
    
    return _country;
}

string Airline::getName() const{
    
    return _name;
}

bool Airline::isActive() const {
    
    return _isActive;
}


