// Se requiere realizar una lógica para poder analizar los “likes” que dan los usuarios a post de 500 fanpages diferentes en una red social. Para ello se cuenta con:
// A) Una pila de datos que contiene los likes que se otorgan a los post de las fanpages. Tener en cuenta que una fanpage X puede recibir muchos likes de un mismo usuario Y. El info de cada nodo de la pila contiene:
// o	Id del usuario que da el like: 999999	o	Id de la fanpage que recibe el like: [1..500]
// o	Nombre del usuario que da el like: 250 caracteres	o	Cod del post que recibe el like: 10 caracteres
// B) Un vector de fanpages (500) con listas que contienen a los diferentes usuarios que dieron likes. Las fanpages se encuentran ordenadas por id ascendente en el vector donde la que tiene id 1 se encuentra en la posición 0 del vector y así sucesivamente. Los elementos del vector tienen la siguiente estructura cargada:
// o	Cantidad total de likes recibidos: Inicializado en 0	o	Lista de usuarios únicos que dan like: inicializada en NULL
	
// C) Las listas dentro del vector tendrán a los usuarios únicos con los siguientes campos dentro del info:

// o	Id del usuario que da el like: 999999	o	Nombre del usuario que da el like: 250 caracteres
// o	Cantidad de likes dados a la fanpage: entero	

1) Codifique la definición de los tipos de datos a utilizar (pila, vector y listas del vector)

struct NodoPilaLikes {
    NodoPilaLikes* sgte;
    Likes info;
}

struct Likes {
    int idUsuario;
    int idFanpage;
    char NombreUsuario [250 + 1];
    char codPost [10 + 1];
}

struct NodoListaUsuariosUnicos {
    NodoListaUsuariosUnicos*  sgte;
    Usuario info;
}

struct Usuario {
    int idUsuario;
    char NombreUsuario [250 + 1];
    int CantidadLikes;
}

struct Fanpage  {
    int cantidadLikes;
    NodoListaUsuariosUnicos* raizListaUsuariosUnicos
}

// 2.A) Desarrolle y luego utilice en el punto 3):
// template <typename T> T pop(Nodo<T>*& p)

NodoPilaLikes* pop(NodoPilaLikes*& raiz) {
    NodoPilaLikes* pAux = raiz;

    Likes info = pAux -> info;
    raiz = pAux -> sgte;
    delete pAux;
    return info;
}

// 2.B) Desarrolle y luego utilice en el punto 5):
// template <typename T> void liberar(Nodo<T>*& p)

NodoListaUsuariosUnicos* pop(NodoListaUsuariosUnicos*& raiz) {
    // No es necesario desarrollar
}

void liberar(NodoListaUsuariosUnicos*& raiz) {
    while (raiz != NULL) {
        pop(raiz);
    }
}

// 3) Desarrolle un procedimiento cargarLikes que asigna los likes de la pila a cada fanpage en el vector. El procedimiento debe cumplir con  lo siguiente:
// - Los parámetros recibidos son 2: el puntero a la raíz de la pila, el vector con sus fanpages ya cargadas
// - Consumir la pila de likes e insertar a los usuarios únicos (usuarios distintos sin repetirse) que dan likes en sus correspondientes listas dentro del vector.
// - Ordenar las listas por Id del usuario que da el like ascendente.
// - Para cada fanpage en el vector contabilizar la cantidad de likes totales recibidos.
// - Para cada  usuario único en la fanpage contabilizar los likes que le da a esa fanpage

void buscaEInsertaOrdenado(NodoListaUsuariosUnicos*& raiz, Usuario info, bool& enc) {
    // No es necesario desarrollar, ordena las listas por id del usuario que da like ascendente.
}

void cargarLikes(NodoPilaLikes*& raiz, Fanpage vectF[]) {
    while (raiz != NULL ) {
        Likes infoLike = pop(raiz);
        int posFanpage = infoLike.idFanpage - 1;

        vectF[posFanpage].cantidadLikes++;

        Usuario infoUsuario;
        infoUsuario.idUsuario = infoLike.idUsuario;
        infoUsuario.NombreUsuario = infoUsuario.NombreUsuario;
        infoUsuario.cantidadLikes = 0;

        bool enc;

        NodoListaUsuariosUnicos* ptr = buscaEInsertaOrdenado(arrF[posFanpage].raizListaUsuariosUnicos, infoUsuario, enc);

        ptr -> info.cantidadLikes++;
    }
}

// 4) Desarrolle una función contarUsuarios que recibe como parámetro una lista de usuarios únicos y retorna la cantidad de usuarios que contiene (cantidad de nodos de la lista).

void contarUsuarios(NodoListaUsuariosUnicos* raiz) {
    int cantidadUsuarios = 0;

    NodoListaUsuariosUnicos* pAux = raiz;
    
    while (pAux != NULL) {
        cantidadUsuarios++;
        pAux = pAux -> sgte;
    }

    return cantidadUsuarios;
}

// 5) Desarrolle un procedimiento mostrarCantidades que recibe como parámetro el vector con sus listas de usuarios ya cargadas y lo recorre mostrando por pantalla el id de cada fanpage junto con la cantidad de usuarios únicos que posee. Para esto debe invocar a la función contarUsuarios realizada en el punto 4). En este procedimiento debe liberar la memoria dinámica que ocupan las listas de usuarios únicos ya que luego no tendrán más utilidad.

void mostrarCantidades(Fanpage vectF[]) {
    for (int i = 0; i <= 500; i++) {
        int idFanpage = i + 1;
        int cantidadUsuarios = contarUsuarios(vectF[i].raizListaUsuariosUnicos);

        <<cout << idFanpage << " | " << cantidadUsuarios <<endl;

        contarUsuarios(vectF[i].raizListaUsuariosUnicos);
        
        liberar(vectF[i].raizListaUsuariosUnicos);
    }
}