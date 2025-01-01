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


add_executable(vokab
  src/main.cpp
  src/MainWindow.cpp
  src/User.cpp
  src/FileManager.cpp
  src/MainWindow.h
  src/User.h
  src/AuthDialog.h
  src/AddDialog.h
  src/FileManager.h
  src/HomeWidget.cpp
  src/HomeWidget.h
  src/FlashcardWidget.cpp
  src/FlashcardWidget.h
  src/VocabFileHandler.cpp
  src/VocabFileHandler.h
)

target_link_libraries(vokab PRIVATE Qt5::Widgets nlohmann_json::nlohmann_json)

# Post-build command to run the executable
add_custom_command(
    TARGET vokab
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Running Vokab..."
    COMMAND $<TARGET_FILE:vokab>
)
 
