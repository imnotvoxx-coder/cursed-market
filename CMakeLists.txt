cmake_minimum_required(VERSION 3.25)

project(CursedMarket)

find_package(Geode REQUIRED)

add_geode_mod(
    ${PROJECT_NAME}
    SOURCES src/main.cpp
    RESOURCES 
        resources/1000037107.png
        resources/1000037108.jpg
        resources/1000037109.jpg
        resources/1000037110.jpg
        resources/1000037111.jpg
        resources/1000037112.jpg
        resources/1000037113.jpg
)
