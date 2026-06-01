#include <string>
#include "../utils/Utils.h"

//TODO: undef?
class Column {
private:
    std::string name;
    Utils::DataType type;

public:
    Column(const std::string& name, Utils::DataType type);

    std::string getName() const;
    Utils::DataType getType() const;
};