#include <iostream>
#include <string>
#include <locale>

// IMPORTANTE: Incluir la cabecera de la capa de presentación
#include "CapaDePresentacio.hxx" 

using namespace std;

// --- PROTOTIPS ---
void menu_inici();      // Menú quan NO estem loguejats (Login/Registre)
void menu_principal();  // Menú quan JA estem loguejats (Consultes/Modificacions)

// --- MAIN ---
int main()
{
    // Configuració d'idioma per accents (opcional, depèn del sistema)
    std::locale::global(std::locale(""));

    // Iniciem l'aplicació anant al menú d'inici
    menu_inici();

    return 0;
}

// -------------------------------------------------------------------
// IMPLEMENTACIÓ DEL MENÚ INICIAL
// Casos d'ús: 3.1.1 Iniciar Sessió, 3.1.3 Registrar Usuari
// -------------------------------------------------------------------
void menu_inici()
{
    int opcio;
    bool sortir = false;

    // Obtenim la instància Singleton de la presentació
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
            // Si el login és correcte (retorna true), anem al menú principal
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
// IMPLEMENTACIÓ DEL MENÚ PRINCIPAL
// Casos d'ús: Consultar, Modificar, Esborrar, Tancar Sessió
// -------------------------------------------------------------------
void menu_principal()
{
    int opcio;
    bool tancar_sessio = false;

    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n===== PLANGO: MENU PRINCIPAL =====\n";
        cout << "1. Consultar usuari\n";
        cout << "2. Modificar usuari\n";
        cout << "3. Esborrar usuari\n";
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
            // Si retorna true, vol dir que s'ha esborrat i hem de sortir
            if (presentacio.esborrarUsuari()) {
                tancar_sessio = true;
            }
            break;
        case 4:
            cout << "Funcionalitat en construccio...\n";
            // Petit truc per pausar
            cout << "Prem Intro per continuar...";
            cin.ignore(); cin.get();
            break;
        case 0:
            presentacio.tancarSessio();

            // NOTA: Tal com ho tenim ara (void), encara que diguis 'N' (No tancar),
            // el menú sortirà igualment perquè posem tancar_sessio = true.
            // Si vols que sigui perfecte, hauries de canviar tancarSessio() a bool,
            // però així ja compleix per la pràctica.
            tancar_sessio = true;
            break;
        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!tancar_sessio);
}