//Laura Galera Alfaro
//u1959173
//practica final

#include "Airlines.h"

Airlines::Airlines() {}

Airlines::Airlines(const Airlines &a){
    
    copy(a);
}

Airlines::~Airlines(){
    
    free();
}

Airlines& Airlines::operator=(const Airlines&a) {
    
    if (this != &a) {
        free();
        copy(a);
    }
    return (*this);
}

void Airlines::addAirline(const vector<string> &dataRead){
    
    Airline * newAirline = new Airline(dataRead);
    _mapIDAirlines[newAirline->getID()] = newAirline;
    if (newAirline->knownIATA())
        manageIATARepeated(newAirline);
    if (newAirline->knownICAO())
        manageICAORepeated(newAirline);
}

pair<string, string> Airlines::lookForCountry(int ID, string IATAICAO) const {

    pair<string, string> countryAirline;

    if (ID != -1) {
        map<int, Airline *>::const_iterator it = _mapIDAirlines.find(ID);
        countryAirline.first = it->second->getCountry();
        countryAirline.second = it->second->getName();
    } else {
        map<string, Airline *>::const_iterator it;
        if (IATAICAO.length() == 2)
            it = _mapIATAAirlines.find(IATAICAO);
        else
            it = _mapICAOAirlines.find(IATAICAO);

        countryAirline.first = it->second->getCountry();
        countryAirline.second = it->second->getName();
    }

    return countryAirline;
}

 InfoAirline Airlines::gatherInfoAirline(string IATA) const {
     
    map<string, Airline *>::const_iterator it = _mapIATAAirlines.find(IATA);
    InfoAirline airline;
    airline.name = it->second->getName();
    airline.country = it->second->getCountry();
    
    return airline;
}
 
Airline * Airlines::giveAirline(string IATA) const{
    
    Airline * air = NULL;
    map<string, Airline *>::const_iterator it = _mapIATAAirlines.find(IATA);
    if(it!= _mapIATAAirlines.end()) air = it->second;
    
    return air;
}

bool Airlines::airlineExists(int ID, string IATAICAO) const {

    bool exists = false;
    if (ID == -1) {
        if (IATAICAO.length() == 2) {
            if (_mapIATAAirlines.find(IATAICAO) != _mapIATAAirlines.end())
                exists = true;
        } else {
            if (_mapICAOAirlines.find(IATAICAO) != _mapICAOAirlines.end())
                exists = true;
        }
    } else {
        if (_mapIDAirlines.find(ID) != _mapIDAirlines.end())
            exists = true;
    }
    return exists;
}

void Airlines::finishReading() {
    
    for (string i : _IATARepeated)
        _mapIATAAirlines.erase(i);
    
    for(string j : _ICAORepeated)
        _mapICAOAirlines.erase(j);

    _IATARepeated.clear();
    _ICAORepeated.clear();
}

/*****************/
/*MÈTODES PRIVATS*/
/*****************/

void Airlines::manageIATARepeated(Airline * newAirline) {
    
    string IATA = newAirline->getIATA();
    map<string, Airline *>::iterator it = _mapIATAAirlines.find(IATA);
    
    if (it != _mapIATAAirlines.end()) { //codi IATA ja existent
        
        bool activeOldOne = (it->second)->isActive();
        
        if (newAirline->isActive() and !activeOldOne) { //nova activa, primera inactiva
            _mapIATAAirlines[IATA] = newAirline; //substituim
            if (_IATARepeated.find(IATA) != _IATARepeated.end()) _IATARepeated.erase(IATA); //IATA ja no compta com a repetit
        } else if ((newAirline->isActive() and activeOldOne) or (!(newAirline->isActive()) and !activeOldOne)) { //nova i primera actives o nova i primera inactives
            _IATARepeated.insert(IATA); //afegim el IATA a repetits
        }
    } else _mapIATAAirlines[IATA] = newAirline; //codi IATA no està al map, afegim.
}

void Airlines::manageICAORepeated(Airline * newAirline) {
    
    string ICAO = newAirline->getICAO();
    map<string, Airline *>::iterator it = _mapICAOAirlines.find(ICAO);
    
    if (it != _mapICAOAirlines.end()) { //codi ICAO ja existent
        
        bool activeOldOne = (it->second)->isActive();
        
        if (newAirline->isActive() and !activeOldOne) { //nova activa, primera inactiva
            _mapICAOAirlines[ICAO] = newAirline; //substituim
            if (_ICAORepeated.find(ICAO) != _ICAORepeated.end()) _ICAORepeated.erase(ICAO); //ICAO ja no compta com a repetit
        } else if ((newAirline->isActive() and activeOldOne) or (!(newAirline->isActive()) and !activeOldOne)) { //nova i primera actives o nova i primera inactives
            _ICAORepeated.insert(ICAO); //afegim ICAO a repetits
        }
    } else _mapICAOAirlines[ICAO] = newAirline; //codi ICAO no està al map, afegim
}

void Airlines::copy(const Airlines &a){
    
    for(pair<int, Airline *> i : a._mapIDAirlines){
        
        Airline * aux = new Airline(*(i.second)); //copiem l'aerolínia
        _mapIDAirlines[aux->getID()] = aux; //inserim a _mapIDAirlines
        if(aux->knownIATA()) //inserim si cal a _mapIATAAirlines
            manageIATARepeated(aux);
        if(aux->knownICAO()) //inserim si cal a _mapICAOAirlines
            manageICAORepeated(aux);
    }
    finishReading(); //netegem _mapIATAAirlines i _mapICAOAirlines de codis no identificadors
}

void Airlines::free(){
    
    for(pair<int, Airline *> i : _mapIDAirlines){ //eliminem totes les aerolínies
        delete i.second;
        i.second = NULL;
    }
    
    _mapIDAirlines.clear();
    _mapIATAAirlines.clear();
    _mapICAOAirlines.clear();
    _IATARepeated.clear();
    _ICAORepeated.clear();
}

