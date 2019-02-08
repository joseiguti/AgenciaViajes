/*
 * Clientes.h
 *
 *  Created on: Oct 22, 2018
 *      Author: joseiguti
 */

#ifndef LIBRARY_CLIENTS_H_
#define LIBRARY_CLIENTS_H_

#endif /* LIBRARY_CLIENTES_H_ */

bool existReservsByClientId(int clientId) {

	bool toReturn = false;

	if (primeroC != NULL) {

		struct reservas * aux = primeroR;

		while (aux != NULL) {

			if (aux->cliente_id == clientId) {

				toReturn = true;

				break;
			}

			aux = aux->siguiente;
		}

	}

	return toReturn;
}

class Clientes {

public:

	void consultClientById() {

		if (primeroC == NULL) {

			std::cout << ERROR_BLANK_LIST << "\n";

		} else {

			clientes * toFind;

			Utility utility;

			toFind = this->getNodeById(
					utility.putNumber(TAG_ID, ERROR_NOT_A_NUMBER));

			if (toFind != NULL) {

				std::cout << TAG_NAME << toFind->nombre << " " << TAG_LASTNAME
						<< toFind->apellido << "\n";

			} else {

				std::cout << ERROR_ID_NOT_FOUND << " \n";

			}

		}

	}

	void consultClientByIdTree (){

		raizClientes = NULL;

		Utility utility;

		struct clientes * aux = primeroC;

		while (aux != NULL) {

			insertarEnArbol(raizClientes, aux->id, aux->nombre, aux->apellido, aux->type);

			aux = aux->siguiente;

		}

		int id = utility.putNumber("ID:", "Error, no es ID valido", 1, 1000000000);

		arbolClientes * buscar = this->buscarEnArbol(raizClientes, id);

		if (buscar != NULL){

			std::cout << "El cliente con el ID " << buscar->id << " existe en nuestra Bd con el nombre de \"" <<  buscar->nombre << " " << buscar->apellido << "\"\n\n";


		}else{

			std::cout << "No existe el cliente.\n";

		}

	}

	void printList() {

		raizClientes = NULL;

		tiposCliente.push_back("_blank_");

		tiposCliente.push_back("Normal");

		tiposCliente.push_back("Socio");

		int indice = 0;

		struct clientes * aux = primeroC;

		if (primeroC == NULL) {

			std::cout << ERROR_BLANK_LIST << "\n";

		} else {

			std::cout << "\n" << MSG_LIST_ALL << "\n";

			while (aux != NULL) {

				insertarEnArbol(raizClientes, aux->id, aux->nombre, aux->apellido, aux->type);

				aux = aux->siguiente;

				indice++;
			}

			std::cout << "\n";

		}

		std::cout

			<< "|" << TAG_ID << std::setw(toreturnNSpaces(TAG_ID)+1)

			<< "|" << TAG_NAME  << std::setw(toreturnNSpaces(TAG_NAME)+1)

			<< "|" << TAG_LASTNAME  << std::setw(toreturnNSpaces(TAG_LASTNAME)+1)

			<< "|" << TAG_TYPE_CLIENT_SHORT << std::setw(toreturnNSpaces(TAG_TYPE_CLIENT_SHORT)) << "|\n";

		pintarArbol (raizClientes);

		std::cout << "\n";

	}

	void insertAtEnd() {

		clientes * nuevo = this->createNode();

		if (nuevo != NULL) {

			std::cout << MSG_PUT_NODE << "\n\n";

			nuevo = this->updateNode(nuevo);

			nuevo->siguiente = NULL;
		}

		if (primeroC == NULL) {

			primeroC = nuevo;

		} else {

			clientes * ultimo = this->get((this->lenght() - 1));

			ultimo->siguiente = nuevo;

		}

	}

	void deleteById() {

		if (primeroC == NULL) {

			std::cout << ERROR_BLANK_LIST << "\n";

		} else {

			clientes * toDelete;

			Utility utility;

			toDelete = this->getNodeById(
					utility.putNumber(TAG_ID, ERROR_NOT_A_NUMBER));

			if (toDelete != NULL) {

				if (!existReservsByClientId(toDelete->id)) {

					if (this->lenght() == 1) {

						primeroC = NULL;

						std::cout << MSG_RECORD_DELETED << " " << toDelete->id
								<< "\n";

						toDelete->siguiente = NULL;

					} else {

						int actualPos = NULL;

						actualPos = this->getPosById(toDelete->id);

						if (actualPos == 0) {

							clientes * afterCurrent = this->get(1);

							primeroC = afterCurrent;

						} else {

							clientes * beforeCurrent = this->get(
									(actualPos - 1));

							clientes * afterCurrent = this->get(
									(actualPos + 1));

							beforeCurrent->siguiente = afterCurrent;

						}

						std::string newMessage(MSG_RECORD_DELETED);

						utility.replace(newMessage, "$id",
								std::to_string(toDelete->id));

						std::cout << newMessage << "\n";
					}

				} else {

					std::cout << ERROR_ID_EXISTS_IN_RESERVES << " \n";

				}

			} else {

				std::cout << ERROR_ID_NOT_FOUND << " \n";

			}

		}

	}

	clientes * getClientById(int id) {

		clientes * elemento = this->getNodeById(id);

		return elemento;
	}

	bool isEmpty() {

		bool isEmpty = true;

		if (this->lenght() > 0) {

			isEmpty = false;
		}

		return isEmpty;
	}

	int lenght() {

		int cantidad = 0;

		struct clientes * aux;

		aux = primeroC;

		while (aux != NULL) {

			aux = aux->siguiente;

			cantidad++;
		}

		free(aux);

		return cantidad;
	}

	clientes * get(int index) {

		return this->indexOf(index);
	}

private:

	arbolClientes * buscarEnArbol (arbolClientes * nodo, int valor, bool encontro = false){

		if (nodo->id == valor){

			return nodo;

		}else{

			if (nodo->izquierda != NULL){

				this->buscarEnArbol(nodo->izquierda, valor, encontro);

			}

			if (nodo->derecha != NULL){

				this->buscarEnArbol(nodo->derecha, valor, encontro);

			}

			return NULL;
		}

	}

	int toreturnNSpaces (std::string string){

		return (20-string.length());
	}

	void pintarArbol (arbolClientes * nodo){

		if (nodo != NULL){

			if (nodo->izquierda != NULL){

				pintarArbol(nodo->izquierda);

			}

			std::cout

				<< "|" << nodo->id << std::setw(toreturnNSpaces(std::to_string(nodo->id))) << " "

				<< "|" << nodo->nombre << std::setw( toreturnNSpaces(nodo->nombre) ) << " "

				<< "|" << nodo->apellido << std::setw(  toreturnNSpaces(nodo->apellido) ) << " "

				<< "|" << tiposCliente[nodo->type] << std::setw( toreturnNSpaces(tiposCliente[nodo->type]) ) << "|\n";


			if (nodo->derecha != NULL){

				pintarArbol(nodo->derecha);
			}

		}

	}

	arbolClientes * crearNodo() {

		arbolClientes * temp = new arbolClientes();

		return temp;
	}

	void insertarEnArbol(arbolClientes * nodo, 	int id, std::string nombre, std::string apellido, int type, std::string orderBy = "apellido") {

			if (nodo == NULL){

				arbolClientes * nuevo = this->crearNodo();

				nuevo->id = id;

				nuevo->nombre = nombre;

				nuevo->apellido = apellido;

				nuevo->type = type;

				nuevo->padre = NULL;

				raizClientes = nuevo;

			}else{

				if (id < nodo->id){

					if (nodo->izquierda == NULL){

						arbolClientes * nuevo = this->crearNodo();

						nuevo->id = id;

						nuevo->nombre = nombre;

						nuevo->apellido = apellido;

						nuevo->type = type;

						nuevo->padre = nodo;

						nodo->izquierda = nuevo;

					}else{

						insertarEnArbol(nodo->izquierda, id, nombre, apellido, type, orderBy);

					}

				}else {

					if (nodo->derecha == NULL){

						arbolClientes * nuevo = this->crearNodo();

						nuevo->id = id;

						nuevo->nombre = nombre;

						nuevo->apellido = apellido;

						nuevo->type = type;

						nuevo->padre = nodo;

						nodo->derecha = nuevo;

					}else{

						insertarEnArbol(nodo->derecha, id, nombre, apellido, type, orderBy);
					}

				}



			}

		}

	std::vector<std::string> tiposCliente;

	int getPosById(int id) {

		int pos = 0;

		struct clientes * aux;

		aux = primeroC;

		while (aux != NULL) {

			if (aux->id == id) {

				break;
			}

			aux = aux->siguiente;

			pos++;

		}

		return pos;
	}

	clientes * getNodeById(int id) {

		clientes * elemento = NULL;

		struct clientes * aux;

		aux = primeroC;

		while (aux != NULL) {

			if (aux->id == id) {

				elemento = aux;

				break;
			}

			aux = aux->siguiente;

		}

		return elemento;
	}

	clientes * createNode() {

		clientes * temporal = new clientes();

		if (temporal == NULL) {

			std::cout << MSG_NO_MEMORY << " \n";

		}

		return temporal;
	}

	clientes * updateNode(clientes * temporal) {

		clientes * toFind;

		Utility utility;

		std::string newMessage(ERROR_ID_ALREADY_EXITS);

		int id = NULL;

		do {

			id = utility.putNumber(TAG_ID, ERROR_NOT_A_NUMBER);

			toFind = this->getNodeById(id);

			if (toFind != NULL) {

				utility.replace(newMessage, "$id", std::to_string(toFind->id));

				utility.replace(newMessage, "$name", toFind->nombre);

				std::cout << newMessage << "\n";

			}

		} while (toFind != NULL);

		temporal->id = id;

		std::cout << TAG_NAME << " \n";

		std::cin.ignore();

		std::getline(std::cin, temporal->nombre);

		std::cout << TAG_LASTNAME << " \n";

		std::cin.ignore();

		std::getline(std::cin, temporal->apellido);

		temporal->type = utility.putNumber(TAG_TYPE_CLIENT, ERROR_NOT_A_NUMBER,
				1, 2);

		return temporal;
	}

	clientes * indexOf(int index) {

		int indexi = 0;

		clientes * elemento = NULL;

		struct clientes * aux;

		aux = primeroC;

		while (aux != NULL) {

			if (indexi == index) {

				elemento = aux;

				break;
			}

			aux = aux->siguiente;

			indexi++;
		}

		return elemento;
	}

};
