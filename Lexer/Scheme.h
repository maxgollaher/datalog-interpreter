#ifndef PROJECT03_SCHEME_H
#define PROJECT03_SCHEME_H

#include <string>
#include <vector>
using namespace std;

class Scheme : public vector<string> {
public:
    Scheme() = default;
    Scheme(vector<string> names) : vector<string>(names) {}
};

#endif //PROJECT03_SCHEME_H
