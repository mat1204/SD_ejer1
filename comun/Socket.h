/*
 * Socket.h
 *
 *  Created on: 18/05/2014
 *      Author: migue
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdlib.h>
#include "inet.h"

class Socket {
public:
	Socket();

	Socket(int fd);

	Socket(const char* fdStr);

	Socket(const Socket& orig);

	const Socket& operator = (const Socket& orig);

	void enviar(const void* datos, size_t tam);

	void recibir(void* datos, size_t tam);

	int conectar(const char* servidor, int puerto);

	int conectar(struct sockaddr_in& direccion, int puerto);

	void enlazar(int puerto, int conexEnEspera = 5);

	Socket aceptarConexion(struct sockaddr_in& direccion);

	Socket aceptarConexion();

	int descriptor();

	bool socketValido();

	const char* descriptorAString();

	void cerrar();

	virtual ~Socket();

private:

	char* _stringFd;

	int _fd;
	bool _cerrado;
	bool _conectado;

	bool _valido;
};

#endif /* SOCKET_H_ */
