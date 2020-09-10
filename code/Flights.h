//Laura Galera Alfaro
//u1959173
//practica final

/// @file Flights.h
/// @brief Classe Flights

#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <iostream>
#include <string>
#include <vector>

#include <map>
#include <list>

#include "Flight.h"
#include "Airlines.h"
#include "Airports.h"

/** @class Flights
    @brief Un conjunt de vols
    @author Laura Galera Alfaro
 */

class Flights {
public:

    ///@brief Crea un conjunt de vols buit.
    Flights();

    ///@breif Conjunt de vols és una copia de \p f.
    Flights(const Flights &f);

    ///@brief Allibera memòria.
    ~Flights();
    
    ///@brief Conjunt de vols és una copia de \p f.
    Flights& operator=(const Flights& f);
    

    /** @brief Afageix un vol al conjunt de vols sempre i quan aquest sigui vàlid.
     *  @pre   La mida del vector \p dataRead és 20. Les dades estan en el següent ordre:
     *          \verbatim
                    any, mes, dia, diaMes, IATAAerolínia, Numvol, IATAAeroportSortida, ciutatAeroportSortida,
                    IATAAeroportArribada, ciutatAeroportArribada, horaEsperadaSortida,horaSortida, retardSortida,
                    horaEsperadaArribada, horaArribada, retardArribada, cancelat, duradaEsperadaVol, duradaVol
                    distancia.
               \endverbatim
     *  @post   Donat un vector de strings amb els valors d'un vol, es crea el vol i s'afageix al conjunt de vols
     *          després de verifica si aquell vol és valid, comprovant si existeix la companyia aeria que l'opera i
     *          tant l'aeroport de sortida com el d'arribada.
     */
    void addFlight(const vector<string> &dataRead, const Airports &aeroports, const Airlines &aerolinies);
    
    /** @brief  Retorna un vector de n parelles, ordenat decreixentment pel primer, amb el primer argument la suma de retards
     *          d'arribada o de sortida dels vols i com a segon una tupla \g InfoAirport fent referència a l'aeroport.
     *  @pre    El vector \p dataRead conté quants aeroports llistar (0 per tots), any, mes, dia del mes. \p type pot ser <b>'D'</b>,
     *          per indicar retards de sortida, o <b>'A'</b> per indicar retards d'arribada.
     *          Si la data no existeix és llença una excepció.
     *  @post   Retorna un vector de n parelles on el primer valor representa la suma de retards de sortida o bé d'arribada -depenent
     *          del valor de \p type- de tots els vols que té un aeroport en la data indicada a \p dataRead. L'aeroport ve identificat
     *          a partir de la tupla \c InfoAirport amb el nom, la ciutat i el país, ocupant el segon lloc de la parella. El vector està
     *          ordenat de forma decreixent pel primer valor de la parella i es retornen tots o els n primers aeroports amb més retards.
     */
   vector<pair<int, InfoAirport>> mostDelayedAirports(const vector<string> &dataRead, const Airports & airports, char option) const;
    
    /** @brief  Retorna un vector de n parelles, ordenat decreixentment pel primer, amb el primer argument la suma de retards
     *          d'arribada o sortida dels vols i com a segon una tupla \c InfoAirline fent referència a l'aerolínia.
     *  @pre    El vector \p dataRead conté quantes aerolínies llistar (0 per totes). \p type és <b>'D'</b> per indicar retards de sortida
     *          o <b>'A'</b> per indicar retards d'arribada.
     *  @post   Retorna un vector de n parelles on el primer valor representa la suma de retards de sortida o bé d'arribada -depent del valor
     *          de \p type- de tots els vols que té una aerolínia. L'aerolínia ve identificada a partir de la tupla \c InfoAirline on hi
     *          consta el nom i el país de l'aerolínia, ocupant el segon lloc de la parella. El vector està ordenat
     *          decreixentment pel primer valor de la parella i es retornen totes o les n primeres aerolínies amb retards.
     */
    vector<pair<int, InfoAirline>> mostdelayedAirlines(const vector<string> &dataRead, const Airlines & airlines, char option) const;
    
    /** @brief  Retorna una llista de n parelles on el primer valor fa referència a la data i el segon a la suma de retards, tant de
     *          sortida com d'arribada, en aquella data que han tingut un subconjunt d'aeroports.
     *  @pre    El vector \p dataRead conté els n codis IATA del subconjunt d'avions.
     *          Si un dels codis IATA no existeix a \p airports es mostra missatge d'error.
     *  @post   Retorna una llista de parelles on el primer valor representa la data i el segon la suma de retards, tant de sortida
     *          com d'arribada, del subconjunt d'aeroports. Sempre es retorna la parella amb el màxim nombre de retards, i en cas 
     *          d'empat totes aquelles amb el mateix retard.
     */
    list<pair<Date, int>> daysMoreDelay(const vector<string> &dataRead, const Airports & airports) const;

private:

    map<Date, list<Flight*>> _mapDate;          /**< Map que té com a clau una data i a cada descripció s'hi troba una llista que guarda punters a tots els vols 
                                                 *   realitzats en aquella data.
                                                 */
    map<string, list<Flight*>> _mapIATAAirline; /**< Map que té com a clau el codi IATA de l'aerolínia i com a descripció una llista de punters a tots els vols
                                                 *  que han sigut operats per aquella aerolínia.
                                                 */
    map<string, list<Flight*>> _mapIATAAirport; /**< Map que té com a clau el codi IATA de l'aeroport i com a descripció una llista amb punters a tots els vols
                                                 *  que s'han realitzat en aquell aeroport, sense distingir si era l'aeroport de sortida o el d'arribada.
                                                 */

    /** @brief Afageix un vol a totes les estructures de dades del conjunt.
     *  @pre   El vol a inserir està verificat; existeixen la companyia aeria i els aeroports.
     *  @post  S'insereix el punter, que apunta a un nou vol, a cadascuna de les estructures de la classe: per data al \c _mapData,
     *         per codi IATA de l'aerolínia al \g _mapIATAAirlines i pels codis IATA de l'aeroport de sortida i el d'arribada al map
     *         \g _mapIATAAirport (s'inserirà dos cops en aquest últim cas, un pel d'arribada i un altre pel de sortida).
     */
    void includeToAllStructures(Flight * newFlight);

    ///@brief El conjunt d'avions és una copia de \p f.
    void copy(const Flights &f);

    ///@brief Allibera memòria.
    void free();
};

#endif /* FLIGHTS_H */

