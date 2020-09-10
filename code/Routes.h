//Laura Galera Alfaro
//u1959173
//practica final

/// @file Routes.h
/// @brief Classe Routes

#ifndef ROUTES_H
#define ROUTES_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "Route.h"
#include "Airlines.h"
#include "Airports.h"
#include "Planes.h"

class Airports;

using namespace std;

/** @class Routes
    @brief Un conjunt de rutes
    @author Laura Galera Alfaro
*/     

class Routes {
public:
    
    ///@brief  Crea un conjunt de rutes buit.
    Routes();
    
    ///@brief  El conjunt de rutes és una copia de \p r.
    Routes(const Routes &r);
    
    ///@brief  Allibera memòria.
    ~Routes();
    
    ///@brief  El conjunt de rutes és una copia de \p r.
    Routes& operator=(const Routes& r);
    
    
    /** @brief Afageix una ruta al conjunt de rutes, sempre i quan la ruta sigui
     *         vàlida.
     *  @pre   La mida del vector \p dataRead és 9. Les dades estan ordenades de la
     *         següent manera:
     *              \verbatim
                    IATAAerolinia, codiIDAerolinia, IATAAeroportSortida,
                    codiIDAeroportSortida, IATAAeroportArribada, codiIDAeroportArribada,
                    codeShare, parades, equipament.
                    \endverbatim
     *  @post  Donat un vector de strings amb els valors d'una ruta, es crea la ruta
     *         i s'afageix al conjunt de rutes després de verifica si aquella ruta és
     *         valida; és a dir, la companyia aeria que l'opera existeix a \p aerolinies,
     *         els dos aeroports, sortida i arribada, també existeixen a \p aeroports, i
     *         finalment, tot l'equipament usat correspon a avions de \p avions.
     */
    void addRoute(const vector<string> &dataRead, const Airports &aeroports, const Airlines & aerolinies, const Planes & avions);
    
    /** @brief Retorna un set que conté tuples de tipus \c AirlineType amb el recompte de rutes
     *         nacionals i internacionals de les aerolínies que han operat un subconjunt de rutes.
     *  @pre   Cert.
     *  @post  Retorna un set de tuples \c AirlineType, on cada tupla conté el nom de l'aerolínia,
     *         la quantitat de rutes nacionals d'aquella aerolínia i el total de rutes internacionals.
     *         El set queda ordenat per ordre alfabètic.
     */
    set<AirlineType> countRoutesByAirline(const Airlines & aerolinies, const Airports & aeroports) const;
    
    /** @brief Retorna un map amb el nom de l'aerolínia i una llista del nom dels
     *         avions més utilitzats per l'aerolínia en les seves rutes.
     * @pre    Cert.
     * @post   Retorna un map amb el nom de l'aerolínia i una llista amb el nom
     *         dels avions més utilitzats, és a dir, l'avió o avions que s'han usat
     *         més cops en les rutes operades per \p IATAAirline.
     *         Si la ruta no existeix a \p airlines, és llença una excepció. No obstant
     *         això, si sí que existeix però no ha operat cap ruta del conjunt, simplement
     *         es retorna un map buit.
     */
    map<string,list<string>> mostUsedPlane(string IATAAirline, const Airlines & airlines, const Planes & planes) const;
    

private:
    map<int, list<Route *> > _mapRoutesAirline; /**< Map que té com a clau l'ID de l'aerolínia i per cada descripció hi figura una llista que
                                                 *   emmagatzema punters a totes les rutes que han sigut operades per aquella aerolínia.
                                                 *   Evidentment només s'hi guarden les rutes on l'ID aerolínia és conegut.
                                                 */
    map<string, list<Route *> > _mapRoutesIATA; /**< Map que té com a clau el codi IATA de l'aerolina i a cada descripció hi figua una llista
                                                 *   on s'hi guarden punters a totes les rutes que han sigut operades per aquella aerolínia.
                                                 *   Aquesta és una estructura auxiliar per tal de complementar el \g mapRoutesAirline.
                                                 *   Per tant nomes s'hi guarden les rutes per les quals no es pot identificar l'aerolínia a
                                                 *   partir del seu ID però si pel seu IATA.
                                                 */
    map<string, list<Route *> > _mapRoutesICAO; /**< Map que té com a claus el codi ICAO de l'aerolina i a cada descripció hi figua una llista
                                                 *   on s'hi guarden punters a totes les rutes que han sigut operades per aquella aerolínia.
                                                 *   Aquesta és una estructura auxiliar per tal de complementar el \g mapRoutesAirline.
                                                 *   Per tant nomes s'hi guarden les rutes per les quals no es pot identificar l'aerolínia a
                                                 *   partir del seu ID pero si pel seu ICAO.
                                                 */
    
    /** @brief Afageix la ruta a l'estructura que li pertoca, per tant, a \g _mapRoutesAirlines
     *         a \g _mapRoutesIATA o a \g _mapRoutesICAO.
     *  @pre   La ruta apuntada per \p ruta és vàlida.
     *  @post  Donat un punter a una ruta, aquest s'afageix a una de les estructures que conformen
     *         el conjunt de rutes. Si es coneix el seu ID s'afageix al \p _mapRoutesAirlines.
     *         En cas de que aquesta dada sigui desconeguda, s'afageix al map auxiliar \g _mapRoutesIATA
     *         si es disposa del codi IATA de l'aerolínia, o bé al \p _mapRoutesICAO si es disposa del 
     *         ICAO.
     */
    void addToRightStructure(Route * ruta);
    
    /** @brief Guarda al set \p countTypeAirlines una tupla de tipus \c AirlineType amb el nom de
     *         l'aerolínia i el total de rutes nacionals i internacionals d'aquesta.
     *  @pre   \p listRoutes conté totes les rutes fetes per l'aerolínia amb nom \p nameAirline. 
     *  @post  S'inclou al set \p countTypeAirlines una tupla amb el nom \p nameAirline i el recompte
     *         de rutes nacionals i internacionals fetes per l'aerolínia. Aclarim que es consideren
     *         nacionals les rutes on els dos aeroports comparteixen el mateix país (\p countryAirline)
     *         de l'aerolínia, pel contrari és internacional.
     */
    void classifyRoutesAirline(const list<Route *> & listRoutes, set<AirlineType> &countTypeAirlines, string countryAirline, string nameAirline, const Airports & aeroports) const;
    
    /** @brief Es retorna la llista de vols operats per una aerolínia
     *  @pre   Cert
     *  @post  Retorna una llista de punters a totes les rutes operades per la companyia apuntada
     *         per \p airline. Si l'aerolínia no ha operat cap ruta, es retorna una llista buida.
     */
    list<Route *> getAllRoutes(Airline * airline) const;
    
    ///@brief El conjunt de rutes és una copia \p r.
    void copy(const Routes &r);
    
    ///@brief Allibera memòria.
    void free();
};

#endif /* ROUTES_H */

