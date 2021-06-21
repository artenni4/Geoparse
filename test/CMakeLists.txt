add_executable(TestGeoparse test.cpp)

target_link_libraries(TestGeoparse PRIVATE Geoparse)
target_include_directories(TestGeoparse PRIVATE ${PROJECT_SOURCE_DIR}/src)

add_test(NAME TestGeoparse COMMAND TestGeoparse)