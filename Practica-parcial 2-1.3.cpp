// 1) Codifique la definición de todos los tipos de datos a utilizar (lista de usuarios con sublistas de libros y registros del archivo de intercambios).

struct NodoListaUsuarios* {
    Usuario info;
    NodoListaUsuarios* sgte;
}

struct Usuario {
    int idUsuario;
    char nombreUsuario[50 + 1];
    int cantidadIntercambios;
    NodoListaLibros* raizListaLibros;
};

struct NodoListaLibros* {
    Libro info;
    NodoListaLibros* sgte;
}

struct Libro{
    int codigoLibro[5 + 1];
    char autorLibro[50 + 1];
    char tituloLibro[100 + 1];
};

struct RegistroIntercambio {
    int IdUsuario;
    int IdUsuario2;
    char CodigoLibro[5 + 1];
    char CodigoLibro2[5 + 1];
}

// 2) Desarrolle y luego utilice en la solución de su examen las siguientes funciones:
// 2.1) push: agrega un nuevo nodo al principio de la lista de libros.
// 2.2) buscar: busca un usuario en la lista de usuarios a partir de un Id del Usuario y retorna su posición de memoria de ser encontrado.

void push(NodoListaLibros*& raiz, Libro info ) {
    NodoListaLibros pAux = new NodoListaLibros();

    pAux -> info = info;
    pAux -> sgte = raiz;
    raiz = pAux;
}

NodoListaUsuarios* buscar(NodoListaUsuarios* raiz, int idUsuario) {
    NodoListaLibros pNodo = NULL;
    NodoListaLibros pAux = raiz;

    while (pAux != NULL && pNodo == NULL) {
        if (pAux -> info.idUsuario == idUsuario) {
            pNodo = pAux
        }

        pAux = pAux -> sgte;
    }
    return pNodo;
}

// 3) Desarrolle el procedimiento intercambiarLibros que recibe 4 parametros: dos listas de libros y dos Códigos de Libros (código del libro de la primera lista y código del libro de la segunda lista). El libro de la primera lista deberá ser eliminado de ésta y agregado al principio de la segunda lista. A su vez, el libro de la segunda lista deberá ser eliminado de ésta y agregado al principio de la primera lista. Puede utilizar sin desarrollar la siguiente función:
// Tipo_del_info_de_un_nodo_libro eliminar(Tipo_nodo_libro*& raizListaLibro, char* codigoLibro): dada una lista de libros, busca el codigo de libro informado, elimina el nodo y retorna su info para posterior uso. Redefina su encabezado según los tipos de datos que haya creado.

NodoListaLibros* eliminar(NodoListaLibros*& raizListaLibro, char* codigoLibro) {
    // no es necesario desarrollar
}

void intercambiarLibros(NodoListaLibros*& raizUno, NodoListaLibros*& raizDos, char codigoLibroUno[5 + 1], char codigoLibroDos[5 + 1]) {
    Libro libroInfo1 = eliminar(raizUno, codigoLibroUno);
    push(raizDos, libroInfo1);
    Libro libroInfo2 = eliminar(raizDos, codigoLibroDos);
    push(raizUno, libroInfo2);
}

// 4) Desarrolle el procedimiento aplicarIntercambios que recibe por parámetro la lista de usuarios (ya cargada junto con sus sublistas de libros cargadas). Debe abrir y recorrer el archivo de Intercambios.dat y para cada uno de sus registros:
// -	Encontrar a los dos usuarios correspondientes que intercambiarán libros.
// -	A cada uno de estos dos usuarios incrementarle en uno (1) la cantidad de intercambios realizados.
// -	Invocar a la función intercambiarLibros con las listas de libros de cada uno de estos dos usuarios y los códigos de libros correspondientes.

void aplicarIntercambios(NodoListaUsuarios*& raiz) {
    FILE * arch = fopen("Intercambios.dat", "rb+");

    Intercambio regI;

    fread(&regI, sizeof(Intercambio), 1, arch);
    while (!feof(arch)) {
        NodoListaUsuarios* ptrUsuario1 = buscar(raiz, regI.idUsuario1);
        NodoListaUsuarios* ptrUsuario2 = buscar(raiz, regI.idUsuario2);

        ptrUsuario1 -> info.cantidadIntercambios++;
        ptrUsuario2 -> info.cantidadIntercambios++;

        intercambiarLibros(ptrUsuario1 -> info.raizListaLibros, ptrUsuario2 -> info.raizListaLibros, regI.codigoLibroUno, regI.codigoLibroDos);

        fread(&regI, sizeof(Intercambio), 1, arch);
    }
    fclose(arch);
}