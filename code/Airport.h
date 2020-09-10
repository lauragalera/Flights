//Laura Galera Alfaro
//u1959173
//practica final

/// @file Airport.h
/// @brief Classe Airport
/// @author Laura Galera Alfaro

#ifndef AIRPORT_H
#define AIRPORT_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** @class Airport
    @brief Un aeroport
    @author Laura Galera Alfaro
 */

struct InfoAirport{
    
    string name, city, country;
    
    ///@brief Operador relacional.
    bool operator<(const InfoAirport &r) const{
        return name < r.name;
    }
}; ///< Tupla que conté el nom de l'aeroport, la ciutat i el país on es troba.

class Airport {
public:
    
    /** @brief Crea un aeroport a partir d'un vector de strings.
     *  @pre La mida del vector \p dataRead és 14. Les dades estan
     *       en el següent ordre: 
                \verbatim
                ID, nom, ciutat, pais, IATA, ICAO, latitud, longitud, altitud,
                TimeZone, DST, databaseTZ, tipus, fontDades.
                \endverbatim
     *  @post Crea un nou aeroport a partir dels valors continguts al vector \p dataRead.
     *        Per a tot valor desconegut se li assigna un <b>\N</b> si es tracta d'una
     *        cadena de caràcters o un <b>-1000</b> si és un valor numèric.
     */
    Airport(const vector<string> &dataRead);

    /// @brief Retorna el valor del codi IATA d'aquest aeroport.
    string getIATA() const;

    /// @brief Retorna el valor del codi ICAO d'aquest aeroport.
    string getICAO() const;

    /// @brief Retorna el valor del codi ID d'aquest aeroport.
    int getID() const;
    
    /// @brif Retorna el valor del país d'aquest aeroport.
    string getCountry() const;
    
    /// @breif Retorna una tupla \c InfoAirport amb el nom de l'aeroport, la ciutat i el país.
    InfoAirport getNamePlace() const;

    /// @brief Retorna cert si el valor del codi IATA és conegut (entenent com a conegut un no Null), fals altrament.
    bool knownIATA() const;

    /// @brief Retorna cert si el valor del codi ICAO és conegut (entenent com a conegut un no Null), fals altrament.
    bool knownICAO() const;

private:

    int _ID;            ///< Codi ID de l'aeroport.
    string _name;       ///< Nom de l'aeroport.
    string _city;       ///< Ciutat on es troba l'aeroport.
    string _country;    ///< País o territori on s'ubica l'aeroport.
    string _IATACode;   ///< Codi Iata de 3 lletres de l'aeroport. Si es deconeix <b>\\N</b>.
    string _ICAOCode;   ///< Codi Icao de 4 lletres de l'aeroport. Si es deconeix <b>\\N</b>.
    float _latitude;    ///< Latitud en graus decimals. Negatiu és Sud, positiu és Nort.
    float _longitude;   ///< Longitud en graus decimals. Negatiu és Oest, positiu és Est.
    int _altitude;      ///< Alitud en peus.
    float _timeZone;    ///< Zona horària respecte UTZ. Si es desconeix <b>-1000</b>.
    char _DST;          ///< Horari d'estiu. E(Europa), A(US/Canada), S(South America), O(Australia), Z(New Zealand), N(none), U(unknown).
    string _databaseTz; ///< Zona horària en format tz. Si es desconeix <b>\\N</b>.
    string _type;       ///< Tipus, sempre aiport.
    string _source;     ///< Font de les dades.

    enum IndexData {
        ID, name, city, country, IATA, ICAO, latitude, longitude, altitude, timeZone, DST, TZ, type, source
    }; ///< Enumeració auxiliar usada al constructor per identificar què representa cada índex del vector \p dataRead.
};

#endif /* AIRPORT_H */

