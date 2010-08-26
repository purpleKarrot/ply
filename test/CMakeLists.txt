
include(AddTestModule)

set(BUNNY_TGZ ${CMAKE_SOURCE_DIR}/data/bunny.ply.gz)
file(COPY ${BUNNY_TGZ} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
execute_process(COMMAND gunzip -c ${BUNNY_TGZ}
  OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/bunny.ply)

add_test_module(ply_test
  header.cpp
  model.cpp
  )

add_custom_target(check
  ${ply_test_EXECUTABLE} --result_code=no --log_level=all
  DEPENDS ${ply_test_EXECUTABLE}
  )
