cmake_minimum_required(VERSION 3.15)
project(Energy VERSION 1.0.0 LANGUAGES C CXX)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
#set(SOURCES src/energy.c)

add_library(rapl STATIC ${SOURCES})
target_include_directories(rapl PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

target_compile_features(rapl PUBLIC c_std_99)

add_library(rapl::rapl ALIAS rapl)

install(TARGETS rapl 
	EXPORT rapl_targets 
	ARCHIVE DESTINATION lib 
	LIBRARY DESTINATION lib
	RUNTIME  DESTINATION bin
	INCLUDES DESTINATION include

)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT rapl_targets #enable find_package
	FILE rapl_targets.cmake
	NAMESPACE rapl::
	DESTINATION lib/cmake/Rapl
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	RaplConfigVersion.cmake
    	VERSION ${PROJECT_VERSION}
    	COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
	cmake/RaplConfig.cmake.in
    	RaplConfig.cmake
    	INSTALL_DESTINATION lib/cmake/Rapl
)

install(FILES 
	${CMAKE_CURRENT_BINARY_DIR}/RaplConfig.cmake
    	${CMAKE_CURRENT_BINARY_DIR}/RaplConfigVersion.cmake
	DESTINATION lib/cmake/Rapl
)


enable_testing()
#find_package(Rapl REQUIRED CONFIG)
add_executable(rapl_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/main/saxpy.cpp )
target_link_libraries(rapl_test PRIVATE rapl::rapl)
add_test(NAME saxpy_test COMMAND rapl_test)
