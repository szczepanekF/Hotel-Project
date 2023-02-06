cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
    include/model/Client.h src/model/Client.cpp
        include/typedefs.h src/model/ClientType.cpp include/model/ClientType.h src/model/ShortTerm.cpp include/model/ShortTerm.h src/model/Standard.cpp include/model/Standard.h src/model/LongTerm.cpp include/model/LongTerm.h

        include/model/Room.h include/model/RoomWithoutTerrace.h include/model/RoomWithTerrace.h src/model/Room.cpp src/model/RoomWithTerrace.cpp src/model/RoomWithoutTerrace.cpp src/model/Reservation.cpp include/model/Reservation.h src/repositories/Repository.cpp include/repositories/Repository.h src/repositories/RoomRepository.cpp include/repositories/RoomRepository.h
         src/exceptions/HotelError.cpp include/exceptions/HotelError.h src/exceptions/ClientError.cpp include/exceptions/ClientError.h src/exceptions/ReservationError.cpp include/exceptions/ReservationError.h src/exceptions/RoomError.cpp include/exceptions/RoomError.h src/repositories/ClientRepository.cpp include/repositories/ClientRepository.h src/repositories/ReservationRepository.cpp include/repositories/ReservationRepository.h src/managers/RoomManager.cpp include/managers/RoomManager.h include/managers/ClientManager.h src/managers/ClientManager.cpp src/managers/ReservationManager.cpp include/managers/ReservationManager.h include/model/Predicates.h src/model/Predicates.cpp src/socket/C_client.cpp include/socket/C_client.h)


#Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)
find_package (Boost 1.60.0 COMPONENTS date_time)


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/ClientTest.cpp
        test/RoomTest.cpp test/ReservationTest.cpp test/RepositoryTest.cpp test/RoomManagerTest.cpp test/ClientManagerTest.cpp test/ReservationManagerTest.cpp test/PredicateTest.cpp) # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTest ${SOURCE_TEST_FILES} )


#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.cApp do programu testów
target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_LIBRARIES}
        ${Boost_DATE_TIME_LIBRARY}
        )

#dodaj cApp TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
