set(cmake_generated ${CMAKE_BINARY_DIR}/CMakeCache.txt
                    ${CMAKE_BINARY_DIR}/CPackConfig.cmake
                    ${CMAKE_BINARY_DIR}/cmake_install.cmake  
                    ${CMAKE_BINARY_DIR}/Makefile
                    ${CMAKE_BINARY_DIR}/CMakeFiles
		    ${CMAKE_BINARY_DIR}/CPackSourceConfig.cmake
                    ${CMAKE_BINARY_DIR}/pdct
		    ${CMAKE_BINARY_DIR}/pdct_lib
		    ${CMAKE_BINARY_DIR}/pdct_config.h
)

foreach(file ${cmake_generated})
  if (EXISTS ${file})
     file(REMOVE_RECURSE ${file})
  endif()
endforeach(file)

message( STATUS "Clean all cmake cache file!!!!!" )
