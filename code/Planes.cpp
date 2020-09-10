//Laura Galera Alfaro
//u1959173
//practica final

#include <list>
#include <set>

#include "Planes.h"

Planes::Planes() {
}

Planes::Planes(const Planes &p) {
    copy(p);
}

Planes::~Planes() {
    free();
}

Planes& Planes::operator=(const Planes& p) {
    if (this != &p) {
        free();
        copy(p);
    }
    return (*this);
}

void Planes::addPlane(const vector<string> &dataRead) {
    Plane * newPlane = new Plane(dataRead);
    if (newPlane->knownIATA()) {
        string IATA = newPlane->getIATA();
        map<string, Plane *>::iterator it = _mapIATAPlanes.find(IATA);
        if (it != _mapIATAPlanes.end()) _IATARepeated.insert(IATA); //Ja hi ha un avió amb el mateix IATA
        else _mapIATAPlanes[IATA] = newPlane;
    }
    else delete newPlane;
}

bool Planes::planesUsedExist(const list<string> &IATAPlanes) const {
    bool exist = true;
    list<string>::const_iterator it = IATAPlanes.begin();
    while (it != IATAPlanes.end() and exist) {
        map<string, Plane *>::const_iterator itP = _mapIATAPlanes.find(*it); 
        if (itP == _mapIATAPlanes.end()) exist = false; //N'hi ha un que no existeix
        else it++;
    }
    return exist;
}

string Planes::getNameSpecificPlane(string IATA) const{
            
        map<string, Plane *>::const_iterator it = _mapIATAPlanes.find(IATA);
        return (it->second->getName());
}

void Planes::finishReading() {

    for (string i : _IATARepeated){
       map<string, Plane *>::iterator it = _mapIATAPlanes.find(i);
       delete it->second;
       _mapIATAPlanes.erase(i);
    }
    _IATARepeated.clear();
}

/*****************/
/*MÈTODES PRIVATS*/
/*****************/

void Planes::copy(const Planes &p){
    
    for(pair<string, Plane *> i : p._mapIATAPlanes){
        Plane * aux = new Plane(*(i.second));
        _mapIATAPlanes[aux->getIATA()] = aux;
    }
}

void Planes::free(){
    
    for(pair<string, Plane *> i : _mapIATAPlanes){
        delete i.second;
        i.second = NULL;
    }
    
    _mapIATAPlanes.clear();
    _IATARepeated.clear();
}