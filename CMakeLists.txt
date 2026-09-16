# ══════════════════════════════════════════════════════════════
#  2D_RIEE — 競技程式(Competitive Programming)
#
#  ★ 這個檔你不需要打開。規則只有一條:
#
#        編譯的永遠只有 solve.cpp 這一支。
#
#  template.cpp / solved/**/*.cpp / codebook/**/*.cpp 全部不編譯
#  (它們每一支都有自己的 main(),一起編會撞在一起)。
#
#  想看的話:CLion 右上 target 下拉只會有 solve 一個,不用選。
# ══════════════════════════════════════════════════════════════
cmake_minimum_required(VERSION 3.25)
project(RIEE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solve solve.cpp)

# ── GCC / MinGW(CLion + MSYS2 UCRT64 走這條)────────────────
target_compile_options(solve PRIVATE -Wall -Wextra)

#  坑:MinGW 編出來的 exe 少一顆 DLL 會「靜靜地什麼都不做」,
#      沒有錯誤訊息。-static 把它全部包進 exe 裡。
target_link_options(solve PRIVATE -static -static-libgcc -static-libstdc++)

# ── ★ Debug 才有的兩個保護,Release 自動消失 ──────────────────
#   LOCAL             -> solve.cpp 裡的 dbg(x) 才會印東西
#                        好處:交題之前不用刪任何 debug 程式碼
#   _GLIBCXX_ASSERTIONS -> vector 越界會直接喊出來,不是印一個亂數
target_compile_definitions(solve PRIVATE
    $<$<CONFIG:Debug>:LOCAL>
    $<$<CONFIG:Debug>:_GLIBCXX_ASSERTIONS>)

message(STATUS "[RIEE] 編譯目標:solve.cpp -> solve.exe")

# ══════════════════════════════════════════════════════════════
#  以後真的要做演算法視覺化(raylib)再回來加,現在不用看:
#
#    set(BUILD_EXAMPLES    OFF CACHE BOOL "" FORCE)
#    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
#    add_subdirectory(_old/vendor/raylib EXCLUDE_FROM_ALL)
#    add_executable(viz _old/src/_viz/viz.cpp)
#    target_link_libraries(viz PRIVATE raylib)
# ══════════════════════════════════════════════════════════════
