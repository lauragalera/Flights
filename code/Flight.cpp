//Laura Galera Alfaro
//u1959173
//practica final

#include <set>

#include "Flight.h"

Flight::Flight(const vector<string> &dataRead) {
    
    _date = Date(dataRead[dayMonth], dataRead[month], dataRead[year]);
    _dayOfWeek = stoi(dataRead[dayWeek]);
    _IATACodeAirline = dataRead[IATAairline];
    _flightNum = stoi(dataRead[flightNum]);
    _IATACodeAirportDep = dataRead[IATAairportD];
    _cityDeparture = dataRead[cityD];
    _IATACodeAirportArr = dataRead[IATAairportA];
    _cityArrival = dataRead[cityA];
    _expDepTime = stoi(dataRead[expDTime]);
    _expArrTime = stoi(dataRead[expATime]);
    _expElapsedTime = stoi(dataRead[expETime]);
    _distance = stoi(dataRead[distance]);
    
    if (dataRead[realDTime].empty()) _realDepTime = -1000;
    else _realDepTime = stoi(dataRead[realDTime]);
    
    if (dataRead[Ddelay].empty()) _depDelay = -1000;
    else _depDelay = stoi(dataRead[Ddelay]);
    
    if (dataRead[realATime].empty()) _realArrTime = -1000;
    else _realArrTime = stoi(dataRead[realATime]);
    
    if (dataRead[Adelay].empty()) _arrDelay = -1000;
    else _arrDelay = stoi(dataRead[Adelay]);
    
    if (dataRead[cancelled] == "1") _cancelled = true;
    else _cancelled = false;
    
    if (dataRead[realETime].empty()) _realElapsedTime = -1000;
    else _realElapsedTime = stoi(dataRead[realETime]);
}

string Flight::getIATAAirline() const {
    
    return _IATACodeAirline;
}

string Flight::getIATAAirport(char type) const {
    
    if (type == 'D') return _IATACodeAirportDep;
    else return _IATACodeAirportArr;
}

int Flight::getDelay(char type) const{
    
    if(type == 'D') return _depDelay;
    else return _arrDelay;
}

Date Flight::getDate() const {
    
    return _date;
}
