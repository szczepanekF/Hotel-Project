cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
    src/math_helpers.cpp
        src/model/Client.cpp include/model/Client.h include/model/Address.h src/model/Address.cpp include/model/Vehicle.h src/model/Vehicle.cpp src/model/Rent.cpp include/model/Rent.h include/model/typedef.h src/repositories/ClientRepository.cpp include/repositories/ClientRepository.h src/repositories/VehicleRepository.cpp include/repositories/VehicleRepository.h src/repositories/RentRepository.cpp include/repositories/RentRepository.h src/repositories/StorageContainer.cpp include/repositories/StorageContainer.h src/model/Bicycle.cpp include/model/Bicycle.h src/model/MotorVehicle.cpp include/model/MotorVehicle.h src/model/Moped.cpp include/model/Moped.h src/model/Car.cpp include/model/Car.h src/model/ClientType.cpp include/model/ClientType.h src/model/Default.cpp include/model/Default.h src/model/Bronze.cpp include/model/Bronze.h src/model/Silver.cpp include/model/Silver.h src/model/Gold.cpp include/model/Gold.h src/model/Platinum.cpp include/model/Platinum.h src/model/Diamond.cpp include/model/Diamond.h src/managers/ClientManager.cpp include/managers/ClientManager.h src/managers/VehicleManager.cpp include/managers/VehicleManager.h src/managers/RentManager.cpp include/managers/RentManager.h)
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
        test/ClientTest.cpp test/master.cpp test/AddressTest.cpp test/VehicleTest.cpp test/RentTest.cpp test/ClientRepositoryTest.cpp test/RentRepositoryTest.cpp test/VehicleRepositoryTest.cpp test/BicycleTest.cpp test/MopedTest.cpp test/CarTest.cpp test/ClientManagerTest.cpp test/VehicleManagerTest.cpp test/RentManagerTest.cpp) # tu w przyszłości będą dodawane pliki źródłowe testów

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