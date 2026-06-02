#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "../entities/Column.h"
#include "Datatype.h"

const std::string FILE_PATH = "data/";
const std::string FILE_TYPE = ".txt";

class Utils {
public:
    enum Color {
        DEFAULT,
        RED,
        GREEN,
        YELLOW
    };

    static std::string getColorCode(Color col);

    static std::string getTypeAsString(DataType type);
    static DataType stringToDataType(const std::string& type);

    static std::vector<std::string> splitRow(const std::string& row, char sep);
    static std::string concatRow(const std::vector<std::string>& data, char sep);

    static std::vector<Column> splitHeader(const std::string& titleRow, char sep);
    static std::string concatHeader(const std::vector<Column>& columns, char sep);

    static void log(const std::string& text, Color col = Color::DEFAULT);

    static std::string toUpperCase(std::string s);

    static std::string fileTableName(const std::string& fileName);
};

#endif