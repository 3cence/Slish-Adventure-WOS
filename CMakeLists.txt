cmake_minimum_required(VERSION 3.0.0)
project(SAWOS VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("headers/"
"/usr/include")
add_executable(SAWOS src/main.cpp
src/Bullet.cpp
src/Constants.cpp
src/Entity.cpp
src/Green_Slish.cpp
src/Player.cpp
src/Utils/Fractions.cpp
src/Utils/Graphing.cpp
src/Utils/Shapes.cpp
src/Utils/Resources.cpp)
target_link_libraries(SAWOS SDL2 SDL2main SDL2_image SDL2_ttf)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
