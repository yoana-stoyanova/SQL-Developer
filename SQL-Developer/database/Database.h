#include <vector>
#include <string>

#include "../entities/Table.h"

const std::string CATALOG_FILE = "data/catalog.txt";

class Database {
    private:
    std::vector<Table> tables; 
    std::string catalogFileName = CATALOG_FILE;

public:
    Database();



    Table* findTableByName(const std::string& name);
    const Table* findTableByName(const std::string& name) const;

    void importTable(const std::string& fileName, const std::string& table);
    void showTables() const;
    void exportTable(const std::string& table, const std::string& fileName);

    void describe(const std::string& table) const;
    void addColumn(const std::string& table, const std::string& col, const std::string& type);
    void renameTable(const std::string& oldName, const std::string& newName);

    void printTable(const std::string& table) const;
    void select(size_t colIdx, const std::string& value, const std::string& table) const;
    void updateRow(const std::string& table, size_t searchCol, const std::string& searchValue, size_t targetCol, const std::string& targetValue);
    void deleteRows(const std::string& table, size_t col, const std::string& value);
    void insertRow(const std::string& table, const std::vector<std::string>& row);

    void innerJoin(const std::string& t1, size_t col1, const std::string& t2, size_t col2);
    int count(const std::string& table, size_t searchCol, const std::string& searchValue) const;
    void aggregate(const std::string& table, size_t searchCol, const std::string& searchValue, size_t targetCol, const std::string& operation);
};