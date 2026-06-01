#include <vector>
#include "Column.h"

class Table {
private:
    std::string name;
    std::string fileName;

    std::vector<Column> cols;
    std::vector<std::vector<std::string>> rows;

public:
    Table(std::string name, std::string fileName);

    void showDetails() const;

    void addColumn(const std::string& name, const std::string& type);
    void Table::addRow(const std::vector<std::string>& row);

    std::string Table::getName() const;
    void Table::setName(const std::string& name);

    const std::vector<Column>& Table::getColumns() const;
    const std::vector<std::vector<std::string>>& Table::getRows() const;
};