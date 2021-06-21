set(SOURCES Geoparse.cpp Geoparse.hpp)

add_library(Geoparse STATIC ${SOURCES})

#target_link_libraries(Geoparse INTERFACE Simplexer)
target_include_directories(Geoparse PUBLIC ${PROJECT_SOURCE_DIR}/lib/Simplexer/include)