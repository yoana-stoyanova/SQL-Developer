#include <string>

class Utils {
public:
    enum class DataType {
        INT,
        DOUBLE,
        STRING,
        NULL_TYPE
    };

    enum Color {
        DEFAULT,
        RED,
        GREEN,
        YELLOW
    };

    static std::string getColorCode(Color col);
    static std::string getTypeAsString(DataType type);
    static DataType stringToDataType(const std::string& type);
    static void log(const std::string& text, Color col = Color::DEFAULT);
};