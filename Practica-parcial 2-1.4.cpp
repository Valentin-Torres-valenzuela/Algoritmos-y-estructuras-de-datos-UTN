 
// 1) Codifique la definición de los tipos de datos a utilizar (pila, vector y listas del vector)

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

NodoPilaLikes pop(NodoPilaLikes*& raiz) {
    NodoPilaLikes* pAux = raiz;

    Likes infoLikes = pAux -> info;
    raiz = pAux -> sgte;
    delete pAux;
    return info;
}

// 2.B) Desarrolle y luego utilice en el punto 5):
// template <typename T> void liberar(Nodo<T>*& p)

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

void buscaEInsertaOrdenado(NodoListaUsuariosUnicos*& raiz, Usuario info, bool& enc);

void cargarLikes(NodoPilaLikes*& raizPilaLikes, Fanpage vectF[]) {   
    
    while (raiz != NULL) {
        Likes infoLike = pop(raiz);
        int posFanpage = infoLike.idFanpage - 1;

        vectF[posFanpage].cantidadLikes++;

        Usuario infoUsuario;
        infoUsuario.idUsuario = infoLike.idUsuario;
        infoUsuario.NombreUsuario = infoUsuario.NombreUsuario;
        infoUsuario.cantidadLikes = 0;

        bool enc;

        NodoListaUsuariosUnicos* ptr = buscaEInsertaOrdenado(vectF[posFanpage].raizListaUsuariosUnicos, infoUsuario, enc);

        ptr -> info.cantidadLikes++;
    }
}

// 4) Desarrolle una función contarUsuarios que recibe como parámetro una lista de usuarios únicos y retorna la cantidad de usuarios que contiene (cantidad de nodos de la lista).

void contarUsuarios(NodoListaUsuariosUnicos* raiz) {
    int cantidadUsuarios = 0;

    NodoListaUsuariosUnicos* pAux = raiz;

    while (pAux != NULL) {
        cantidadUsuarios ++;
        pAux = pAux -> sgte;
    }
    return cantidadUsuarios;
}

// 5) Desarrolle un procedimiento mostrarCantidades que recibe como parámetro el vector con sus listas de usuarios ya cargadas y lo recorre mostrando por pantalla el id de cada fanpage junto con la cantidad de usuarios únicos que posee. Para esto debe invocar a la función contarUsuarios realizada en el punto 4). En este procedimiento debe liberar la memoria dinámica que ocupan las listas de usuarios únicos ya que luego no tendrán más utilidad.

void mostrarCantidades(Fanpage vectF[]) {
    for (int i = 0; i < 500; i++) {
        int idFanpage = i + 1;
        int cantidadUsuarios = contarUsuarios(vectF[i].raizListaUsuariosUnicos);

        <<cout << idFanpage << " | " << cantidadUsuarios << endl;

        contarUsuarios(vectF[i].raizListaUsuariosUnicos);
        
        liberar(vectF[i].raizListaUsuariosUnicos);
    }
    
}