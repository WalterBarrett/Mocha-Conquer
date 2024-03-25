add_executable(mochamix makemix.cpp mixnamedb.cpp mixnamedb.h mixnamedb_data.cpp crc32.cpp crc32.h fastini.cpp fastini.h)
target_link_libraries(mochamix PUBLIC common miniposix ${STATIC_LIBS})

if (WIN32)
    target_compile_definitions(mochamix PRIVATE -DNOMINMAX)
endif()