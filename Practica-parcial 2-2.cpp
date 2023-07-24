
// 1) Declare las estructuras de datos necesarias para implementar la matriz dispersa con un vector de listas (1 punto)

const int N = 100;
const int M = 1000;

struct Info {
    int columna;
    int valor;
}

struct Nodo* {
    Info info;
    Nodo* sgte;
}

// 2) Declare y defina la función Nodo* Insertar (int Fila, int Columna int Valor, Nodo*V[]) que inserte un nodo en la matriz esparcida  (2 puntos)

Nodo* insertaOrdenado(Nodo*& raiz, Info info) {
	// no es necesario desarrollar
	// ordena por columna
	return NULL;
}


Nodo* Insertar (int fila, int Columna, int Valor, Nodo*V[]) {
    Info info;

    info.columna = columna;
    info.valor = valor;

    Nodo* ptr = insertaOrdenado(v[fila], info);

    return ptr;
}

// 3) Declare y defina la función buscar que dado un valor indique la dirección de memoria en la que se encuentra o NULL en caso contrario. (2 puntos)

Nodo* buscaNodo(Nodo* raiz, int valor) {
	// no es necesario desarrollar
	// buscar por valor
	return NULL;
}

void buscar(Nodo* v[], int valor) {
    Nodo* ptr = NULL;

    int i = 0;
    while (i <= N - 1 && ptr == NULL) {
        ptr = buscarNodo(v[i], valor);
        i++;
    }
    return ptr;
}

// 4) Desarrolle un programa en C, C++ que permita cargar nodos en una matriz esparcida de enteros, se debe conocer el numero de filas (N) y el numero de columnas (M)y simular el ingreso de todos los enteros por columna, y los valores cero no cargarlos (4 puntos)

int main() {
    Nodo* arr[N];
    for (int i = 0; i <= N - 1; i++) {
        arr[i] = NULL; // inicializo cada raiz
    }

    for (int j = 0; j <= M - 1; j++) {
        for(int i = 0; i <= N - 1; i++) {
            int valor;
            cin >> valor;
            if (valor != 0) {
                insertar(i, j, valor, arr)
            }
        }
    }
    return 0;
}