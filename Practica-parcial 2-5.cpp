#include <iostream>
using namespace std;
#include <string.h>

// 1)

struct InfoDuplicado {
	int campo1;
	char campo2[20 + 1];
	float campo3;
	int campo4;
};

struct NodoListaDuplicados {
	InfoDuplicado info;
	NodoListaDuplicados* sgte;
};

struct InfoSubLista {
	float campo3;
	int campo4;
};

struct NodoSubLista {
	InfoSubLista info;
	NodoSubLista* sgte;
};

struct InfoLista {
	int campo1;
	char campo2[20 + 1];
	NodoSubLista* punteroSubLista;
};

struct NodoLista {
	InfoLista info;
	NodoListaDuplicados* sgte;
};

// 2)

void inicializar(NodoLista*& raiz) {
	raiz = NULL;
}

void inicializar(NodoSubLista*& raiz) {
	raiz = NULL;
}

bool estaVacia(NodoListaDuplicados* raiz) {
	return raiz == NULL;
}

InfoDuplicado pop(NodoListaDuplicados*& raiz) {
	// no es necesario implementar
	InfoDuplicado info;
	return info;
}

// insertarSinRepetir
NodoLista* buscaEInsertaOrdenado(NodoLista*& p, InfoLista v, bool& enc) {
	// no es necesario implementar
	// busca e inserta ordenado segun campo1 y campo2 ASC
	return NULL;
}

NodoSubLista* insertarOrdenado(NodoSubLista* & raiz, InfoSubLista v) {
	// no es necesario implementar
	// inserta ordenado segun campo3 y campo4 ASC
	return NULL;
}


NodoLista* cargarListaDeListas(NodoListaDuplicados*& listaDato) {
	NodoLista* listaResultado;
	inicializar(listaResultado); // listaResultado = NULL

	while(!estaVacia(listaDato)) { // listaDato != NULL
		InfoDuplicado dato = pop(listaDato);

		// cargo el nodo en la lista principal si es que no existe

		InfoLista infoLista;
		infoLista.campo1 = dato.campo1;
		strcpy(infoLista.campo2, dato.campo2);
		inicializar(infoLista.punteroSubLista); // infoLista.punteroSubLista = NULL;

		bool enc;
		NodoLista* ptr = buscaEInsertaOrdenado(listaResultado, infoLista, enc);

		// cargo el nodo en la sublista

		InfoSubLista infoSubLista;
		infoSubLista.campo3 = dato.campo3;
		infoSubLista.campo4 = dato.campo4;

		insertarOrdenado(ptr -> info.punteroSubLista, infoSubLista);
	}

	return listaResultado;
}

int main() {

	// 3)

	NodoListaDuplicados* listaDato = NULL;
	//se pueden cargar nodos en la listaDato;

	NodoLista* listaResultado = cargarListaDeListas(listaDato);

	NodoLista* pAux = listaResultado;
	while (pAux != NULL) {
		// muestro algun dato de los nodos
		pAux = pAux -> sgte;
	}

	return 0;
}