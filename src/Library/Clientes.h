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

	void printList() {

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

				std::cout

				<< TAG_ID << aux->id << " "

				<< TAG_NAME << aux->nombre << " "

				<< TAG_LASTNAME << aux->apellido << " "

				<< TAG_TYPE_CLIENT_SHORT << tiposCliente[aux->type] << "\n";

				aux = aux->siguiente;

				indice++;
			}

			std::cout << "\n";

		}

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
