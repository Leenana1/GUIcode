#pragma once

#include "RenderWell/render_well_export.hpp"
#include "RenderWell/DataObject.hpp"

#include <filesystem>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace RenderWell
{
class RENDERWELL_EXPORT DataBase
{
  //-----------------------------------------------------------
  // static Member Constants
  //-----------------------------------------------------------
public:
  static constexpr unsigned long k_FavoritesId = 0;

  //-----------------------------------------------------------
  // Object Modifiers
  //-----------------------------------------------------------
  explicit DataBase(const fs::path& inputDirectory = {});
  ~DataBase() noexcept = default;

  DataBase(const DataBase& obj) = default;
  DataBase(DataBase&& obj) noexcept = default;

  DataBase& operator=(const DataBase& obj) = default;
  DataBase& operator=(DataBase&& obj) = default;

  //-----------------------------------------------------------
  // Member Functions
  //-----------------------------------------------------------
  bool createList(std::string&& name, std::vector<unsigned long>&& books = {});
  bool deleteList(unsigned long listId);
  void writeListsToDisk();


  //-----------------------------------------------------------
  // Getters and Setters
  //-----------------------------------------------------------
  [[nodiscard]] unsigned long getLastUUID() const;
  [[nodiscard]] const std::vector<unsigned long>& getListIds() const;
  [[nodiscard]] const std::vector<unsigned long>& getBookIds() const;

  [[nodiscard]] DataObject* getDataObject(unsigned long index);
  [[nodiscard]] DataObject& getDataObjectRef(unsigned long index);
  [[nodiscard]] const DataObject* getDataObject(unsigned long index) const;
  [[nodiscard]] const DataObject& getDataObjectRef(unsigned long index) const;

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  T* getDataObjectAs(unsigned long index)
  {
    return static_cast<T*>(getDataObject(index));
  }

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  T& getDataObjectRefAs(unsigned long index)
  {
    return static_cast<T&>(getDataObjectRef(index));
  }

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  const T* getDataObjectAs(unsigned long index) const
  {
    return static_cast<const T*>(getDataObject(index));
  }

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  const T& getDataObjectRefAs(unsigned long index) const
  {
    return static_cast<const T&>(getDataObjectRef(index));
  }

  //-----------------------------------------------------------
  // Private Member Variables
  //-----------------------------------------------------------
private:
  std::map<unsigned long, std::shared_ptr<DataObject>> m_Objects;
  unsigned long m_NextUUID = 0;
  std::vector<unsigned long> m_BookIds = {};
  std::vector<unsigned long> m_ListIds = {};

  //-----------------------------------------------------------
  // Private Member Functions
  //-----------------------------------------------------------
  bool insert(const std::shared_ptr<DataObject>& object);
  void loadBooks(const fs::path& inputDirectory);
  void loadLists();
};
}
