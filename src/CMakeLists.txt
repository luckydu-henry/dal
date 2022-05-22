set(ROOT ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

# Set static link path.
set(UNIX_LINK_PATH /usr/lib)
set(WIN32_LINK_PATH ${ROOT}/lib/WIN32/)
# Set dynamic link path.
set(WIN32_RUNTIME ${WIN32_LINK_PATH}/runtime/)

include_directories(${ROOT}/include/)

if(WIN32)
    message("Using system Windows.")
    link_directories(${WIN32_LINK_PATH})
elseif(UNIX)
    message("Using system Unix-likes.")
    link_directories(${UNIX_LINK_PATH})
endif(WIN32)

set(EXECUTABLE_OUTPUT_PATH ${ROOT}/build/bin)

# Because UNIXs uses static linking so it's not neccessary to copy 'a' files.
if(WIN32)
    message("Copy runtimes to: " ${EXECUTABLE_OUTPUT_PATH})
    file(COPY ${WIN32_RUNTIME} DESTINATION ${EXECUTABLE_OUTPUT_PATH})
elseif(UNIX)
    message("No need to copy runtimes.")    
endif(WIN32)

aux_source_directory(${ROOT}/src SRC_DIR)
add_executable(${PROJECT_NAME} ${SRC_DIR})

# Static link librarys.
if(WIN32)
    target_link_libraries(${PROJECT_NAME} OpenAL32)
    target_link_libraries(${PROJECT_NAME} sndfile)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} libopenal.so)
    target_link_libraries(${PROJECT_NAME} libsndfile.so)
endif(WIN32)
