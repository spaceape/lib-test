project(test)
set(NAME "test")

set(PREFIX)
set(TEST_SRC_DIR ${GLOBL_SRC_DIR}/test)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_definitions(
  -fPIC -DPIC
)

set(inc
  base.h driver.h scenario.h suite.h harness.h
)

set(srcs
  driver/pass.cpp driver/fail.cpp driver/basic.cpp driver/chrono.cpp driver/glfw.cpp
  test.cpp
)

set(libs
)

add_subdirectory(driver)

add_library(${NAME} STATIC ${srcs})
set_target_properties(${NAME} PROPERTIES PREFIX "${PREFIX}")
target_link_libraries(${NAME} ${libs})

if(SDK)
  file(MAKE_DIRECTORY ${TEST_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${TEST_SRC_DIR}
  )
endif(SDK)
