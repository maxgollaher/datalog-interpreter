#ifndef PROJECT03_DATABASE_H
#define PROJECT03_DATABASE_H

#include <utility>
#include <vector>
#include "Relation.h"
#include <map>

class Database : public map<string, Relation> {
public:
    Database() = default;
    explicit Database(map<string, Relation> &relations) : map<string, Relation>(relations) {};
};

#endif //PROJECT03_DATABASE_H
