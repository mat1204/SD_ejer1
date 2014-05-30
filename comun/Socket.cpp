/*
 * Socket.cpp
 *
 *  Created on: 18/05/2014
 *      Author: migue
 */

#include "Socket.h"
//#include "inet.h"
#include "SalidaPorPantalla.h"


extern int tcpopact(const char *server, int puerto);
extern int tcpopact_dir(const struct sockaddr_in& direccion, int puerto);
extern int tcpoppas(int puerto, int enEspera);

extern int _skc_recibir(int sockfd, void *datos, size_t nbytes);
extern int _skc_enviar(int sockfd, const void *datos, size_t nbytes);

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

//	if (!_cerrado) {
//		close(_fd);
//	}
}

Socket::Socket(const Socket& orig) {
	(*this) = orig;
}

const Socket& Socket::operator = (const Socket& orig) {
	this->_fd = orig._fd;

	this->_cerrado = orig._cerrado;
	this->_conectado = orig._conectado;
	this->_valido = orig._valido;


	return (*this);
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

void Socket::enviar(const void* datos, size_t tam) {
	//SalidaPorPantalla::instancia().mostrar("socket: enviando por fd: ", _fd);
	int enviados = _skc_enviar(_fd, datos, tam);
	//SalidaPorPantalla::instancia().mostrar("socket: datos enviados: ", enviados);
}

void Socket::recibir(void* datos, size_t tam) {
	//SalidaPorPantalla::instancia().mostrar("socket: recibiendo por fd: ", _fd);
	int leidos = _skc_recibir(_fd, datos, tam);
	//SalidaPorPantalla::instancia().mostrar("socket: datos recibidos: ",leidos );
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

		//SalidaPorPantalla::instancia().mostrar("socket: conectado a fd: ", _fd);

		_valido = true;
		_conectado = true;
		_cerrado = false;

		return 0;
	}
}

int Socket::conectar(struct sockaddr_in& direccion, int puerto) {
	if (_fd != -1) {
		close(_fd);
	}
	_fd = tcpopact_dir(direccion, puerto);

	if (_fd == -1) {
		SalidaPorPantalla::instancia().error("Hubo un error en la conexion: ", strerror(errno));
		return -1;
	}
	else {
		_valido = true;
		_conectado = true;
		_cerrado = false;
		return 0;
	}
}


void Socket::enlazar(int puerto, int conexEnEspera) {
	_fd = tcpoppas(puerto, conexEnEspera);
	if (_fd <= 0 ) {
		SalidaPorPantalla::instancia().error("No se pudo crear crear y conectar socket");
		_valido = false;
		_conectado = false;
		_cerrado = true;
	}
	else {
		_valido = true;
		_conectado = false;
		_cerrado = false;
	}
}

Socket Socket::aceptarConexion() {

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


Socket Socket::aceptarConexion(struct sockaddr_in& direccion) {

	unsigned clilen;
	struct sockaddr_in	cli_addr;
	clilen = sizeof(cli_addr);

	int fdNuevoSck;

	fdNuevoSck = accept(_fd, (struct sockaddr *) &cli_addr, &clilen);

	Socket nuevoSocket(fdNuevoSck);

	if (fdNuevoSck < 0) {
		nuevoSocket._valido = false;
		memcpy((void*) &direccion, (const void*) &cli_addr, clilen);
	}
	else {
		memset((void*) &direccion, 0 , clilen);
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

	std::stringstream ss;

	ss << _fd;

	if (_stringFd != NULL) {
		delete _stringFd;
	}

	_stringFd = strdup(ss.str().c_str());

	return _stringFd;

}

void Socket::cerrar() {
	if (_fd != -1) {
		close(_fd);
		_cerrado = true;
		_conectado = false;
		_valido = false;
		_fd = -1;
	}
}

