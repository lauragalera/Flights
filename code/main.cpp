//Laura Galera Alfaro
//u1959173
//pràctica 1

/**
 *@file main.cpp
 *@brief part principal del programa
 *@author Laura Galera Alfaro
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

#include "utils.h"
#include "Airports.h"
#include "Airlines.h"
#include "Routes.h"
#include "Planes.h"
#include "Flights.h"

using namespace std;

enum F {file_Airports, file_Airlines, file_Planes, file_Routes, file_Flights}; //< enumeració auxiliar usada per identificar què representa cada fitxer llegit a la funció \p readAllData. 

/**
 * @brief Es llegeixen les dades dels fitxers a partir de les rutes entrades per teclat i es processen
 *        per tal de guardar aquelles que seran útils per les posteriors consultes.
 * @pre   La seqüència de fitxers és:
 *        aeroports, aerolínies, avions, rutes i vols. El format de les dades es caracteritza per ser de 
 *        la següent manera:
 * 
 *          \verbatim
            Aeroport: ID, nom, ciutat, pais, IATA, ICAO, latitud, longitud, altitud, TimeZone, DST, databaseTZ, tipus, fontDades.
            g.e: 12,"Red Deer Regional Airport","Red Deer Industrial","Canada","YQF","CYQF",52.18220138549805,-113.89399719238281,2968,-7,"A","America/Edmonton","airport","OurAirports"
   
            Aerolínia: ID, nom, alies, codiIATA, codiICAO, callsing, pais, activa.
            g.e: 12,"611897 Alberta Limited",\\N,"","THD","DONUT","Canada","N"
   
            Avió: NomAvio, IATAAvio, ICAOAvio
            g.e: "Airbus A330-200","332","A332"
   
            Ruta: IATAAerolinia, codiIDAerolinia, IATAAeroportSortida, codiIDAeroportSortida, IATAAeroportArribada, codiIDAeroportArribada, codeShare, parades, equipament.
            g.e: 2B,410,SVX,2975,OVB,4078,,0,CR2
   
            Vol: any, mes, dia, diaMes, IATAAerolínia, Numvol, IATAAeroportSortida, ciutatAeroportSortida, IATAAeroportArribada, ciutatAeroportArribada, horaEsperadaSortida, horaSortida, 
            retardSortida, horaEsperadaArribada, horaArribada, retardArribada, cancelat, duradaEsperadaVol, duradaVol, distancia.
            g.e:2019, 6, 27, 4, B6, 333, BOS, Boston, MA, SFO, San Francisco, CA, 2138, 2151, 13, 110, 103, -7, 0, 392, 372, 2704
            \endverbatim
 * 
 * @post Es llegeixen les dades referents als cinc primers fitxers. Després de tractar aquestes dades, ja que cal assegurar 
 *       que cap d'elles viola la precondició de tenir camps identificatius únics, llegibles i que permetin enlleçar i verificar
 *       les dades amb altres classes (e.g Airlines i Routes), es guarden als objectes de tipus \c Airports, \c Airlines, \c Planes,
 *       \c Routes i \c Vols.
 */
void readAllData(Airports &aeroports, Airlines &aerolinies, Routes &rutes, Planes &avions, Flights &vols);

///@brief mostra la consulta amb els valors del vector \p dataRead.
void showQuery(const vector<string> &dataRead);

 /**@brief Mostra la sortida de la consulta <b>"DEPARTURE DELAY AIRPORTS"</b> i <b>"DEPARTURE ARRIVAL AIRPORTS"</b>.
  * @pre   Cert.
  *     @param v és un vector que conté parelles \c int i \c InfoAirport, ordenades decreixentment
  *            pel primer valor.
  *     @param dataRead, un vector de strings, guarda la consulta feta.
  *     @param option és un string que bé prèn el valor <b>departure</b> o <b>arrival</b>, depenent de la consulta
  *            a mostrar.
  * @post  Mostra la sortida referent a les consultes tres i quatre: la data i el contingut del vector \p v,
  *        acompanyats d'un missatge elaborat. 
  */
void showQueryAirportsDelay(const vector<pair<int, InfoAirport>> &v, const vector<string> &dataRead, string option);

/**@breif Mostra la sortida de la consulta <b>"DEPARTURE DELAY AIRLINES"</b> i <b>"ARRIVAL DELAY AIRLINES</b>
 * @pre   Cert
 *      @param v és un vector que conté parelles \c int i \c InfoAirline, ordenat decreixentment
 *             pel primer valor.
 *      @param dataRead, un vector de strings, guarda la consulta feta.
 *      @param option és un string que bé prèn valor <b>departure</b> o <b>arrival</b>, depenent de la consulta
 *             a mostrar.
 * @post  Mostra la sortida referent a les consultes cinc i sis: l'acumulació de retards juntament amb la informació
 *        de l'aerolinia, tot guardat a \p v. 
 */
void showQueryAirlinesDelay(const vector<pair<int, InfoAirline>> &v, const vector<string> &dataRead, string option);


/**@brief Realitza un seguit de consultes sobre les dades llegides anteriorment.
 * @pre   El fitxer, la ruta del qual és entrada per teclat, ha de contenir consultes que es tractaran a partir de les dades emmagatzemades
 *        en els parametres d'entrada \p aeroports, \p aerolinies, \p rutes, \p avions i \p vols.\n
 *        Les consultes són del tipus: 
 *           \verbatim
             "COUNT ROUTES"
             "MOST USED PLANE",IATA
             "DEPARTURE DELAY AIRPORTS",n,year,month,day_of_month
             "ARRIVAL DELAY AIRPORTS",n,year,month,day_of_month
             "DEPARTURE DELAY AIRLINES",n
             "ARRIVAL DELAY AIRLINES",n
             "DAY WITH MORE DELAYS",IATA_1,...,IATA_N    
            \endverbatim
 *
 * @post Mostra el resultat de totes les consultes llegides, i un respectiu error si no s'ha pogut realitzar alguna d'elles:\n
 *
 *       Per la primera consulta es llisten totes les aerolínies juntament amb quantes rutes nacionals i internacionals han operat.
 *       A la segona es mostra l'avió més utilitzat per determinada companyia.
 *       Per la tercera, donada una data, es mostren els n aeroports amb més retards de sortida. Tots els aeroports si n=0.
 *       Amb el mateix concepte que la tercera, la quarta consisteix en mostrar els n aeroports amb més retards d'arribada en una data. Tots els aeroports si n=0.
 *       A la cinquena es llisten les n aerolínies amb més retards de sortida. Totes si n=0.
 *       La sisena es basa en el mateix que la cinquena: es llisten les n aerolínies amb més retards d'arribada. Totes si n=0.
 *       Per últim, donat un subconjunt d'aeroports s'indica la data en què hi ha hagut més retards entre els vols efectuats en aquests aeroports.
 */
void manageQueries(const Airports &aeroports, const Airlines &aerolinies, const Routes &rutes, const Planes &avions, const Flights &vols);

/** @pre  S'entren per teclat les rutes a sis fitxers i, en aquest ordre, si troben un conjunt de dades sobre aeroports,
 *        aerolínies, avions, rutes, vols i consultes a realitzar amb tota la informació llegida dels esmentats fitxers. 
 *        Les consultes de l'últim fitxer s'especifiquen a la funció \g manageQueries.
 *  @post Llegeix totes les dades del fitxer d'entrada, refinant la informació quan aquesta és llegida per tal de fer possible l'execució de les consultes,
 *        i mostra les peticions referents a cadascuna de les consultes fins al final de fitxer. 
 */
int main(int argc, char** argv) {
    Airports aeroports;
    Airlines aerolinies;
    Routes rutes;
    Planes avions;
    Flights vols;
    
    readAllData(aeroports, aerolinies, rutes, avions, vols);
    manageQueries(aeroports, aerolinies, rutes, avions, vols);
}

/***********************************/
/*FUNCIONS I ACCIONS: IMPLEMENTACIÓ*/
/***********************************/

void readAllData(Airports &aeroports, Airlines &aerolinies, Routes &rutes, Planes &avions, Flights &vols) {
    
    string whichFileRead[] = {"airports", "airlines", "planes", "routes", "flights"};
    for (int i = 0; i < 5; i++) { //recorregut pels 5 fitxers
        
        string fileName;
        cin >> fileName;
        ifstream currentFile;
        openFile(currentFile, fileName); //obrim el fitxer
        cout << "Loading " << whichFileRead[i] << "..." << endl;
        vector<string> dataRead;
        
        if (i == 1 or i == 4) getNextLineAndSplitIntoTokens(currentFile); //ignorem el header d'aerolínies i vols
        dataRead = getNextLineAndSplitIntoTokens(currentFile);
        while (!currentFile.eof()) { //llegim totes les dades del fitxer
            switch (i) { //per cada línia, processem la informació a la classe indicada
                case file_Airports:
                    aeroports.addAirport(dataRead);
                    break;
                case file_Airlines:
                    aerolinies.addAirline(dataRead);
                    break;
                case file_Planes:
                    avions.addPlane(dataRead);
                    break;
                case file_Routes:
                    rutes.addRoute(dataRead, aeroports, aerolinies, avions);
                    break;
                case file_Flights:
                    vols.addFlight(dataRead, aeroports, aerolinies);
                    break;
            }
            dataRead = getNextLineAndSplitIntoTokens(currentFile);
        }
        
        if (i == 1) aerolinies.finishReading(); //refinament de les dades a aerolínies
        else if (i == 2) avions.finishReading(); //refinament de les dades a avions
        currentFile.close(); //tanquem el fitxer
    }
}

void showQuery(const vector<string> &dataRead){
    
    cout << "--------------------------------------------------------------------------------" << endl;
    cout<<"Query: ";
    vector<string>::const_iterator it = dataRead.begin();
    while(it!=dataRead.end()-1){ //recorrem el vector fins el penúltim element
        cout<<*it<<", ";
        it++;
    }
    cout<<*it<<endl; //mostrem l'últim element
    cout<<endl;
}

void showQueryAirportsDelay(const vector<pair<int, InfoAirport>> &v, const vector<string> &dataRead, string option) {
    
    if(stoi(dataRead[1]) != 0 and v.size()<stoul(dataRead[1])) cout<<"There are less airports than what you expected. \n\n";
    cout << "The ";
    if (stoi(dataRead[1]) != 0) cout << v.size()<<" ";
    cout << "airports with more " << option << " delays on " << dataRead[2] << "/" << dataRead[3] << "/" << dataRead[4] << " are: \n\n";
    for (pair<int, InfoAirport> i : v)
        cout << "Accum. " << option << " delays: " << i.first << " - " << i.second.name << ", " << i.second.city << ", " << i.second.country << endl;
}

void showQueryAirlinesDelay(const vector<pair<int, InfoAirline>> &v, const vector<string> &dataRead, string option) {
    
    if(stoi(dataRead[1]) != 0 and v.size()<stoul(dataRead[1])) cout<<"There are less airlines than what you expected. \n\n";
    cout << "The ";
    if (stoi(dataRead[1]) != 0) cout << v.size()<<" ";
    cout << "airlines with more " << option << " delays are: \n\n";
    for (pair<int, InfoAirline> i : v)
        cout << "Accum. " << option << " delays: " << i.first << " - " << i.second.name << ", " << i.second.country << endl;
}

void manageQueries(const Airports &aeroports, const Airlines &aerolinies, const Routes &rutes, const Planes &avions, const Flights &vols) {
    
    string fileName;
    cin >> fileName;
    ifstream currentFile;
    openFile(currentFile, fileName); //obertura del fitxer
    cout << "Loading queries..." << endl;
    vector<string> dataRead = getNextLineAndSplitIntoTokens(currentFile);
    
    while (!currentFile.eof()) { //llegim totes les consultes del fitxer
        showQuery(dataRead);
        string query = dataRead[0];
        
        /*PRIMERA CONSULTA*/
        if (query == "COUNT ROUTES") {
            set<AirlineType> countRoutes = rutes.countRoutesByAirline(aerolinies, aeroports);
            cout << right << setw(6) << "NAT." << right << setw(8) << "INTL." <<setw(50) << "AIRLINE" << endl; //Mostra la consulta
            for (AirlineType t : countRoutes) {
                cout << right << setw(6) << t.natio << right << setw(8) << t.inter << setw(50) << t.nameAirline << endl;
            }
            
        /*SEGONA CONSULTA*/ 
        } else if (query == "MOST USED PLANE") {
            try {
                map<string, list < string>> mostUsedPlane = rutes.mostUsedPlane(dataRead[1], aerolinies, avions);

                if (mostUsedPlane.size() == 0) cout << "The airline " << dataRead[1] << " has not used any plane" << endl; //L'aerolínia existeix però no ha fet vols
                else { //Mostra la consulta
                    for (pair<string, list < string >> l : mostUsedPlane) { 
                        cout << "The most used plane by \"" << l.first << "\" is/are \"";
                        for (string s : l.second)
                            cout << s << "\" ";
                        cout << endl;
                    }
                }
            } catch (const char *message) { //ERROR
                cout << "ERROR: " << dataRead[1] << " is an unknown IATA airline code."<<endl; 
            }
        
        /*TERCERA CONSULTA*/
        } else if (query == "DEPARTURE DELAY AIRPORTS") {
            try {
                vector<pair<int, InfoAirport>> airportsDelayD = vols.mostDelayedAirports(dataRead, aeroports, 'D');
                showQueryAirportsDelay(airportsDelayD, dataRead, "departure"); //Mostra la consulta
            } catch (const char *message) { //ERROR
                cout << "ERROR: not registed date" << endl;
            }

        /*QUARTA CONSULTA*/
        } else if (query == "ARRIVAL DELAY AIRPORTS") {
            try {
                vector<pair<int, InfoAirport>> airportsDelayA = vols.mostDelayedAirports(dataRead, aeroports, 'A');
                showQueryAirportsDelay(airportsDelayA, dataRead, "arrival"); //Mostra la consulta
            } catch (const char *message) { //ERROR
                cout << "ERROR: not registed date" << endl;
            }

        /*CINQUENA CONSULTA*/
        } else if (query == "DEPARTURE DELAY AIRLINES") {
            vector<pair<int, InfoAirline>> airlineDelayedD = vols.mostdelayedAirlines(dataRead, aerolinies, 'D');
            showQueryAirlinesDelay(airlineDelayedD, dataRead, "departure"); //Mostra la consulta

        /*SISENA CONSULTA*/
        } else if (query == "ARRIVAL DELAY AIRLINES") {
            vector<pair<int, InfoAirline>> airlineDelayedA = vols.mostdelayedAirlines(dataRead, aerolinies, 'A');
            showQueryAirlinesDelay(airlineDelayedA, dataRead, "arrival"); //Mostra la consulta

        /*SETENA CONSULTA*/
        } else if (query == "DAY WITH MORE DELAYS") {
            list<pair<Date, int>> daysDelay = vols.daysMoreDelay(dataRead, aeroports);
            if (daysDelay.size() == 0) cout << "No flights, no delays" << endl; //existeix l'aeroport, però no ha tingut cap vol
            else { //Mostra la consulta
                cout << "The day/s with more delays in the given airports has/have been " << endl;
                for (list<pair < Date, int>>::const_iterator it = daysDelay.begin(); it != daysDelay.end(); it++) {
                    cout << it->first << " with total departure and arrival delays = " << it->second << endl;
                }
            }

        /*CONSULTA DESCONEGUDA*/
        } else {
            cout << "ERROR: unknown Query" << endl;
        }
        dataRead = getNextLineAndSplitIntoTokens(currentFile);
    }
    currentFile.close(); //tanquem el fitxer
}