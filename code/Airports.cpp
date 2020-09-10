//Laura Galera Alfaro
//u1959173
//practica 

#include "Airports.h"

Airports::Airports() {}

Airports::Airports(const Airports &a) {

    copy(a);
}

Airports::~Airports() {

    free();
}

Airports& Airports::operator=(const Airports& a) {

    if (this != &a) {
        free();
        copy(a);
    }
    return (*this);
}

void Airports::addAirport(const vector<string> &dataRead) {

    Airport * newAirport = new Airport(dataRead);
    int airport_ID = newAirport->getID();
    _mapIDAirports[airport_ID] = newAirport;

    if (newAirport->knownIATA())
        _mapIATAAirports[newAirport->getIATA()] = newAirport;
    if (newAirport->knownICAO())
        _mapICAOAirports[newAirport->getICAO()] = newAirport;
}

InfoAirport Airports::gatherInfoAirport(string IATA) const {

    map<string, Airport *>::const_iterator it = _mapIATAAirports.find(IATA);
    return it->second->getNamePlace();
}

bool Airports::airportExists(int ID, string IATAICAO) const {

    bool exists = false;
    if (ID == -1) {
        if (IATAICAO.length() == 3) {
            if (_mapIATAAirports.find(IATAICAO) != _mapIATAAirports.end()) exists = true;
        } else {
            if (_mapICAOAirports.find(IATAICAO) != _mapICAOAirports.end()) exists = true;
        }
    } else
        if (_mapIDAirports.find(ID) != _mapIDAirports.end()) exists = true;
    return exists;
}

bool Airports::isNationalAirports(int IDAirportSource, string IATAICAOAirportSource, int IDAirportDeparture, string IATAICAOAirportDeparture, string countryAirline) const {

    bool national = false;

    string nameCountrySource = getNameCountry(IDAirportSource, IATAICAOAirportSource);
    string nameCountryDeparture = getNameCountry(IDAirportDeparture, IATAICAOAirportDeparture);

    if (countryAirline == nameCountrySource && nameCountryDeparture == countryAirline)
        national = true;

    return national;

}

/*****************/
/*MÈTODES PRIVATS*/
/*****************/

string Airports::getNameCountry(int IDAirport, string IATAICAOAirport) const {

    string country;
    if (IDAirport != -1) {
        map<int, Airport *>::const_iterator it = _mapIDAirports.find(IDAirport);
        country = it->second->getCountry();
    } else {
        map<string, Airport *>::const_iterator it;

        if (IATAICAOAirport.length() == 3)
            it = _mapIATAAirports.find(IATAICAOAirport);
        else
            it = _mapICAOAirports.find(IATAICAOAirport);

        country = it->second->getCountry();
    }
    return country;
}

void Airports::copy(const Airports &a) {

    for (pair<int, Airport*> i : a._mapIDAirports) {
        Airport * aux = new Airport(*(i.second));
        _mapIDAirports[i.first] = aux;
        if (aux->knownIATA())
            _mapIATAAirports[aux->getIATA()] = aux;
        if (aux->knownICAO())
            _mapICAOAirports[aux->getICAO()] = aux;
    }
}

void Airports::free() {

    for (pair<int, Airport *> i : _mapIDAirports) {
        delete i.second;
        i.second = NULL;
    }
    
    _mapIDAirports.clear();
    _mapIATAAirports.clear();
    _mapICAOAirports.clear();
}
