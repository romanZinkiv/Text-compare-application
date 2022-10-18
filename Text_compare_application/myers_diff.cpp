#include "myers_diff.h"

Myers_diff::Myers_diff()
{
public:
    class V {
    public:
        V(int start, int end) : start_(start), end_(end), i_(new int[end - start + 1]) {}

        virtual ~V() {
            delete[](i_);
        }
        int& operator[](int index) {
            return i_[index - start_];
        }
    private:
        int* i_;
        int start_;
        int end_;
    };

    int MyersDiff(const char a[], int N, const char b[], int M) {
        int MAX = M + N;
        V V(-MAX, MAX);
        V[1] = 0;
        int x, y;
        for (int D = 0; D <= MAX; D++) {
            for (int k = -D; k <= D; k += 2) {
                if (k == -D || (k != D && V[k - 1] < V[k + 1])) {
                    x = V[k + 1];
                }
                else {
                    x = V[k - 1] + 1;
                }
                y = x - k;
                while (x < N && y < M && a[x] == b[y]) {
                    x += 1;
                    y += 1;
                }
                V[k] = x;
                if (x >= N && y >= M) {
                    return D;
                }
            }
        }
    }

    std::tuple<int, int, int, int, int> FindMiddleSnake(const char a[], int N, const char b[], int M) {
        int delta = N - M;
        int MAX = M + N;
        static V fv(-MAX, MAX);
        static V rv(-MAX, MAX);
        int x, y;
        fv[1] = 0;
        rv[delta + 1] = N + 1;
        for (int D = 0; D <= std::ceil((M + N) / 2.0); D++) {
            for (int k = -D; k <= D; k += 2) {
                if (k == -D || (k != D && fv[k - 1] < fv[k + 1])) {
                    x = fv[k + 1];
                }
                else {
                    x = fv[k - 1] + 1;
                }
                y = x - k;
                while (x < N && y < M && a[x] == b[y]) {
                    x += 1;
                    y += 1;
                }
                fv[k] = x;
                if (delta % 2 != 0 && k >= delta - (D - 1) && k <= delta + D - 1) {
                    if (fv[k] >= rv[k]) {
                        return std::make_tuple(rv[k], rv[k] - k, x, y, 2 * D - 1);
                    }
                }
            }

            for (int k = -D + delta; k <= D + delta; k += 2) {
                if (k == -D + delta || (k != D + delta && rv[k - 1] >= rv[k + 1])) {
                    x = rv[k + 1] - 1;
                }
                else {
                    x = rv[k - 1];
                }
                y = x - k;
                while (x > 0 && y > 0 && a[x - 1] == b[y - 1]) {
                    x -= 1;
                    y -= 1;
                }
                rv[k] = x;
                if (delta % 2 == 0 && k >= -D && k <= D) {
                    if (fv[k] >= rv[k]) {
                        return std::make_tuple(x, y, fv[k], fv[k] - k, 2 * D);
                    }
                }
            }
        }
        return {};
    }

    void SES(const char a[], int N, const char b[], int M) {
        static const char* startA = nullptr;
        if (startA == nullptr) {
            startA = a;
        }
        while (*a == *b && N > 0 && M > 0) {
            ++a;
            ++b;
            --N;
            --M;
        }
        while (*(a + N - 1) == *(b + M - 1) && N > 0 && M > 0) {
            --N;
            --M;
        }
        if (N > 0 && M > 0) {
            int x, y, u, v, D;
            std::tie(x, y, u, v, D) = FindMiddleSnake(a, N, b, M);
            SES(a, x, b, y);
            SES(a + u, N - u, b + v, M - v);
        }
        else if (N > 0) {
            std::cout << "-";
            for (int i = 0; i < N; i++) {
                std::cout << startA[(a + i) - startA];
            }
        }
        else if (M > 0) {
            std::cout << "+" << a - startA;
            for (int i = 0; i < M; i++) {
                std::cout << b[i];
            }
        }
        //std::cout << '\n';
    }

}
#include <iostream>
#include <tuple>
#include <cmath>

