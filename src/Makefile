SERVER=server
CLIENT=client

SERVERSRC=mainServer.cpp Mysocket.cpp
CLIENTSRC=mainClient.cpp Mysocket.cpp

${SERVER} : ${SERVERSRC}
	g++ ${SERVERSRC} -o ${SERVER}
	g++ ${CLIENTSRC} -o ${CLIENT}

clean:
	rm -rf ${SERVER} ${CLIENT}
