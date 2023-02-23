PokemonsBattles:MainSecond.o Pokemon.o LinkedList.o MaxHeap.o BattleByCategory.o
	gcc MainSecond.o Pokemon.o LinkedList.o MaxHeap.o BattleByCategory.o -o PokemonsBattles
LinkedList.o:LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
MaxHeap.o:MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c
Pokemon.o:Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c
BattleByCategory.o:BattleByCategory.c BattleByCategory.h Defs.h LinkedList.h MaxHeap.h Defs.h
	gcc -c BattleByCategory.c
MainSecond.o:MainSecond.c Pokemon.h BattleByCategory.h Defs.h
	gcc -c MainSecond.c
clean:
	rm -f *.o PokemonsBattles
