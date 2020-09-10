//Laura Galera Alfaro
//u1959173
//practica final

#include "Flights.h"

Flights::Flights() {}

Flights::Flights(const Flights & f){
    
    copy(f);
}

Flights::~Flights(){
    
    free(); 
}

Flights& Flights::operator=(const Flights& f){
    
    if (this != &f) {
        free();
        copy(f);
    }
    return (*this);
}

void Flights::addFlight(const vector<string> &dataRead, const Airports &aeroports, const Airlines &aerolinies) {

    Flight newFlight(dataRead);

    if (aerolinies.airlineExists(-1, newFlight.getIATAAirline())) { //aerolinia existeix
        if (aeroports.airportExists(-1, newFlight.getIATAAirport('D')) and aeroports.airportExists(-1, newFlight.getIATAAirport('A'))) { //aeroports existeixen
            includeToAllStructures(new Flight(dataRead));
        }
    }
}

vector<pair<int, InfoAirport>> Flights::mostDelayedAirports(const vector<string> &dataRead, const Airports & airports, char option) const {

    vector<pair<int, InfoAirport>> mostDelayedAirports;
    Date d(dataRead[4], dataRead[3], dataRead[2]);
    map<Date, list<Flight *> >::const_iterator it = _mapDate.find(d);
    if (it == _mapDate.end()) { //ERROR la data no existeix
        throw "not found date";
    } else {
        map<string, int> airportsDelay;
        string IATA;
        int delay;
        for (Flight * f : it->second) { //tots els vols fets en aquella data

            if (option == 'D') {
                IATA = f->getIATAAirport('D');
                delay = f->getDelay('D');
            } else {
                IATA = f->getIATAAirport('A');
                delay = f->getDelay('A');
            }

            if (delay > 0) {
                if (airportsDelay.find(IATA) == airportsDelay.end())
                    airportsDelay[IATA] = 0;
                airportsDelay[IATA] += delay; //acumulem el retard
            }
        }
        set<pair<int, InfoAirport>> delayedAirports;

        for (pair<string, int> i : airportsDelay) { //ordenem en un set per retard

            InfoAirport airport = airports.gatherInfoAirport(i.first);
            delayedAirports.insert(make_pair(i.second, airport));
        }

        int n = stoi(dataRead[1]); //guardem en un vector els n elements demanats, ordenats decreixentment.
        if (n == 0) n = delayedAirports.size();
        mostDelayedAirports.reserve(n);
        int i = 0;
        set<pair<int, InfoAirport> >::reverse_iterator itR = delayedAirports.rbegin();
        while (i < n and itR != delayedAirports.rend()) {
            mostDelayedAirports.push_back(make_pair(itR->first, itR->second));
            itR++;
            i++;
        }
    }
    return mostDelayedAirports;
}

vector<pair<int, InfoAirline>> Flights::mostdelayedAirlines(const vector<string> &dataRead, const Airlines & airlines, char option) const {

    multimap<int, InfoAirline> delayedAirlines;
    for (pair<string, list < Flight * >> i : _mapIATAAirline) {

        int delay = 0;
        for (Flight * j : i.second) {

            if (option == 'D' and j->getDelay(option) > 0)
                delay += j->getDelay(option);
            else if (option == 'A' and j->getDelay(option) > 0)
                delay += j->getDelay(option);
        }
        if (delay > 0) { //si el retard és més gran que 0 inserim al multimap
            InfoAirline airline = airlines.gatherInfoAirline(i.first);
            delayedAirlines.insert(make_pair(delay, airline));
        }
    }
    
    vector<pair<int, InfoAirline>> mostDelayedAirlines;
    
    int n = stoi(dataRead[1]);
    if (n == 0) n = delayedAirlines.size();
    mostDelayedAirlines.reserve(n);
    int j = 0;
    multimap<int, InfoAirline>::reverse_iterator itR = delayedAirlines.rbegin();
    while (j < n and itR != delayedAirlines.rend()) { //ens quedem amb els n elements demanats, ordenats decreixentment
        mostDelayedAirlines.push_back(make_pair(itR->first, itR->second));
        itR++;
        j++;
    }
    return mostDelayedAirlines;
}

list<pair<Date, int>> Flights::daysMoreDelay(const vector<string> &dataRead, const Airports & airports) const {

    map<Date, int> countDate;
    if (dataRead.size() == 1) { //per a tots els aeroports
        for (pair<Date, list < Flight*>> i : _mapDate) {
            countDate[i.first] = 0;
            for (Flight * f : i.second) { //recorrem els vols d'una data
                if (f->getDelay('D') > 0)
                    countDate[f->getDate()] += f->getDelay('D'); //sumem retard sortida
                if (f->getDelay('A') > 0)
                    countDate[f->getDate()] += f->getDelay('A'); //sumem retard arribada
            }
        }
    } else { //només per a un subconjunt d'aeroports
        for (unsigned i = 1; i < dataRead.size(); i++) { //recorrem cada aeroport
            if (!airports.airportExists(-1, dataRead[i]))
                cerr << "ERROR: " + dataRead[i] + " is an unknown IATA airport code \n\n"; //missatge d'error, no existeix.
            else {
                map<string, list<Flight * > >::const_iterator it = _mapIATAAirport.find(dataRead[i]);
                if (it != _mapIATAAirport.end()) { //si l'aeroport ha tingut vols
                    for (Flight * f : it->second) { //recorrem tots els vols de l'aeroport.
                        int delay = 0;
                        if (f->getIATAAirport('D') == dataRead[i] and f->getDelay('D') > 0) { //si és l'aeroport de sortida i el retard es positiu
                            delay = f->getDelay('D');
                        } else if (f->getIATAAirport('A') == dataRead[i] and f->getDelay('A') > 0) { //si és l'aeroport d'arribada i el retard es positiu
                            delay = f->getDelay('A');
                        }
                        if (delay > 0) { //en aquella data hi ha hagut retard
                            if(countDate.find(f->getDate()) == countDate.end()) //la data no s'ha inserit encara
                                countDate[f->getDate()] = 0;
                            countDate[f->getDate()] += delay; //sumem el retard
                        }
                    }
                }
            }
        }
    }

    set<pair<int, Date>> orderedDelayDay;
    for (pair<Date, int> j : countDate) //set per ordenar segons retard
        orderedDelayDay.insert(make_pair(j.second, j.first));

    list<pair<Date, int>> dayMoreDelay;

    if (countDate.size() > 0) {
        set<pair<int, Date>>::reverse_iterator itR = orderedDelayDay.rbegin();
        int most = itR->first;
        while (itR != orderedDelayDay.rend() and itR->first == most) { //ens quedem amb les dates que han tingut max retard
            dayMoreDelay.push_back(make_pair(itR->second, itR->first));
            itR++;
        }
    }

    return dayMoreDelay;
}

/*****************/
/*MÈTODES PRIVATS*/
/*****************/

void Flights::includeToAllStructures(Flight * newFlight) {
    
    Date date = newFlight->getDate();
    
    _mapDate[date].push_back(newFlight);    
    
    string IATA = newFlight->getIATAAirline();
        
    _mapIATAAirline[IATA].push_back(newFlight);
    
    string IATASourceAirport = newFlight->getIATAAirport('D');
    string IATADestAirport = newFlight->getIATAAirport('A');
        
    _mapIATAAirport[IATASourceAirport].push_back(newFlight);
        
    _mapIATAAirport[IATADestAirport].push_back(newFlight);
}

void Flights::copy(const Flights &f){
    
    for(pair<Date, list<Flight *>> i : f._mapDate){
        for(Flight * l : i.second){
            Flight * aux = new Flight(*l);
            includeToAllStructures(aux);
        }
    }
}

void Flights::free(){
    
    for(pair<Date, list<Flight*>> f : _mapDate){
        for( Flight * i : f.second){
            delete i;
            i = NULL;
        }
    }
    
    _mapDate.clear();
    _mapIATAAirport.clear();
    _mapIATAAirline.clear();
}

