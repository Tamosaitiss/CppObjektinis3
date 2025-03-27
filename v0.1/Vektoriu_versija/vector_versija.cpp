#include "studentas.h"

Studentas::Studentas() : vardas_(""), pavarde_(""), egzaminas_(0) {}
Studentas::Studentas(string vardas, string pavarde, vector<int> nd, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzaminas_(egzaminas) {}
Studentas::Studentas(istream& is) { read(is); }
Studentas::~Studentas() {}

string Studentas::vardas() const { return vardas_; }
string Studentas::pavarde() const { return pavarde_; }
vector<int> Studentas::nd() const { return nd_; }
int Studentas::egzaminas() const { return egzaminas_; }

istream& Studentas::read(istream& is) {
    is >> vardas_ >> pavarde_;
    nd_.clear();
    int pazymys;
    for (int i = 0; i < 5; i++) {
        is >> pazymys;
        nd_.push_back(pazymys);
    }
    is >> egzaminas_;
    return is;
}

double Studentas::galutinisVidurkis() const {
    if (nd_.empty()) return egzaminas_;
    double suma = accumulate(nd_.begin(), nd_.end(), 0.0);
    double vidurkis = suma / nd_.size();
    return 0.4 * vidurkis + 0.6 * egzaminas_;
}

double Studentas::galutinisMediana() const {
    if (nd_.empty()) return egzaminas_;
    vector<int> visi = nd_;
    visi.push_back(egzaminas_);
    sort(visi.begin(), visi.end());
    int dydis = visi.size();
    if (dydis % 2 == 0) return (visi[dydis / 2 - 1] + visi[dydis / 2]) / 2.0;
    else return visi[dydis / 2];
}

bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas_ < b.vardas_;
}
bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde_ < b.pavarde_;
}
bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas_ > b.egzaminas_;
}