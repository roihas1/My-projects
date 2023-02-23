CPP_FARM:Animal.o Cow.o Chicken.o Sheep.o Farm.o ChickenFarm.o CowFarm.o SheepFarm.o Market.o farmMarket.o
	g++ Animal.o Cow.o Chicken.o Sheep.o Farm.o ChickenFarm.o CowFarm.o SheepFarm.o Market.o farmMarket.o -o CPP_FARM


Animal.o:Animal.cpp
	g++ -c Animal.cpp
Cow.o:Cow.cpp Animal.h
	g++ -c Cow.cpp
Chicken.o:Chicken.cpp Animal.h
	g++ -c Chicken.cpp
Sheep.o:Sheep.cpp Animal.h
	g++ -c Sheep.cpp
	
Farm.o:Farm.cpp Farm.h Animal.h
	g++ -c Farm.cpp
CowFarm.o:CowFarm.cpp Farm.h Sheep.h
	g++ -c CowFarm.cpp
SheepFarm.o:SheepFarm.cpp Farm.h Cow.h
	g++ -c SheepFarm.cpp
ChickenFarm.o:ChickenFarm.cpp Farm.h Chicken.h  
	g++ -c ChickenFarm.cpp


Market.o:Market.cpp ChickenFarm.h CowFarm.h SheepFarm.h Exceptions.h
	g++ -c Market.cpp

farmMarket.o:farmMarket.cpp Market.h
	g++ -c farmMarket.cpp



	
clean:
	rm -f *.o CPP_FARM
	
	
	
