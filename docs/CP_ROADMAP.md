# CP 技術地圖 —— 初階到紅名

> 建立 2026-09-07。
> **這份是「地圖」,不是「待辦」。** 一次只看你所在的那一格,和它的下一格。
> 打勾規則:**必須是「用它 AC 過一題」才能打勾。看懂不算。**

---

## §0 Codeforces 顏色與分數對照

| 顏色 | 名稱 | 分數 |
|---|---|---|
| 灰 | Newbie | < 1200 |
| 綠 | Pupil | 1200 – 1399 |
| 青 | Specialist | 1400 – 1599 |
| 藍 | Expert | 1600 – 1899 |
| 紫 | Candidate Master | 1900 – 2099 |
| 橙 | Master / International Master | 2100 – 2399 |
| **紅** | **Grandmaster 以上** | **2400 +** |

**★ 你現在的位置:DP 初階 ≈ 青(1400–1599)那一格。**

---

## §1 灰 (< 1200) —— 語言本身

| 技術 | 打勾 | codebook |
|---|---|---|
| cin/cout 解綁、vector、string、pair | [ ] | `codebook/01_basic/io.cpp` |
| sort + 自訂比較函式 | [ ] | — |
| 模擬(題目說什麼就做什麼) | [ ] | — |
| 暴力枚舉 + 剪枝 | [ ] | — |
| 奇偶性、gcd、簡單數學觀察 | [ ] | — |

**判準:2 小時內能解出 Div2 A。**

---

## §2 綠 (1200 – 1399) —— 常用工具

| 技術 | 打勾 | codebook |
|---|---|---|
| STL:map / set / priority_queue | [ ] | — |
| 排序後貪心(掃一遍) | [ ] | — |
| **前綴和 / 差分**(1D + 2D) | [ ] | `codebook/01_basic/prefix_diff.cpp` |
| **二分搜 / 二分答案** | [ ] | `codebook/01_basic/binary_search.cpp` |
| **雙指標 / 滑動視窗** | [ ] | `codebook/01_basic/two_pointers.cpp` |
| 簡單構造題 | [ ] | — |

**判準:穩定解 A + B。**

---

## §3 青 (1400 – 1599) —— ★ 你在這裡

| 技術 | 打勾 | codebook |
|---|---|---|
| **DP 入門**:線性 DP、狀態設計 | [ ] | — |
| **背包**(01 / 完全 / 多重) | [ ] | `codebook/04_dp/knapsack.cpp` |
| **LIS** O(n log n) | [ ] | `codebook/04_dp/lis.cpp` |
| **BFS / DFS / 連通塊 / 網格** | [ ] | `codebook/03_graph/traverse.cpp` |
| **並查集 DSU** | [ ] | `codebook/02_ds/dsu.cpp` |
| **質數篩 + 質因數分解** | [ ] | `codebook/06_math/sieve.cpp` |
| **快速冪 / 逆元 / 組合數** | [ ] | `codebook/06_math/modpow_inv.cpp` |
| 貪心 + 交換論證(證明為什麼貪心對) | [ ] | — |
| 二分圖染色 | [ ] | — |

**判準:穩定解 A + B + C。**

---

## §4 藍 (1600 – 1899) —— 演算法開始有名字

| 技術 | 打勾 | codebook |
|---|---|---|
| **Dijkstra**(非負權最短路) | [ ] | `codebook/03_graph/dijkstra.cpp` |
| Floyd / Bellman-Ford(負權) | [ ] | — |
| **拓撲排序 + DAG 上的 DP** | [ ] | `codebook/03_graph/topo_sort.cpp` |
| **最小生成樹 Kruskal** | [ ] | `codebook/03_graph/mst_kruskal.cpp` |
| **樹狀陣列 BIT** | [ ] | `codebook/02_ds/fenwick.cpp` |
| **ST 表(靜態 RMQ)** | [ ] | `codebook/02_ds/sparse_table.cpp` |
| **區間 DP** | [ ] | `codebook/04_dp/interval_dp.cpp` |
| **樹形 DP** | [ ] | `codebook/04_dp/tree_dp.cpp` |
| **字串雜湊** | [ ] | `codebook/05_string/hashing.cpp` |
| 二分答案 + 貪心 check | [ ] | — |

**判準:穩定 A–D,偶爾摸到 E。**

---

## §5 紫 (1900 – 2099) —— 資料結構的主場

| 技術 | 打勾 | codebook |
|---|---|---|
| **線段樹 + 懶標** | [ ] | `codebook/02_ds/segtree_lazy.cpp` |
| **LCA 倍增 / 樹上跳躍** | [ ] | `codebook/03_graph/lca_binlift.cpp` |
| **狀壓 DP** | [ ] | `codebook/04_dp/bitmask_dp.cpp` |
| **數位 DP** | [ ] | `codebook/04_dp/digit_dp.cpp` |
| **KMP / Z 函數** | [ ] | `codebook/05_string/kmp_z.cpp` |
| Trie 字典樹 | [ ] | 尚未寫 |
| SCC(Tarjan)/ 割點 / 橋 | [ ] | 尚未寫 |
| 容斥原理 / 排列組合進階 | [ ] | 尚未寫 |
| 根號分治入門 | [ ] | 尚未寫 |

**判準:穩定 A–E。**

---

## §6 橙 (2100 – 2399) —— 開始需要「優化」而不只是「會」

| 技術 | 打勾 | codebook |
|---|---|---|
| 線段樹進階(動態開點 / 合併 / 分治) | [ ] | 尚未寫 |
| 樹鏈剖分 HLD | [ ] | 尚未寫 |
| 網路流 / 二分圖最大匹配 | [ ] | 尚未寫 |
| DP 優化:單調隊列 | [ ] | 尚未寫 |
| DP 優化:斜率優化 / 決策單調性 | [ ] | 尚未寫 |
| 矩陣快速冪 | [ ] | 尚未寫 |
| 莫隊演算法 / 分塊 | [ ] | 尚未寫 |
| FFT / NTT | [ ] | 尚未寫 |
| 期望 DP / 機率 | [ ] | 尚未寫 |

**判準:穩定 A–E,常摸到 F。**

---

## §7 紅 (2400 +) —— ★ 模板救不了你的那一層

| 技術 | 打勾 |
|---|---|
| 可持久化資料結構 / 主席樹 | [ ] |
| 平衡樹(Treap / Splay)/ LCT | [ ] |
| SOS DP / 輪廓線 DP / 插頭 DP | [ ] |
| 生成函數 / 多項式全家桶 | [ ] |
| Burnside / Polya / 線性代數 | [ ] |
| 一般圖匹配、最小割建模 | [ ] |

### ⚠ 這一格的真相,要先講

> **2000 分以前,主要瓶頸是「知不知道這個演算法」。**
> **2000 分以後,主要瓶頸是「看不看得出這題可以轉成那個演算法」。**

**→ codebook 的邊際效用,在紫名之後急速下降。**
到那時候你缺的不是模板,是**問題轉化能力**,而那個只能靠「大量做題 + 每題都寫下『我卡在哪一步』」累積。

**這就是為什麼 `cp/solved/` 那些 `.md` 比 codebook 更重要。**

---

## §8 每一格的通關動作

| 步驟 | 做什麼 |
|---|---|
| 1 | 在自己那一格挑一個還沒打勾的技術 |
| 2 | 找 3–5 題那個 tag 的題目(Codeforces problemset 可以照 tag + rating 篩) |
| 3 | 第一題可以看題解,**後面幾題不准看** |
| 4 | AC 之後 → 回來把 `[ ]` 改成 `[OK] 日期 題號` |
| 5 | 同時把 codebook 那支的「驗證」欄從 `[  ]` 改成 `[OK]` |

**★ 一格全部打勾 = 可以往下一格。沒打完不准跳。**
