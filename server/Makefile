# *********************
# Apexia Platforms
# Valora KVS
# Server
# Makefile
# *********************

valora_server: main.o valora_valorakvs.o valora_queryhandler.o
	-rm -r build
	mkdir build
	g++ -std=c++17 main.o valora_valorakvs.o valora_queryhandler.o -o ./build/valora_server -O3 -lzmq -lrocksdb -pthread
	rm *.o

main.o: ./src/main.cxx
	g++ -std=c++17 -c ./src/main.cxx -o main.o -O3 -lzmq -lrocksdb -pthread

valora_valorakvs.o: ./src/ValoraKVS.cxx ./src/ValoraKVS.h
	g++ -std=c++17 -c ./src/ValoraKVS.cxx -o valora_valorakvs.o -O3 -lzmq -lrocksdb -pthread

valora_queryhandler.o: ./src/QueryHandler.cxx ./src/QueryHandler.h
	g++ -std=c++17 -c ./src/QueryHandler.cxx -o valora_queryhandler.o -O3 -lzmq -lrocksdb -pthread

clean:
	-rm *.o
	-rm *.deb
	-rm -r build
