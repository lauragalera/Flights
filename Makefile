CC=g++ 
CPPFLAGS=-g -Wall -std=c++14

aviacio: main.o Airline.o Airlines.o Airport.o Airports.o Flight.o Flights.o Plane.o Planes.o Route.o Routes.o utils.o
	$(CC) -o aviacio main.o Airline.o Airlines.o Airport.o Airports.o Flight.o Flights.o Plane.o Planes.o Route.o Routes.o utils.o

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp
	
Airline.o: Airline.cpp Airline.h
	$(CC) $(CPPFLAGS) -c Airline.cpp
	
Airlines.o: Airlines.cpp Airlines.h
	$(CC) $(CPPFLAGS) -c Airlines.cpp
	
Airport.o: Airport.cpp Airport.h
	$(CC) $(CPPFLAGS) -c Airport.cpp
	
Airports.o: Airports.cpp Airports.h
	$(CC) $(CPPFLAGS) -c Airports.cpp
	
Route.o: Route.cpp Route.h
	$(CC) $(CPPFLAGS) -c Route.cpp

Routes.o: Routes.cpp Routes.h
	$(CC) $(CPPFLAGS) -c Routes.cpp

Plane.o: Plane.cpp Plane.h
	$(CC) $(CPPFLAGS) -c Plane.cpp
	
Planes.o: Planes.cpp Planes.h
	$(CC) $(CPPFLAGS) -c Planes.cpp
	
Flight.o: Flight.cpp Flight.h
	$(CC) $(CPPFLAGS) -c Flight.cpp
	
Flights.o: Flights.cpp Flights.h
	$(CC) $(CPPFLAGS) -c Flights.cpp

utils.o: utils.cpp utils.h
	$(CC) $(CPPFLAGS) -c utils.cpp
	
clean:
	rm *.o aviacio