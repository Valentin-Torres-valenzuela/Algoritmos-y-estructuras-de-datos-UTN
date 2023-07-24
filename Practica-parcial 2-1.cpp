
// A) Una cola que contiene los datos de los usuarios. Los structs que la representan son los siguientes:

struct InfoColaUsuarios {
	int idUsuario;
	char nombreUsuario[250 + 1];
};

struct NodoColaUsuarios {
	InfoColaUsuarios info;
	NodoColaUsuarios* sgte;
};

// B) Un archivo compras.dat que contiene los libros que compran los usuarios. Tener en cuenta que un usuario puede comprar muchos libros,  pero no puede comprar libros repetidos, siempre son todos distintos. Cada registro contiene:

struct Compra {
	int idLibro;
	char nombreLibro[100 + 1];
	int idUsuario;
};

// Se requiere utilizar los datos de la cola y los datos del archivo para cargar una lista de usuarios donde cada usuario tenga una lista con los libros que compró.

// 1) Codifique la definición de los tipos de datos a utilizar (lista de usuarios y lista de libros de cada usuario)

struct NodoListaUsuarios* {
    Usuario info;
    NodoListaUsuarios* sgte;
}

struct Usuario {
    int idUsuario;
    char nombreUsuario[250 + 1];
    int cantidadTotatLibrosComprados;
    NodoListaLibros* raizListaLibros;

}

struct NodoListaLibros* {
    Libro info;
    NodoListaLibros* sgte;
}

struct Libro {
    int idLibro;
    char nombreLibro[100 + 1];
}

// 2)  retorna la lista de usuarios requerida. Para esto debe consumir la cola y armar la lista de usuarios con los datos obtenidos. 


void inicializar(NodoListaUsuarios*& raiz) {
	//no es necesario desarrollar
}

void inicializar(NodoListaLibros*& raiz) {
	//no es necesario desarrollar
}

bool estaVacia(NodoColaUsuarios* raiz) {
	//no es necesario desarrollar
	return true;
}

InfoColaUsuarios desencolar(NodoColaUsuarios*& colaFte, NodoColaUsuarios*& colaFin) {
	//no es necesario desarrollar
	InfoColaUsuarios info;
	return info;
}

void push(NodoListaUsuarios*& raiz, Usuario info) {
	//no es necesario desarrollar
}

NodoListaUsuarios* obtenerListaUsuarios(NodoColaUsuarios*& colaFte, NodoColaUsuarios*& colaFin) {
    NodoListaUsuarios raizListaUsuarios;
    inicializar(raizListaUsuarios);

    while (!estaVacia(colaFte)) {

        InfoColaUsuarios infoCola = desencolar(colaFte, colaFin);
        Usuario infoLista;
        
        infoLista.idUsuario = infoCola.idUsuario;
        infoLista.nombreUsuario = infoCola.nombreUsuario;
        infoLista.cantidadTotatLibrosComprados = 0
        inicializar(infoLista.raizListaLibros);

        push(raizListaUsuarios, infoLista);
    }
    return raizListaUsuarios;
}

// 3) 
// - Se debe leer secuencialmente el archivo compras.dat
// - Por cada compra, agregar el libro en la lista de libros comprados del usuario correspondiente
// - Por cada compra, contabilizar en el usuario correspondiente la cantidad de total de libros comprados

NodoListaUsuarios* buscar(NodoListaUsuarios* raiz, int idUsuario) {
	//no es necesario desarrollar
	return NULL;
}

void push(NodoListaLibros*& raiz, Libro info) {
	//no es necesario desarrollar
}

void cargarCompras(NodoListaUsuarios* raizListaUsuarios) {
    FILE * arch = fopen("compras.dat", "rb+");

    Compra regC;
    fread(&regC, sizeof(Compra), 1, arch);

    while (!feof(arch)) {

        NodoListaUsuarios* ptr = buscar(raizListaUsuarios, regC.idUsuario);

        ptr -> info.cantidadTotatLibrosComprados++;

        Libro infoLibro;
        infoLibro.idLibro = regC.idLibro;
        infoLibro.nombreLibro = regC.nombreLibro;
        
        push(ptr -> info.raizListaLibros ,infoLibro);

        fread(&regC, sizeof(Compra), 1, arch);
    }

    fclose(arch);
}

// 4) Desarrolle el procedimiento mostrarUsuarios que recibe por parámetro la lista de usuarios (luego de que se cargaron la compras), la recorre secuencialmente y muestra por pantalla para cada usuario el Id del usuario y la cantidad total de libros comprados.

void mostrarUsuarios(NodoListaUsuarios*& raiz) {
    NodoListaUsuarios* pAux = raizListaUsuarios;

    while (pAux != NULL) {
        cout << pAux -> info.idUsuario << ' | ' << pAux -> info.cantidadLibrosComprados << endl;
        pAux = pAux -> sgte;
    }
}