target_sources(engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FrameBuffer.cpp
)

add_subdirectory(Camera)
