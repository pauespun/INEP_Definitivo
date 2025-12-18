#include "CtrlRegistraUsuari.hxx"
#include <odb/exceptions.hxx>

void CtrlRegistraUsuari::registrarUsuari(const std::string& nom, const std::string& sobrenom,
    const std::string& contrasenya, const std::string& correu, int edat) {
    DAOUsuari dao;

    // 1. Validar edad (Restricción RIT1) [cite: 73, 203]
    if (edat < 18) {
        throw MenorEdat();
    }

    // 2. Crear el objeto
    usuari nouUsuari(sobrenom, nom, correu, contrasenya, edat);

    // 3. Intentar guardar en BD
    try {
        dao.inserta(nouUsuari);
    }
    catch (const odb::object_already_persistent&) {
        // Si ya existe la Clave Primaria (Sobrenom)
        throw SobrenomExisteix();
    }
    catch (const odb::exception&) {
        // Si se viola el UNIQUE del correo [cite: 74]
        // ODB lanza esto cuando se repite un campo único que no es PK
        throw CorreuExisteix();
    }


}