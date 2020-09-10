//Laura Galera Alfaro
//u1959173
//practica final

/// @file Airlines.h
/// @brief Classe Airlines

#ifndef AIRLINES_H
#define AIRLINES_H

#include <string>
#include <ostream>
#include <set>
#include <map>
#include <vector>
#include "Airline.h"

using namespace std;

/** @class Airlines
    @brief Un conjunt d'aerolinies
    @author Laura Galera Alfaro
*/

class Airlines {
public:
    ///@brief Crea un conjunt d'aerolínies buit.
    Airlines();
    
    ///@brief El conjunt d'aerolínies és una copia d' \p a.
    Airlines(const Airlines &a);
    
    ///@brief Allibera memòria.
    ~Airlines();
    
    ///@brief El conjunt d'aerolínies és una copia d' \p a.
    Airlines& operator=(const Airlines&a);
    
    /** @brief  Afageix una aerolínia vàlida al conjunt d'aerolínies.
     *  @pre    La mida del vector \p dataRead és 8. Les dades estan 
     *          en el següent ordre:
                   \verbatim
                   ID, nom, alies, codiIATA, codiICAO, callsing, país, activa.
                   \endverbatim
     *          El codi ID de l'aerolínia ha de ser únic i identificatiu. 
     *          Pel contrari, els codis IATA i ICAO poden repetir-se dins el conjunt. 
     *  @post   Donat un vector de strings amb els valors d'una aerolínia, crea l'aerolínia
     *          i l'afageix al conjunt d'aerolínies, respectant els següents criteris:
     *          -Tota aerolínia entrada és inclosa al conjunt d'aerolínies i 
     *           ha de disposar d'un codi ID únic (violació precondició en cas contrari). \n
     *          -Només serà possible identificar per codi IATA les aerolínies
     *           amb camp IATA diferent de <b>\N</b> i que no comparteixin el mateix
     *           IATA amb una o altres aerolínies. Si s'acceptarà però, com identificada
     *           per IATA, aquella aerolínia que sigui activa entre un conjunt d'aerolínies
     *           inactives, tenint totes el mateix IATA. \n
     *          -La identificació d'una aerolínia per ICAO és el mateix esquema que per IATA.
     *           Per tal de gestionar el segon i tercer punt, sempre, després d'afegir la 
     *           última aerolínia al conjunt, cal invocar la funció \g finishReading.
     */
    void addAirline(const vector<string> &dataRead);

    /** @brief  Comprova a partir del ID o del codi IATA o ICAO d'una aerolínia si aquesta 
     *          existeix en el conjunt.
     *  @pre   \p ID és <b>-1</b> si es desconeix. Si es disposa dels dos paràmetres, \p ID i
     *         \p IATAICAO han de fer referència a la mateix aerolínia.
     *  @post   Retorna cert si dins del conjunt hi ha una aerolínia que tingui com a ID el valor
     *          d'entrada \p ID. Si aquest és desconegut, s'intenta identificar per codi IATA o ICAO.
     *          Es retorna fals quan per cap dels paràmetres s'ha pogut comprovar l'existència de
     *          l'aerolínia dins el conjunt.  
    */
    bool airlineExists(int ID, string IATAICAO) const;
    
    /** @brief  Retorna una parella de valors on el primer indica el nom del país al qual pertany
     *          l'aerolínia i el segon el nom de l'aerolínia.
     *  @pre    \p ID és <b>-1</b> si es desconeix. Si es disposa dels dos paràmetres, \p ID i
     *          \p IATAICAO han de fer referència a la mateix aerolínia, però amb \p ID és suficient.
     *          L'aerolínia ha d'existir dins el conjunt d'aerolínies.
     *  @post   A partir d'un indentificador de la aerolínia, bé ID -primer identificador contemplat-
     *          o bé codi IATA o codi ICAO, es retorna una parella de valors; al primer hi consta el
     *          nom del país on s'ubica l'aerolínia i al segon el nom de l'aerolínia.
     */
    pair<string, string> lookForCountry(int ID, string IATAICAO) const;
    
    /** @brief Retorna una tupla \c InfoAirline amb el nom i el país de l'aerolínia identificada a partir de \p IATA.
     *  @pre   L'aerolínia amb codi \p IATA ha d'existir dins del conjunt.
     *  @post  Retorna una tupla \c InfoAirline, amb nom i país, de l'aerolínia que té per codi IATA el paràmetre
     *         d'entrada.
     */
    InfoAirline gatherInfoAirline(string IATA) const;
    
    /** @brief Retorna un punter a l'aerolínia del conjunt si existeix amb el codi IATA donat.
     *  @pre   Cert.
     *  @post  Retorna un punter a l'aerolínia del conjunt que te per codi IATA el paràmetre IATA, si no existeix
     *         retorna un punter a NULL
     */
    Airline * giveAirline(string IATA) const;
    
    /** @brief Neteja les dades que poden generar ambigüitats per a identificar aerolínies, ja que certs
     *         camps que haurien de ser usats com identificadors poden estar repetits.
     *   @pre  Cridar sempre després de llegir un conjunt d'aerolínies.
     *   @post S'han descartat com a identificadors de membres del conjunt el codi IATA o ICAO de certes 
     *         aerolínies llegides -les que comparteixen mateix codi IATA (ICAO), i no tenen una activa
     *         d'entre la resta d'inactives-, ja que no fer-ho provocaria ambigüitat per a futures tasques
     *         identificatives del conjunt.
     */
    void finishReading();
    
private:
    map<int, Airline *> _mapIDAirlines;         ///< Map que té com a camp clau el codi ID de l'aerolínia i a la seva descripció un punter a aquella aerolínia.
    map<string, Airline *> _mapIATAAirlines;    /**< Map que té com a camp clau el codi IATA de les aerolínies i a la seva respectiva descripció hi consta un 
                                                 *   punter que apunta a aquella aerolínia. Important, en aquesta estructura només hi apareixen les aerolínies
                                                 *   que sí es poden identificar per IATA, és a dir, no hi hauran les aerolínies amb codi IATA \b NULL,
                                                 *   tampoc aquelles que comparteixen codi IATA amb altres aerolínies que com ella estan actives, o dues o més
                                                 *   aerolínies inactives sense cap activa perquè fa impossible identificar-les per IATA.
                                                 */ 
    map<string, Airline *> _mapICAOAirlines;    /**< Map que té com a camp clau el codi ICAO de les aerolínies i a la seva descripció hi consta un punter que
                                                 *  apunta a la aerolínia. Important, en aquesta estructura només hi apareixen les aerolínies que sí es poden
                                                 *  identificar per ICAO, és a dir, no hi hauran les aerolínies amb codi ICAO \b NULL, tampoc aquelles que
                                                 *  comparteixen codi ICAO amb altres aerolínies que com ella estan actives, o dues o més aerolínies inactives
                                                 *  sense cap activa perquè fa impossible identificar-les per ICAO.
                                                 */
    set<string> _IATARepeated;                  /**< Set que conté les aerolínies que no es poden guardar en el map \g _mapIATAAirlines perquè el codi IATA no
                                                 *  és identificatiu. S'utilitza al finalitzar la lectura de dades i es buit durant la resta de la vida de 
                                                 * l'objecte.
                                                 */
    set<string> _ICAORepeated;                  /**< Set que conté les aerolínies que no es poden guardar en el map \p _mapICAOAirlines perquè el codi ICAO no
                                                 *  és identificatiu. S'utilitza al finalitzar la lectura de dades i es buit durant la resta de la vida de
                                                 *  l'objecte.
                                                 */
    
    /** @brief Afageix el punter de \p newAirline a l'estructura \g _mapIATAAirlines, després
     *         de contemplar un seguit de criteris per a l'acceptació o no del codi IATA com
     *         a identificador de l'aerolínia. Actualitza el set \g _IATARepeated.
     *  @pre  \p newAirline és un punter a una \g Airline llegida.
     *  @post Donat un punter a una nova Aerolínia \p newAirline, aquest s'afageix a l'estructura
     *        \g _mapIATAAirlines si:\n
     *        - No existeix al map cap amb aquell IATA.\n 
     *        - En cas de trobar que a \g _mapIATAAirlines hi ha una altra aerolínia amb el mateix IATA,
     *          la nova ocupa el lloc de la primera si la nova és activa a diferència de la primera que és
     *          inactiva. I si un cas el codi IATA es troba al set \g _IATARepeated, aquest s'elimina
     *          perquè sí hi haurà una aerolínia amb possibilitat d'identificar.\n
     *       També es modifica el set \g _IATARepeated afegint el codi IATA a eliminar si:\n
     *       - En cas de trobar que a \g _mapIATAAirlines hi ha una altra aerolínia amb el mateix IATA,
     *         les dues són inactives, nova i primera, o les dues són actives.
     */
    void manageIATARepeated(Airline * newAirline);
    
    /** @brief Afageix el punter de \p newAirline a l'estructura \g _mapICAOAirlines, després
     *         de contemplar un seguit de criteris per a l'acceptació o no del codi ICAO com
     *         a identificador de l'aerolínia. Actualitza el set \g _ICAORepeated.
     *  @pre  \p newAirline és un punter a una \g Airline llegida.
     *  @post Donat un punter a una nova Aerolínia \p newAirline, aquest s'afageix a l'estructura
     *        \g _mapICAOAirlines si:\n
     *        - No existeix al map cap amb aquell ICAO. 
     *        - En cas de trobar que a \g _mapIATAAirlines hi ha una altra aerolínia amb el mateix ICAO,
     *          la nova ocupa el lloc de la primera si la nova és activa a diferència de la primera que és
     *          inactiva. I si un cas el codi ICAO es troba al set \g _IATARepeated, aquest s'elimina
     *          perquè sí hi haurà una aerolínia amb possibilitat d'identificar.
     *       També es modifica el set \g _ICAORepeated afegint el codi IATA a eliminar si:\n
     *       - En cas de trobar que a \g _mapICAOAirlines hi ha una altra aerolínia amb el mateix ICAO,
     *         les dues són inactives, nova i primera, o les dues són actives.
     */
    void manageICAORepeated(Airline * newAirline);
    
    ///@brief el conjunt d'aerolínies és una copia d'\p a.
    void copy(const Airlines &a);
    
    ///@brief allibera memòria.
    void free();
};

#endif /* AIRLINES_H */

