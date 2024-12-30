cmake_minimum_required(VERSION 3.5)

project(Vokab LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)


add_executable(Vokab
  src/main.cpp
  src/mainWindow.cpp
  src/user.cpp
  src/fileManager.cpp
  src/mainWindow.h
  src/user.h
  src/authDialog.h
  src/FileManager.h
)

target_link_libraries(Vokab PRIVATE Qt5::Widgets nlohmann_json::nlohmann_json)
 
