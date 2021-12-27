build: 
	g++  --std=c++1z main.cpp wget.cpp tcpsocket.cpp httpprotocol.cpp -o wget

clean:
	rm wget