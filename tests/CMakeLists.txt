
# find diff program
FIND_PROGRAM(DIFF_EXECUTABLE
	     NAMES numdiff diff FC
	     HINTS ${DIFF_DIR}
	     PATH_SUFFIXES bin
	     )

IF(NOT DIFF_EXECUTABLE MATCHES "-NOTFOUND")
  SET(TEST_DIFF ${DIFF_EXECUTABLE})
	MESSAGE(STATUS "Found ${DIFF_EXECUTABLE} to test the difference between files.")
ELSE()
  MESSAGE(FATAL_ERROR
          "Could not find numdiff, diff or fc. This is required for running the testsuite.\n"
          "Please specify TEST_DIFF by hand.")
ENDIF()


#test CPP compilation and wrapper
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP)
list(GET 1 ${MPI_INCLUDE_PATH}, MPI_single_include_path)
if(NOT MSVC AND NOT APPLE)
  add_test(NAME compile_simple_CPP_test
  COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/CPP/test.cpp ${OPENLEM_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} -o ${CMAKE_BINARY_DIR}/tests/CPP/test${CMAKE_EXECUTABLE_SUFFIX} ${OPENLEM_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} -lstdc++ -std=c++14 ) 
elseif(APPLE)
  add_test(NAME compile_simple_CPP_test
    COMMAND clang ${CMAKE_CURRENT_SOURCE_DIR}/CPP/test.cpp -L${CMAKE_BINARY_DIR}/lib/ ${OPENLEM_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} -o test${CMAKE_EXECUTABLE_SUFFIX} ${OPENLEM_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} -lc++ -std=c++14 -lm -I/usr/include/ -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/  ${LDFLAGS} -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -L${MPI_CXX_LIBRARIES} -I${MPI_single_include_path} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/)  
else()
  #MSVS
  if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_test(NAME compile_simple_CPP_test 
      COMMAND ${CMAKE_CXX_COMPILER} /I${CMAKE_SOURCE_DIR}\\include ${CMAKE_CURRENT_SOURCE_DIR}/CPP/test.cpp /W3 /EHsc /RTC1 /MDd /link /INCREMENTAL /NOLOGO ${CMAKE_BINARY_DIR}\\lib\\${WB_TARGET}.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib /IMPLIB:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib /WHOLEARCHIVE:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib ${WB_C_COMPILER_FLAGS_COVERAGE} /out:test${CMAKE_EXECUTABLE_SUFFIX} ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/)
  else()
    add_test(NAME compile_simple_CPP_test 
    COMMAND ${CMAKE_CXX_COMPILER} /I${CMAKE_SOURCE_DIR}\\include ${CMAKE_CURRENT_SOURCE_DIR}/CPP/test.cpp /W3 /EHsc /RTC1 /MD /link /INCREMENTAL /NOLOGO ${CMAKE_BINARY_DIR}\\lib\\${WB_TARGET}.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib /IMPLIB:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib /WHOLEARCHIVE:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib ${WB_C_COMPILER_FLAGS_COVERAGE} /out:test${CMAKE_EXECUTABLE_SUFFIX} ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/)
  endif()
endif()
set_tests_properties(compile_simple_CPP_test PROPERTIES TIMEOUT 60) 
add_test(run_simple_CPP_test
         ${CMAKE_COMMAND}
               -D TEST_NAME=run_simple_CPP_test
               -D TEST_PROGRAM=${CMAKE_BINARY_DIR}/tests/CPP/test${CMAKE_EXECUTABLE_SUFFIX} 
               -D TEST_ARGS=${CMAKE_CURRENT_SOURCE_DIR}/data/continental_plate.wb
               -D TEST_OUTPUT=${CMAKE_BINARY_DIR}/tests/CPP/run_simple_CPP_test.log
   -D TEST_REFERENCE=${CMAKE_CURRENT_SOURCE_DIR}/CPP/run_simple_CPP_test.log
               -P ${CMAKE_SOURCE_DIR}/tests/CPP/run_CPP_tests.cmake
               WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/) 
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP)
set_tests_properties(run_simple_CPP_test PROPERTIES TIMEOUT 60)
set_tests_properties(run_simple_CPP_test PROPERTIES DEPENDS compile_simple_CPP_test)


if(NOT MSVC AND NOT APPLE)
  add_test(NAME compile_simple_CPP_example 
     COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/CPP/example.cpp  -I${CMAKE_SOURCE_DIR}/ ${OPENLEM_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} -o example${CMAKE_EXECUTABLE_SUFFIX} ${OPENLEM_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} #-lstdc++ -std=c++14 
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/)
elseif(APPLE)
  add_test(NAME compile_simple_CPP_example 
     COMMAND clang ${CMAKE_CURRENT_SOURCE_DIR}/CPP/example.cpp -L${CMAKE_BINARY_DIR}/lib/ -Wl,-force_load,${CMAKE_BINARY_DIR}/lib/lib${WB_TARGET}.a -I${CMAKE_SOURCE_DIR}/include/ ${WB_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} -o example${CMAKE_EXECUTABLE_SUFFIX} ${WB_COMPILER_OPTIONS_PRIVATE_COVERAGE_NEW} -lc++ -std=c++14 -lm -I/usr/include/ -I/Library/Developer/CPPommandLineTools/SDKs/MacOSX.sdk/usr/include/ -L${MPI_CXX_LIBRARIES} -I${MPI_single_include_path}
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/)
else()
  #MSVS
  if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_test(NAME compile_simple_CPP_example 
    COMMAND ${CMAKE_CXX_COMPILER} /I${CMAKE_SOURCE_DIR}\\include ${CMAKE_CURRENT_SOURCE_DIR}/CPP/example.cpp /W3 /EHsc /RTC1 /MDd /link /INCREMENTAL /NOLOGO ${CMAKE_BINARY_DIR}\\lib\\${WB_TARGET}.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib /IMPLIB:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib /WHOLEARCHIVE:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib ${WB_C_COMPILER_FLAGS_COVERAGE} /out:example${CMAKE_EXECUTABLE_SUFFIX} ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/)
  else()
    add_test(NAME compile_simple_CPP_example 
    COMMAND ${CMAKE_CXX_COMPILER} /I${CMAKE_SOURCE_DIR}\\include ${CMAKE_CURRENT_SOURCE_DIR}/CPP/example.cpp /W3 /EHsc /RTC1 /MD /link /INCREMENTAL /NOLOGO ${CMAKE_BINARY_DIR}\\lib\\${WB_TARGET}.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib /IMPLIB:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib /WHOLEARCHIVE:${CMAKE_BINARY_DIR}/lib/${WB_TARGET}.lib ${WB_C_COMPILER_FLAGS_COVERAGE} /out:example${CMAKE_EXECUTABLE_SUFFIX} ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/)
  endif()
endif()
set_tests_properties(compile_simple_CPP_example PROPERTIES TIMEOUT 60) 
add_test(run_simple_CPP_example
   ${CMAKE_COMMAND}
               -D TEST_NAME=run_simple_CPP_example
               -D TEST_PROGRAM=${CMAKE_BINARY_DIR}/tests/CPP/example${CMAKE_EXECUTABLE_SUFFIX}
	       -D TEST_ARGS=${CMAKE_SOURCE_DIR}/data/lapalma.flt
	       -D TEST_ARGS_2=H4
               -D TEST_OUTPUT=${CMAKE_BINARY_DIR}/tests/CPP/run_simple_CPP_example.log
   -D TEST_REFERENCE=${CMAKE_CURRENT_SOURCE_DIR}/CPP/run_simple_CPP_example.log
               -P ${CMAKE_SOURCE_DIR}/tests/CPP/run_CPP_tests.cmake
               WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/CPP/) 
set_tests_properties(run_simple_CPP_example PROPERTIES TIMEOUT 60) 
set_tests_properties(run_simple_CPP_example PROPERTIES DEPENDS compile_simple_CPP_example)

