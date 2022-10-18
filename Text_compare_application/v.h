#ifndef V_H
#define V_H

#include <iostream>
#include <tuple>
#include <cmath>


class V
{

private:
    int* i_;
    int start_;
    int end_;

public:
    V(int start, int end);

    virtual ~V();

    int& operator[](int index);


    static int MyersDiff(const char a[], int N, const char b[], int M);

    static std::tuple<int, int, int, int, int> FindMiddleSnake(const char a[], int N, const char b[], int M);

    static void SES(const char a[], int N, const char b[], int M, std::string *content);

};

#endif // V_H
