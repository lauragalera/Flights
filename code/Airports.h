//Laura Galera Alfaro
//u1959173
//practica final

/// @file Airports.h
/// @brief Classe Airports

#ifndef AIRPORTS_H
#define AIRPORTS_H


#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include "Airport.h"

using namespace std;

/** @class Airports
    @brief Un conjunt d'aeroports
    @author Laura Galera Alfaro
*/

class Airports {
public:
    
    ///@brief Conjunt d'aeroports buit.
    Airports();
    
    ///@brief Aquest conjunt d'aeroports és una copia del conjunt \p a.
    Airports(const Airports &a);
    
    ///@brief Allibera memòria.
    ~Airports();
    
    ///@brief Aquest conjunt d'aeroports és una copia del conjunt \p a.
    Airports& operator=(const Airports& a);
    
    /** @brief  Afageix un aeroport al conjunt d'aeroports.
     *  @pre    La mida del vector \p dataRead és 14. Les dades estan en el
     *          següent format:
     *              \verbatim
                     ID, nom, ciutat, pais, IATA, ICAO, latitud, longitud, altitud,
                     TimeZone, DST, databaseTZ, tipus, fontDades.
                     \endverbatim
     *          El codi ID, el codi IATA i el codi ICAO han de ser identificatius per
     *          cada aeroport, és a dir, no pot haver-hi dos aeroports amb algun dels
     *          camps esmentats iguals entre els dos. No obstant, si és possible no
     *          conèixer el codi IATA o ICAO d'un aeroport, però sempre cal proporcinar el ID.
     *  @post   Crea un aeroport a partir dels valors del vector \p dataRead i l'afageix al
     *          conjunt d'aeroports. El codi ID és identificatiu per a cada aeroport. També 
     *          ho és el codi IATA i ICAO si es disposa d'ells.
     */
    void addAirport(const vector<string> &dataRead);
    
    /** @brief  Comprova a partir del ID, el codi IATA o el codi ICAO si existeix l'aeroport
     *          dins el conjunt.
     *  @pre    \p ID és \b -1 si es desconeix. Si es disposa del dos parametres, aquests han de
     *          fer referència al mateix aeroport.
     *  @post   Retorna cert si dins del conjunt hi ha una aeroport que tingui com a ID el valor
     *          d'entrada \p ID. Si aquest és desconegut, s'intenta identificar per codi IATA o ICAO.
     *          Es retorna fals quan per cap dels paràmetres s'ha pogut comprovar l'existència de
     *          l'aeroport dins el conjunt.
     */
    bool airportExists(int IDairport, string IATAICAOairport) const;
    
    /** @breif  Retorna cert si dos aeroports, un de sortida i l'altre d'arribada, estan ubicats
     *          al mateix país d'una aerolínia, fals altrament.
     *  @pre    \p IDAirportSource i \p IDAirportDeparture són \b -1 si es desconeixen; pel contrari,
     *          IATAICAO sempre seran valors proporcionats, ja que s'usen com a recolzament per a
     *          identificar els aeroports en cas de no disposar de ID.
     *          Els aeroports han d'existir dins el conjunt d'aeroports.
     *          \p countryAirline és el país amb el que es compara; país de l'aerolinia
     *  @post   Retorna cert si els dos aeroports, identificats pel codi ID com a primera opció o
     *          pel codi IATAICAO com a segona, es troben al mateix país que l'aerolínia, fals altrament.
     */
    bool isNationalAirports(int IDAirportSource, string IATAICAOAirportSource, int IDAirportDeparture, string IATAICAOAirportDeparture, string countryAirline) const;
    
    /** @brief Retorna una tupla de tipus \c InfoAirport amb el nom i país de l'aeroport.
     *  @pre   \p IATA és el codi IATA d'un aeroport que es troba dins el conjunt.
     *  @post  Retorna una tupla de tipus \c InfoAirport amb el nom i el país de 
     *         l'aeroport que té com a codi IATA \p IATA.
     */
    InfoAirport gatherInfoAirport(string IATA) const;
    
private:
    
    map<int, Airport *> _mapIDAirports;      /**< map de punters a objectes de tipus \c Airport on la clau és el codi ID i a la seva descripció hi
                                              *   ha un punter a l'aeroport que té aquest codi ID.
                                              */
    map<string, Airport *> _mapIATAAirports; /**< map de punters a objectes de tipus \c Airport on la clau és el codi IATA i a la seva descripció hi
                                              *   un punter a l'aeroport que té aquest codi IATA. Fer notori que només guarda aeroports amb un codi
                                              *  IATA conegut.
                                              */
    map<string, Airport *> _mapICAOAirports; /**< map de punters a objectes de tipus \c Airport on la clau és el codi ICAO i a la seva descripció hi
                                              *   ha un punter a l'aeroport que té aquest codi ICAO. Fer notori que només guarda aeroports amb un codi
                                              *  ICAO conegut.
                                              */
    
    /** @brief Retorna el país de l'aeroport que es pot identifica pels paràmetres d'entrada.
     *  @pre   \p IDAirport és \b -1 si es desconeix, per tant s'ha de diposar del codi IATA o
     *         ICAO -qualsevol dels dos a \p IATAICAOAirport- amb seguretat. 
     *         L'aeroport ha d'existir dins el conjunt d'aeroports. 
     *  @post  Retorna el país on es troba l'aeroport identificat pel ID \p IDAirport com a primera
     *         opció, o bé pel codi IATA o ICAO (\p IATAICAOAirport) si no es disposa de ID.
     */ 
    string getNameCountry( int IDAirport, string IATAICAOAirport) const;
    
    ///@brief Aquest conunt d'aeroports és una copia d' \p a.
    void copy(const Airports &a);
    
    ///@brief Allibera memòria.
    void free();
};

#endif /* AIRPORTS_H */

