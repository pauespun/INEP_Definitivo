#include <iostream>
#include <string>
#include <locale>
#include "CapaDePresentacio.hxx"

using namespace std;

// Prototips
void menu_inici();      // Menú quan NO estem loguejats
void menu_principal();  // Menú quan JA estem loguejats (dins l'app)

int main()
{
    // Configurem l'idioma per acceptar accents i caràcters especials
    std::locale::global(std::locale("es_ES.UTF-8"));

    // L'aplicació comença al menú d'inici (Login/Registre)
    menu_inici();

    return 0;
}

// -------------------------------------------------------------------
// MENÚ INICIAL (Abans d'entrar al sistema)
// Casos d'ús: 3.1.1 Iniciar Sessió, 3.1.3 Registrar Usuari
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
        cout << "0. Sortir de l'aplicacio\n";
        cout << "Opcio: ";
        cin >> opcio;

        switch (opcio)
        {
        case 1:
            // Intentem iniciar sessió. Si va bé, passem al menú principal.
            if (presentacio.iniciarSessio()) {
                menu_principal();
            }
            break;
        case 2:
            presentacio.registrarUsuari();
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
// MENÚ PRINCIPAL (Dins del sistema)
// Casos d'ús: Gestió d'usuaris, Reserves, etc.
// -------------------------------------------------------------------
void menu_principal()
{
    int opcio;
    bool tancar_sessio = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n===== PLANGO: MENU PRINCIPAL =====\n";
        cout << "1. Consultar el meu usuari\n";
        cout << "2. Modificar el meu usuari\n";
        cout << "3. Esborrar el meu usuari\n";
        cout << "----------------------------\n";
        cout << "4. Gestio de Reserves (Proximament)\n";
        cout << "----------------------------\n";
        cout << "0. Tancar Sessio\n";
        cout << "Opcio: ";
        cin >> opcio;

        switch (opcio)
        {
        case 1:
            presentacio.consultarUsuari();
            break;
        case 2:
            presentacio.modificarUsuari();
            break;
        case 3:
            // Si l'usuari s'esborra, hem de tancar sessió automàticament
            if (presentacio.esborrarUsuari()) {
                tancar_sessio = true;
            }
            break;
        case 4:
            cout << "Funcionalitat en construccio...\n";
            break;
        case 0:
            presentacio.tancarSessio();
            cout << "Tancant sessio...\n";
            tancar_sessio = true; // Això ens farà tornar al menu_inici()
            break;
        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!tancar_sessio);
}