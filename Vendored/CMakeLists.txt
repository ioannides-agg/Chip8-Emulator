add_subdirectory(SDL)

add_library(Vendored INTERFACE)
target_link_libraries(Vendored INTERFACE SDL3::SDL3)