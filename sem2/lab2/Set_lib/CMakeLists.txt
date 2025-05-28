project(Set)

set(HEADER_FILES
        Set.hpp
)

set(SOURCE_FILES
        Set.cpp
)

add_library(Set_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})