// Tips primer parcial 

Si dice que tiene 5 o 6 digitos simplemente es un INT, no un array

Si el vector es de 50 elementos entonces es [50 + 1]

Busqueda binaria, para poder utilizarla el vector debe estar ordenado por la clave de busqueda y la estructura debe permitir acceso directo a sus elementos, sino usamos la busqueda secuencial

Si se necesitan comparar dos chars hay que usar la funcion de strcmp()

El len u otro dato no lleva & cuando no varia la cantidad de elementos del array sino que solo modifico los que ya están [lectura]

la función inserta ordenado lo agrega y lo ordena y si los datos se repiten los coloca dos veces

la función busca e inserta ordenado lo agrega y lo ordena y si los datos se repiten NO los coloca dos veces

// Apareo

void inicializar(int& len) {
	len = 0; // el array comienza teniendo 0 elementos útiles
}

void agregar(int arr[], int& len, int v) {
	arr[len] = v; // agrego el elemento en la primera posición libre
	len = len + 1; // incremento la cantidad de elementos útiles que tengo en mi array
}

// recibo A y B ordenados y los apareo dejando el resultado en el array C
void apareo(int arrA[], int lenA, int arrB[], int lenB, int arrC[], int& lenC) {
	inicializar(lenC); // lenC = 0;

	int i = 0;
	int j = 0;

	while((i <= lenA - 1) && (j <= lenB - 1)) {
		if(arrA[i] < arrB[j]) {
			agregar(arrC, lenC, arrA[i]);
			i++;
		} else {
			agregar(arrC, lenC, arrB[j]);
			j++;
		}
	}

	if(i <= lenA - 1) { // no terminó de recorrer A
		while(i <= lenA - 1) {
			agregar(arrC, lenC, arrA[i]);
			i++;
		}
	} else { // no terminó de recorrer B
		while(j <= lenB - 1) {
			agregar(arrC, lenC, arrB[j]);
			j++;
		}
	}
}

// Operaciones con archivos - read, write, seek, filePos, fileSize, buscar, busquedaBinaria

int read(FILE* f) {
	int reg;
	fread(&reg, sizeof(int), 1, f);
	return reg;
}

void write(FILE* f, int v) {
	fwrite(&v, sizeof(int), 1, f);
}

// me devuelve la posición lógica actual en el archivo
long filePos(FILE* f) {
	long posFisica = ftell(f);
	long posLogica = posFisica / sizeof(int);
	return posLogica;
}

// me posiciona en la posición logica n
void seek(FILE* f, long n) {
	long posFisica = n * sizeof(int);
	fseek(f, posFisica, SEEK_SET);
}

// devuelve la cantidad de registros/elementos que tiene mi archivo
long fileSize(FILE* f) {
	long posLogicaActual = filePos(f); // obtengo la posición actual
	fseek(f, 0, SEEK_END); // voy al final del archivo
	long posLogicaFinal = filePos(f); // es lo mismo que la cantidad de registros/elementos
	seek(f, posLogicaActual); // vuelvo a la posición que estaba antes
	return posLogicaFinal;
}

// devuelve la posición donde se encuentra el registro o -1 si no lo encuentra
int busquedaSecuencial(FILE* f, int v) {
	long posLogicaActual = filePos(f); // obtengo la posición actual
	seek(f, 0); // me paro al principio del archivo

	int pos = -1;
	int reg = read(f);

	while(!feof(f) && pos == -1) { // mientras el archivo no termina y no encontré la posición
		if (reg == v) {
			pos = filePos(f) - 1; // guardo la posición del registro que ya leí (estoy parado en el próximo a leer)
		}
		reg = read(f);
	}

	seek(f, posLogicaActual); // vuelvo a la posición que estaba antes
	return pos;
}

// devuelve la posición donde se encuentra el registro o -1 si no lo encuentra
int busquedaBinaria(FILE* f, int v) {
	long posLogicaActual = filePos(f); // obtengo la posición actual

	int pos = -1;
	int ini = 0;
	int fin = fileSize(f) - 1;

	while(pos == -1 && ini <= fin) { // mientras no haya encontrado la posición y no haya terminado de recorrer el archivo
		int medio = (ini + fin) / 2;
		seek(f, medio);
		int reg = read(f);
		if (reg == v) {
			pos = medio;
		} else {
			if (v < reg) {
				fin  = medio - 1;
			} else {
				ini = medio + 1;
			}
		}
	}

	seek(f, posLogicaActual); // vuelvo a la posición que estaba antes
	return pos;
}

// 1) a) PILAS:
	- el ultimo elemento en entrar es el 1er elemento en salir (Last In First Out = LIFO)
		- los elementos se insertan al principio
		- cuando saco un elemento, siempre va a ser el el último que ingresó
	- no puedo recorrer la estructura, solo inicializar, estáVacia, push, pop

// 1) b) COLAS:
	- el primero elemento en entrar es el primero elemento en salir (Fist In First Out = FIFO)
		- los elementos se insertan al final
		- cuando saco un elemento, siempre va a ser el primero
	- no puedo recorrer la estructura solo inicializar, estáVacia, encolar, desencolar

// 1) c) LISTAS:
	- puedo agregar nodos donde quiera
	- puedo eliminar cualquier nodo
	- puedo recorrer la estructura inicializar, estáVacia, push, pop, buscar, liberar, insertaOrdenado, agregar, eliminar, buscaEInsertaOrdenado, ordenar

// Operaciones comunes para pilas, colas y listas

void inicializar(NodoPilaAlumno*& raiz) {
	raiz = NULL;
}

bool estaVacia(NodoColaAlumno* raiz) {
	return raiz == NULL;
}

// PUSH Y POP NO SE USAN EN COLAS

// push / meter / insertaAdelante / insertaPrimero
void push(NodoListaAlumno*& raiz, AlumnoInfo info) {
	NodoListaAlumno* pAux = new NodoListaAlumno(); // Creo un nuevo puntero auxiliar, Solo new para estructuras nuevas
	pAux -> info = info; // Le asigno a pAux el contenido del info que me mandaron por parametro
	pAux -> sgte = raiz; // Le digo a pAux que el contenido siguiente va a ser la vieja estructura que se encuentra en la raiz
	raiz = pAux; // Ahora la raiz apunta al nodo que se puso adelante de todos los que ya habia
}

// pop / sacar / suprimePrimero / eliminarPrimerNodo
AlumnoInfo pop(NodoListaAlumno*& raiz) {
	NodoListaAlumno* pAux = raiz; // Creamos un nuevo puntero auxiliar que apunte a donde apunta la raiz pero no hacemos el new porque no necesito una nueva estructura
	AlumnoInfo info = pAux -> info; // Asignamos la info de ese pAux
	raiz = pAux -> sgte; // hago que la raiz apunte a la siguiente estructura
	delete pAux; // elimino la estructura
	return info;
}

// Operaciones solo de colas - encolar, desencolar

void encolar(NodoColaAlumno*& colaFte, NodoColaAlumno*& colaFin, AlumnoInfo info) {
	NodoColaAlumno* pAux = new NodoColaAlumno(); // Creo un nuevo puntero auxiliar, Solo new para estructuras nuevas
	pAux -> info = info; // Le asigno a pAux el contenido del info que me mandaron por parametro
	pAux -> sgte = NULL; // Le digo a pAux que el contenido siguiente va a ser NULL ya que siempre la ultima estructura apunta a NULL
	if (estaVacia(colaFte)) { // Si colaFte está vacia le asigno la nueva estructura pAux 
		colaFte = pAux;
	} else {
		colaFin -> sgte = pAux;  // Le asigno a la direccion de colafin la del siguiente y lo asigno a pAux
	}
	colaFin = pAux; // le asigno la nueva estructura pAux a colaFin
}

AlumnoInfo desencolar(NodoColaAlumno*& colaFte, NodoColaAlumno*& colaFin) { 
	NodoColaAlumno* pAux = colaFte; // Creamos un nuevo puntero auxiliar que apunte a donde apunta colaFte pero no hacemos el new porque no necesito una nueva estructura
	AlumnoInfo info = pAux -> info; // Asignamos la info de ese pAux
	colaFte = pAux -> sgte; // hago que la colaFte apunte a la siguiente estructura
	delete pAux; // elimino la estructura
	if(estaVacia(colaFte)) {
		colaFin = NULL;
	}
	return info;
}

// Operaciones solo de listas - buscar, liberar, insertaOrdenado, agregar, eliminar, buscaEInsertaOrdenado, ordenar

void liberar(NodoListaAlumno*& raiz) {
	while(!estaVacia(raiz)) { // raiz != NULL
		pop(raiz);
	}
}

// devuelve la dirección de memoria del nodo que estoy buscando, sino retorna NULL
NodoListaAlumno* buscar(NodoListaAlumno* raiz, int legajo) {
	NodoListaAlumno* pNodo = NULL; // puntero al elemento que busco, si es que lo encontramos tendrá una direccion de memoria, sino seguirá siendo NULL
	NodoListaAlumno* pAux = raiz; // Creamos un nuevo puntero auxiliar que apunte a donde apunta la raiz pero no hacemos el new porque no necesito una nueva estructura

	while(pAux != NULL && pNodo == NULL) { // recorro mientras no llegué al final de la lista y no lo encontré
		if (pAux -> info.legajo == legajo) { // Si coinciden los legajos entonces guardo el valor en pNodo
			pNodo = pAux;
		}
		pAux = pAux -> sgte; // Mientras el puntero no sea null, avanzo
	}
	return pNodo;
}

NodoListaAlumno* insertaOrdenado(NodoListaAlumno*& raiz, AlumnoInfo info) { // PRECONDICION -> La lista ya tiene que estar ordenada por la clave que quiero insertar el nuevo dato ordenado
	NodoListaAlumno* pAux = new NodoListaAlumno(); // Creo un nuevo puntero auxiliar, Solo new para estructuras nuevas
	pAux -> info = info; // Le asigno a pAux el contenido del info que me mandaron por parametro

	NodoListaAlumno* pAct = raiz; // pAct es otro puntero auxiliar que hace referencia al actual al que le seteo el valor de la raiz
	NodoListaAlumno* pAnt = NULL; // pAnt es otro puntero auxiliar que hace referencia al anterior al que le seteo el valor de NULL

	while(pAct != NULL && pAct -> info.legajo < info.legajo) { // mientras pAct sea distinto de null y el contenido que tenga en la lista sea menor que lo que me pasaron por parametro, avanzo
		pAnt = pAct; // Al valor anterior le asigno el valor actual
		pAct = pAct -> sgte; // Al valor actual le coloco al valor siguiente
	}

	pAux -> sgte = pAct; //Ahora pAux apunta a donde apunta pAct

	if (pAnt == NULL) { // si el nodo anterior sigue siendo null
		raiz = pAux; // va adelante de todos los nodos
	} else {
		pAnt -> sgte = pAux; // va en el medio
	}
	return pAux;
}

// agregar / agregarAlFinal / insertarAlFinal / "encolar"
NodoListaAlumno* agregar(NodoListaAlumno*& raiz, AlumnoInfo info) {
	NodoListaAlumno* pAux = new NodoListaAlumno(); // Creo un nuevo puntero auxiliar, Solo new para estructuras nuevas
	pAux -> info = info; // Le asigno a pAux el contenido del info que me mandaron por parametro

	NodoListaAlumno* pAct = raiz; // pAct es otro puntero auxiliar que hace referencia al actual al que le seteo el valor de la raiz
	NodoListaAlumno* pAnt = NULL; // pAnt es otro puntero auxiliar que hace referencia al anterior al que le seteo el valor de NULL

	while(pAct != NULL) { // mientras el nodo actual sea distinto de NULL
		pAnt = pAct; // Al valor anterior le asigno el valor actual
		pAct = pAct -> sgte; // Al valor actual le coloco al valor siguiente
	}

	pAux -> sgte = pAct; // siempre pAct va a ser NULL

	if (pAnt == NULL) {
		raiz = pAux; //va adelante de todos los nodos
	} else {
		pAnt -> sgte = pAux; // va en el medio
	}
	return pAux;
}

void eliminar(NodoListaAlumno*& raiz, int legajo) {
	NodoListaAlumno* pAct = raiz; // pAct es otro puntero auxiliar que hace referencia al actual al que le seteo el valor de la raiz
	NodoListaAlumno* pAnt = NULL; // pAnt es otro puntero auxiliar que hace referencia al anterior al que le seteo el valor de NULL

	while(pAct != NULL && pAct -> info.legajo != legajo) { // mientras el nodo actual sea distinto de NULL y el contenido en legajo sea distinto al legajo enviado por parametro
		pAnt = pAct; // Al valor anterior le asigno el valor actual
		pAct = pAct -> sgte; // Al valor actual le coloco al valor siguiente
	}

	if (pAct -> info.legajo == legajo) { // si lo encontramos
		if (pAnt == NULL) {
			raiz = pAct -> sgte; // A la raiz le asigno el siguiente
		} else {
			pAnt -> sgte = pAct -> sgte; // Sino, al nodo anterior contenido siguiente va a ser igual al nodo actual contenido siguiente
		}
		delete pAct;
	}
}

// retorna la direccion de memoria del nodo encontrado o insertado si es que no existe
NodoListaAlumno* buscaEInsertaOrdenado(NodoListaAlumno*& raiz, AlumnoInfo info, bool& enc) {
	NodoListaAlumno* ptr = buscar(raiz, info.legajo); // Invoco a buscar y hago una busqueda por el valor que me pidan y esto me devuelve un puntero (PTR). [DATO]: Aunque la lista esté ordenada hago una busqueda secuencial y no una binaria porque no tengo acceso directo ya que al intentar acceder se pierde la performance.

	if (ptr == NULL) { // Si el puntero es NULL entonces no lo encontré y es nuevo
		ptr = insertaOrdenado(raiz, info); // Inserto este nuevo nodo y le asigno la posicion al ptr
		enc = false; // No lo encontré 
	} else {
		enc = true; // Lo encontré
	}
	return ptr;
}

void ordenar(NodoListaAlumno*& raiz) {
	NodoListaAlumno* raizAux;
	inicializar(raizAux); // raizAux = NULL

	while(!estaVacia(raiz)) { // raiz != NULL
		AlumnoInfo info = pop(raiz); // Eliminamos la raiz y nos devuelve un info
		insertaOrdenado(raizAux, info); // Inserto ese info a la raiz auxiliar
	}

	raiz = raizAux; // Cuando terminé de recorrer todo en el while debo setearle a la raiz original lo que tenga la raiz auxiliar
}

// LECTURA DE ARCHIVOS 

void cargarCompras(NodoListaUsuarios* raizListaUsuarios) {
	FILE * arch = fopen("compras.dat", "rb+");

	Compra regC;
	fread(&regC, sizeof(Compra), 1, arch);

	while(!feof(arch)) {
		NodoListaUsuarios* ptr = buscar(raizListaUsuarios, regC.idusuario);

		ptr -> info.cantidadLibrosComprados = ptr -> info.cantidadLibrosComprados + 1;

		Libro infoLibro;
		infoLibro.idLibro = regC.idLibro;
		strcpy(infoLibro.nombreLibro, regC.nombreLibro);

		push(ptr -> info.raizListaLibros, infoLibro);

		fread(&regC, sizeof(Compra), 1, arch);
	}

	fclose(arch);
}