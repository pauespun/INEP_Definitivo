#pragma once

#include <vector>
#include <memory>                    
#include <odb/mysql/database.hxx>    

#include "DTOExperiencia.hxx"

class DAOExperiencia {
public:
    DAOExperiencia();

    std::vector<DTOExperiencia> obte_novetats(int numElems);

private:
    std::shared_ptr<odb::mysql::database> _db;
};
