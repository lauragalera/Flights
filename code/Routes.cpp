//Laura Galera Alfaro
//u1959173
//practica final

#include "Routes.h"

Routes::Routes() {}

Routes::Routes(const Routes &r) {
    
    copy(r);
}

Routes::~Routes() {
    
    free();
}

Routes& Routes::operator=(const Routes& r) {
    
    if (this != &r) {
        free();
        copy(r);
    }
    return (*this);
}

void Routes::addRoute(const vector<string> &dataRead, const Airports &aeroports, const Airlines & aerolinies, const Planes & avions) {
    Route ruta(dataRead);
    if (aerolinies.airlineExists(ruta.getIDAirline(), ruta.getIATAICAOAirline())) {
        if (aeroports.airportExists(ruta.getIDAirport('S'), ruta.getIATAICAOAirport('S')) and aeroports.airportExists(ruta.getIDAirport('D'), ruta.getIATAICAOAirport('D'))) {
            if (avions.planesUsedExist(ruta.getEquipment())) {
                addToRightStructure(new Route(dataRead));
            }
        }
    }
}

set<AirlineType> Routes::countRoutesByAirline(const Airlines & aerolinies, const Airports & aeroports) const {

    set<AirlineType> countTypeAirlines;
    
    if (_mapRoutesAirline.size() > 0) { //comptem totes les rutes d'aerolínies identificades per ID
        for (auto i : _mapRoutesAirline) {
            int codeAirline = i.first;
            pair<string, string> countryAirline = aerolinies.lookForCountry(codeAirline, "\\N"); //mètode de Airlines que retorna el país i el nom de l'aerolínia.
            if (!countryAirline.first.empty()) { //si es coneix el país de l'aerolínia
                classifyRoutesAirline(i.second, countTypeAirlines, countryAirline.first, countryAirline.second, aeroports); //actualitza countTypeAirline, afegint l'aerolínia i el recompte
            }
        }
    }

    if (_mapRoutesIATA.size() > 0) { 
        for (auto i : _mapRoutesIATA) { //comptem totes les rutes d'aerolínies identificades per IATA
            string codeIATA = i.first;
            pair<string, string> countryAirline = aerolinies.lookForCountry(-1, codeIATA);
            if (!countryAirline.first.empty())
                classifyRoutesAirline(i.second, countTypeAirlines, countryAirline.first, countryAirline.second, aeroports); 
        }

    }

    if (_mapRoutesICAO.size() > 0) {
        for (auto i : _mapRoutesICAO) { //comptem totes les rutes d'aerolínies identificades per ICAO
            string codeICAO = i.first;
            pair<string, string> countryAirline = aerolinies.lookForCountry(-1, codeICAO);
            if (!countryAirline.first.empty())
                classifyRoutesAirline(i.second, countTypeAirlines, countryAirline.first, countryAirline.second, aeroports);
        }
    }

    return countTypeAirlines;
}

map<string, list<string>> Routes::mostUsedPlane(string IATAAirline, const Airlines & airlines, const Planes & planes) const {

    map<string, list < string>> mostUsedPlaneAirline;
    Airline * airline = airlines.giveAirline(IATAAirline);
    if (airline == NULL) throw "non-existent"; //l'aerolinia no existeix
    else {
        list<Route *> listofRoutes = getAllRoutes(airline); //llista amb les rutes de l'aerolínia
        map<string, int> countPlane;

        for (Route * r : listofRoutes) { //recorrem totes les rutes
            for (string IATA : r->getEquipment()) { //recorrem cada avió usat en una ruta
                if (countPlane.find(IATA) == countPlane.end())
                    countPlane[IATA] = 0;
                countPlane[IATA]++; //incrementem el comptador en 1 per a aquell avió
            }
        }

        set<pair<int, string>> planesUsed;
        //ordenem en un set el número de repetits i el nom de l'avio
        for (pair<string, int> i : countPlane) {
            string namePlane = planes.getNameSpecificPlane(i.first);
            planesUsed.insert(make_pair(i.second, namePlane));
        }

        list<string> mostUsedPlane; //en una list afegirem els avions amb el mateix nombre de repetits que el màxim
        if (planesUsed.size() > 0) {
            set<pair<int, string> >::reverse_iterator itR = planesUsed.rbegin();
            int freqMostUsed = itR->first; //quants cops s'ha usat l'avió més usat de tots
            while (itR != planesUsed.rend() and freqMostUsed == itR->first) { //mentre no arribem al final i hi hagi avions amb el mateix nombre que l'avió més usat
                mostUsedPlane.push_back(itR->second);
                itR++;
            }
            mostUsedPlaneAirline.insert(make_pair(airline->getName(), mostUsedPlane)); //l'afegim al map
        }
        return mostUsedPlaneAirline;
    }
}

/*****************/
/*MÈTODES PRIVATS*/
/*****************/

void Routes::addToRightStructure(Route * ruta) {

    int IDAirline = ruta->getIDAirline();
    
    if (IDAirline != -1) { 
        //afegim al map _mapRoutesAirlines
        _mapRoutesAirline[IDAirline].push_back(ruta);
    } else {
        
        string code = ruta->getIATAICAOAirline();
        if (code.length() == 2) {
            //afegim al map _mapRoutesIATA
            _mapRoutesIATA[code].push_back(ruta);
            
        } else { 
            //afegim al map _mapRoutesICAO
            _mapRoutesICAO[code].push_back(ruta);
        }
    }
}

void Routes::classifyRoutesAirline(const list<Route *> & listRoutes, set<AirlineType> &countTypeAirlines, string countryAirline, string nameAirline, const Airports & aeroports) const {

    int inter, natio;
    inter = natio = 0;
    for (auto j : listRoutes) { //recorrem la llista de vols de l'aerolínia
        bool isNational = aeroports.isNationalAirports(j->getIDAirport('D'), j->getIATAICAOAirport('D'), j->getIDAirport('A'), j->getIATAICAOAirport('A'), countryAirline); /*metode de Airports per saber
                                                                                                                                                                              si la ruta es nacional*/
        if (isNational)
            natio++;
        else inter++;
    }

    AirlineType aux; //creem la tupla a inserir
    aux.nameAirline = nameAirline;
    aux.inter = inter;
    aux.natio = natio;

    countTypeAirlines.insert(aux); //la inserim
}

list<Route *> Routes::getAllRoutes(Airline * airline) const {

    list<Route *> r;
    map<int, list < Route *>>::const_iterator itID = _mapRoutesAirline.find(airline->getID());

    if (itID == _mapRoutesAirline.end()) { //no està al map ID
        if (airline->knownIATA()) { //si l'aerolinia té codi IATA conegut
            map<string, list < Route*>>::const_iterator itI = _mapRoutesIATA.find(airline->getIATA());
            if (itI == _mapRoutesIATA.end()) { //no està al map IATA tampoc
                if (airline->knownICAO()) { //si l'aerolinia té codi ICAO conegut
                    itI = _mapRoutesICAO.find(airline->getICAO());
                    if (itI != _mapRoutesICAO.end())
                        r = itI->second; //l'aerolínia està al map _mapRoutesICAO
                }
            } else r = itI->second; //l'aerolínia està al map _mapRoutesIATA
        }
    } else r = itID->second; //l'aerolínia està al map _mapRoutesAirline

    return r;
}

void Routes::copy(const Routes &r) {

    for (pair<int, list < Route *>> i : r._mapRoutesAirline) {
        for (Route * o : i.second) {
            Route * aux = new Route(*o);
            _mapRoutesAirline[aux->getIDAirline()].push_back(aux);
        }
    }
    for (pair<string, list < Route *>> i : r._mapRoutesIATA) {
        for (Route * o : i.second) {
            Route * aux = new Route(*o);
            _mapRoutesIATA[aux->getIATAICAOAirline()].push_back(aux);
        }
    }
    for (pair<string, list < Route *>> i : r._mapRoutesICAO) {
        for (Route * o : i.second) {
            Route * aux = new Route(*o);
            _mapRoutesICAO[aux->getIATAICAOAirline()].push_back(aux);
        }
    }
}

void Routes::free() {

    for (pair<int, list < Route *>> i : _mapRoutesAirline) {
        for (Route * r : i.second) {
            delete r;
            r = NULL;
        }
    }
    for (pair<string, list < Route *>> i : _mapRoutesIATA) {
        for (Route * r : i.second) {
            delete r;
            r = NULL;
        }
    }
    for (pair<string, list < Route *>> i : _mapRoutesICAO) {
        for (Route * r : i.second) {
            delete r;
            r = NULL;
        }
    }
    
    _mapRoutesAirline.clear();
    _mapRoutesIATA.clear();
    _mapRoutesICAO.clear();
}

