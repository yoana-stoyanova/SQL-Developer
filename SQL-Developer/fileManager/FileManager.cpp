#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "FileManager.h"
#include "../utils/Utils.h"
#include "../entities/Table.h"
#include "../entities/Column.h"

//TODO: error handling;
bool FileManager::loadTable(const std::string& fileName, Table& table) {
    std::ifstream file(fileName);

    if(!file.is_open()) {
        Utils::log("Could not open file.", Utils::Color::RED);
        return false;
    }

    std::string line;

    if(std::getline(file, line)) {
        if(!line.empty() && line.back() == '\r'){
            line.pop_back();
        }
        
        std::vector<Column> columns = Utils::splitHeader(line, '|');

        int len = columns.size();
        for(int i = 0; i < len; i++) {
            table.addColumn(columns[i].getName(), Utils::getTypeAsString(columns[i].getType()));
        }
    }

    while(std::getline(file, line)) {
        if(line.empty()) continue;
        
        if(!line.empty() && line.back() == '\r'){
            line.pop_back();
        }

        std::vector<std::string> row = Utils::splitRow(line, '|');
        table.addRow(row);
    }

    file.close();
    return true;
}

bool FileManager::saveTable(const std::string& fileName, const Table& table) {
    std::ofstream file(fileName);

    if(!file.is_open()) {
        Utils::log("Could not write to file " + fileName, Utils::Color::RED);
        return false;
    }

    std::vector<Column> columns = table.getColumns();
    std::string header = Utils::concatHeader(columns, '|');

    file << header;

    std::vector<std::vector<std::string>> rows = table.constGetRows();

    int len = rows.size();

    for(int i = 0; i < len; i++) {
        std::string row = Utils::concatRow(rows[i], '|');
        file << row;
    }

    file.close();

    return true;
}