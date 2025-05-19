#include "studentas.h"
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <iostream>

Studentas::Studentas() : Zmogus("", ""), egzaminas_(0) {}

Studentas::Studentas(string vardas, string pavarde, vector<int> nd, int egzaminas)
    : Zmogus(vardas, pavarde), nd_(nd), egzaminas_(egzaminas) {}

Studentas::Studentas(istream& is) {
    read(is);
}

// Rule of Five
Studentas::Studentas(const Studentas& other)
    : Zmogus(other.vardas_, other.pavarde_), nd_(other.nd_), egzaminas_(other.egzaminas_) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
    }
    return *this;
}

Studentas::Studentas(Studentas&& other) noexcept
    : Zmogus(std::move(other.vardas_), std::move(other.pavarde_)),
      nd_(std::move(other.nd_)), egzaminas_(other.egzaminas_) {
    //resetina objekto reiksmes
    other.vardas_.clear();
    other.pavarde_.clear();
    other.nd_.clear();
    other.egzaminas_ = 0;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        nd_ = std::move(other.nd_);
        egzaminas_ = other.egzaminas_;

        //resetina objekto reiksmes
        other.vardas_.clear();
        other.pavarde_.clear();
        other.nd_.clear();
        other.egzaminas_ = 0;
    }
    return *this;
}

Studentas::~Studentas() {}

vector<int> Studentas::nd() const { return nd_; }

int Studentas::egzaminas() const { return egzaminas_; }

double Studentas::galutinisVidurkis() const {
    if (nd_.empty()) return 0.4 * 0 + 0.6 * egzaminas_;
    double suma = std::accumulate(nd_.begin(), nd_.end(), 0.0);
    return 0.4 * (suma / nd_.size()) + 0.6 * egzaminas_;
}

double Studentas::galutinisMediana() const {
    if (nd_.empty()) return 0.4 * 0 + 0.6 * egzaminas_;
    vector<int> nd_kopija = nd_;
    std::sort(nd_kopija.begin(), nd_kopija.end());
    size_t dydis = nd_kopija.size();
    double mediana;
    if (dydis % 2 == 0)
        mediana = (nd_kopija[dydis / 2 - 1] + nd_kopija[dydis / 2]) / 2.0;
    else
        mediana = nd_kopija[dydis / 2];
    return 0.4 * mediana + 0.6 * egzaminas_;
}

istream& Studentas::read(istream& is) {
    string v, p;
    is >> v >> p;
    setVardas(v);
    setPavarde(p);
    int pazymys;
    nd_.clear();
    while (is >> pazymys) {
        nd_.push_back(pazymys);
    }
    if (!nd_.empty()) {
        egzaminas_ = nd_.back();
        nd_.pop_back();
    }
    return is;
}

ostream& Studentas::spausdinti(ostream& os) const {
    string v = vardas_.empty() ? "-" : vardas_;
    string p = pavarde_.empty() ? "-" : pavarde_;
    double g = nd_.empty() && v == "-" && p == "-" ? 0.0 : galutinis();

    os << std::left << std::setw(20) << v
       << std::setw(25) << p
       << std::fixed << std::setprecision(2) << g;
    return os;
}

ostream& operator<<(ostream& os, const Studentas& s) {
    return s.spausdinti(os);
}

istream& operator>>(istream& is, Studentas& s) {
    return s.read(is);
}

// Lyginimo funkcijos
bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() > b.egzaminas();
}