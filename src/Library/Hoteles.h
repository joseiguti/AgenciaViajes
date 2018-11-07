/*
 * Hoteles.h
 *
 *  Created on: Sep 27, 2018
 *      Author: joseiguti
 */

#ifndef LIBRARY_HOTELES_H_
#define LIBRARY_HOTELES_H_

#endif /* LIBRARY_HOTELES_H_ */

class Hoteles {

public:

	bool existReservsByHotelId(int hotelId) {

		bool toReturn = false;

		if (primeroC != NULL) {

			struct reservas * aux = primeroR;

			while (aux != NULL) {

				if (aux->hotel_id == hotelId) {

					toReturn = true;

					break;
				}

				aux = aux->siguiente;
			}

		}

		return toReturn;
	}

	void printList() {

		int indice = 0;

		struct hotel * aux = primeroH;

		if (primeroH == NULL) {

			std::cout << ERROR_BLANK_LIST << "\n";

		} else {

			std::cout << "\n" << MSG_LIST_ALL << "\n";

			while (aux != NULL) {

				std::cout << TAG_ID << aux->id << ", " << TAG_NAME
						<< aux->nombre << "\n";

				aux = aux->siguiente;

				indice++;
			}

			std::cout << "\n";

		}

	}

	void insertAtEnd() {

		hotel * nuevo = this->createNode();

		if (nuevo != NULL) {

			std::cout << MSG_PUT_NODE << "\n\n";

			nuevo = this->updateNode(nuevo);

			nuevo->siguiente = NULL;
		}

		if (primeroH == NULL) {

			primeroH = nuevo;

		} else {

			hotel * ultimo = this->get((this->lenght() - 1));

			ultimo->siguiente = nuevo;

		}

	}

	void deleteById() {

		if (primeroH == NULL) {

			std::cout << ERROR_BLANK_LIST << "\n";

		} else {

			hotel * toDelete;

			Utility utility;

			toDelete = this->getNodeById(
					utility.putNumber(TAG_ID, ERROR_NOT_A_NUMBER));

			if (toDelete != NULL) {

				if (!this->existReservsByHotelId(toDelete->id)) {

					if (this->lenght() == 1) {

						primeroH = NULL;

						std::cout << MSG_RECORD_DELETED << " " << toDelete->id
								<< "\n";

						toDelete->siguiente = NULL;

					} else {

						int actualPos = NULL;

						actualPos = this->getPosById(toDelete->id);

						if (actualPos == 0) {

							hotel * afterCurrent = this->get(1);

							primeroH = afterCurrent;

						} else {

							hotel * beforeCurrent = this->get((actualPos - 1));

							hotel * afterCurrent = this->get((actualPos + 1));

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

	bool isEmpty() {

		bool isEmpty = true;

		if (this->lenght() > 0) {

			isEmpty = false;
		}

		return isEmpty;
	}

	hotel * getHotelById(int id) {

		hotel * elemento = this->getNodeById(id);

		return elemento;
	}

	int lenght() {

		int cantidad = 0;

		struct hotel * aux;

		aux = primeroH;

		while (aux != NULL) {

			aux = aux->siguiente;

			cantidad++;
		}

		free(aux);

		return cantidad;
	}

	hotel * get(int index) {

		return this->indexOf(index);
	}

private:

	int getPosById(int id) {

		int pos = 0;

		struct hotel * aux;

		aux = primeroH;

		while (aux != NULL) {

			if (aux->id == id) {

				break;
			}

			aux = aux->siguiente;

			pos++;

		}

		return pos;
	}

	hotel * getNodeById(int id) {

		hotel * elemento = NULL;

		struct hotel * aux;

		aux = primeroH;

		while (aux != NULL) {

			if (aux->id == id) {

				elemento = aux;

				break;
			}

			aux = aux->siguiente;

		}

		return elemento;
	}

	hotel * createNode() {

		hotel * temporal = new hotel();

		if (temporal == NULL) {

			std::cout << MSG_NO_MEMORY << " \n";

		}

		return temporal;
	}

	hotel * updateNode(hotel * temporal) {

		hotel * toFind;

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

		return temporal;
	}

	hotel * indexOf(int index) {

		int indexi = 0;

		hotel * elemento = NULL;

		struct hotel * aux;

		aux = primeroH;

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
