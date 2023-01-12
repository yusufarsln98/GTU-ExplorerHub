target:	hw2

hw2_lib:	hw2_lib.h hw2_lib.cpp
			g++ -std=c++11 -c hw2_lib.cpp 

hw2_main:	hw2_lib.h hw2_main.cpp
			g++ -std=c++11 -c hw2_main.cpp 


hw2:	hw2_main hw2_lib
		g++ -std=c++11 hw2_lib.o hw2_main.cpp -o hw2 

clean:
		rm hw2