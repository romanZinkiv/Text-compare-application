#include "v.h"

/*! class to work with Myers diff algorithm
 * \brief V::V
 * \param start x
 * \param end y
 *
 * This class is a realization of the basic greedy diff algorithm, as described by Eugene W. Myers
 * File A and File B
 * The diff algorithm takes two files as input. The first, usually older, one is file A, and the second one is file B. The algorithm generates instructions to turn file A into file B.
 * Shortest Edit Script ( SES )
 * The algorithm finds the Shortest Edit Script that converts file A into file B. The SES contains only two types of commands: deletions from file A and insertions in file B.
 * Longest Common Subsequence ( LCS )
 * Finding the SES is equivalent to finding the Longest Common Subsequence of the two files.
 * The LCS is the longest list of characters that can be generated from both files by removing some characters.
 * The LCS is distinct from the Longest Common Substring, which has to be contiguous.
 * For any two files, there can be multiple LCSs. For example, given the sequences "ABC" and "ACB", there are two LCSs of length 2: "AB" and "AC".
 * An LCS corresponds directly to an SES, so it is also true that there can be multiple SESs of the same length for any two files.
 * The algorithm just returns the first LCS / SES that it finds, which therefore may not be unique.
 *
 * This 'greedy' algorithm has complexity O( (N+M) D ) in both time and space.
 */
V::V(int start, int end) : start_(start), end_(end) {
    i_ = new int[end - start + 1];
}

V::~V() {
    delete[](i_);
}
/*!
 * \brief V::operator [] overload
 * \param index element index
 * \return returns the value corresponding to the element index
 */
int& V::operator[](int index) {
    return i_[index - start_];
}

/*!
 * \brief finds the first snake that reaches the end of both sequences
 * \param a first file
 * \param N size of first file
 * \param b second file
 * \param M size of second file
 * \return size of snake
 *
 * Snake to be defined as a single deletion or insertion followed by zero or more diagonals The solution is the shortest path from the top-left corner to the bottom-right corner.
 * You can always move one character horizontally or vertically. A horizontal ( right ) move represents a deletion from file A, and a vertical ( down ) move
 * represents an insertion in file B. If there is a matched character, then you can also move diagonally, ending at the match. The solution(s) are the trace(s) that
 * include the most diagonals. The LCS is the diagonals in the trace, and the SES is the horizontal and vertical moves in it.
 */
int V::MyersDiff(const char a[], int N, const char b[], int M) {
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
    return 0;
}

/*!
 * \brief V::FindMiddleSnake
 * \param a first file
 * \param N size of first file
 * \param b second file
 * \param M size of second file
 * \return tuple for further operation of the algorithm
 *
 * The data in V only stores the latest end point for each k line. To find all the snakes that lead to the solution
 * requires taking a snapshot of V after each iteration of d and then working backwards from dsolution to 0.
 */
std::tuple<int, int, int, int, int> V::FindMiddleSnake(const char a[], int N, const char b[], int M) {
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

/*!
 * \brief Shortest Edit Script
 * \param a first file
 * \param N size of first file
 * \param b second file
 * \param M size of second file
 * \param content string that stores additions and deletions
 *
 * The algorithm finds the Shortest Edit Script that converts file A into file B. The SES contains only two types of commands: deletions from file A and insertions in file B.
 */
void V::SES(const char a[], int N, const char b[], int M, std::string* content) {
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
        std::tie(x, y, u, v, D) = V::FindMiddleSnake(a, N, b, M);
        SES(a, x, b, y, content);
        SES(a + u, N - u, b + v, M - v, content);
    }
    else if (N > 0) {
        *content += "-";
        for (int i = 0; i < N; i++) {
            *content += startA[(a + i) - startA];
        }
    }
    else if (M > 0) {
        *content += "+";
        *content += startA[a - startA];
        for (int i = 0; i < M; i++) {
            *content += b[i];
        }
    }
    //*content += '\n';
}

