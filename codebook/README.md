# codebook —— 模板庫

> **這是解決「不能積累」的那個東西。**
> 每一支都是**可以直接編譯執行**的完整程式,不是片段。
> 貼進題目時把 `main()` 刪掉,留上面的函式/struct 就好。

---

## §0 目前有什麼(23 支,2026-09-07 全部編譯 + 執行驗證通過)

| 資料夾 | 檔案 | 等級 | 一句話 |
|---|---|---|---|
| **01_basic** | `io.cpp` | 灰 | 快速輸入輸出 + 常用縮寫 + 多測骨架 |
| | `binary_search.cpp` | 綠 | 二分搜 / 二分答案 / 實數二分 |
| | `prefix_diff.cpp` | 綠 | 前綴和 + 差分(1D / 2D) |
| | `two_pointers.cpp` | 綠 | 雙指標 / 滑動視窗(最長 + 最短 + 不重複) |
| **02_ds** | `dsu.cpp` | 青 | 並查集(路徑壓縮 + 按大小合併) |
| | `fenwick.cpp` | 藍 | 樹狀陣列 + 樹上二分 |
| | `sparse_table.cpp` | 藍 | ST 表(靜態 RMQ,O(1) 查詢) |
| | `segtree_lazy.cpp` | 紫 | 線段樹(區間加 + 區間和,懶標) |
| **03_graph** | `traverse.cpp` | 青 | BFS / 迭代 DFS / 連通塊 / 網格 BFS |
| | `dijkstra.cpp` | 藍 | 最短路 + 路徑還原 |
| | `topo_sort.cpp` | 藍 | 拓撲排序 + 判環 + DAG 最長路 |
| | `mst_kruskal.cpp` | 藍 | 最小生成樹 |
| | `lca_binlift.cpp` | 紫 | LCA 倍增 + 樹上距離 |
| **04_dp** | `knapsack.cpp` | 青 | 背包 01 / 完全 / 多重 / 恰好裝滿 |
| | `lis.cpp` | 青 | LIS(嚴格 / 非嚴格 / 還原序列) |
| | `interval_dp.cpp` | 藍 | 石子合併 / 最少插入成迴文 |
| | `tree_dp.cpp` | 藍 | 子樹大小 / 最大權獨立集 / 樹直徑 |
| | `bitmask_dp.cpp` | 紫 | 狀壓 DP(TSP)+ 位元技巧 |
| | `digit_dp.cpp` | 紫 | 數位 DP |
| **05_string** | `hashing.cpp` | 藍 | 雙模數字串雜湊(隨機 base 防 hack) |
| | `kmp_z.cpp` | 紫 | KMP + Z 函數 |
| **06_math** | `sieve.cpp` | 青 | 線性篩 + 質因數分解 |
| | `modpow_inv.cpp` | 青 | 快速冪 / 逆元 / 組合數 |

**還沒寫的看 `docs/CP_ROADMAP.md` §5–§7,那裡標了「尚未寫」。**

---

## §1 怎麼用

| 情境 | 做什麼 |
|---|---|
| 想確認某支怎麼用 | **直接編譯執行它**,每支都有 `main()` 示範 + 預期輸出寫在註解 |
| 要用在題目上 | 複製「`main()` 以外」的部分,貼進 `src/_solve/solve.cpp` |
| 編譯單一支 | `g++ -std=c++20 -O2 -o out.exe codebook/04_dp/knapsack.cpp` |
| 全部重新驗證 | 見 §3 |

---

## §2 ★ 規則:沒有驗證過的模板不准信

每一支最上面都有一欄:

```
//  驗證   : [  ] 還沒用它 AC 過
```

| 狀態 | 意思 |
|---|---|
| `[  ]` | **我寫的,編譯執行過,但你還沒用它 AC 過任何一題** |
| `[OK] 2026-09-20 CF1234D` | **你用它 AC 過了。這時候才能信它** |

**⚠ 為什麼要分兩級:**
編譯過 ≠ 演算法對 ≠ 邊界對 ≠ 在你的題目上對。
**一個沒驗證過的模板,比沒有模板更危險** —— 因為你會信它,然後花兩小時 debug 別的地方。

**AC 之後,回來把那一欄改掉。這是這個 codebook 唯一的維護動作。**

---

## §3 全部重新驗證(換編譯器 / 改過模板之後)

```
cd /d/2D_RIEE
for %f in (codebook\*\*.cpp) do g++ -std=c++20 -O2 -Wall -o nul "%f"
```

或在 CLion 底下的 Terminal(bash):

```
for f in codebook/*/*.cpp; do g++ -std=c++20 -O2 -Wall -fsyntax-only "$f" || echo "FAIL $f"; done
```

**2026-09-07 的紀錄:23 支全部編譯成功 + 執行輸出與註解相符。**
