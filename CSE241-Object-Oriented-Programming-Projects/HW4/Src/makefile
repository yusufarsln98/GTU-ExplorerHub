target:	hw4

hw4_lib:	hw4_lib.h hw4_lib.cpp
			g++ -std=c++11 -c hw4_lib.cpp 

hw4_main:	hw4_lib.h hw4_main.cpp
			g++ -std=c++11 -c hw4_main.cpp 


hw4:	hw4_main hw4_lib
		g++ -std=c++11 hw4_lib.o hw4_main.cpp -o hw4 

clean:
		rm hw4