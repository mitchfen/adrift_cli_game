adrift: ./src/player.h ./src/player.cpp ./src/main.cpp

	g++ -o adrift ./src/main.cpp -static

clean:

	rm adrift
