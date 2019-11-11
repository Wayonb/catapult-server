cmake_minimum_required(VERSION 3.2)

add_subdirectory(fuzz)
add_subdirectory(impl)

catapult_define_tool(pipeline)
target_link_libraries(catapult.tools.pipeline catapult.tools.pipeline.impl)
