/*
 * Socket.cpp
 *
 *  Created on: 18/05/2014
 *      Author: migue
 */

#include "Socket.h"
#include "inet.h"
#include "SalidaPorPantalla.h"


extern int tcpopact(const char *server, int puerto);
extern int tcpoppas(int puerto);

extern int recibir(int sockfd, void *datos, size_t nbytes);
extern int enviar(int sockfd, void *datos, size_t nbytes);

int __recibir(int sockfd, void *datos, size_t nbytes) {
	return recibir(sockfd, datos, nbytes);
}

int __enviar(int sockfd, void *datos, size_t nbytes) {
	return enviar(sockfd, datos, nbytes);
}


Socket::Socket() {
	_fd = -1;
	_conectado = false;
	_cerrado = false;
	_valido = true;
	_stringFd = NULL;
}

Socket::~Socket() {
	if (_stringFd != NULL)
		delete _stringFd;

	if (!_cerrado) {
		close(_fd);
	}
}

Socket::Socket(const Socket& orig) {
	(*this) = orig;
}

Socket::Socket(int fd) {
	_fd = fd;
	_conectado = true;
	_cerrado = false;
	_valido = true;
	_stringFd = NULL;
}

Socket::Socket(const char* fdStr) {
	_fd = atoi(fdStr);
	_conectado = true;
	_cerrado = false;
	_valido = true;
	_stringFd = NULL;
}

void Socket::enviar(void* datos, size_t tam) {
	__enviar(_fd, datos, tam);
}

void Socket::recibir(void* datos, size_t tam) {
	__recibir(_fd, datos, tam);
}

int Socket::conectar(const char* servidor, int puerto) {
	if (_fd != -1) {
		close(_fd);
	}
	_fd = tcpopact(servidor, puerto);

	_valido = false;

	if (_fd == -1) {
		SalidaPorPantalla::instancia().error("Hubo un error en la conexion: ", strerror(errno));
		return -1;
	}
	else if (_fd == -2) {
		SalidaPorPantalla::instancia().error("No existe nombre de servidor");
		return -2;
	}
	else {
		_valido = true;
		_conectado = true;
		return 0;
	}
}

void Socket::enlazar(int puerto, int conexEnEspera) {
	_fd = tcpoppas(puerto);
	if (_fd <= 0 ) {
		SalidaPorPantalla::instancia().error("No se pudo crear crear y conectar socket");
	}
}

Socket Socket::escucharConexion() {

	unsigned clilen;
	struct sockaddr_in	cli_addr;
	clilen = sizeof(cli_addr);

	int fdNuevoSck;

	fdNuevoSck = accept(_fd, (struct sockaddr *) &cli_addr, &clilen);

	Socket nuevoSocket(fdNuevoSck);

	if (fdNuevoSck < 0) {
		nuevoSocket._valido = false;
	}

	return nuevoSocket;
}

int Socket::descriptor() {
	return _fd;
}

bool Socket::socketValido() {
	return _valido;
}

const char* Socket::descriptorAString() {
	if (_stringFd == NULL) {
		_stringFd = new char[15];
	}
	sprintf(_stringFd, "%d\0", _fd);

	return _stringFd;
}

void Socket::cerrar() {
	if (_fd != -1) {
		close(_fd);
		_cerrado = true;
		_conectado = false;
		_valido = false;
	}
}

const Socket Socket::operator = (const Socket& orig) {
	this->_fd = orig._fd;

	this->_cerrado = orig._cerrado;
	this->_conectado = orig._conectado;
	this->_valido = orig._valido;

	return *this;
}

