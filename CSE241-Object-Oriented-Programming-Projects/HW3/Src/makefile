target:	hw3

hw3_lib:	hw3_lib.h hw3_lib.cpp
			g++ -std=c++11 -c hw3_lib.cpp 

hw3_main:	hw3_lib.h hw3_main.cpp
			g++ -std=c++11 -c hw3_main.cpp 


hw3:	hw3_main hw3_lib
		g++ -std=c++11 hw3_lib.o hw3_main.cpp -o hw3 

clean:
		rm hw3