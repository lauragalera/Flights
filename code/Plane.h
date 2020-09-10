//Laura Galera Alfaro
//u1959173
//practica final

/// @file Plane.h
/// @brief Classe Plane

#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** @class Plane
    @brief Un avió
    @author Laura Galera Alfaro
 */
class Plane {
public:

    /** @brief Crea un avió a partir d'un vector de strings.
     *  @pre La mida del vector \p dataRead és 3. Les dades estan
     *       en el següent ordre: 
                    \verbatim
                    NomAvio, IATAAvio, ICAOAvio
                    \endverbatim
     *  @post Crea un nou avió a partir dels valors continguts al vector \p dataRead.
     *        <b>\\N</b> per qualsevol camp desconegut.
     */
    Plane(const vector<string> &dataRead);
    
    ///@brief Retorn el valor del codi IATA de l'avió.
    string getIATA() const;
    
    ///@brief Retorna el nom de l'avió.
    string getName() const;
    
    ///@brief Retorna cert si es coneix el valor del codi IATA, fals altrament.
    bool knownIATA() const;

private:
    string _name;     ///< Nom de l'avió.
    string _IATACode; ///< Codi IATA de 3 lletres de l'avió. Si es desconeix <b>\\N</b>.
    string _ICAOCode; ///< Codi ICAO de 4 lletres de l'avió. Si es desconeix <b>\\N</b>.

    enum IndexData { 
        name, IATA, ICAO
    };///< Enumeració auxiliar usada al constructor per identificar què representa cada índex del vector \p dataRead. 
};

#endif /* PLANE_H */

