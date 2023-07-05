#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct LONG_NUMBER {
    bool isNegative = false;
    unsigned short int pointPlace;
    vector<unsigned short int> digArr; \
};
struct LONG_BINARY_NUMBER {
    bool isNegative = false;
    unsigned short int pointPlace;
    vector<bool> binArr;
};

bool longMult(LONG_NUMBER& a) {
    bool value = (a.digArr[a.pointPlace] * 2) / 10;
    a.digArr[a.pointPlace] = (a.digArr[a.pointPlace] * 2) % 10;
    for (int i = a.pointPlace + 1; i < a.digArr.size(); i++) {
        a.digArr[i - 1] += (a.digArr[i] * 2) / 10;
        a.digArr[i] = (a.digArr[i] * 2) % 10;
    }
    return value;
}
LONG_NUMBER longDiv(const LONG_NUMBER& a, int n, int start) {
    LONG_NUMBER res;
    if (start == 0) {
        int num = 0;
        for (int i = 0; i < a.pointPlace; i++) {
            num += a.digArr[i];
            res.digArr.push_back(num / n);
            num = num % n;
            num *= 10;
        }
        if ((res.digArr[0] == 0) && (res.digArr.size() != 0)) {
            res.digArr.erase(res.digArr.begin());
        }
        if (res.digArr.size() == 0) res.digArr.push_back(0);
        res.pointPlace = res.digArr.size();
        for (int i = a.pointPlace; i < a.digArr.size(); i++) {
            res.digArr.push_back(a.digArr[i]);
        }
    }
    if (res.pointPlace == 0) {
        res.digArr.push_back(res.digArr[res.digArr.size() - 1]);
        for (int i = res.digArr.size() - 2; i > 0; i--) {
            res.digArr[i] = res.digArr[i + 1];
        }
        res.digArr[0] = 0;
    }
    return res;
}
