cmake_minimum_required(VERSION 3.4)

project(Program)


find_package(wxWidgets REQUIRED COMPONENTS net core base)

include(${wxWidgets_USE_FILE})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../library

)
#Ustaw we własnej zmiennej SOURCE_FILES zbiór plików źródłowych projektu
set(SOURCE_FILES src/cApp.cpp src/gMain.cpp src/LoginPanel.cpp include/LoginPanel.h src/RegistrationPanel.cpp include/RegistrationPanel.h src/baseLogRegistPanel.cpp include/baseLogRegistPanel.h)

#Włącz powyższy zbiór plików do zbudowania programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})
#Określenie zależności pomiędzy projektami Program i Biblioteka


target_link_libraries(Program Library)

#Dołącz katalog include podprojektu Program do globalnej listy. Dzięki temu każdy inny podprojekt będzie ten katalog "widział"
target_include_directories(Program PUBLIC include)
target_link_libraries(Program
        ${wxWidgets_LIBRARIES})
enable_testing()