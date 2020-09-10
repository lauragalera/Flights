//Laura Galera Alfaro
//u1959173
//practica final

/// @file Flight.h
/// @brief Classe Flight

#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

/** @class Flight
    @brief Un vol
    @author Laura Galera Alfaro
 */

struct Date{
    
    int day, month, year;
    
    //@brief Constructor sense paràmetres.
    Date(){
        day=month=year=0;
    }
    
    //@brief Crea una data a partir dels paràmetres d'entrada.
    Date(string dayf, string monthf, string yearf){
        day = stoi(dayf);
        month = stoi(monthf);
        year = stoi(yearf);
    }
    
    //@brief Operador relacional.
    bool operator<(const Date &d) const{
        bool less = false;
        if(year<d.year) less=true;
        else if(year == d.year){
            if(month < d.month) less=true;
            else if(month==d.month and day<d.day) less=true;
        }
        return less;
    }
    
    //@brief Escriu les dades de la data \p d al canal de sortida \p o, tot en una sola línia.
    friend ostream & operator<<(ostream & o, const Date &d){
        o<<d.year<<"/"<<d.month<<"/"<<d.day;
        
        return o;
    }
    
}; ///< Tupla per guardar-hi una data, concretament del vol.

class Flight {
public:
    
    /** @brief Crea una ruta a partir d'un vector de strings.
     *  @pre La mida del vector \p dataRead és 20. Les dades estan
     *       ordenades de la forma següent: 
     *          \verbatim
                    any, mes, dia, diaMes, IATAAerolínia, Numvol, IATAAeroportSortida, ciutatAeroportSortida,
                    IATAAeroportArribada, ciutatAeroportArribada, horaEsperadaSortida,horaSortida, retardSortida,
                    horaEsperadaArribada, horaArribada, retardArribada, cancelat, duradaEsperadaVol, duradaVol
                    distancia.
                \endverbatim
     *  @post Crea un nou vol a partir dels valors continguts al vector \p dataRead.
     *        Si el retard d'arribada, de sortida, el temps real de sortida, d'arribada
     *        o de durada del vol són desconeguts, reben el valor <b>-1000</b>.
     */
    Flight(const vector<string> &dataRead);
    
    ///@brief Retorna el valor del codi IATA de l'aerolínia que opera el vol.
    string getIATAAirline() const;
    
    ///@brief Retorna el valor del codi IATA de l'aeroport de sortida o el d'arribada.
    ///@pre \p Type és <b>D</b> o <b>A</b>.
    ///@post Retorna el valor del codi IATA de l'aeroport de sortida si \p type és <b>D</b> o el de l'aeroport d'arribada si és \p <b>A</b>.
    string getIATAAirport(char type) const;
    
    ///@brief Retorna el valor del retard de sortida o el d'arribada.
    ///@pre \p Type és <b>D</b> o <b>A</b>.
    ///@post Retorna el valor del retard de sortida si \p type és <b>D</b> o el retard d'arribada si és <b>A</b>.
    int getDelay(char type) const;
    
    ///@brief retorna la data d'aquest vol.
    Date getDate() const;

private:

    Date _date;                 ///< Data amb el dia, mes i any del vol.
    int _dayOfWeek;             ///< Dia de la setmana.
    string _IATACodeAirline;    ///< Codi IATA de l'aerolínia que ha operat el vol.
    int _flightNum;             ///< Número de vol.
    string _IATACodeAirportDep; ///< Codi IATA de l'aeroport de sortida.
    string _cityDeparture;      ///< Ciutat des d'on s'ha efectuat la sortida.
    string _IATACodeAirportArr; ///< Codi IATA de l'aeroport d'arribada.
    string _cityArrival;        ///< Ciutat on s'ha efectuat l'arribada.
    int _expDepTime;            ///< Temps previst de sortida del vol, en format HHMM. 
    int _realDepTime;           ///< Temps real de la sortida del vol, en format HHMM. Si es desconeix <b>-1000</b>.
    int _depDelay;              ///< Retràs en minuts entre el temps previst de sortida i el real, negatiu si la sortida ha sigut abans d'hora. Si es desconeix <b>-1000</b>.
    int _expArrTime;            ///< Temps previst d'arribada del vol HHMM.
    int _realArrTime;           ///< Temps real d'arribada del vol, en format HHMM. Si es deconeix <b>-1000</b>.
    int _arrDelay;              ///< Retràs en minuts entre el temps previst d'arribada i el real, negatiu si l'arribada ha sigut abans d'hora. Si es desconeix <b>-1000</b>.
    bool _cancelled;            ///< Cert si el vol ha estat cancelat, fals altrament.
    int _expElapsedTime;        ///< Temps previst de durada del vol en minuts.
    int _realElapsedTime;       ///< Durada real del vol en minuts. Si es desconeix <b>-1000</b>.
    int _distance;              ///< Distancia recorreguda en milles.

    enum IndexData { 
        year, month, dayMonth, dayWeek, IATAairline, flightNum, IATAairportD, cityD, IATAairportA, cityA,
        expDTime, realDTime, Ddelay, expATime, realATime, Adelay, cancelled, expETime, realETime, distance
    }; ///< Enumeració auxiliar usada al constructor per identificar què representa cada índex del vector \p dataRead. 
};

#endif /* FLIGHT_H */

