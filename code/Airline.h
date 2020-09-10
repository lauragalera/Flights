//Laura Galera Alfaro
//u1959173
//practica final

/// @file Airline.h
/// @brief Classe Airline

#ifndef AIRLINE_H
#define AIRLINE_H

#include <iostream>
#include <string>
#include <string>
#include <vector>

using namespace std;

/** @class Airline
    @brief Una aerolínia
    @author Laura Galera Alfaro
 */

struct InfoAirline{
    
    string name, country;
}; ///< Tupla que conté el nom i el país de l'aerolínia.

struct AirlineType{
    
    string nameAirline;
    int natio;
    int inter;

    ///@brief Operador relacional.
    bool operator<(const AirlineType &r) const{
        return nameAirline < r.nameAirline;
    }
};///< Tupla que conté el nom de l'aerolínia, el seu total de rutes nacionals i el seu total de rutes internacionals.

class Airline {
public:
    
    /** @brief Crea una aerolínia a partir d'un vector de strings.
     *  @pre La mida del vector \p dataRead és 8. Les dades estan 
     *       en el següent ordre: 
             \verbatim
             ID, nom, alies, codiIATA, codiICAO, callsing, país, activa.
             \endverbatim
     *  @post Crea una nova aerolínia a partir dels valors continguts al vector \p dataRead.
     *        Per a tot valor desconegut se li assigna un <b>\\N</b>.
     */
    Airline(const vector<string> &dataRead);
    
    ///@brief Retorna el valor del codi ID de l'aerolínia.
    int getID() const;
    
    ///@brief Retorna cert si es coneix el valor del codi IATA, fals altrament.
    bool knownIATA() const;
    
    ///@brief Retorna cert si es coneix el valor del codi ICAO, fals altrament.
    bool knownICAO() const;
    
    ///@brief Retorna el valor del codi IATA.
    string getIATA() const;
    
    ///@brief Retorna el valor del codi ICAO.
    string getICAO() const;
    
    ///@brief Retorna el valor del país on l'aerolínia s'ubica.
    string getCountry() const;
    
    ///@brief Retorna el valor del nom de l'aerolínia.
    string getName() const;
    
    ///@brief Retorna cert si l'aerolínia està activa, fals altrament.
    bool isActive() const;

private:

    int _ID;            ///< Codi ID de l'aerolínia.
    string _name;       ///< Nom de l'aerolínia.
    string _alias;      ///< Alias de l'aerolinia. Si no en té o es desconeix <b>\\N</b>.
    string _IATACode;   ///< Codi IATA de 2 lletres. Si és desconeix <b>\\N</b>.
    string _ICAOCode;   ///< Codi ICAO de 3 lletres. Si és desconeix <b>\\N</b>.
    string _callsign;   ///< Nom de cirda de l'aerolínia. Si no en té o es desconeix cadena buida.
    string _country;    ///< País o territori on l'aerolínia s'ubica. Si es desconeix cadena buida.
    bool _isActive;     ///< Cert si l'aerolínia està activa, fals altrament.

    enum IndexData {
        ID, name, alias, IATA, ICAO, callsign, country, active
    }; ///< Enumeració auxiliar usada al constructor per identificar què representa cada índex del vector \p dataRead. 
};

#endif /* AIRLINE_H */

