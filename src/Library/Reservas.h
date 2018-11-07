/*
 * Reservas.h
 *
 *  Created on: Oct 22, 2018
 *      Author: joseiguti
 */

#ifndef LIBRARY_RESERVAS_H_
#define LIBRARY_RESERVAS_H_

#endif /* LIBRARY_RESERVAS_H_ */

class Reservas {

public:

	void printList() {

		int indice = 0;

		struct reservas * aux = primeroR;

		if (primeroR == NULL) {

			std::cout << ERROR_BLANK_LIST << "\n";

		} else {

			std::cout << "\n" << MSG_LIST_ALL << "\n";

			while (aux != NULL) {

				std::cout

				<< TAG_ID_CLIENT << aux->cliente_id << ", "

				<< TAG_HOTEL
						<< this->hotelesR.getHotelById(aux->hotel_id)->nombre
						<< ", "

						<< TAG_NAME
						<< this->clientesR.getClientById(aux->cliente_id)->nombre
						<< ", "

						<< TAG_LASTNAME
						<< this->clientesR.getClientById(aux->cliente_id)->apellido
						<< ", "

						<< TAG_DATE << aux->fecha_reserva.ano << "/"
						<< aux->fecha_reserva.mes << "/"
						<< aux->fecha_reserva.dia

						<< "\n";

				aux = aux->siguiente;

				indice++;

				if (indice == 10) {
					break;
				}

			}

			std::cout << "\n";

		}

	}

	void addReserva() {

		reservas * nuevo = this->createNode();

		Clientes cliente;

		Hoteles hoteles;

		if (nuevo != NULL) {

			std::cout << MSG_PUT_NODE << "\n\n";

			nuevo = this->updateNode(nuevo);

			nuevo->siguiente = NULL;
		}

		if (primeroR == NULL) { // NO habian elementos en la lista

			primeroR = nuevo;

		} else { // Ya habian elementos en la lista

			if (cliente.getClientById(nuevo->cliente_id)->type == 2) {

				reservas * nodoUltimo2 = this->getLastNodeByCustomerType(2);

				reservas * nodoPrimer1 = this->getFirstNodeByCustomerType(1);

				if (cliente.getClientById(nodoUltimo2->cliente_id)->type == 1) {

					primeroR = nuevo;

					nuevo->siguiente = nodoUltimo2;

				} else {

					nodoUltimo2->siguiente = nuevo;

					nuevo->siguiente = nodoPrimer1;

				}

			} else {

				reservas * ultimo = this->get((this->lenght() - 1));

				ultimo->siguiente = nuevo;

			}

		}

	}

	reservas * getLastNode() {

		Clientes cliente;

		struct reservas * nodo = primeroR;

		struct reservas * aux = primeroR;

		while (aux != NULL) {

			nodo = aux;

			aux = aux->siguiente;

		}

		return nodo;
	}

	Reservas(Hoteles hoteles, Clientes clientes);

private:

	Clientes clientesR;

	Hoteles hotelesR;

	reservas * getLastNodeByCustomerType(int customerType) {

		Clientes cliente;

		struct reservas * nodo = primeroR;

		struct reservas * aux = primeroR;

		while (aux != NULL) {

			if (cliente.getClientById(aux->cliente_id)->type == customerType) {

				nodo = aux;
			}

			aux = aux->siguiente;

		}

		return nodo;
	}

	reservas * getFirstNodeByCustomerType(int customerType) {

		Clientes cliente;

		struct reservas * nodo = NULL;

		struct reservas * aux = primeroR;

		while (aux != NULL) {

			if (cliente.getClientById(aux->cliente_id)->type == customerType) {

				nodo = aux;

				break;
			}

			aux = aux->siguiente;

		}

		return nodo;

	}

	reservas * updateNode(reservas * temporal) {

		Utility utility;

		std::string newMessage(ERROR_ID_NOT_EXISTS);

		clientes * toFindClient = new clientes();

		hotel * toFindHotel = new hotel();

		if (!this->clientesR.isEmpty()) {

			if (!this->hotelesR.isEmpty()) {

				int idClient;

				do {

					idClient = utility.putNumber(TAG_ID_CLIENT,
							ERROR_NOT_A_NUMBER);

					toFindClient = this->clientesR.getClientById(idClient);

					if (toFindClient == NULL) {

						utility.replace(newMessage, "$id",
								std::to_string(idClient));

						std::cout << newMessage << "\n";

					}

				} while (toFindClient == NULL);

				temporal->cliente_id = toFindClient->id;

				int idHotel;

				do {

					idHotel = utility.putNumber(TAG_ID_HOTEL,
							ERROR_NOT_A_NUMBER);

					toFindHotel = this->hotelesR.getHotelById(idHotel);

					if (toFindHotel == NULL) {

						utility.replace(newMessage, "$id",
								std::to_string(idHotel));

						std::cout << newMessage << "\n";

					}

				} while (toFindHotel == NULL);

				temporal->hotel_id = toFindHotel->id;

				temporal->fecha_reserva.ano = utility.putNumber(TAG_YEAR,
						ERROR_NOT_A_NUMBER, 2000, 2020);

				temporal->fecha_reserva.mes = utility.putNumber(TAG_MONTH,
						ERROR_NOT_A_NUMBER, 1, 12);

				temporal->fecha_reserva.dia = utility.putNumber(TAG_DAY,
						ERROR_NOT_A_NUMBER, 1, 31);

			} else {

				std::cout << ERROR_BLANK_LIST_HOTELS << "\n";

			}

		} else {

			std::cout << ERROR_BLANK_LIST_CLIENTS << "\n";

		}

		return temporal;
	}

	reservas * createNode() {

		reservas * temporal = new reservas();

		if (temporal == NULL) {

			std::cout << MSG_NO_MEMORY << " \n";

		}

		return temporal;
	}

	int lenght() {

		int cantidad = 0;

		struct reservas * aux;

		aux = primeroR;

		while (aux != NULL) {

			aux = aux->siguiente;

			cantidad++;
		}

		free(aux);

		return cantidad;
	}

	reservas * get(int index) {

		return this->indexOf(index);
	}

	reservas * indexOf(int index) {

		int indexi = 0;

		reservas * elemento = NULL;

		struct reservas * aux;

		aux = primeroR;

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

Reservas::Reservas(Hoteles hoteles, Clientes clientes) {

	this->hotelesR = hoteles;

	this->clientesR = clientes;
}
