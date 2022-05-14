set(ROOT ${PROJECT_SOURCE_DIR})

include_directories(${ROOT}/include)
link_directories(${ROOT}/lib)

aux_source_directory(${ROOT}/src SRC_DIR)
add_executable(Musx ${SRC_DIR})


if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(Musx libopenal.a)
    target_link_libraries(Musx libsndfile.a)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(Musx libopenal.lib)
    target_link_libraries(Musx libsndfile.lib)
endif()