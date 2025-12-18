// CapaDeDomini.cxx
#include "CapaDeDomini.hxx"
#include "CtrlRegistraUsuari.hxx" 
#include "CtrlIniciSessio.hxx"    

// Singleton
CapaDeDomini& CapaDeDomini::getInstance() {
    static CapaDeDomini instance;
    return instance;
}

// Implementación Registrar Usuari
void CapaDeDomini::registrarUsuari(const DTOUsuari& dto) {
    // Creamos el controlador específico del caso de uso [cite: 211]
    CtrlRegistraUsuari ctrl;

    // Pasamos los datos del DTO a los tipos primitivos que espera el controlador
    // Asegúrate de que tu DTOUsuari tiene estos getters
    ctrl.registrarUsuari(
        dto.get_nom(),
        dto.get_sobrenom(),
        dto.get_contrasenya(), // Necesitas este getter en el DTO (o get_contrasenya())
        dto.get_correuElectronic(),
        dto.get_edat()
    );
}

// Implementación Iniciar Sessio
void CapaDeDomini::iniciarSessio(const std::string& sobrenom, const std::string& contrasenya) {
    // Creamos el controlador específico del caso de uso [cite: 142]
    CtrlIniciSessio ctrl;

    // Llamamos al método. Si falla, el controlador lanzará una excepción
    // que llegará hasta la Capa de Presentación.
    ctrl.iniciSessio(sobrenom, contrasenya);
}
