#ifndef DAORESERVA_HXX
#define DAORESERVA_HXX

#include <string>
#include <memory>
#include <vector>
// Forward declarations necessàries
namespace odb { namespace mysql { class database; } }
class reserva; // IMPRESCINDIBLE per evitar l'error C2061

class DAOReserva {
public:
    DAOReserva();

    // Comprova si l'usuari té alguna reserva prèvia (per al descompte)
    bool teAlgunaReserva(const std::string& sobrenom);

  
    int placesOcupades(const std::string& nomExperiencia);

    // Guarda una nova reserva
    void inserta(reserva& r);


    // Retorna totes les reserves d'un usuari ordenades per data descendent
    std::vector<std::shared_ptr<reserva>> obteReservesUsuari(const std::string& sobrenom);

private:
    std::shared_ptr<odb::mysql::database> _db;
};

#endif // DAORESERVA_HXX
