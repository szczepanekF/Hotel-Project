cmake_minimum_required(VERSION 3.4)

project(Program)


find_package(wxWidgets REQUIRED)
find_package( Boost  1.60.0 COMPONENTS date_time REQUIRED)
include(${wxWidgets_USE_FILE})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../library
        ${Boost_INCLUDE_DIRS}
)
#Ustaw we własnej zmiennej SOURCE_FILES zbiór plików źródłowych projektu
set(SOURCE_FILES src/cApp.cpp src/cMain.cpp src/LoginPanel.cpp include/LoginPanel.h src/RegistrationPanel.cpp include/RegistrationPanel.h src/baseLogRegistPanel.cpp include/baseLogRegistPanel.h src/MenuPanel.cpp include/MenuPanel.h src/basePanel.cpp include/basePanel.h src/SettingsPanel.cpp include/SettingsPanel.h src/RoomsPanel.cpp include/RoomsPanel.h src/ReservationPanel.cpp include/ReservationPanel.h include/Lists/RoomItemData.h include/Lists/SimpleRoomVirtualListControl.h src/Lists/SimpleRoomVirtualListControl.cpp src/Lists/SimpleReservationVirtualListControl.cpp include/Lists/SimpleReservationVirtualListControl.h include/Lists/ReservationItemData.h src/baseLoggedPanel.cpp include/baseLoggedPanel.h include/Lists/SimpleVirtualListBase.h)

#Włącz powyższy zbiór plików do zbudowania programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})
#Określenie zależności pomiędzy projektami Program i Biblioteka



target_link_libraries(Program Library ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})

#Dołącz katalog include podprojektu Program do globalnej listy. Dzięki temu każdy inny podprojekt będzie ten katalog "widział"
target_include_directories(Program PUBLIC include)

enable_testing()