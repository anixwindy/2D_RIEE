// ══════════════════════════════════════════════════════════════
//  ★ 演算法視覺化 —— 遙遠未來用的,環境先弄好
//
//  現在按 ▶ 應該會看到一個視窗,裡面有一格一格的網格。
//  ★ 看到視窗 = raylib 環境是好的。這就是這支現在唯一的用途。
//
//  未來要做什麼(不是現在):
//    [ ] 把 BFS 的擴散畫出來(一層一個顏色)
//    [ ] 把 DP 表格畫出來(填表過程動畫)
//    [ ] 把線段樹畫成樹,更新時路徑亮起來
//
//  ⚠ 判準:做完第一個之後,下次遇到同型題你會不會真的打開它?
//     會 -> 繼續做第二個。不會 -> 立刻收掉,不要做第二個。
// ══════════════════════════════════════════════════════════════
#include "raylib.h"

int main() {
    const int W = 900, H = 600;
    const int CELL = 40;

    InitWindow(W, H, "CP Visualizer - environment check");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int y = 0; y < H / CELL; ++y)
            for (int x = 0; x < W / CELL; ++x) {
                Color c = ((x + y) % 2 == 0) ? LIGHTGRAY : RAYWHITE;
                DrawRectangle(x * CELL, y * CELL, CELL - 1, CELL - 1, c);
            }

        DrawText("raylib is alive. Grid is ready.", 20, 20, 24, DARKBLUE);
        DrawText("This is the seed for algorithm visualization.", 20, 54, 18, GRAY);
        DrawFPS(W - 90, 10);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
