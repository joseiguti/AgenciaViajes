//
//  Menu.h
//  EstructuraDeDatos
//
//  Created by José Ignacio Gutiérrez Guzmán on 9/3/18.
//  Copyright © 2018 José Ignacio Gutiérrez Guzmán. All rights reserved.
//

#ifndef Menu_h
#define Menu_h

#endif /* Menu_h */

class Menu {

public:

	void run() {

		runMainMenu();

	}

	void loadData() {

		int lineCounter = 0;

		std::string initialPath = PATH_DATA;

		std::string line;

		/**
		 * Carga de hoteles
		 */
		std::ifstream myfileHoteles(initialPath + "hoteles.data");

		Hoteles hoteles;

		if (myfileHoteles.is_open()) {

			lineCounter = 0;

			while (getline(myfileHoteles, line)) {

				struct hotel * temporal = new hotel();

				//std::cout << line << '\n';

				std::vector < std::string > splittedStrings = this->split(line,
						'|');

				for (int i = 0; i < splittedStrings.size(); i++) {

					//std::cout << i << " " << splittedStrings[i] << std::endl;

					if (i == 0)

						temporal->id = stoi(splittedStrings[i]);

					if (i == 1)

						temporal->nombre = splittedStrings[i];

				}

				if (lineCounter == 0) {

					temporal->siguiente = NULL;

					primeroH = temporal;

				} else {

					struct hotel * ultimo = hoteles.get((hoteles.lenght() - 1));

					ultimo->siguiente = temporal;

				}

				lineCounter++;
			}

			myfileHoteles.close();
		}

		/**
		 * Carga de clientes.
		 */
		std::ifstream myfileClientes(initialPath + "clientes.data");

		Clientes cliente;

		if (myfileClientes.is_open()) {

			lineCounter = 0;

			while (getline(myfileClientes, line)) {

				struct clientes * temporal = new clientes();

				std::vector < std::string > splittedStrings = this->split(line,
						'|');

				for (int i = 0; i < splittedStrings.size(); i++) {

					if (i == 0)

						temporal->id = stoi(splittedStrings[i]);

					if (i == 1)

						temporal->nombre = splittedStrings[i];

					if (i == 2)

						temporal->apellido = splittedStrings[i];

					if (i == 3)

						temporal->type = stoi(splittedStrings[i]);

				}

				if (lineCounter == 0) {

					temporal->siguiente = NULL;

					primeroC = temporal;

				} else {

					struct clientes * ultimo = cliente.get(
							(cliente.lenght() - 1));

					ultimo->siguiente = temporal;

				}

				lineCounter++;
			}

			myfileClientes.close();
		}

		std::ifstream myfileReservas(initialPath + "reservas.data");

		Reservas reserva(hoteles, cliente);

		if (myfileReservas.is_open()) {

			lineCounter = 0;

			while (getline(myfileReservas, line)) {

				struct reservas * temporal = new reservas();

				std::vector < std::string > splittedStrings = this->split(line,
						'|');

				for (int i = 0; i < splittedStrings.size(); i++) {

					if (i == 0)

						temporal->cliente_id = stoi(splittedStrings[i]);

					if (i == 1)

						temporal->hotel_id = stoi(splittedStrings[i]);

					if (i == 2)

						temporal->fecha_reserva.ano = stoi(splittedStrings[i]);

					if (i == 3)

						temporal->fecha_reserva.mes = stoi(splittedStrings[i]);

					if (i == 4)

						temporal->fecha_reserva.dia = stoi(splittedStrings[i]);

				}

				if (lineCounter == 0) {

					temporal->siguiente = NULL;

					primeroR = temporal;

				} else {

					struct reservas * ultimo = reserva.getLastNode();

					ultimo->siguiente = temporal;

				}

				lineCounter++;
			}

			myfileReservas.close();
		}

	}

protected:

	std::vector<std::string> split(std::string strToSplit, char delimeter) {

		std::stringstream ss(strToSplit);

		std::string item;

		std::vector < std::string > splittedStrings;

		while (std::getline(ss, item, delimeter)) {

			splittedStrings.push_back(item);

		}

		return splittedStrings;
	}

	std::vector<std::string> split(std::string stringToBeSplitted,
			std::string delimeter) {

		std::vector < std::string > splittedString;

		int startIndex = 0;

		int endIndex = 0;

		while ((endIndex = stringToBeSplitted.find(delimeter, startIndex))
				< stringToBeSplitted.size()) {

			std::string val = stringToBeSplitted.substr(startIndex,
					endIndex - startIndex);

			splittedString.push_back(val);

			startIndex = endIndex + delimeter.size();

		}
		if (startIndex < stringToBeSplitted.size()) {

			std::string val = stringToBeSplitted.substr(startIndex);

			splittedString.push_back(val);
		}

		return splittedString;
	}

	int showMainMenu() {

		std::cout << "::: Main Menu :::\n";

		std::cout << "1- Hoteles.\n";

		std::cout << "2- Clientes.\n";

		std::cout << "3- Reservas.\n";

		std::cout << "4- Save Data.\n";

		std::cout << "5- Exit.\n";

		return 0;
	}

	void runMainMenu() {

		Hoteles hoteles;

		Clientes clientes;

		Reservas reservas(hoteles, clientes);

		Utility utility;

		int option = 0;

		do {

			showMainMenu();

			option = utility.putNumber(MSG_SELECT_ANY_OPTION,
					ERROR_NOT_A_NUMBER, 1, 5);

			switch (option) {
			case 1:
				runHotelsMenu(hoteles);
				break;
			case 2:
				runClientsMenu(clientes);
				break;
			case 3:
				runReservasMenu(reservas);
				break;
			case 4:
				utility.saveData();
				break;
			}

		} while (option != 5);

	}

	int showHotelesMenu() {

		std::cout << "::: Hotels Menu :::\n";

		std::cout << "1- Listar.\n";

		std::cout << "2- Agregar.\n";

		std::cout << "3- Eliminar por ID.\n";

		std::cout << "4- Back to main menu.\n";

		return 0;

	}

	void runHotelsMenu(Hoteles hoteles) {

		Utility utility;

		int option = 0;

		do {

			showHotelesMenu();

			option = utility.putNumber(MSG_SELECT_ANY_OPTION,
					ERROR_NOT_A_NUMBER, 1, 4);

			switch (option) {

			case 1:
				hoteles.printList();
				break;
			case 2:
				hoteles.insertAtEnd();
				break;
			case 3:
				hoteles.deleteById();
				break;
			case 4:
				std::cout << "Backing to the main menu...\n\n";
				break;

			}

		} while (option != 4);

	}

	int showClientesMenu() {

		std::cout << "::: Clients Menu :::\n";

		std::cout << "1- Listar.\n";

		std::cout << "2- Agregar.\n";

		std::cout << "3- Eliminar por ID.\n";

		std::cout << "4- Consultar por ID.\n";

		std::cout << "5- Back to main menu.\n";

		return 0;

	}

	void runClientsMenu(Clientes clientes) {

		Utility utility;

		int option = 0;

		do {

			showClientesMenu();

			option = utility.putNumber(MSG_SELECT_ANY_OPTION,
					ERROR_NOT_A_NUMBER, 1, 5);

			switch (option) {

			case 1:
				clientes.printList();
				break;
			case 2:
				clientes.insertAtEnd();
				break;
			case 3:
				clientes.deleteById();
				break;
			case 4:
				clientes.consultClientById();
				break;
			case 5:
				std::cout << "Backing to the main menu...\n";
				break;
			}

		} while (option != 5);

	}

	int showReservasMenu() {

		std::cout << "::: Reservas Menu :::\n";

		std::cout << "1- Agregar.\n";

		std::cout << "2- Listar.\n";

		std::cout << "3- Back to main menu.\n";

		return 0;
	}

	void runReservasMenu(Reservas reservas) {

		Utility utility;

		int option = 0;

		do {

			showReservasMenu();

			option = utility.putNumber(MSG_SELECT_ANY_OPTION,
					ERROR_NOT_A_NUMBER, 1, 3);

			switch (option) {

			case 1:
				reservas.addReserva();
				break;
			case 2:
				reservas.printList();
				break;
			case 3:
				std::cout << "Backing to the main menu...\n";
				break;
			}

		} while (option != 3);

	}

};
