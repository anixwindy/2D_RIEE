# NOTES.md — 差分帳本(CP 版)

> **規則:每個實作日五行。**
> 沒解題的那天,寫「沒解題」也算一行,**不要留白**。
> 留白三次 = 🔴 紅色警報第一條(圓心漂走了)。

格式:

```
## YYYY-MM-DD
- 解了什麼   : 題號 + rating
- 結果       : AC 一發 / WA N 次後 AC / 看題解才會 / 沒解出來
- 打勾了什麼 : CP_ROADMAP 的哪一格 / codebook 哪一支從 [  ] 變 [OK]
- 學到 / 踩到:
- NEXT       :
```

**★ 詳細的想法寫在 `cp/solved/*.md`,這裡只寫五行摘要。兩份不要重複。**

---

## 2026-09-07
- 解了什麼   : 無。今天在建工作區。
- 結果       : —
- 打勾了什麼 : 零。**codebook 23 支全部是 `[  ]`,一個 `[OK]` 都還沒有。**
- 學到 / 踩到: 從 D:\2D_EIRR 複製一份出來改成 CP 工作區。砍掉 29 個遊戲/教材資料夾、
               roadmap、years、raylib教學、MSVC 專用的 .bat。
               改了 CMakeLists:只有 `#include "raylib.h"` 的資料夾才連 raylib
               → `_solve` 編譯不用再等 raylib。
               ⚠ 建工作區不是解題。今天的真實產出是 0 題。
- NEXT       : **挑一題 1400 分的 DP,寫在 `src/_solve/solve.cpp`。**
               AC 之後在 `cp/solved/` 留下第一份 .md,
               再回頭把 `codebook/04_dp/knapsack.cpp` 的驗證欄改成 `[OK]`。

---
