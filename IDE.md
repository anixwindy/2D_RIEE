# IDE 分工:CLion 主力,VS 待命

> 建立 2026-09-07。
> **主力 = CLion**(90% 的時間在這裡寫 code)。**VS 不刪**,但只有三種情況才打開。
> ★ 這份只講「按哪裡」。「為什麼」寫在 `CLAUDE.md`,不重複。

---

## §0 一句話

> **CLion 寫 code、跑、量分數。**
> **只有兩件事去開 VS:「要知道哪個函式最慢」和「變數看起來像亂碼」。**
> **其他全部留在 CLion。**

---

## §0-1 ★ 三塊地盤,不准共用(這條是 LNK1104 的根治法)

| 工具 | 碰不碰 CMake | 用哪個建置目錄 |
|---|---|---|
| **`build.bat`** | ✅ configure + build | `build\` / `build-release\` / `build-asan\` |
| **CLion** | ✅ configure + build(**前提:toolchain 必須是 Visual Studio**) | **`cmake-build-clion\`(獨立,不共用)** |
| **Visual Studio** | ⛔ **永遠不要用「開啟資料夾」** | **不碰任何建置目錄** |

**為什麼 VS 完全不用碰 CMake:** §4 那三個用途(profiler / 看變數 / 看呼叫堆疊)**全部是對著一支已經建好的 exe 做事**。VS 不需要自己編。

| VS 要用時 | 怎麼開 |
|---|---|
| 程式正在跑,想看變數 | **Debug → Attach to Process** → 選 `hello_r.exe` |
| 想從頭 debug | **File → Open → Project/Solution → 直接選 `bin\hello_d.exe`** |
| 想 profile | 同上開 exe → **`Alt+F2`** |

### ⚠ 為什麼共用目錄會出事(2026-09-07 實測)

**`CMakeCache.txt` 記編譯器的「路徑」,不記編譯器需要的「環境變數」。**

VS 先在 `build\` 寫下 `cl.exe` 的絕對路徑 → CLion 進來看到 cache 有編譯器就**跳過偵測**直接用 → 但 CLion 的環境是 MinGW 的、`LIB` 是空的 → 編譯過、**link 炸 `LNK1104: 無法開啟檔案 kernel32.lib`**。

**不是「搶」,是「繼承了一個自己沒能力使用的編譯器」。CMake 察覺不到。**

---

## §1 每天的 CLion 操作表

| 按什麼 | 看到什麼 |
|---|---|
| 右上**組態**下拉 → **`x64 Release preset`** | ★ 量分數前的第一個動作。沒切就白量 |
| 右上 **target** 下拉 → 選資料夾名 | 例如 `hello` / `_s01_pong` / `_sand` |
| **▶(綠色三角)** | 編譯 + 跑。**不附加除錯器 → 數字乾淨** |
| 🐞(蟲子) | 附加除錯器。**只在找 bug 時按,不能拿來量分數** |
| `Shift+F6` | 全專案改名 ← CLion 最強的地方 |
| `Ctrl+Alt+M` | 把選起來的幾行抽成函式 |
| `Ctrl+Alt+S` | 開 Settings(下面 §5 要用) |
| 底下 Terminal → `build.bat hello release` | 完全繞過 IDE 的等價路徑。**設定弄不順時走這條** |

### ★ 驗收:不要看下拉選單寫什麼,看 exe 檔名

| 組態 | 產出 |
|---|---|
| Debug | `bin\hello_d.exe` |
| **Release** | **`bin\hello_r.exe`** ← **看到 `_r` 才算在量分數** |
| ASan | `bin\hello_asan.exe` |

Run 視窗第一行會印完整路徑。規則寫死在 `CMakeLists.txt:92-94`。

---

## §2 ⛔ 絕對不用開 VS

| 訊號 | 為什麼不用 |
|---|---|
| **量分數** | CLion 切 `x64 Release preset` + 按 ▶ 就夠 |
| **編譯錯誤** | 兩邊同一個編譯器,噴一模一樣的訊息。**捲到第一個紅字** |
| **改名 / 拆函式 / 找定義** | **CLion 在這塊贏 VS**,切過去是退步 |
| 「感覺 VS 比較專業」 | 🔴 這是圓心漂移,不是技術理由 |

---

## §3 ⚠ 可以開 VS,但有更省事的做法

| 訊號 | VS 能做 | ★ 但更好的是 |
|---|---|---|
| 陣列越界、記憶體亂寫 | ASan | **CLion 也能跑 ASan**(前提:§5-1 做完)。或雙擊 `_tools\build_asan.bat` |
| 想看編譯器有沒有向量化 / 產出的組語 | 反組譯視窗 | **godbolt.org** —— 貼上函式,右邊直接出組語,零安裝 |
| 想看 GPU / OpenGL 在幹嘛 | ❌ **VS 的圖形除錯只支援 D3D,對 raylib 的 OpenGL 沒用** | **RenderDoc**(獨立 exe) |
| 想量得比 VS 更準 | — | **Superluminal**(獨立 exe,不用開 IDE) |

---

## §4 ✅ 一定要開 VS —— 只有這三條

| 觸發訊號 | 開 VS 做什麼 | 什麼時候會發生 |
|---|---|---|
| **想知道「哪個函式吃掉最多時間」** | 開資料夾 → **`Alt+F2`**(診斷工具)→ CPU 使用率 | **階段 5(SIMD)左右**。見 §6 |
| **停在中斷點,但變數顯示成垃圾 / `<optimized out>` / STL 容器展不開** | **`F5`**,在中斷點上看變數 | 不定。**看到變數怪怪的就換,不要跟它耗** |
| **當機發生在 raylib 或系統 DLL 裡,看不到自己的呼叫堆疊** | **`F5`**,呼叫堆疊視窗最完整 | 少見,但發生時 CLion 幫不上忙 |

### ⚠ VS 這邊的坑

| 坑 | 解 |
|---|---|
| ⛔ **不要用「開啟資料夾」** | 會去 configure `build\`,污染 `build.bat` 的地盤。**直接開 exe 或 Attach to Process**(見 §0-1) |
| 🔴 **`hello_r.exe` 沒有 `.pdb`,profiler 只看得到位址,看不到函式名** | 要 profile 得先有一個帶符號的 Release → 見 §6-1 |
| 按 `F5` 量分數,數字是髒的 | **量分數按 `Ctrl+F5`**。但你根本不該用 VS 量分數(見 §2) |

---

## §5 一次性設定(做完就不用再碰)

### 5-1 🔴 兩件事一起做,少一件就會再爆

**只加 toolchain 不改目錄 → 還是會撞 cache。只改目錄不加 toolchain → 會安靜地用 GCC 編成功(更糟)。**

#### (a) 加 Visual Studio toolchain

| 順序 | 按什麼 |
|---|---|
| 1 | `Ctrl+Alt+S` → **Build, Execution, Deployment → Toolchains** |
| 2 | 左上 **`+`** → 選 **`Visual Studio`** |
| 3 | 自動找到 `C:\Program Files\Microsoft Visual Studio\18\Community`。**Architecture 選 `amd64`** |
| 4 | 選中它 → 按 **`▲`** 移到最上面(**最上面 = 預設**) |

⚠ CLion 2025.3.1 比 VS 18 早出。**如果這一步偵測不到 VS,就是版本太舊** → 建置回 `build.bat`,CLion 的 toolchain 留 MinGW 只給索引用(程式碼模型會有些微差異,但不影響寫 code)。

#### (b) 每個 profile 的 Build directory 改成獨立的

| Profile | Build directory 改成 |
|---|---|
| `x64 Debug preset` | `cmake-build-clion-debug` |
| `x64 Release preset` | `cmake-build-clion-release` |
| `x64 Debug + AddressSanitizer preset` | `cmake-build-clion-asan` |

(`.gitignore` 的 `cmake-build-*/` 已經擋掉了,不會進版控。)

#### 驗收 —— ★ 看 configure 的第一行,不要看下拉選單

| 印出什麼 | 意思 |
|---|---|
| `-- The CXX compiler identification is **MSVC** 19.x` | ✅ 對的 |
| `-- The CXX compiler identification is **GNU** 15.x` | 🔴 **是 GCC。這個數字不能跟 `build.bat` 的比** |

**這一步是安靜的失敗模式:GCC 會編成功、會跑、不報任何錯,只是數字錯。**

### 5-2 七個 profile,只留三個

`Ctrl+Alt+S` → **Build, Execution, Deployment → CMake**

| 清單上顯示 | 是什麼 | 怎麼處理 |
|---|---|---|
| **`Debug`**(彩色圖示) | 🔴 CLion 自己建的,建到 `cmake-build-debug\` | **關掉**(取消 Enable profile)。留著會有兩個 Debug 分不清 |
| `x64 Debug preset` | ✅ 你的 | **打勾** |
| **`x64 Release preset`** | ✅ 你的 | **打勾** ★ 量分數用這個 |
| `x64 Debug + AddressSanitizer preset` | ✅ 你的 | **打勾** |
| `x64-debug - x64-debug preset` | 重複品 | **不用管** |
| `x64-release - x64-release preset` | 重複品 | **不用管** |
| `x64-asan - x64-asan preset` | 重複品 | **不用管** |

**為什麼會有重複品:** `CMakePresets.json` 裡 `configurePresets` 和 `buildPresets` 各有三個同名項,CLion 各認一次 → 3 × 2 = 6,加自建的 Debug = 7。
**→ 只用短名字那三個(`x64 XXX preset`)。**

---

## §6 那張欠條:profiler

**CLion 在 Windows 上沒有內建 CPU profiler,也沒有能補的外掛。**(內建 profiler 只支援 Linux 的 perf / macOS 的 DTrace。)

**但這不重要,因為 Windows 的 profiler 全部是獨立 exe,attach 到跑起來的 process,不需要 IDE 整合。**

### 6-1 🔴 先解決一件事:Release 沒有符號檔

```
bin\*_d.pdb   → 49 個   (Debug 有符號)
bin\*_r.pdb   →  0 個   (Release 完全沒有)
```

**→ 現在直接拿 profiler 對 `hello_r.exe`,只會看到一堆記憶體位址,看不到函式名字。**

`CMakeLists.txt:94` 已經備好 `OUTPUT_NAME_RELWITHDEBINFO "${app}_rd"`,**缺的只是 `CMakePresets.json` 裡一個 `x64-relwithdebinfo` preset**(加 preset 不違反「不准改 CMakeLists.txt」的規則)。

那個組態 = **Release 的最佳化 + Debug 的符號**,產出 `bin\hello_rd.exe`。profiler 專用。
**★ 但量分數還是用 `_r.exe`,不要用 `_rd.exe`。**

### 還債順序

| 順位 | 工具 | 摩擦 | 什麼時候 |
|---|---|---|---|
| **1** | **★ 自己寫分段計時** → 印在 HUD | **零安裝** | **現在就能做(TIER 1-2)** |
| 2 | VS 診斷工具 `Alt+F2` | 中 | 階段 5 |
| 3 | Superluminal / VTune / AMD uProf | 中～高 | 階段 5 之後 |

### 分段計時的形狀(提示,不是答案)

- raylib 有 `GetTime()`,回傳 `double`(秒)。你要的是**兩次相減**
- **先分三段就好:更新 / 碰撞 / 繪製**。分太細第一次會做不完
- `DrawText` 印在 HUD,跟 FPS 放一起 → **它就變成計分板的一部分**
- 秒 × 1000 = ms。**NOTES 要記的就是 ms**
- 只看一幀會跳動 → **要平均**(例如記最近 60 幀)

### 欠條到期日

| 什麼時候手寫計時**不夠用** | 為什麼 |
|---|---|
| 分段計時說「更新最慢」,但不知道**更新裡面哪一行**最慢 | 手寫只能量你**已經懷疑**的地方 |
| 懷疑是**快取未命中 / 分支預測失敗** | 手寫**量不到**,一定要硬體計數器 |

**→ 大約在階段 5(SIMD / SoA)。階段 3(空間切分)的效果是 5-10 倍,大到手寫計時就看得一清二楚,不需要 profiler。**

---

## §7 現在的狀態

```
[OK] 2026-09-07  刪掉被 VS/CLion/build.bat 三方污染的 build\ 和 .idea\
[OK] 2026-09-07  build.bat 重建驗證通過（bin\hello_d.exe 連結成功）
[  ] §5-1(a) 加 Visual Studio toolchain      ← 🔴 沒做,CLion 現在只有兩個 MinGW
[  ] §5-1(b) 三個 profile 改成獨立 build 目錄  ← 🔴 沒做
[  ] §5-2    重設 profile(.idea 刪了,要重來)
[  ] §6-1    加 x64-relwithdebinfo preset(要 profile 才需要)
[  ] §6      分段計時(窮人的 profiler)
```

**★ 但這四項全部都不是最優先的。最優先的是 `docs\NOTES.md` 那一行空白 —— 第 0 號基準線。**
**設定弄不順就走逃生門:CLion 底下的 Terminal 打 `build.bat hello release`。**
