#ifndef COLUMN_H
#define COLUMN_H

#include <string>
#include "../utils/DataType.h"

class Column {
private:
    std::string name;
    DataType type;

public:
    Column(const std::string& name, DataType type);

    std::string getName() const;
    DataType getType() const;
};

#endif