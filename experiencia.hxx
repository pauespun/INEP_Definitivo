#ifndef EXPERIENCIA_HXX
#define EXPERIENCIA_HXX

#include <string>
#include <odb/core.hxx>

#pragma db object polymorphic pointer(std::shared_ptr) table("experiencia")
class experiencia {
public:
    virtual ~experiencia();

    // Getters
    std::string get_nom() const;
    std::string get_descripcio() const;
    std::string get_ciutat() const;
    int get_maxim_places() const;
    float get_preu() const;
    std::string get_data_alta() const;
    int get_num_reserves() const;

    // Setters
    void set_nom(const std::string& n);
    void set_descripcio(const std::string& d);
    void set_ciutat(const std::string& c);
    void set_maxim_places(int mp);
    void set_preu(float p);
    void set_data_alta(const std::string& da);
    void set_num_reserves(int nr);

    // Método abstracto
    virtual float calculaPreu(int nPersones, bool primeraRes);

protected:
    friend class odb::access;
    experiencia();

#pragma db id
    std::string _nom;

    std::string _descripcio;
    std::string _ciutat;

#pragma db column("maxim_places")
    int _maxim_places;

    float _preu;

#pragma db column("data_alta")
    std::string _data_alta;

#pragma db column("num_reserves")
    int _num_reserves;
};

#endif