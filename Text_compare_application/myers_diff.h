#ifndef MYERS_DIFF_H
#define MYERS_DIFF_H


class Myers_diff
{
public:
    Myers_diff();
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

    static int MyersDiff(const char a[], int N, const char b[], int M);
};

#endif // MYERS_DIFF_H
