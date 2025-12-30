#include "CapaDePresentacio.hxx"
#include "CtrlIniciSessio.hxx"
#include "CtrlRegistraUsuari.hxx"
#include "CtrlTancaSessio.hxx"
#include "CtrlConsultaUsuari.hxx"
#include "CtrlModificaUsuari.hxx"
#include "CtrlEsborrarUsuari.hxx"
#include "CtrlReservaEscapada.hxx"
#include "CtrlReservaActivitat.hxx"
#include "CtrlConsultaExperiencies.hxx"
#include "CtrlConsultaReserves.hxx"
#include "DTOReserves.hxx"
#include "CtrlConsultaNovetats.hxx"
#include "CtrlConsultaMesReservades.hxx"

#include "PlanGo.hxx" 
#include <iostream>

using namespace std;

// Singleton
CapaDePresentacio& CapaDePresentacio::getInstance() {
    static CapaDePresentacio instance;
    return instance;
}

CapaDePresentacio::CapaDePresentacio() {}

bool CapaDePresentacio::iniciarSessio() {
    string sobrenom, contrasenya;

    cout << "** Inici sessio **" << endl;
    cout << "Sobrenom: ";
    cin >> sobrenom;
    cout << "Contrasenya: ";
    cin >> contrasenya;

    // Creamos el controlador
    CtrlIniciSessio ctrl;

    try {
        // Llamamos a la lógica
        ctrl.iniciSessio(sobrenom, contrasenya);
		// Guardamos el sobrenom localmente
		usuariLoguejat = sobrenom;

        // Si no ha saltado error, es que ha ido bien 
        cout << "Sessio iniciada correctament!" << endl;

        return true; // Retorna true para cambiar de menú en main.cpp
    }
    catch (UsuariNoExisteix) {
        // Capturamos el struct vacío
        cout << "Hi ha hagut un error amb el sobrenom o la contrasenya" << endl; 
    }
    catch (ErrorContrasenya) {
        cout << "Hi ha hagut un error amb el sobrenom o la contrasenya" << endl; 
    }
    catch (std::exception& e) {
        cout << "Error inesperat: " << e.what() << endl;
    }

    return false; // Login fallido
}

void CapaDePresentacio::registrarUsuari() {
    string nom, sobrenom, contrasenya, correu;
    int edat;

    cout << "** Registre usuari **" << endl;

    cin.ignore();

    cout << "Nom complet: ";
    getline(cin, nom); // getline permite espacios

    cout << "Sobrenom: ";
    cin >> sobrenom;

    cout << "Contrasenya: ";
    cin >> contrasenya;

    cout << "Correu electronic: ";
    cin >> correu;

    cout << "Edat: ";
    cin >> edat;

    // Creamos controlador
    CtrlRegistraUsuari ctrl;

    try {
        ctrl.registrarUsuari(nom, sobrenom, contrasenya, correu, edat);
        cout << "Usuari registrat amb exit!" << endl; 
    }
    catch (SobrenomExisteix) {
        cout << "Ja existeix un usuari amb aquest sobrenom" << endl; 
    }
    catch (CorreuExisteix) {
        cout << "Ja existeix un usuari amb aquest correu electronic" << endl; 
    }
    catch (MenorEdat) {
        cout << "No es pot registar un menor" << endl;
    }
    catch (std::exception& e) {
        cout << "Error tècnic: " << e.what() << endl;
    }
}

bool CapaDePresentacio::tancarSessio() { 
    char opcio;
    cout << "Vols tancar la sessio? (S/N): ";

    cin >> opcio;

    if (opcio == 'S' || opcio == 's') {

        CtrlTancaSessio ctrl;
        ctrl.tancaSessio();

        cout << "Sessio tancada correctament!" << endl;
        return true; // <--- Devuelve TRUE si cerró
    }
    // Si dice 'N' o cualquier otra cosa:
    return false; // <--- Devuelve FALSE si NO cerró
}

void CapaDePresentacio::consultarUsuari() {
    std::cout << "** Consulta usuari **" << std::endl;

    try {
        CtrlConsultaUsuari ctrl;
        DTOUsuari info = ctrl.consultaUsuari();

        std::cout << "Nom: " << info.get_nom() << std::endl;
        std::cout << "Sobrenom: " << info.get_sobrenom() << std::endl;
        std::cout << "Correu electronic: " << info.get_correuElectronic() << std::endl;
        std::cout << "Edat: " << info.get_edat() << std::endl;
        std::cout << "Total reserves: " << info.get_totalReserves() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nPrem Intro per continuar...";
    std::cin.ignore();
    std::cin.get();
}
void CapaDePresentacio::modificarUsuari() {
    using namespace std;
    cout << "** Modificar usuari **" << endl;

    CtrlModificaUsuari ctrl;

    try {
        // Llamamos a consultaUsuari del propio controlador de modificación
        DTOUsuari infoActual = ctrl.consultaUsuari();

        cout << "--- Dades actuals ---" << endl;
        cout << "Nom: " << infoActual.get_nom() << endl;
        cout << "Correu: " << infoActual.get_correuElectronic() << endl;
        cout << "Edat: " << infoActual.get_edat() << endl;
        cout << "---------------------" << endl;
    }
    catch (std::exception& e) {
        cout << "Error al recuperar dades: " << e.what() << endl;
        return; // Si no podemos leer, salimos
    }

    cout << "(Deixa en blanc per mantenir el valor actual)" << endl;

    string nom, correu, edatStr;
    int edat = -1;

    cin.ignore(); // Limpiar buffer

    cout << "Nom complet: ";
    getline(cin, nom);

    cout << "Correu electronic: ";
    getline(cin, correu);

    cout << "Edat: ";
    getline(cin, edatStr);

    if (!edatStr.empty()) {
        try {
            edat = stoi(edatStr);
        }
        catch (...) {
            cout << "Format incorrecte. No es modificara l'edat." << endl;
            edat = -1;
        }
    }

    try {
        // El controlador nos devuelve la info leída directamente de la BD post-cambio
        DTOUsuari infoModificada = ctrl.modificaUsuari(nom, correu, edat);

        cout << "Usuari modificat correctament!" << endl;
        cout << "--- Dades actualitzades (Base de Dades) ---" << endl;
        cout << "Nom: " << infoModificada.get_nom() << endl;
        cout << "Correu: " << infoModificada.get_correuElectronic() << endl;
        cout << "Edat: " << infoModificada.get_edat() << endl;
    }
    catch (CorreuExisteix) {
        cout << "Error: El correu electronic ja existeix." << endl;
    }
    catch (MenorEdat) {
        cout << "Error: No es poden registrar usuaris menors." << endl;
    }
    catch (std::exception& e) {
        cout << "Error tècnic: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.get();
}

bool CapaDePresentacio::esborrarUsuari() {
    using namespace std;
    string contrasenya;
    char confirmacio;

    cout << "** Esborrar usuari **" << endl;

    // 1. Pedir contraseña
    cout << "Introdueix la teva contrasenya per confirmar: ";
    cin >> contrasenya;

    // 2. Pedir confirmación explícita
    cout << "Estas segur que vols donar-te de baixa? (S/N): ";
    cin >> confirmacio;

    if (confirmacio == 'S' || confirmacio == 's') {
        try {
            CtrlEsborrarUsuari ctrl;

            // 3. Llamar al controlador con la contraseña
            ctrl.esborrarUsuari(contrasenya);

            // Si llegamos aquí, se ha borrado bien
            // Limpiamos variable local
			usuariLoguejat = "";
            cout << "Usuari esborrat correctament. Fins aviat!" << endl;

            cout << "\nPrem Intro per continuar...";
            cin.ignore(); cin.get();

            return true; // Indica al Main que debe salir al menú de inicio
        }
        catch (ErrorContrasenya) {
            // Escenario alternativo: Contraseña incorrecta
            cout << "Error: La contrasenya no es correcta. L'usuari no s'ha esborrat." << endl;
        }
        catch (std::exception& e) {
            cout << "Error tècnic: " << e.what() << endl;
        }
    }
    else {
        // Escenario alternativo: Usuario no confirma
        cout << "Operacio cancel.lada." << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore(); cin.get();

    return false; // No se ha borrado, nos quedamos en el menú principal
}


void CapaDePresentacio::reservarEscapada() {
    using namespace std;
    string nomEscapada;
    char confirmacio;

    cout << "** Reservar escapada **" << endl;

    cout << "Nom: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, nomEscapada);

    CtrlReservaEscapada ctrl;

    try {
        DTOExperiencia info = ctrl.consulta_escapada(nomEscapada);

        // Mostrar informació
        cout << "Descripcio: " << info.get_descripcio() << endl;
        cout << "Ciutat: " << info.get_ciutat() << endl;
        cout << "Places: " << info.get_maxim_places() << endl;
        cout << "Hotel: " << info.get_hotel() << endl;
        cout << "Nits: " << info.get_num_nits() << endl;
        cout << "Preu: " << info.get_preu() << endl;

        cout << "Vols continuar amb la reserva? (S/N): ";
        cin >> confirmacio;

        if (confirmacio == 'S' || confirmacio == 's') {

       
            DTOReserva resultat = ctrl.reserva_escapada();

            cout << "Reserva enregistrada correctament." << endl;

         
            cout << "Data i hora de la reserva: " << resultat.get_data() << endl;

            cout << "Preu aplicat a la reserva: " << resultat.get_preuPagat() << endl;
        }
        else {
            cout << "Operacio cancel.lada." << endl;
        }
    }
    catch (EscapadaNoExisteix) {
        cout << "Error: L'escapada introduida no existeix." << endl;
    }
    catch (std::exception& e) {
        cout << "Error inesperat: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore(); cin.get();
}


void CapaDePresentacio::reservarActivitat() {
    using namespace std;
    string nomActivitat;
    int numPersones;
    char confirmacio;

    cout << "** Reservar activitat **" << endl;

    if (cin.peek() == '\n') cin.ignore();
    cout << "Introdueix el nom de l'activitat a reservar: ";
    getline(cin, nomActivitat);

    CtrlReservaActivitat ctrl;

    try {
        // Escenari alternatiu: Activitat no existeix
        DTOExperiencia info = ctrl.consulta_activitat(nomActivitat);

        // Mostrar dades...
        cout << "Nom: " << info.get_nom() << endl;
        cout << "Descripció: " << info.get_descripcio() << endl;
        cout << "Ciutat: " << info.get_ciutat() << endl;
        cout << "Places màximes: " << info.get_maxim_places() << endl;
        cout << "Preu per persona: " << info.get_preu() << "$" << endl;
        cout << "Durada (minuts): " << info.get_durada() << endl;

        float preuTotal = 0.0f;
        bool valid = false;

        // Escenari alternatiu: Supera màxim (Bucle de reintent)
        while (!valid) {
            cout << "Introdueix el nombre de persones: ";
            cin >> numPersones;

            if (numPersones < 1) {
                cout << "Error: Minim 1 persona." << endl;
                continue;
            }

            try {
                preuTotal = ctrl.preu_total(numPersones);
                valid = true;
            }
            catch (SuperaMaxim) {
                int lliures = ctrl.places_disponibles();

                cout << "Error: El nombre de persones supera les places disponibles." << endl;

                // Mostrem la realitat
                cout << "Places lliures actualment: " << lliures << endl;

                cout << "Vols introduir un altre nombre? (S/N): ";
                cin >> confirmacio;

                if (confirmacio == 'N' || confirmacio == 'n') {
                    cout << "Operacio cancel.lada." << endl;
                    cin.ignore(); cin.get();
                    return;
                }
            }
        }

        cout << "Preu total: " << preuTotal << endl;
        cout << "Vols continuar? (S/N): ";
        cin >> confirmacio;

        if (confirmacio == 'S' || confirmacio == 's') {
            ctrl.reserva_activitat(numPersones);
            cout << "Reserva enregistrada correctament." << endl;
        }
        else {
            cout << "Operacio cancel.lada." << endl;
        }

    }
    catch (ActivitatNoExisteix) {
        cout << "L'activitat no existeix." << endl; // Missatge d'error i finalitza
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore(); cin.get();
}


void CapaDePresentacio::consultarExperiencies() {
    using namespace std;

    string ciutat;
    int numPersones;

    cout << "** Consultar experiències **" << endl;

    cout << "Introdueix la ciutat: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, ciutat);

    cout << "Introdueix el nombre de persones: ";
    cin >> numPersones;

    try {
        CtrlConsultaExperiencies ctrl;

        auto escapades = ctrl.consulta_escapades(ciutat, numPersones);
        auto activitats = ctrl.consulta_activitats(ciutat, numPersones);

        cout << "\n--- Escapades ---" << endl;
        if (escapades.empty()) {
            cout << "No hi ha escapades disponibles." << endl;
        }
        for (const auto& e : escapades) {
            cout << "Nom: " << e.get_nom() << endl;
            cout << "Descripcio: " << e.get_descripcio() << endl;
            cout << "Ciutat: " << e.get_ciutat() << endl;
            cout << "Places: " << e.get_maxim_places() << endl;
            cout << "Preu: " << e.get_preu() << endl;
            cout << "Hotel: " << e.get_hotel() << endl;
            cout << "Nits: " << e.get_num_nits() << endl;
            cout << "-----------------------------" << endl;
        }

        cout << "\n--- Activitats ---" << endl;
        if (activitats.empty()) {
            cout << "No hi ha activitats disponibles." << endl;
        }
        for (const auto& a : activitats) {
            cout << "Nom: " << a.get_nom() << endl;
            cout << "Descripcio: " << a.get_descripcio() << endl;
            cout << "Ciutat: " << a.get_ciutat() << endl;
            cout << "Places: " << a.get_maxim_places() << endl;
            cout << "Preu: " << a.get_preu() << endl;
            cout << "Durada: " << a.get_durada() << endl;
            cout << "-----------------------------" << endl;
        }
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore();
    cin.get();
}

void CapaDePresentacio::visualitzarReserves() {
    using namespace std;
    cout << "\n--- LES MEVES RESERVES ---" << endl;

    try {
        CtrlConsultaReserves ctrl;
        DTOReserves dades = ctrl.consultaReserves();

        auto llistaCompleta = dades.get_llista();

        // Escenari alternatiu: Usuari no té reserves
        if (llistaCompleta.empty()) {
            cout << "No tens cap reserva registrada." << endl;
            cout << "\nPrem Intro per continuar...";
            cin.ignore(); cin.get();
            return;
        }

        // Mostrem el total global
        cout << "Total pagat acumulat: " << dades.get_totalPagat() << " EUR" << endl;

        // 1. SEPAREM LA LLISTA EN DOS GRUPS
        // Com que 'llistaCompleta' ja ve ordenada per data (del DAO),
        // al separar-la mantenim l'ordre cronològic dins de cada grup.
        vector<DTOReserva> llistaActivitats;
        vector<DTOReserva> llistaEscapades;

        for (const auto& r : llistaCompleta) {
            DTOExperiencia exp = r.get_experiencia();
            // Si té "nits", és una Escapada. Si no, és una Activitat.
            if (exp.get_num_nits() > 0) {
                llistaEscapades.push_back(r);
            }
            else {
                llistaActivitats.push_back(r);
            }
        }

        // Funció auxiliar lambda per no repetir codi d'impressió
        auto imprimirReserva = [](const DTOReserva& r) {
            DTOExperiencia exp = r.get_experiencia();
            cout << "Data Reserva: " << r.get_data() << endl;
            cout << "Experiencia:  " << exp.get_nom() << " (" << exp.get_ciutat() << ")" << endl;
            cout << "Descripcio:   " << exp.get_descripcio() << endl;
            cout << "Places:       " << r.get_numPlaces() << endl;
            cout << "Preu Pagat:   " << r.get_preuPagat() << " EUR" << endl;

            if (exp.get_num_nits() > 0) { // Escapada
                cout << "Hotel:        " << exp.get_hotel() << endl;
                cout << "Nits:         " << exp.get_num_nits() << endl;
            }
            else { // Activitat
                cout << "Durada:       " << exp.get_durada() << " minuts" << endl;
            }
            cout << "------------------------------------------------" << endl;
            };

        // 2. MOSTREM LA PART D'ACTIVITATS
        if (!llistaActivitats.empty()) {
            cout << "\n=== RESERVES D'ACTIVITATS ===" << endl;
            for (const auto& r : llistaActivitats) {
                imprimirReserva(r);
            }
        }

        // 3. MOSTREM LA PART D'ESCAPADES
        if (!llistaEscapades.empty()) {
            cout << "\n=== RESERVES D'ESCAPADES ===" << endl;
            for (const auto& r : llistaEscapades) {
                imprimirReserva(r);
            }
        }

    }
    catch (std::exception& e) {
        cout << "Error al consultar reserves: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore(); cin.get();
}

void CapaDePresentacio::consultarNovetats()
{
    using namespace std;

    cout << "** Consultar novetats **" << endl;

    try {
        CtrlConsultaNovetats ctrl;
        auto novetats = ctrl.consultar_novetats(10);

        if (novetats.empty()) {
            cout << "No hi ha experiències recents." << endl;
        }

        for (const auto& e : novetats) {
            if (!e.get_hotel().empty()) {
                cout << "Tipus: ESCAPADA" << endl;
            }
			else {
				cout << "Tipus: ACTIVITAT" << endl;
			}
            cout << "Nom: " << e.get_nom() << endl;
            cout << "Descripcio: " << e.get_descripcio() << endl;
            cout << "Ciutat: " << e.get_ciutat() << endl;
            cout << "Places: " << e.get_maxim_places() << endl;
            cout << "Preu: " << e.get_preu() << endl;

            if (!e.get_hotel().empty()) {
              
                cout << "Hotel: " << e.get_hotel() << endl;
                cout << "Nits: " << e.get_num_nits() << endl;
            }
            else {
           
                cout << "Durada: " << e.get_durada() << endl;
            }

            cout << "-------------------------" << endl;
        }
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore();
    cin.get();
}

void CapaDePresentacio::consultarMesReservades()
{
    using namespace std;

    cout << "Consultar experiències més reservades" << endl;

    try {
        CtrlConsultaMesReservades ctrl;

        // Recuperem les llistes
        auto escapades = ctrl.consulta_escapades(5);
        auto activitats = ctrl.consulta_activitats(5);

        // --- ESCAPADES ---
        cout << "\n--- Escapades més reservades ---" << endl;
        if (escapades.empty())
            cout << "No hi ha escapades." << endl;

        int i = 1;
        for (const auto& e : escapades) {
            cout << i << ". Nom: " << e.get_nom() << endl;
           
            cout << "   Descripcio: " << e.get_descripcio() << endl;
            cout << "   Ciutat: " << e.get_ciutat() << endl;
            cout << "   Places: " << e.get_maxim_places() << endl;
            cout << "   Preu: " << e.get_preu() << endl;

            // Específic d'Escapada
            cout << "   Hotel: " << e.get_hotel() << endl;
            cout << "   Nits: " << e.get_num_nits() << endl;
            cout << "-------------------------" << endl;
            i++;
        }

        // --- ACTIVITATS ---
        cout << "\n--- Activitats més reservades ---" << endl;
        if (activitats.empty())
            cout << "No hi ha activitats." << endl;

        i = 1;
        for (const auto& a : activitats) {
            cout << i << ". Nom: " << a.get_nom() << endl;
        
            cout << "   Descripcio: " << a.get_descripcio() << endl;
            cout << "   Ciutat: " << a.get_ciutat() << endl;
            cout << "   Places: " << a.get_maxim_places() << endl;
            cout << "   Preu: " << a.get_preu() << endl;

            // Específic d'Activitat
            cout << "   Durada: " << a.get_durada() << " minuts" << endl;
            cout << "-------------------------" << endl;
            i++;
        }
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore();
    cin.get();
}
