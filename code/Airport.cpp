//Laura Galera Alfaro
//u1959173
//practica final

#include "Airport.h"


Airport::Airport(const vector<string> &dataRead) {

    _ID = stoi(dataRead[ID]);
    _name = dataRead[name];
    _city = dataRead[city];
    _country = dataRead[country];
    _IATACode = dataRead[IATA];
    _ICAOCode = dataRead[ICAO];
    _latitude = stof(dataRead[latitude]);
    _longitude = stof(dataRead[longitude]);
    _altitude = stoi(dataRead[altitude]);
    _databaseTz = dataRead[TZ];
    _type = dataRead[type];
    _source = dataRead[source];
    
    if (dataRead[timeZone] == "\\N") _timeZone = -1000;
    else _timeZone = stof(dataRead[timeZone]);
    
    if (dataRead[DST] == "\\N") _DST = 'U';
    else _DST = dataRead[DST].at(0);
    
}

string Airport::getIATA() const {
    
    return _IATACode;
}

string Airport::getICAO() const {
    
    return _ICAOCode;
}

int Airport::getID() const {
    
    return _ID;
}

string Airport::getCountry() const{
    
    return _country;
}

InfoAirport Airport::getNamePlace() const{
    
    InfoAirport a;
    a.name = _name;
    a.city = _city;
    a.country = _country;
    
    return a;
}

bool Airport::knownIATA() const {
    
    return (_IATACode != "\\N");
}

bool Airport::knownICAO() const {
    
    return (_ICAOCode != "\\N");
}


