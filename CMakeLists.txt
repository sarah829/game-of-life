cmake_minimum_required(VERSION 3.17)
project(GameOfLife)
set(CMAKE_CXX_STANDARD 14)

set(SRC_FILES SimpleArrayGame.cpp SimpleArrayGame.h FrameGraphics.cpp FrameGraphics.h GraphicsGameClasses.cpp GraphicsGameClasses.h GameOfLifeApp.cpp GameOfLifeApp.h)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets 3.1 COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})