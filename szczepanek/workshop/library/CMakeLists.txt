cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES

        src/model/Client.cpp)
#Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
