project(zSearchTests)

set(addLnkTargets zSearch XLib)
CreateTests(zSearch_ "${CMAKE_SOURCE_DIR}/ZSearch" ${addLnkTargets})