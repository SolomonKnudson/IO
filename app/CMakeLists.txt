add_executable(io-test
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)

target_link_libraries(io-test PRIVATE
  IO
)

