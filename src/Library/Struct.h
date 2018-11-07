//
//  Struct.h
//  EstructuraDeDatos
//
//  Created by José Ignacio Gutiérrez Guzmán on 8/8/18.
//  Copyright © 2018 José Ignacio Gutiérrez Guzmán. All rights reserved.
//

#ifndef Struct_h
#define Struct_h

#endif /* Struct_h */

struct fecha {

	int dia;

	int mes;

	int ano;
};

struct hotel {

	int id;

	std::string nombre;

	hotel * siguiente;

};

struct reservas {

	bool estado;

	int hotel_id;

	int cliente_id;

	struct fecha fecha_reserva;

	reservas * siguiente;
};

struct clientes {

	int id;

	std::string nombre;

	std::string apellido;

	int type;

	struct reservas reserva_cliente;

	clientes * siguiente;
};

struct clientes * primeroC;

struct hotel * primeroH;

struct reservas * primeroR;
