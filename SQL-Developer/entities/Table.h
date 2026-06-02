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
    void addRow(const std::vector<std::string>& row);

    std::string getName() const;
    void setName(const std::string& name);

    const std::string getFileName() const;

    const std::vector<Column>& getColumns() const;

    const std::vector<std::vector<std::string>>& constGetRows() const;
    std::vector<std::vector<std::string>>& getRows();
};