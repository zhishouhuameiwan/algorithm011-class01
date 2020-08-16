//给定一个整数，编写一个函数来判断它是否是 2 的幂次方。

#include <iostream>
using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 ?  (n & n - 1) == 0 : false;
    }
};

//编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为汉明重量）。
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count  = 0;
        while(n != 0)
        {
            n &= (n - 1);
            count++;
        }
        return count;
    }
};
 

//190  颠倒给定的 32 位无符号整数的二进制位。

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0, step = 31;
        while(n != 0)
        {
            res += ((n & 1) << (step--));
            n = (n >> 1);
        }
        return res;
    }
};