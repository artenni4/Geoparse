add_executable(TestGeoparse test.cpp)

target_link_libraries(TestGeoparse PUBLIC Geoparse)
target_include_directories(TestGeoparse PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_test(NAME TestGeoparse COMMAND TestGeoparse)