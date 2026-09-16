# IDE —— CLion + MinGW GCC

> 這個資料夾只有**一個**工具鏈:**CLion + MinGW GCC**(`C:/msys64/ucrt64`)。
> 跟 Codeforces 同一家編譯器,`bits/stdc++.h` 也只有 GCC 有。
> **這裡沒有 Visual Studio、沒有 MSVC、沒有 `build.bat`。也不需要。**

---

## §1 每天按什麼

| 按什麼 | 看到什麼 |
|---|---|
| target 下拉選 **`_solve`** | 你的解題檔 `src/_solve/solve_model.cpp` |
| **▶(綠三角)** | 編譯 + 執行,**測資從 `in.txt` 自動餵進去**(要先做 §2) |
| **🐞(蟲子)** | 同上但可以下中斷點看變數。CLion 用 msys64 的 gdb,跟 GCC 完全對得上 |
| `Shift+F6` | 全專案改名 |
| `Ctrl+B` / `Alt+F7` | 跳到定義 / 找出誰用了它 |
| target 選 **`_viz`** → ▶ | 一個網格視窗 = raylib 還活著 |

### ★ Debug 和 Release 的差別(只有一個,但很重要)

| 組態 | `dbg(x)` 巨集 | 產出 |
|---|---|---|
| **Debug** | ✅ **會印到 stderr** | `bin/_solve_d.exe` |
| Release | ❌ 完全消失 | `bin/_solve_r.exe` |

`CMakeLists.txt` 在 Debug 版自動定義 `LOCAL`,`solve.cpp` 的 `dbg()` 靠它開關。
**→ 平常用 Debug 跑,交題目之前不用刪任何 debug 程式碼。**

---

## §2 一次性設定 —— 只有一項,但它是最值錢的一項

**讓測資自動從 `in.txt` 進去,不用每次手打。**

| 順序 | 按什麼 |
|---|---|
| 1 | 右上 target 下拉 → **Edit Configurations...** |
| 2 | 選 **`_solve`** |
| 3 | 勾 **`Redirect input from`** |
| 4 | 填 **`src/_solve/in.txt`** |
| 5 | OK |

**之後每一題:測資貼進 `in.txt` → 按 ▶ → 直接看答案。**

---

## §3 編單獨一支 codebook

不用開 CMake,直接在 CLion 底下的 Terminal:

```
g++ -std=c++20 -O2 -o out.exe codebook/04_dp/knapsack.cpp && ./out.exe
```

全部重驗一次(改過模板 / 換過編譯器之後):

```
for f in codebook/*/*.cpp; do g++ -std=c++20 -O2 -fsyntax-only "$f" || echo "FAIL $f"; done
```

---

## §4 ⛔ 三件不要做的事

| 不要做 | 為什麼 |
|---|---|
| **不要在 CLion 加 Visual Studio toolchain** | MSVC **沒有 `bits/stdc++.h`**。這個資料夾就是要用 GCC |
| **不要用 VS「開啟資料夾」開這裡** | 它會 configure 你的建置目錄,把 MSVC 的環境灌進 cache |
| **不要跟別的工具共用同一個建置目錄** | ↓ 見下面那個坑 |

### 🔴 2026-09-07 實測到的坑(記著,別再踩)

**`CMakeCache.txt` 記編譯器的「路徑」,不記編譯器需要的「環境變數」。**

當時的情況:VS 先在 `build/` 寫下 `cl.exe` 的絕對路徑 → CLion 進來看到 cache 已經有編譯器就**跳過偵測**直接用 → 但 CLion 的環境沒有 MSVC 的 `LIB` → 編譯過了,**link 炸 `LNK1104: 無法開啟檔案 kernel32.lib`**。

**不是「兩個工具搶目錄」,是「繼承了一個自己沒能力使用的編譯器」,而 CMake 察覺不到。**

**→ 在這個資料夾,只要維持「只有 CLion + GCC」,這個坑就不存在。**

---

## §5 什麼時候才需要別的工具

| 訊號 | 用什麼 |
|---|---|
| 想看某段 code 編出來的組合語言 | **godbolt.org**(貼上去就好,零安裝) |
| 想知道哪個函式最慢 | CP 幾乎用不到。真要的話裝 **Superluminal / VTune**(獨立 exe) |
| `_viz` 以後要看 OpenGL 在幹嘛 | **RenderDoc**(獨立 exe) |

**★ 全部都是獨立工具,跟 IDE 無關。所以「CLion 沒有內建 profiler」在這裡完全不是問題。**
