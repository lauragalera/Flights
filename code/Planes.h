//Laura Galera Alfaro
//u1959173
//practica final

/// @file Planes.h
/// @brief Classe Planes

#ifndef PLANES_H
#define PLANES_H

#include <iostream>
#include <string>
#include <vector>
#include<map>
#include "Plane.h"

using namespace std;

/** @class Planes
    @brief Un conjunt d'avions
    @author Laura Galera Alfaro
*/ 
class Planes {
public:
    
    ///@brief Crea un conjunt d'avions buit.
    Planes();
    
    ///@brief El conjunt d'avions és una copia de \p p.
    Planes(const Planes &p);
    
    ///@brief Allibera memòria.
    ~Planes();
    
    ///@brief El conjunt d'avions és una copia de \p p.
    Planes& operator=(const Planes& p);
    
    /** @brief Afageix un avió al conjunt d'avions si aquest és vàlid.
     *  @pre   La mida del vector \p dataRead és 3. Les dades estan ordenades
     *         de la següent manera:
     *              \verbatim
     *              NomAvio, IATAAvio, ICAOAvio
     *              \endverbatim
     *  @post  Donat un vector de strings amb els valors d'un avió, es crea l'avió i s'afageix al
     *         conjunt d'avions després de verifica que es pot identificar pel codi IATA, és a dir,
     *         que no hi ha multiples avions amb el mateix codi IATA, ni aquest camp es NULL.
     */
    void addPlane(const vector<string> &dataRead);
    
    /** @brief Retorna cert si tots els avions de la llista pertanyen al conjunt.
     *  @pre   Cert.
     *  @post  Donada una llista amb codis IATA d'avions, retorna cert si tots els avions de la llista
     *         pertanyen al conjunt d'avions.
     */
    bool planesUsedExist(const list<string> &IATAPlanes) const;
    
    /** @brief Retorna el nom de l'avió.
     *   @pre  L'avió amb aquest codi IATA ha d'existir segur dins del conjunt.
     *   @post Donat el codi IATA de l'avió, retorna el nom d'aquest.
     */
    string getNameSpecificPlane(string IATA) const;
    
    /** @brief Neteja les dades que poden generar ambigüitats per a identificar avions, ja que el seu
     *         codi IATA està repetit.
     *  @pre  Cridar sempre després de finalitzar la lectura d'un conjunt d'avions.
     *  @post S'han eliminat els avions del conjunt que no poden ser identificats per codi IATA,
     *         ja que el codi IATA és compartit amb altres avions.
     */
    void finishReading();
    
private:
    map<string, Plane *> _mapIATAPlanes; /**< Map que té com a clau els codis IATA dels avions i a la descripció de cada clau hi ha un punter
                                          *   que apunta al seu respectiu avió. No es guardaran avions que no puguin ser identificats pel codi
                                          *  IATA.
                                          */
    set<string> _IATARepeated;           /**< Set que conté els avions que no es poden guardar en el map \p _mapIATAPlanes perquè el codi IATA
                                          *  no és identificatiu. S'utilitza al finalitzar la lectura de dades i es buit durant la resta de la
                                          *  vida de l'objecte.
                                          */
    
    ///@brief El conjunt d'avions és una copia de \p p.
    void copy(const Planes &p);
    
    ///@brief Allibera memòria.
    void free();
};

#endif /* PLANES_H */

