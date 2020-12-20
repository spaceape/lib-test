set(NAME driver)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(DRIVER_SRC_DIR ${TEST_SRC_DIR}/${NAME})

set(inc
  pass.h fail.h basic.h chrono.h glfw.h
)

if(SDK)
  file(MAKE_DIRECTORY ${DRIVER_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${DRIVER_SRC_DIR}
  )
endif(SDK)
