#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

using std::string;

class Zmogus {
public:
    virtual ~Zmogus() = default;

    virtual string vardas() const = 0;
    virtual string pavarde() const = 0;
};

#endif