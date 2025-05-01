#include "studentas.h"

Studentas::Studentas() : vardas_(""), pavarde_(""), egzaminas_(0) {}

Studentas::Studentas(string vardas, string pavarde, vector<int> nd, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzaminas_(egzaminas) {}

Studentas::Studentas(istream& is) {
    read(is);
}

// Rule of Five
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_), nd_(other.nd_), egzaminas_(other.egzaminas_) {}

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
    : vardas_(std::move(other.vardas_)), pavarde_(std::move(other.pavarde_)),
      nd_(std::move(other.nd_)), egzaminas_(other.egzaminas_) {}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        nd_ = std::move(other.nd_);
        egzaminas_ = other.egzaminas_;
    }
    return *this;
}

Studentas::~Studentas() {}

// Getteriai
string Studentas::vardas() const { return vardas_; }

string Studentas::pavarde() const { return pavarde_; }

vector<int> Studentas::nd() const { return nd_; }

int Studentas::egzaminas() const { return egzaminas_; }

// Galutinis
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

// Nuskaitymas
istream& Studentas::read(istream& is) {
    is >> vardas_ >> pavarde_;
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

// Operatoriai
ostream& operator<<(ostream& os, const Studentas& s) {
    os << std::left << std::setw(20) << s.vardas_
       << std::setw(25) << s.pavarde_
       << std::fixed << std::setprecision(2) << s.galutinis();
    return os;
}

istream& operator>>(istream& is, Studentas& s) {
    s.nd_.clear();
    is >> s.vardas_ >> s.pavarde_;
    int pazymys;
    while (is >> pazymys) {
        s.nd_.push_back(pazymys);
    }
    if (!s.nd_.empty()) {
        s.egzaminas_ = s.nd_.back();
        s.nd_.pop_back();
    }
    return is;
}

// Lyginimo funkcijos
bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas_ < b.vardas_;
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde_ < b.pavarde_;
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas_ > b.egzaminas_;
}