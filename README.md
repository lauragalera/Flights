# Flights

The program starts by reading five files and loads the data in appropriate data structures in c++ to query information quickly and efficiently. The first four files contain data regarding airports, airlines, planes and routes belonging to [OpenFlights](https://openflights.org/data.html), and the format is dat. The fifth file is a CSV reporting a set of flights. It can be found in this repository under the name ''T_ONTIME_REPORTING_2019_6.csv''. 

There is a list of queries retrieving information that combines the previous files. The available queries are:

* "COUNT ROUTES"
  
  Displays how many national and international routes each company has in alphabetic order.
  
* "MOST USED PLANE",IATA

  Displays the plane model used in more routes for a specific company (IATA code).
  
* "DEPARTURE DELAY AIRPORTS",n,year,month,day_of_month

  Lists the n (0 = all) airports with more delays in their departures given a specific date. They are ordered decreasingly.
  
* "ARRIVAL DELAY AIRPORTS",n,year,month,day_of_month

  
  Lists the n (0 = all) airports with more delays in their arrivals given a specific date. They are ordered decreasingly.
  
* "DEPARTURE DELAY AIRLINES",n

   Lists the n (0 = all) airports with more delays in their departures. They are ordered decreasingly.
   
* "ARRIVAL DELAY AIRLINES",n

  Lists the n (0 = all) airports with more delays in their arrivals. They are ordered decreasingly.
  
* "DAY WITH MORE DELAYS",IATA_1,...,IATA_N

  Lists the day with more delays, arrivals and departures, for a set of airports (empty set = all aiports). 

To automatize the queries, the program can receive a text file as a parameter that contains all the queries line by line. "queriesMeves.txt" is an example of file, and it is located in playtesting. It is redirected by doing:

```
./main < /data/u/alum/u1959173/eda/p1/jocProves/queries/queriesMeves.txt
```
