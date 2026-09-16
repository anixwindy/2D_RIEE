# ══════════════════════════════════════════════════════════════
#  2D_RIEE — C++20 + raylib 6.0   (CP 競程主場,raylib 只給 src/_viz)
#
#  ★ 這個檔你不需要打開。
#
#  規則只有一條:
#      src/ 底下一個資料夾 = 一個獨立的執行檔
#
#      src/hello/     -> bin/hello.exe
#      src/rain/      -> bin/rain.exe    (你新建資料夾它就自己出現)
#
#  資料夾裡面可以放任意多個 .cpp / .h,
#  但每個資料夾**剛好一個 main()**。
#
#  真的要改這個檔的時機只有兩種:
#    1. 要接一個新的函式庫(例如 raygui)
#    2. 要加網頁編譯(emscripten)
#  這兩件事發生之前,這個檔就當它不存在。
# ══════════════════════════════════════════════════════════════
cmake_minimum_required(VERSION 3.25)
project(EIRR LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# ── 旋鈕:抓陣列越界(C++ 沒有例外訊息,這是唯一的解藥)──
#    平常關著。要抓 bug 時雙擊 _tools\build_asan.bat
option(EIRR_ASAN "AddressSanitizer:陣列越界會印出檔名 + 行號" OFF)

# ── raylib 本體(原始碼在 vendor/raylib,離線可建)──────────
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/CMakeLists.txt")
    message(FATAL_ERROR
        "\n找不到 vendor/raylib\n"
        "-> 雙擊 _tools\get_raylib.bat 重新抓一次\n")
endif()

set(BUILD_EXAMPLES     OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS  OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/raylib EXCLUDE_FROM_ALL)

# ── ASan 的共用設定(只有 -DEIRR_ASAN=ON 才會用到)──────────
if(EIRR_ASAN AND MSVC)
    # MSVC 的 ASan 跟 /RTC1(執行時檢查)互斥,要先把它拿掉
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "" FORCE)

    # 坑:MSVC 的 ASan 需要一顆執行期 DLL,而它不在 PATH 上。
    #     VS 按 F5 會自動處理,但雙擊 .bat 跑就會「什麼都沒發生」。
    #     -> 建置完自動複製到 bin/ 旁邊。DLL 跟 cl.exe 同一個資料夾。
    get_filename_component(MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(ASAN_DLL "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll")
endif()

# ── ★ src/ 底下每一個資料夾 -> 一個執行檔 ────────────────────
#    CONFIGURE_DEPENDS = 你新建資料夾 / 新增 .cpp,CMake 自己會發現
file(GLOB EIRR_APP_PATHS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

set(EIRR_APPS "")

foreach(appPath IN LISTS EIRR_APP_PATHS)
    if(NOT IS_DIRECTORY "${appPath}")
        continue()
    endif()

    get_filename_component(app "${appPath}" NAME)

    file(GLOB_RECURSE appSrc CONFIGURE_DEPENDS "${appPath}/*.cpp" "${appPath}/*.c")

    if(NOT appSrc)
        message(STATUS "[EIRR] src/${app} 裡沒有 .cpp,跳過")
        continue()
    endif()

    add_executable(${app} ${appSrc})
    target_include_directories(${app} PRIVATE "${appPath}")

    # ── ★ 只有真的 #include "raylib.h" 的資料夾才連 raylib ──────
    #    CP 的解題檔完全用不到 raylib。全部都連的話,每次編譯都得先等
    #    raylib 建好(冷建置約 40 秒),那是純浪費。
    #    raylib 是 EXCLUDE_FROM_ALL,沒人連它就完全不會被建。
    set(needsRaylib FALSE)
    foreach(oneSrc IN LISTS appSrc)
        file(READ "${oneSrc}" oneSrcText)
        if(oneSrcText MATCHES "raylib\.h")
            set(needsRaylib TRUE)
            break()
        endif()
    endforeach()
    if(needsRaylib)
        target_link_libraries(${app} PRIVATE raylib)
        message(STATUS "[RIEE] src/${app} -> 連 raylib")
    else()
        message(STATUS "[RIEE] src/${app} -> 純 C++,不連 raylib")
    endif()

    # 執行檔一律放 bin/,★ 檔名帶組態:hello_d.exe / hello_r.exe / hello_asan.exe
    #
    #  為什麼要帶字尾(2026-09-04 實測到的坑,不是潔癖):
    #    三種組態共用同一個 bin/。以前三個都叫 hello.exe ->
    #    Debug 編完會蓋掉 Release 的 exe。接著你切回 Release 再編,
    #    ninja 看到 bin/hello.exe 的時間比自己的 .obj 新 -> 判定「已是最新」
    #    -> 不重新連結,而且照樣印 Build OK。
    #    結果:你以為在量 Release,實際跑的是 Debug,分數低 3-10 倍,零錯誤訊息。
    set_target_properties(${app} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin"
        OUTPUT_NAME_DEBUG                       "${app}_d"
        OUTPUT_NAME_RELEASE                     "${app}_r"
        OUTPUT_NAME_RELWITHDEBINFO              "${app}_rd"
        VS_DEBUGGER_WORKING_DIRECTORY           "${CMAKE_SOURCE_DIR}")

    if(MSVC)
        # /utf-8 -> 原始碼裡的中文註解不會變亂碼; /W3 -> 中等嚴格的警告
        target_compile_options(${app} PRIVATE /utf-8 /W3)
    else()
        # GCC / Clang(CLion + MSYS2 UCRT64 走這條)
        target_compile_options(${app} PRIVATE -Wall -Wextra -Wno-unused-parameter)
        # 坑:MinGW exe 缺 DLL 會「靜靜地什麼都不做」-> 全靜態連結
        target_link_options(${app} PRIVATE -static -static-libgcc -static-libstdc++)
        # Debug 版打開標準函式庫的邊界檢查
        target_compile_definitions(${app} PRIVATE $<$<CONFIG:Debug>:_GLIBCXX_ASSERTIONS>)
    endif()

    # ── ★ Debug 版自動定義 LOCAL ────────────────────────────
    #    src/_solve/solve.cpp 裡的 dbg(x) 巨集只在 LOCAL 有定義時才印東西。
    #    Debug = 本機測試,要看中間值;Release = 乾淨輸出。
    #    好處:交題目之前不用刪任何 debug 程式碼。
    target_compile_definitions(${app} PRIVATE $<$<CONFIG:Debug>:LOCAL>)

    if(EIRR_ASAN AND MSVC)
        target_compile_options(${app} PRIVATE /fsanitize=address /Zi)
        target_link_options(${app} PRIVATE /INCREMENTAL:NO /DEBUG)
        # ASan 是跑在 Debug 組態上,所以要蓋掉上面那行 OUTPUT_NAME_DEBUG,
        # 不然它會變成 hello_d.exe,跟一般 Debug 版撞名(又回到同一個坑)
        set_target_properties(${app} PROPERTIES OUTPUT_NAME_DEBUG "${app}_asan")
        if(EXISTS "${ASAN_DLL}")
            add_custom_command(TARGET ${app} POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                        "${ASAN_DLL}" "$<TARGET_FILE_DIR:${app}>")
        else()
            message(WARNING "[EIRR] 找不到 ASan 執行期 DLL,${app}_asan.exe 可能會靜靜地不動")
        endif()
    endif()

    list(APPEND EIRR_APPS ${app})
endforeach()

if(NOT EIRR_APPS)
    message(FATAL_ERROR
        "\nsrc/ 底下找不到任何含 .cpp 的資料夾\n"
        "-> 建一個資料夾,例如 src/rain/,把 .cpp 放進去\n")
endif()

# ── VS 開起來時,按 F5 預設跑哪一個 ─────────────────────────
if(MSVC)
    if("hello" IN_LIST EIRR_APPS)
        set(EIRR_STARTUP hello)
    else()
        list(GET EIRR_APPS 0 EIRR_STARTUP)
    endif()
    set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                 PROPERTY VS_STARTUP_PROJECT ${EIRR_STARTUP})
    message(STATUS "[EIRR] F5 預設跑:${EIRR_STARTUP}")
endif()

if(EIRR_ASAN AND MSVC)
    message(STATUS "[EIRR] AddressSanitizer: ON  ->  bin/<name>_asan.exe")
endif()

message(STATUS "[EIRR] raylib 6.0 | 執行檔:${EIRR_APPS}")
