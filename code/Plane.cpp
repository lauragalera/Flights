//Laura Galera Alfaro
//u1959173
//practica final

#include "Plane.h"

Plane::Plane(const vector<string> &dataRead) {
    
    _name = dataRead[name];
    _IATACode = dataRead[IATA];
    _ICAOCode = dataRead[ICAO];
}

string Plane::getIATA() const {
    
    return _IATACode;
}

string Plane::getName() const{
    
    return _name;
}

bool Plane::knownIATA() const {
    
    return (_IATACode != "\\N");
}


