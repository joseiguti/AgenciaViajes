//
//  main.cpp
//  EstructuraDeDatos
//
//  Created by José Ignacio Gutiérrez Guzmán on 8/6/18.
//  Copyright © 2018 José Ignacio Gutiérrez Guzmán. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <curses.h>
#include <cctype>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Library/Strings.h"
#include "Library/Struct.h"

#include "Library/AgenciaViajes.h"
#include "Library/Utility.h"

#include "Library/Clientes.h"
#include "Library/Hoteles.h"
#include "Library/Reservas.h"
#include "Library/Menu.h"

int main(int argc, const char * argv[]) {

	Menu menu;

	menu.loadData();

	menu.run();

	return 0;
}
