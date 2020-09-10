//Laura Galera Alfaro
//u1959173
//practica final

/// @file Route.h
/// @brief Classe Route

#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

/** @class Route
    @brief Una ruta
    @author Laura Galera Alfaro
 */

class Route {
public:

    /** @brief Crea una ruta a partir d'un vector de strings.
     *  @pre La mida del vector \p dataRead és 9. Les dades venen
     *       ordenades de la forma següent: 
                    \verbatim
                    IATAAerolinia, codiIDAerolinia, IATAAeroportSortida,
                    codiIDAeroportSortida, IATAAeroportArribada, codiIDAeroportArribada,
                    codeShare, parades, equipament.
     *              \endverbatim
     *   @post Crea un nova ruta a partir dels valors continguts al vector \p dataRead.
     *         El codi ID aerolinia i els codis ID aeroport són <b>-1</b> si el valor
     *         és desconegut. 
     */
    Route(const vector<string> &dataRead);
    
    ///@brief Retorna el codi ID de l'areolínia que opera aquesta ruta.
    int getIDAirline() const;
    
    ///@brief Retorna el codi IATA o ICAO de l'aerolínia que opera aquesta ruta.
    string getIATAICAOAirline() const;
    
    ///@brief Retorna el codi ID de l'aeroport de sortida o destí.
    ///@pre \p Type ha de ser <b>D</b> o <b>A</b>.
    ///@post Retorna el codi ID de l'aeroport de sortida si \p type és <b>D</b> i el de destí si és <b>A</b>.
    int getIDAirport(char type) const;
    
    ///@brief Retorna el codi IATA o ICAO de l'aeroport de sortida o destí.
    ///@pre \p Type ha de ser <b>D</b> o <b>A</b>.
    ///@post Retorna el codi IATA o ICAO de l'aeroport de sortida si \p type és <b>D</b> i el de destí si és <b>A</b>.
    string getIATAICAOAirport(char type) const;
    
    ///@brief Retorna una list de strings amb els codis IATA dels avions usats en aquesta ruta.
    list<string> getEquipment() const;

private:

    string _IATAICAOAirline;    ///< 2 lletres si és el codi IATA, 3 lletres si és el codi ICAO.
    int _airlineID;             ///< Codi ID de l'aerolínia. Si es desconeix <b>-1</b>.
    string _sourceAirport;      ///< Codi IATA de l'aeroport de sortida si té 3 lletres, codi ICAO si en té 4. 
    int _IDsourceAirport;       ///< Codi ID de l'aerport de sortida. Si es desconeix <b>-1</b>.
    string _destinationAirport; ///< Codi IATA de l'aeroport d'arribada si té 3 lletres, codi ICAO si en té 4.
    int _IDdestinationAirport;  ///< Codi ID de l'aeroport d'arribada. Si es desconeix <b>-1</b>.
    bool _codeShare;            ///< Cert si té un codeshare(no es operada per un airline), fals altrament.
    int _stops;                 ///< Número d'escales de la ruta.
    list<string> _equipment;    ///< Llista amb el codi IATA dels avions utilitzats en la ruta.

    enum IndexData {
        IATAICAOAirline, IDAirline, IATAICAOAirportS, IDAirportS, IATAICAOAirportD, IDAirportD, codeShare, stops, flightsUsed
    }; ///< Enumeració auxiliar usada al constructor per identificar què representa cada index del vector \p dataRead. 
};

#endif /* ROUTE_H */

