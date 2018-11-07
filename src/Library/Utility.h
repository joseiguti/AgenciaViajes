/*
 * Utility.h
 *
 *  Created on: Oct 4, 2018
 *      Author: joseiguti
 */

#ifndef LIBRARY_UTILITY_H_
#define LIBRARY_UTILITY_H_

#endif /* LIBRARY_UTILITY_H_ */

class Utility {

public:

	void saveData() {

		std::string initialPath = PATH_DATA;

		std::ofstream clientesFile;

		clientesFile.open(initialPath + "clientes.data");

		struct clientes * aux = primeroC;

		while (aux != NULL) {

			clientesFile << aux->id << "|" << aux->nombre << "|"
					<< aux->apellido << "|" << aux->type << "\n";

			aux = aux->siguiente;
		}

		clientesFile.close();

		std::ofstream hotelesFile;

		hotelesFile.open(initialPath + "hoteles.data");

		struct hotel * aux1 = primeroH;

		while (aux1 != NULL) {

			hotelesFile << aux1->id << "|" << aux1->nombre << "\n";

			aux1 = aux1->siguiente;
		}

		hotelesFile.close();

		std::ofstream reservasFile;

		reservasFile.open(initialPath + "reservas.data");

		struct reservas * aux2 = primeroR;

		while (aux2 != NULL) {

			reservasFile << aux2->cliente_id << "|" << aux2->hotel_id << "|"
					<< aux2->fecha_reserva.ano << "|" << aux2->fecha_reserva.mes
					<< "|" << aux2->fecha_reserva.dia << "\n";

			aux2 = aux2->siguiente;
		}

		reservasFile.close();

		std::cout << MSG_ALL_DATA_SAVED << "\n";

	}

	bool replace(std::string& str, const std::string& from,
			const std::string& to) {

		size_t start_pos = str.find(from);

		if (start_pos == std::string::npos)

			return false;

		str.replace(start_pos, from.length(), to);

		return true;
	}

	int putNumber(std::string askString, std::string notanumString, int min = 0,
			int max = 100000000) {

		std::string errorRange(ERROR_RANGE_NUMBER);

		bool isNumber = false;

		bool inRange = false;

		std::string id;

		do {

			std::cout << askString << " \n";

			std::cin >> id;

			isNumber = this->isNumber(id);

			if (!isNumber)

				std::cout << notanumString << " \n";

			if (stringToInteger(id) < min || stringToInteger(id) > max) {

				replace(errorRange, "$num1", std::to_string(min));

				replace(errorRange, "$num2", std::to_string(max));

				std::cout << errorRange << " \n";

			} else {

				inRange = true;
			}

		} while (isNumber == false || inRange == false);

		return stringToInteger(id);
	}

private:

	int stringToInteger(std::string num) {

		int toReturn = 0;

		try {

			toReturn = atoi(num.c_str());

		} catch (int param) {

			std::cout << " ...Exception";

		}

		return toReturn;
	}

	bool isNumber(const std::string& s) {

		std::string::const_iterator it = s.begin();

		while (it != s.end() && std::isdigit(*it)) {

			++it;
		}

		return (!s.empty() && it == s.end()) ? true : false;
	}

};
