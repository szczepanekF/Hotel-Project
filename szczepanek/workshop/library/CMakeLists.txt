cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES

        src/model/Client.cpp src/model/Address.cpp include/model/Vehicle.h src/model/Vehicle.cpp include/model/Rent.h
        src/model/Rent.cpp include/typedefs.h include/repositories/ClientRepository.h
        include/repositories/VehicleRepository.h include/repositories/RentRepository.h src/repositories/ClientRepository.cpp
        src/repositories/VehicleRepository.cpp src/repositories/RentRepository.cpp include/repositories/StorageContainer.h
        src/repositories/StorageContainer.cpp
        include/model/Bicycle.h include/model/MotorVehicle.h include/model/Moped.h include/model/Car.h
        src/model/Bicycle.cpp
        src/model/MotorVehicle.cpp src/model/Moped.cpp src/model/Car.cpp include/model/ClientType.h src/model/ClientType.cpp include/model/Diamond.h include/model/Platinum.h include/model/Gold.h include/model/Silver.h include/model/Bronze.h include/model/Default.h src/model/Diamond.cpp src/model/Platinum.cpp src/model/Gold.cpp src/model/Silver.cpp src/model/Bronze.cpp src/model/Default.cpp "include/managers/ClientManager.h" src/managers/ClientManager.cpp src/managers/VehicleManager.cpp include/managers/VehicleManager.h include/managers/RentManager.h src/managers/RentManager.cpp)
#Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES


        test/master.cpp test/ClientTest.cpp test/AddressTest.cpp test/VehicleTest.cpp test/RentTest.cpp test/ClientRepositoryTest.cpp test/VehicleRepositoryTest.cpp test/RentRepositoryTest.cpp test/StorageContainerTest.cpp test/BicycleTest.cpp test/MopedTest.cpp test/CarTest.cpp test/ClientManagerTest.cpp test/VehicleManagerTest.cpp test/RentManagerTest.cpp)  # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTest ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})