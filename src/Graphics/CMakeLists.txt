target_sources(engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RendererRasterizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RendererRM.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FrameBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GreedyMesher.cpp
)

add_subdirectory(Camera)
add_subdirectory(Primitives)
