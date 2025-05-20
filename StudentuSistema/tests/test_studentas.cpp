#define CATCH_CONFIG_MAIN
#include "../external/catch2/catch.hpp"
#include "../common/studentas.h"

TEST_CASE("Rule of Five: copy constructor") {
    Studentas original("Jonas", "Jonaitis", {9, 8, 10}, 9);
    Studentas copy(original); // copy constructor

    REQUIRE(copy.vardas() == "Jonas");
    REQUIRE(copy.pavarde() == "Jonaitis");
    REQUIRE(copy.galutinisVidurkis() == Approx(original.galutinisVidurkis()));
}

TEST_CASE("Rule of Five: copy assignment") {
    Studentas a("Aiste", "Aistaityte", {7, 8, 9}, 10);
    Studentas b;
    b = a; // copy assignment

    REQUIRE(b.vardas() == "Aiste");
    REQUIRE(b.pavarde() == "Aistaityte");
    REQUIRE(b.galutinisVidurkis() == Approx(a.galutinisVidurkis()));
}

TEST_CASE("Rule of Five: move constructor") {
    Studentas temp("Tomas", "Tomaitis", {6, 6, 6}, 9);
    Studentas moved(std::move(temp)); // move constructor

    REQUIRE(moved.vardas() == "Tomas");
    REQUIRE(moved.pavarde() == "Tomaitis");
    REQUIRE(moved.galutinisVidurkis() == Approx(0.4 * 6.0 + 0.6 * 9));
}

TEST_CASE("Rule of Five: move assignment") {
    Studentas temp("Laura", "Laurinyte", {10, 9, 8}, 10);
    Studentas moved;
    moved = std::move(temp); // move assignment

    REQUIRE(moved.vardas() == "Laura");
    REQUIRE(moved.pavarde() == "Laurinyte");
    REQUIRE(moved.galutinisVidurkis() == Approx(0.4 * 9.0 + 0.6 * 10));
}

TEST_CASE("Rule of Five: destructor check scope") {
    Studentas* s = new Studentas("Demo", "Destruktorius", {5, 5, 5}, 5);
    REQUIRE(s->vardas() == "Demo");
    delete s; // destructor should be called here
}

TEST_CASE("Galutine mediana skaiciuojama teisingai") {
    Studentas s("Vardenis", "Pavardenis", {6, 5, 7}, 9);
    // Mediana = 6, galutinis = 0.4 * 6 + 0.6 * 9 = 7.8
    REQUIRE(s.galutinisMediana() == Approx(7.8));
}

TEST_CASE("Operatorius << generuoja istrauka su vardu") {
    Studentas s("Monika", "Monikiene", {8, 9, 10}, 10);
    std::ostringstream out;
    out << s;

    std::string result = out.str();
    REQUIRE(result.find("Monika") != std::string::npos);
    REQUIRE(result.find("Monikiene") != std::string::npos);
}