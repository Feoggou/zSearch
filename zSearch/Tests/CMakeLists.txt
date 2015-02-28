project(zSearchTests)

InitExe()

set(G_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/ZSearch")
set(G_LINK_TARGETS ${G_LINK_TARGETS} zSearch XLib)

CreateTests(zSearch_)