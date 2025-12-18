#include "CtrlIniciSessio.hxx"
#include "PlanGo.hxx"
#include <odb/exceptions.hxx> // Para detectar errores de base de datos

void CtrlIniciSessio::iniciSessio(const std::string& sobrenom, const std::string& contrasenya) {
    DAOUsuari dao;

    try {
        // 1. Intentamos cargar el usuario de la BD
        // Si no existe, ODB lanza 'object_not_persistent' automáticamente
        usuari u = dao.obte(sobrenom);

        // 2. Comprobamos la contraseña
        if (!u.comprovaContrasenya(contrasenya)) {
            // "si contrasenya <> cU activa ErrorContrasenya"
            throw ErrorContrasenya();
        }

        // 3. Si todo va bien, guardamos el usuario en la sesión (PlanGo)
        // Convertimos 'usuari' (objeto) a 'shared_ptr<usuari>'
        auto u_ptr = std::make_shared<usuari>(u);
        PlanGo::getInstance().iniciaSessio(u_ptr);

    }
    catch (const odb::object_not_persistent&) {
        // Si ODB dice que no existe, nosotros lanzamos nuestra excepción de dominio
        throw UsuariNoExisteix();
    }
}