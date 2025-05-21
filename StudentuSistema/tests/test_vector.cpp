#include "../external/catch2/catch.hpp"
#include "../common/Vector.h"

TEST_CASE("Vector push_back and access", "[vector]") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 10);
    REQUIRE(v.at(1) == 20);
    REQUIRE(v[2] == 30);
}

TEST_CASE("Vector resize and capacity", "[vector]") {
    Vector<int> v;
    v.resize(5);
    REQUIRE(v.size() == 5);
    v.push_back(42);
    REQUIRE(v.size() == 6);
}

TEST_CASE("Vector front, back and data", "[vector]") {
    Vector<int> v = {1, 2, 3, 4};
    REQUIRE(v.front() == 1);
    REQUIRE(v.back() == 4);
    REQUIRE(v.data()[2] == 3);
}

TEST_CASE("Vector pop_back and clear", "[vector]") {
    Vector<int> v = {5, 6, 7};
    v.pop_back();
    REQUIRE(v.size() == 2);
    v.clear();
    REQUIRE(v.empty());
}

TEST_CASE("Vector reserve and capacity handling", "[vector]") {
    Vector<int> v;
    v.reserve(100);
    REQUIRE(v.capacity() >= 100);
    REQUIRE(v.size() == 0);

    v.resize(50);
    REQUIRE(v.size() == 50);

    v.shrink_to_fit();
    REQUIRE(v.capacity() == v.size());
}

TEST_CASE("Vector copy constructor and assignment", "[vector]") {
    Vector<int> original = {1, 2, 3};
    Vector<int> copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy[0] == 1);
    REQUIRE(copy[1] == 2);
    REQUIRE(copy[2] == 3);

    Vector<int> assigned;
    assigned = copy;

    REQUIRE(assigned.size() == copy.size());
    REQUIRE(assigned[1] == 2);
}

TEST_CASE("Vector move constructor and assignment", "[vector]") {
    Vector<int> source = {10, 20, 30};
    Vector<int> moved(std::move(source));

    REQUIRE(moved.size() == 3);
    REQUIRE(moved[0] == 10);
    REQUIRE(moved[2] == 30);

    Vector<int> moved2;
    moved2 = std::move(moved);

    REQUIRE(moved2.size() == 3);
    REQUIRE(moved2[1] == 20);
}

TEST_CASE("Vector iterator support", "[vector]") {
    Vector<int> v = {1, 2, 3, 4, 5};

    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }

    REQUIRE(sum == 15);
}

TEST_CASE("Vector at() throws out_of_range", "[vector]") {
    Vector<int> v = {1, 2, 3};

    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
    REQUIRE_NOTHROW(v.at(2));
}