int BinaryGCD(int a, int b) {
    // given two integers a and b, a >= b >= 0, return gcd of a and b
    if (b == 0)
        return a;

    // 2|a and 2|b
    else if (a % 2 == 0 && b % 2 == 0)
        return 2 * BinaryGCD(a / 2, b / 2);
    // a is even, b is odd
    else if (a % 2 == 0) {
        if (a / 2 >= b)
            return BinaryGCD(a / 2, b);
        else return BinaryGCD(b, a / 2);
    }
    // b is even, a is odd
    else if (b % 2 == 0)
        return BinaryGCD(a, b / 2);
    // both a and b are odd
    else {
        if ((a - b) / 2 >= b)
            return BinaryGCD((a - b) / 2, b);
        else return BinaryGCD(b, (a - b) / 2);
    }
}