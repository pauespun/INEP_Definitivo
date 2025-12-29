#ifndef ESCAPADA_HXX
#define ESCAPADA_HXX

#include "experiencia.hxx"

#pragma db object table("escapada")
class escapada : public experiencia {
public:
    escapada(const std::string& nom, const std::string& desc, const std::string& ciutat,
        int max_places, float preu, const std::string& data,
        const std::string& hotel, int nits);

    virtual ~escapada();

    // Getters específicos
    std::string get_hotel() const;
    int get_num_nits() const;

    // Setters específicos
    void set_hotel(const std::string& h);
    void set_num_nits(int n);

    float calculaPreu(int /*nPersones*/) const override;

private:
    friend class odb::access;
    escapada();

    std::string _hotel;

#pragma db column("num_nits")
    int _num_nits;
};

#endif