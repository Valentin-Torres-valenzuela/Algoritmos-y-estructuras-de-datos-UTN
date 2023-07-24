#include <iostream>
using namespace std;
#include <stdio.h>

// 1

struct RegistroCaja {
	int nroCaja;
	float efectivoApertura;
};

struct Cliente {
	int nroCarro;
	// Aca pueden ir todos los datos extras del cliente que ahora no tenemos
};

struct NodoCliente {
	Cliente info;
	NodoCliente* sgte;
};

struct Caja {
	float efectivoApertura;
	float ventaDineroEfectivo;
	int cuponesTC;
	float ventaTC;
	int cuponesTD;
	float ventaTD;
	int cantTickets;
	float ventaTickets;
	NodoCliente* colaFte;
	NodoCliente* colaFin;
};


struct Importe {
	float efectivo;
	float TC;
	float TD;
	int cantTickets;
	int dineroTickets;
};

// Las variables que representarían nuestras estructuras
//
//Caja arrCajas[40];
//
//NodoCliente* colaFteUnica;
//NodoCliente* colaFinUnica;


// 2

void inicializar(NodoCliente*& p) {
	p = NULL;
}

void cajasHabilitadas(Caja arrCajas[]) {

	FILE* archCajas = fopen("cajas.dat", "rb+");

	RegistroCaja regCaja;
	fread(&regCaja, sizeof(RegistroCaja), 1, archCajas);
	while(!feof(archCajas)) {
		int pos = regCaja.nroCaja - 1;

		arrCajas[pos].efectivoApertura = regCaja.efectivoApertura;
		arrCajas[pos].ventaDineroEfectivo = 0;
		arrCajas[pos].cuponesTC = 0;
		arrCajas[pos].ventaTC = 0;
		arrCajas[pos].cuponesTD = 0;
		arrCajas[pos].ventaTD = 0;
		arrCajas[pos].cantTickets = 0;
		arrCajas[pos].ventaTickets = 0;
		inicializar(arrCajas[pos].colaFte); // arrCajas[pos].colaFte = NULL
		inicializar(arrCajas[pos].colaFin); // arrCajas[pos].colaFin = NULL

		fread(&regCaja, sizeof(RegistroCaja), 1, archCajas);
	}

	fclose(archCajas);

}


// 3

void queue(NodoCliente*& colaFte, NodoCliente*& colaFin, Cliente info) {
	// No es necesario implementar
}

void nuevoCliente(NodoCliente*& colaFteUnica, NodoCliente*& colaFinUnica, int nroCarro) {
	Cliente info;
	info.nroCarro = nroCarro;
	queue(colaFteUnica, colaFinUnica, info);
}


// 4

Cliente unQueue(NodoCliente*& colaFte, NodoCliente*& colaFin) {
	// No es necesario implementar
	Cliente info;
	return info;
}

Importe calcularImportes(int nroCarro) {
	// No es necesario implementar
	Importe i;
	return i;
}

void atenderCliente(Caja arrCajas[], int nroCaja) {
	int pos = nroCaja - 1;
	Cliente cliente = unQueue(arrCajas[pos].colaFte, arrCajas[pos].colaFin);
	Importe importe = calcularImportes(cliente.nroCarro);

	arrCajas[pos].ventaDineroEfectivo = arrCajas[pos].ventaDineroEfectivo + importe.efectivo;
	if (importe.TC != 0) {
		arrCajas[pos].cuponesTC = arrCajas[pos].cuponesTC + 1;
	}
	arrCajas[pos].ventaTC = arrCajas[pos].ventaTC + importe.TC;
	if (importe.TD != 0) {
		arrCajas[pos].cuponesTD = arrCajas[pos].cuponesTD + 1;
	}
	arrCajas[pos].ventaTD = arrCajas[pos].ventaTD + importe.TD;
	arrCajas[pos].cantTickets = arrCajas[pos].cantTickets + importe.cantTickets;
	arrCajas[pos].ventaTickets = arrCajas[pos].ventaTickets + importe.dineroTickets;
}


// 5

void reasignarCaja(Caja arrCajas[], int nroCajaOrigen, int nroCajaDestino) {
	int posOrigen = nroCajaOrigen - 1;
	Cliente cliente = unQueue(arrCajas[posOrigen].colaFte, arrCajas[posOrigen].colaFin);

	int posDestino = nroCajaDestino - 1;
	queue(arrCajas[posDestino].colaFte, arrCajas[posDestino].colaFin, cliente);
}

int main() {
	return 0;
}