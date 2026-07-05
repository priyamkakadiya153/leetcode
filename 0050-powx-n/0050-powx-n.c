double myPow(double x, long n) {
    if (n == 0) return 1.0;

    if (n < 0) {
        x = 1 / x;
        n = -n;
    }

    double rec = myPow(x, n / 2);

    if (n % 2 == 0)
        return rec * rec;
    else
        return rec * rec * x;
}
