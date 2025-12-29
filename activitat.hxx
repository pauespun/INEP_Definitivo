#ifndef ACTIVITAT_HXX
#define ACTIVITAT_HXX

#include "experiencia.hxx"

#pragma db object table("activitat")
class activitat : public experiencia {
public:
    activitat(const std::string& nom, const std::string& desc, const std::string& ciutat,
        int max_places, float preu, const std::string& data,
        int durada);

    virtual ~activitat();

    // Getters y Setters
    int get_durada() const;
    void set_durada(int d);

    float calculaPreu(int nPersones, bool primeraRes) override;

private:
    friend class odb::access;
    activitat();

#pragma db column("durada")
    int _durada;
};

#endif