#ifndef DAORESERVA_HXX
#define DAORESERVA_HXX

#include <string>
#include <memory>
#include <odb/mysql/database.hxx>

class DAOReserva {
public:
    DAOReserva();

    // Devuelve true si el usuario (sobrenom) tiene AL MENOS una reserva
    bool teAlgunaReserva(const std::string& sobrenom);

private:
    std::shared_ptr<odb::mysql::database> _db;
};

#endif // DAORESERVA_HXX
