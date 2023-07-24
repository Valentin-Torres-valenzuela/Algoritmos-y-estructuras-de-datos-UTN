
struct InfoColaUsuarios {
	int idUsuario;
	char nombreUsuario[250 + 1];
};

struct NodoColaUsuarios {
	InfoColaUsuarios info;
	NodoColaUsuarios* sgte;
};

struct Compra {
	int idLibro;
	char nombreLibro[100 + 1];
	int idUsuario;
};

// 1) Codifique la definición de los tipos de datos a utilizar (lista de usuarios y lista de libros de cada usuario)

struct NodoListaUsuarios* {
    Usuario info;
    NodoListaUsuarios* sgte;
}

struct Usuario {
    int idUsuario;
    char nombreUsuario[100 + 1];
    int cantidadLibrosComprados;
    NodoListaLibros* raizListaLibros;
}

struct NodoListaLibros* {
    Libro info;
    NodoListaLibros* sgte
}

struct Libro {
    int idLibro;
    char nombreLibro[100 + 1];
}

// 2) Desarrolle la función obtenerListaUsuarios que recibe como parámetro los punteros de la cola (colaFte y colaFin) y retorna la lista de usuarios requerida. Para esto debe consumir la cola y armar la lista de usuarios con los datos obtenidos. Dado que todavía no se estan procesando los libros comprados, la cantidad total de libros comprados y la lista de libros comprados para cada usuario deberán quedar inicializados correctamente.

void inicializar(NodoListaUsuarios*& raiz) {
    // no es necesario desarrollar
}

bool estaVacia(NodoColaUsuarios* raiz) {
    // no es necesario desarrollar
    return true;
}

InfoColaUsuarios* desencolar(NodoColaUsuarios colaFte, NodoColaUsuarios colaFin) {
    // no es necesario desarrollar
}

void push(NodoListaUsuarios*& raiz, Usuario info) {
    // no es necesario desarrollar
}

NodoListaUsuarios* obtenerListaUsuarios(NodoColaUsuarios*& colaFte, NodoColaUsuarios*& colaFin) {
    NodoListaUsuarios raizListaUsuarios;
    inicializar(raizListaUsuarios);

    while (estaVacia(colaFte)) {
        InfoColaUsuarios infoCola = desencolar(colaFte, colaFin);
        Usuario infoListaUsuario;

        infoListaUsuario.idUsuario = infoCola.idUsuario;
        infoListaUsuario.nombreUsuario = infoCola.nombreUsuario;
        infoListaUsuario.cantidadLibrosComprados = 0;
        inicializar(infoListaUsuario.raizListaLibros);

        push(raizListaUsuarios, infoListaUsuario);
    }

    return raizListaUsuarios;
}

// 3) Desarrolle el procedimiento cargarCompras que debe cumplir con  lo siguiente:
// - Recibe como parámetro la lista de usuarios ya armada en el punto anterior
// - Se debe leer secuencialmente el archivo compras.dat
// - Por cada compra, agregar el libro en la lista de libros comprados del usuario correspondiente
// - Por cada compra, contabilizar en el usuario correspondiente la cantidad de total de libros comprados

void cargarCompras(NodoListaUsuarios*& raizListaUsuarios) {

    FILE * arch = fopen("compras.dat", "rb+");

    Compra regC;
    fread(&regC, sizeof(Compra), 1, arch);
    
    while (!feof(arch)) {

        NodoListaUsuarios* ptr = buscar(raizListaUsuarios, regC.idUsuario);

        ptr -> info.cantidadTotatLibrosComprados++;

        Libro infoLibro;
        infoLibro.idLibro = regC.idLibro;   
        infoLibro.nombreLibro = regC.nombreLibro;

        push(ptr -> info.raizListaLibros, infoLibro);

        fread(&regC, sizeof(Compra), 1, arch);
    }

    fclose(arch);
}

// 4) Desarrolle el procedimiento mostrarUsuarios que recibe por parámetro la lista de usuarios (luego de que se cargaron la compras), la recorre secuencialmente y muestra por pantalla para cada usuario el Id del usuario y la cantidad total de libros comprados.

void mostrarUsuarios(NodoListaUsuarios* raizListaUsuarios) {
    NodoListaUsuarios* pAux = raizListaUsuarios;

    while (pAux != NULL) {
        cout << "Id usuario: " << pAux -> info.idUsuario << " | " << "Cantidad de libros comprados: " << pAux -> info.cantidadLibrosComprados << endl;
        
        pAux = pAux -> sgte;
    }
}