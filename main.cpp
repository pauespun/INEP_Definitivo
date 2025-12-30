#include <iostream>
#include <string>
#include <locale>

#include "CapaDePresentacio.hxx"
#include "connexioBD.hxx" 

using namespace std;

void menu_inici();          
void menu_principal();      
void menu_gestio_usuaris(bool& sessioTancada);
void menu_gestio_reserves();
void menu_consultes();      


int main()
{
    std::locale::global(std::locale(""));

    try {
        connexioBD::getInstance().getDB();
    }
    catch (...) {
    }

    menu_inici();
    return 0;
}


void menu_inici()
{
    int opcio;
    bool sortir = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n===== PLANGO: MENU INICI =====\n";
        cout << "1. Iniciar Sessio\n";
        cout << "2. Registrar Usuari\n";
        cout << "3. Consultes\n"; 
        cout << "0. Sortir\n";
        cout << "Opcio: ";

        if (!(cin >> opcio)) {
            cout << "Error: Entrada no valida.\n";
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        switch (opcio)
        {
        case 1:
            if (presentacio.iniciarSessio()) {
                menu_principal();
            }
            break;
        case 2:
            presentacio.registrarUsuari();
            break;
        case 3:
            presentacio.consultarExperiencies();
            break;
        case 0:
            cout << "Adeu!\n";
            sortir = true;
            break;
        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!sortir);
}


void menu_principal()
{
    int opcio;
    bool tancar_sessio = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n===== PLANGO: MENU PRINCIPAL =====\n";
        cout << "1. Gestio usuaris\n";
        cout << "2. Gestio reserves\n";  
        cout << "3. Consultes\n";        
        cout << "4. Tancar sessio\n";
        cout << "0. Sortir\n";
        cout << "Opcio: ";

        if (!(cin >> opcio)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        switch (opcio)
        {
        case 1:
            menu_gestio_usuaris(tancar_sessio);
            break;

        case 2:
            menu_gestio_reserves();
            break;

        case 3:
            menu_consultes(); 
            break;

        case 4:
            if (presentacio.tancarSessio()) {
                tancar_sessio = true;
            }
            break;

        case 0:
            cout << "Tancant aplicacio...\n";
            exit(0);
            break;

        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!tancar_sessio);
}


void menu_gestio_usuaris(bool& sessioTancada)
{
    int opcio;
    bool tornar = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n--- GESTIO USUARIS ---\n";
        cout << "1. Consulta usuari\n";
        cout << "2. Modifica usuari\n";
        cout << "3. Esborra usuari\n";
        cout << "4. Tancar sessio\n";
        cout << "0. Sortir\n";
        cout << "Opcio: ";

        if (!(cin >> opcio)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        switch (opcio)
        {
        case 1:
            presentacio.consultarUsuari();
            break;
        case 2:
            presentacio.modificarUsuari();
            break;
        case 3:
            if (presentacio.esborrarUsuari()) {
                sessioTancada = true;
                tornar = true;
            }
            break;
        case 4:
            if (presentacio.tancarSessio()) {
                sessioTancada = true;
                tornar = true;
            }
            break;
        case 0:
            tornar = true;
            break;
        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!tornar);
}

void menu_gestio_reserves()
{
    int opcio;
    bool tornar = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n--- GESTIO RESERVES ---\n";
        cout << "1. Reservar escapada\n";
        cout << "2. Reservar activitat\n";
        cout << "3. Visualitzar reserves\n"; 
        cout << "0. Sortir\n";
        cout << "Opcio: ";

        if (!(cin >> opcio)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        switch (opcio)
        {
        case 1:
            presentacio.reservarEscapada();
            break;
        case 2:
            presentacio.reservarActivitat();
            break;
        case 3:
            presentacio.visualitzarReserves();
            break;
        case 0:
            tornar = true;
            break;
        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!tornar);
}

void menu_consultes()
{
    int opcio;
    bool tornar = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n--- CONSULTES ---\n";
        cout << "1. Consultar experiencies\n";
		cout << "2. Consultar novetats\n";   
        cout << "3. Consultar mes reservades\n";
        cout << "0. Sortir\n";
        cout << "Opcio: ";

        if (!(cin >> opcio)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        switch (opcio)
        {
        case 1:
            presentacio.consultarExperiencies();
            break;
		case 2:
			// Aquí iría el método para consultar novedades
			//presentacio.consultarNovetats();
			break;
		case 3:
			// Aquí iría el método para consultar las más reservadas
			//presentacio.consultarMesReservades();
			break;
        case 0:
            tornar = true;
            break;
        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!tornar);
}