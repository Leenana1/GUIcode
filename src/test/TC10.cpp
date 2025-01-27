#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

#include <string>

TEST_CASE("TC10: Arrange eBooks A-Z:", "[Sorter]")
{
    BackendManager controller = BackendManager();
    
    std::vector<unsigned long> uuidList = controller.sort(k_AtoZ);

    DataBase& dataBase = controller.getDataBaseRef();

    std::string prevName = "";

    for(auto bookId : uuidList)
    {
        auto& book = dataBase.getDataObjectRefAs<EBook>(bookId);

        REQUIRE(book.m_Name < prevName);
    }
    
}    
