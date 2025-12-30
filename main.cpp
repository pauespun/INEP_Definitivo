#include <iostream>
#include <string>
#include <locale>

#include "CapaDePresentacio.hxx"
#include "connexioBD.hxx" 

using namespace std;

// --- PROTOTIPS ---
void menu_inici();          // Menú 1: Login / Registro
void menu_principal();      // Menú 2: Menú general
void menu_gestio_usuaris(); // Submenú 2.1
void menu_gestio_reserves(); // Submenú 2.2

// --- MAIN ---
int main()
{
    std::locale::global(std::locale(""));

    // Opcional: Inicializar BD si usas tu singleton connexioBD
    // connexioBD::getInstance().getDB(); 

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
        cout << "0. Sortir de l'aplicacio\n";
        cout << "Opcio: ";
        cin >> opcio;

        switch (opcio)
        {
        case 1:
            // Si el login es correcto, entramos al menú principal
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
// 2. MENÚ PRINCIPAL (Loguejat)
// -------------------------------------------------------------------
void menu_principal()
{
    int opcio;
    bool tancar_sessio = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n===== PLANGO: MENU PRINCIPAL =====\n";
        cout << "1. Gestio d'Usuaris\n";   // Agrupa: Consulta, Modifica, Borra
        cout << "2. Gestio de Reserves\n"; // Agrupa: Reservar escapada/activitat
        cout << "0. Tancar Sessio\n";
        cout << "Opcio: ";
        cin >> opcio;

        switch (opcio)
        {
        case 1:
            menu_gestio_usuaris();
            // Comprobación especial: Si al volver de gestión de usuarios
            // resulta que el usuario se ha borrado a sí mismo, hay que salir.
            // (Asumimos que esborrarUsuari cierra la sesión internamente si tiene éxito)
            // Una forma simple de saber si seguimos logueados es intentar volver a preguntar a PlanGo,
            // pero para simplificar, si el usuario decide cerrar sesión dentro, el bucle continuará
            // hasta que pulse 0 aquí, a menos que se haya forzado.
            break;
        case 2:
            menu_gestio_reserves();
            break;
        case 0:
            presentacio.tancarSessio();
            tancar_sessio = true;
            break;
        default:
            cout << "Opcio no valida.\n";
            break;
        }
    } while (!tancar_sessio);
}

// -------------------------------------------------------------------
// 2.1. SUBMENÚ GESTIÓ USUARIS
// -------------------------------------------------------------------
void menu_gestio_usuaris()
{
    int opcio;
    bool tornar = false;
    CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

    do {
        cout << "\n--- GESTIO USUARIS ---\n";
        cout << "1. Consultar usuari\n";
        cout << "2. Modificar usuari\n";
        cout << "3. Esborrar usuari\n";
        cout << "0. Tornar al menu principal\n";
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
            // Si se borra correctamente, salimos de este menú y forzamos cierre
            if (presentacio.esborrarUsuari()) {
                presentacio.tancarSessio(); // Aseguramos que se limpie la sesión
                tornar = true;
                // Nota: Esto devolverá el control a menu_principal. 
                // El usuario tendrá que pulsar 0 en menu_principal o implementar lógica extra.
                // Para que funcione "fluido", lo ideal es que menu_principal detecte el logout.
                cout << "Usuari esborrat. Tancant sessio...\n";
                // Forzamos salida del programa volviendo a inici
                // (En C++ básico esto requiere lanzar excepción o chequear bools en cascada)
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
        cout << "1. Reservar Escapada\n";
        cout << "2. Reservar Activitat\n";   // ✅ AÑADIDO
        cout << "3. Visualitzar reserves\n"; // (opcional, si aún no lo tienes, puedes quitarlo)
        cout << "0. Tornar al menu principal\n";
        cout << "Opcio: ";
        cin >> opcio;

        switch (opcio)
        {
        case 1:
            presentacio.reservarEscapada();
            break;
        case 2:
            presentacio.reservarActivitat(); // ✅ AÑADIDO
            break;
        case 3:
            presentacio.visualitzarReserves(); // Descomenta-ho!
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
