all: ./build/rf_send.o ./build/rf_module.o ./build/rf_module

./build/rf_send.o: ./src/rf_send.cc ./src/rf_send.h
	g++ -c ./src/rf_send.cc -o ./build/rf_send.o

./build/rf_module.o: ./src/rf_module.cc ./src/rf_module.h
	g++ -c ./src/rf_module.cc -o ./build/rf_module.o

./build/rf_module: ./build/rf_send.o ./build/rf_module.o
	g++ -pthread ./build/rf_send.o ./build/rf_module.o -o ./build/rf_module

clean: 
	rm ./build/*