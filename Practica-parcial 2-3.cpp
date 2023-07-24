
A) Una lista de usuarios ya cargados donde cada usuario tiene a su vez una sublista de libros que posee actualmente, también ya cargados.
// - La lista de usuarios contiene en cada uno de sus nodos los siguientes datos de interés:

// B) El archivo Intercambios.dat con un registro por cada intercambio realizado. En un intercambio un usuario(1) cambia uno de los libros(1) que posee por otro libro(2) de otro usuario(2) (que recibe el libro(1) del primero). El archivo tiene orden natural (en el orden que ocurrieron los hechos). Tener en cuenta que un libro puede pasar a pertenecer a varios usuarios en un mismo día, por lo cual es importante el orden con el que está dado el archivo, para poder seguir el camino correcto de cada libro. Cada registro contiene la siguiente estructura:

// 1) Codifique la definición de todos los tipos de datos a utilizar (lista de usuarios con sublistas de libros y registros del archivo de intercambios).

struct Usuario {
    int IdUsuario;
    int CantidadIntercambios;
    char NombreUsuario[50 + 1];
    NodoListaLibros* ss;
}

struct NodoListaUsuarios* {
    Usuario info;
    NNodoListaUsuarios* sgte; 
}

struct Libro {
    char CodigoLibro[5 + 1];
    char NombreAutor[50 + 1];
    char TituloLibro[100 + 1];
}

struct NodoListaLibros* {
    Libro info;
    NodoListaLibros* sgte; 
}

struct RegistroIntercambio {
    int IdUsuario;
    int IdUsuario2;
    char CodigoLibro[5 + 1];
    char CodigoLibro2[5 + 1];
}

// 2) Desarrolle y luego utilice en la solución de su examen las siguientes funciones:
// 2.1) push: agrega un nuevo nodo al principio de la lista de libros.

void push(NodoListaLibros*& raiz, Libro info) {
    NodoListaLibros pAux = new NodoListaLibros();
    pAux -> info = info;
    pAux -> sgte = raiz;
    raiz = pAux;
}

// 2.2) buscar: busca un usuario en la lista de usuarios a partir de un Id del Usuario y retorna su posición de memoria de ser encontrado.

NodoListaAlumno* buscar(NodoListaUsuarios* raiz, int IdUsuario) {
    NodoListaUsuarios pNodo = NULL;
    NodoListaUsuarios pAux = raiz;

    while (pAux != NULL && pNodo == NULL) {
        if (pAux -> info.IdUsuario == IdUsuario) {
            pNodo = pAux;
        }
        pAux = pAux -> sgte;
    }
    return pNodo;
}

// 3) Desarrolle el procedimiento intercambiarLibros que recibe 4 parametros: dos listas de libros y dos Códigos de Libros (código del libro de la primera lista y código del libro de la segunda lista). El libro de la primera lista deberá ser eliminado de ésta y agregado al principio de la segunda lista. A su vez, el libro de la segunda lista deberá ser eliminado de ésta y agregado al principio de la primera lista. 


// Puede utilizar sin desarrollar la siguiente función: Tipo_del_info_de_un_nodo_libro eliminar(Tipo_nodo_libro*& s, char* codigoLibro): dada una lista de libros, busca el codigo de libro informado, elimina el nodo y retorna su info para posterior uso. Redefina su encabezado según los tipos de datos que haya creado.

NodoListaLibros* eliminar(NodoListaLibros*& s, char* codigoLibro) {
    // no es necesario desarrollar
    Libro info;
    return info;
}

void intercambiarLibros(NodoListaLibros*& raiz1, NodoListaLibros*& raiz2, char CodigoLibro1[5 + 1], int char CodigoLibro2[5 + 1]) {
    Libro infoLibro1 = eliminar(raiz1, CodigoLibro1);
    push(raiz1, infoLibro1);
    Libro infoLibro2 = eliminar(raiz2, CodigoLibro2);
    push(raiz2, infoLibro2);
}
// 4) Desarrolle el procedimiento aplicarIntercambios que recibe por parámetro la lista de usuarios (ya cargada junto con sus sublistas de libros cargadas). Debe abrir y recorrer el archivo de Intercambios.dat y para cada uno de sus registros:
// -	Encontrar a los dos usuarios correspondientes que intercambiarán libros.
// -	A cada uno de estos dos usuarios incrementarle en uno (1) la cantidad de intercambios realizados.
// -	Invocar a la función intercambiarLibros con las listas de libros de cada uno de estos dos usuarios y los códigos de libros correspondientes.

void aplicarIntercambios(NodoListaUsuarios*& raiz) {
    FILE * archInt = fopen("Intercambios.dat", "rb+");

	Intercambio regI;
	fread(&regI, sizeof(Intercambio), 1, archInt);

    while (!feof(archInt)) {
        NodoListaUsuarios* ptrUsuario1 = buscar(raiz, regI.IdUsuario);
        NodoListaUsuarios* ptrUsuario2 = buscar(raiz, regI.IdUsuario2);

        ptrUsuario1 -> info.CantidadIntercambios++;
        ptrUsuario2 -> info.CantidadIntercambios++;

        intercambiarLibros(ptrUsuario1 -> info.raizListaLibros, ptrUsuario2 -> info.raizListaLibros, regI.CodigoLibro, regI.CodigoLibro2);
        
        fread(&regI, sizeof(Intercambio), 1, archInt);
    }
    fclose(archInt);
}