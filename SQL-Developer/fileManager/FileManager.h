#include <string>
#include <vector>
#include "../entities/Table.h"

class FileManager {
public:
    static bool loadTable(const std::string& fileName, Table& table);
    static bool saveTable(const std::string& fileName, const Table& table);

    static void addToCatalog(const std::string& tableName, const std::string& fileName, const std::string& catalogFileName);

    //base commands
    static bool openFile(const std::string& fileName);
    static bool saveFile(const std::string& fileName, const std::string& changes);
};