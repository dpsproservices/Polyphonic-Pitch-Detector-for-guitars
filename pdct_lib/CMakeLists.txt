# CMake based build system.

# Common include folder
set(SOURCE_FOLDER include)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}")
add_subdirectory (${SOURCE_FOLDER})
set(INCLUDE_FOLDER
   ${INCLUDE_FOLDER}
   "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}"
)

# Add Main folder
set(SOURCE_FOLDER Main)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}")
add_subdirectory (${SOURCE_FOLDER})
set(INCLUDE_FOLDER
   ${INCLUDE_FOLDER}
   "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}"
)
   
# Add Pdct folder
set(SOURCE_FOLDER Pdct)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}")
add_subdirectory (${SOURCE_FOLDER})
set(INCLUDE_FOLDER
   ${INCLUDE_FOLDER}
   "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}"
)

# Add Pdct folder
set(SOURCE_FOLDER Gui)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}")
add_subdirectory (${SOURCE_FOLDER})
set(INCLUDE_FOLDER
   ${INCLUDE_FOLDER}
   "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}"
)

# Add Source folder
set(SOURCE_FOLDER Source)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}")
add_subdirectory (${SOURCE_FOLDER})
set(INCLUDE_FOLDER
   ${INCLUDE_FOLDER}
   "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}"
)

# Add Audio folder
set(SOURCE_FOLDER Audio)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}")
add_subdirectory (${SOURCE_FOLDER})
set(INCLUDE_FOLDER
   ${INCLUDE_FOLDER}
   "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}"
)

set(INCLUDE_FOLDER
   ${INCLUDE_FOLDER}
   "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER}"
    PARENT_SCOPE
)

add_library(pdct_lib ${pdct_lib_SOURCES})
