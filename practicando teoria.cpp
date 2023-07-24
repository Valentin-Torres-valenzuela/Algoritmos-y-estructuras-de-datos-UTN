void push(NodoListaAlumno*& raiz, AlumnoInfo info) {
    NodoListaAlumno* pAux = new nodoListaAlumno();
    pAux->info = info;
    pAux->sgte = raiz
    raiz = pAux;
}

AlumnoInfo pop(NodoListaAlumno*& raiz) {
    NodoListaAlumno* pAux = raiz;
    AlumnoInfo info = pAux->info;
    raiz = pAux -> sgte;
    delete pAux;
    return info;
}


void encolar(NodoColaAlumno*& colaFte, NodoColaAlumno*& colaFin, AlumnoInfo info) {
    NodoListaAlumno* pAux = new nodoListaAlumno();

    pAux -> info = info;
    pAux -> sgte; = NULL;

    if (estaVacia(colaFte)) {
        colaFte = pAux;
    } else {
        colaFin -> sgte = pAux;
    }
    colaFin = pAux;
}

AlumnoInfo desencolar(NodoColaAlumno*& colaFte, NodoColaAlumno*& colaFin) {
    NodoListaAlumno* pAux = colaFte;
    AlumnoInfo info = pAux -> info
    colaFte = pAux -> sgte;
    delete pAux;
    if (estaVacia(colaFte)) {
        colaFin = NULL;
    }
    return info;
}

void liberar(NodoListaAlumno*& raiz) {
    while (!estaVacia(raiz)) {
        pop(raiz);
    }
}

NodoListaAlumno* buscar(NodoListaAlumno* raiz, int legajo) {
    NodoListaAlumno* pAux = raiz;
    NodoListaAlumno* pNodo = NULL;

    while (pAux != NULL && pNodo == NULL) {
        if (pAux -> info.legajo == legajo) {
            pNodo = pAux;
        }
        pAux = pAux -> sgte;
    }
    return pNodo;
}

NodoListaAlumno* insertaOrdenado(NodoListaAlumno*& raiz, AlumnoInfo info) {
    NodoListaAlumno* pAux = new nodoListaAlumno();
    pAux -> info = info;

    NodoListaAlumno* pAct  = raiz;
    NodoListaAlumno* pAnt  = NULL;

    while (pAct =! NULL && pAct -> info.legajo < info.legajo) {
        pAnt = pAct;
        pAct = pAct -> sgte;
    }

    pAux = pAux -> sgte;

    if (pAnt == NULL) {
        raiz = pAux;
    } else {
        pAnt -> sgte = pAux;
    }

    return pAux;
}

NodoListaAlumno* agregar(NodoListaAlumno*& raiz, AlumnoInfo info) {
    NodoListaAlumno* pAux = new nodoListaAlumno();
    pAux -> info = info;

    NodoListaAlumno* pAct = raiz;
    NodoListaAlumno* pAnt = NULL;

    while (pAct != NULL) {
        pAnt = pAct;
        pAct = pAct -> sgte;
    }

    pAux -> sgte = pAct;

    if (pAnt == NULL) {
        raiz = pAux;
    } else {
        pAnt -> sgte = pAux;
    }
    return pAux;
}

void eliminar(NodoListaAlumno*& raiz, int legajo) {
    NodoListaAlumno* pAct = raiz;
    NodoListaAlumno* pAnt = NULL;

    while (pAct != NULL && pAct -> info.legajo != legajo) {
        pAnt = pAct;
        pAct = pAct -> sgte;
    }

    if (pAct -> info.legajo == legajo) {
        if (pAnt == NULL) {
            raiz = pAct -> sgte;
        } else {
            pAnt -> sgte = pAct -> sgte;
        }
        delete pAct;
    }
}

NodoListaAlumno* buscaEInsertaOrdenado(NodoListaAlumno*& raiz, AlumnoInfo info, bool& enc) {
    NodoListaAlumno* ptr = buscar(raiz, info.legajo);

    if (ptr == NULL) {
        insertaOrdenado(raiz, ptr);
        enc = false;
    } else {
        enc = true;
    }
    return ptr;
}

void ordenar(NodoListaAlumno*& raiz) {
    nodoListaAlumno* raizAux;
    inicializar(raizAux);

    while (!estaVacia(raiz)) {
        AlumnoInfo info = pop(raiz);
        insertaOrdenado(raizAux, info);
    }
    raiz = raizAux;
}

void cargarCompras(NodoListaUsuarios* raizListaUsuarios) {
    FILE * arch = fopen("compras.dat", "rb+");

    Compras regC;
    fread(&regC, sizeof(Compras), 1, arch);

    while (!feof(arch)) {
        NodoListaAlumno* ptr = buscar(raizListaUsuarios, regC.idlibro);
        
        ptr -> info.cant++;
        
        Libro info;

        info.idlibro = regC.idlibro;
        strcpy(info.idlibro, regC.idlibro);

        push(raizListaUsuarios, info);

        fread(regC, sizeof(Compras), 1, arch);
    }

    fclose(arch);
}