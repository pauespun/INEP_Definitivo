// main.cpp
#include <iostream>
#include <string>
#include <locale>
#include "CapaDePresentacio.hxx"

using namespace std;

// DECLARACIÓN ADELANTADA (Prototipos) para que el compilador las conozca
void menu_usuari();

void menu_principal()
{
	int opcio;
	do
	{
		cout << "\n===== MENU PRINCIPAL =====\n";
		cout << "1. Gestio d'usuaris\n";
		cout << "0. Sortir\n";
		cout << "Opcio: ";
		cin >> opcio;
		switch (opcio)
		{
		case 1:
			menu_usuari(); // Ahora sí la reconoce porque la declaramos arriba
			break;
		case 0:
			cout << "Adeu!\n";
			break;
		default:
			cout << "Opcio no valida.\n";
			break;
		}
	} while (opcio != 0);
}

void menu_usuari()
{
	int opcio;
	do
	{
		cout << "\n===== MENU USUARIS =====\n";
		cout << "1. Crear usuari\n";
		cout << "2. Llistar tots els usuaris\n";
		cout << "3. Consultar un usuari\n";
		cout << "4. Actualitzar usuari\n";
		cout << "5. Esborrar usuari\n";
		cout << "0. Tornar al menu principal\n";
		cout << "Opcio: ";
		cin >> opcio;
		// Obtenim la façana de presentació (Singleton)
		CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();
		switch (opcio)
		{
		case 1: presentacio.crear_usuari(); break;
		case 2: presentacio.llegir_usuaris(); break;
		case 3: presentacio.llegir_usuari(); break;
		case 4: presentacio.actualitzar_usuari(); break;
		case 5: presentacio.esborrar_usuari(); break;
		case 0: cout << "Tornant al menu principal...\n"; break;
		default: cout << "Opcio no valida.\n"; break;
		}
	} while (opcio != 0);
}

int main()
{
	std::locale::global(std::locale("es_ES.UTF-8"));
	menu_principal();
	return 0;
}