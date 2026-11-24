#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int deltaRow[] = {0, -1, 0, 1}, deltaCol[] = {1, 0, -1, 0};

enum PlaneType : uint8_t { UNDEFINED, BOTTOM, FRONT, RIGHT, LEFT, BACK, LID };

struct Camera {
    PlaneType forward = BACK, backward = FRONT, left = LEFT, right = RIGHT,
              up = LID, down = BOTTOM;

    void pitchForward() {
        swap(up, forward);
        swap(forward, down);
        swap(down, backward);
    }
    void pitchBackward() {
        for (int i = 0; i < 3; i++)
            pitchForward();
    }

    void yawClockwise() {
        swap(forward, right);
        swap(right, backward);
        swap(backward, left);
    }
    void yawCounterclockwise() {
        for (int i = 0; i < 3; i++)
            yawClockwise();
    }
} camera;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool isPlane[8][8] = {};
    vector<pair<int, int>> planes;
    planes.reserve(6);

    for (int i = 1; i <= 6; i++) {
        string s;
        cin >> s;

        s.insert(s.begin(), '#');

        for (int j = 1; j <= 6; j++) {
            if (s[j] == '#') {
                isPlane[i][j] = true;
                planes.emplace_back(i, j);
            }
        }
    }

    PlaneType type[8][8];
    fill(&type[0][0], &type[7][8], UNDEFINED);
    function<void(Camera&, const pair<int, int>&)> findPlaneType =
        [&](Camera& camera, const pair<int, int>& coordinate) {
            auto [r, c] = coordinate;

            ASSERT(camera.forward == type[r][c]);

            if (isPlane[r][c + 1] and type[r][c + 1] == UNDEFINED) {
                type[r][c + 1] = camera.right;
                camera.yawClockwise();
                findPlaneType(camera, {r, c + 1});
                camera.yawCounterclockwise();
            }
            if (isPlane[r - 1][c] and type[r - 1][c] == UNDEFINED) {
                type[r - 1][c] = camera.up;
                camera.pitchBackward();
                findPlaneType(camera, {r - 1, c});
                camera.pitchForward();
            }
            if (isPlane[r][c - 1] and type[r][c - 1] == UNDEFINED) {
                type[r][c - 1] = camera.left;
                camera.yawCounterclockwise();
                findPlaneType(camera, {r, c - 1});
                camera.yawClockwise();
            }
            if (isPlane[r + 1][c] and type[r + 1][c] == UNDEFINED) {
                type[r + 1][c] = camera.down;
                camera.pitchForward();
                findPlaneType(camera, {r + 1, c});
                camera.pitchBackward();
            }
        };

    type[planes[0].first][planes[0].second] = BACK;
    findPlaneType(camera, planes[0]);

    for (int i = 0; i < 6; i++) {
        auto [ri, ci] = planes[i];

        for (int j = i + 1; j < 6; j++) {
            auto [rj, cj] = planes[j];

            if (type[ri][ci] == type[rj][cj]) {
                println("cannot fold");
                return 0;
            }
        }
    }
    println("can fold");

    return 0;
}