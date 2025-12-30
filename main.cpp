#include <iostream>
#include <string>
#include <locale>

#include "CapaDePresentacio.hxx"
#include "connexioBD.hxx" 

using namespace std;

// --- PROTOTIPS ---
void menu_inici();          // Menú 1: Login / Registro
void menu_principal();      // Menú 2: Menú general

// Els submenús ara necessiten saber si s'ha tancat la sessió des de dins
void menu_gestio_usuaris(bool& sessioTancada);
void menu_gestio_reserves();

// --- MAIN ---
int main()
{
    // Configuració regional per a caràcters especials
    std::locale::global(std::locale(""));

    // Inicialització de la BD (opcional segons la teva implementació)
    try {
        connexioBD::getInstance().getDB();
    }
    catch (...) {
        // Ignorem errors d'inicialització aquí, ja sortiran després
    }

    menu_inici();
    return 0;
}

// -------------------------------------------------------------------
// 1. MENÚ D'INICI (No loguejat)
// -------------------------------------------------------------------
void menu_inici()
{
    int opcio;
    bool sortir = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n===== PLANGO: MENU INICI =====\n";
        cout << "1. Iniciar Sessio\n";
        cout << "2. Registrar Usuari\n";
        cout << "3. Consultes\n"; // Assumim consulta experiències sense login
        cout << "0. Sortir\n";
        cout << "Opcio: ";

        // Validació d'entrada per evitar bucles infinits amb lletres
        if (!(cin >> opcio)) {
            cout << "Error: Entrada no valida.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (opcio)
        {
        case 1:
            // Si el login és correcte (retorna true), entrem al menú principal
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

// -------------------------------------------------------------------
// 2. MENÚ PRINCIPAL (Loguejat)
// -------------------------------------------------------------------
void menu_principal()
{
    int opcio;
    bool tancar_sessio = false; // Controla el bucle del menú principal
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n===== PLANGO: MENU PRINCIPAL =====\n";
        cout << "1. Gestio usuaris\n";
        cout << "2. Gestio reserves\n";
        cout << "3. Reserves\n"; // Visualitzar reserves directament
        cout << "4. Tancar sessio\n";
        cout << "0. Sortir de l'aplicacio\n";
        cout << "Opcio: ";

        if (!(cin >> opcio)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        switch (opcio)
        {
        case 1:
            // Passem 'tancar_sessio' per referència.
            // Si dins del submenú es tanca la sessió (o s'esborra l'usuari),
            // aquesta variable es posarà a true.
            menu_gestio_usuaris(tancar_sessio);
            break;

        case 2:
            menu_gestio_reserves();
            break;

        case 3:
            presentacio.visualitzarReserves();
            break;

        case 4:
            // Només sortim del bucle si realment s'ha tancat la sessió (usuari diu 'S')
            if (presentacio.tancarSessio()) {
                tancar_sessio = true;
            }
            break;

        case 0:
            cout << "Tancant aplicacio...\n";
            exit(0); // Sortida directa del programa
            break;

        default:
            cout << "Opcio no valida.\n";
            break;
        }

        // Si tornem d'un submenú i s'ha tancat la sessió, el 'while' fallarà i sortirem
        // automàticament cap al menu_inici().
    } while (!tancar_sessio);
}

// -------------------------------------------------------------------
// 2.1. SUBMENÚ GESTIÓ USUARIS
// -------------------------------------------------------------------
void menu_gestio_usuaris(bool& sessioTancada)
{
    int opcio;
    bool tornar = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n--- GESTIO USUARIS ---\n";
        cout << "1. Consultar usuari\n";
        cout << "2. Modificar usuari\n";
        cout << "3. Esborrar usuari\n";
        cout << "4. Tancar sessio\n";
        cout << "0. Tornar al menu principal\n";
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
            // Si esborrarUsuari retorna true, vol dir que s'ha esborrat i s'ha de tancar sessió
            if (presentacio.esborrarUsuari()) {
                // presentacio.esborrarUsuari ja hauria de netejar les dades de sessió internament
                // o pots cridar presentacio.tancarSessio() forçat si cal, però el bool ja indica èxit.

                sessioTancada = true; // Avisem al menú principal que plegui
                tornar = true;        // Sortim d'aquest submenú
            }
            break;
        case 4:
            // Si tanquem sessió aquí, avisem al pare
            if (presentacio.tancarSessio()) {
                sessioTancada = true; // Avisem al menú principal
                tornar = true;        // Sortim d'aquest submenú
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

// -------------------------------------------------------------------
// 2.2. SUBMENÚ GESTIÓ RESERVES
// -------------------------------------------------------------------
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
        cout << "0. Tornar al menu principal\n";
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