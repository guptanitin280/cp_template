//all solution of ax+by=c in [minx,maxx], [miny,maxy]
int gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool solve_any(int a, int b, int c, int &x, int &y, int &g) {
    if (a == 0 && b == 0) {
        g = x = y = 0;
        return true;
    }
    g = gcd(abs(a), abs(b), x, y);
    if (c % g != 0) {
        return false;
    }
    x *= (c / g);
    y *= (c / g);
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

void shift(int &x, int &y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int solve_all(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!solve_any(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;
    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;
    shift(x, y, a, b, (minx - x) / b);
    if (x < minx) {
        shift(x, y, a, b, sign_b);
    }
    if (x > maxx)
        return 0;
    int lx1 = x;
    shift(x, y, a, b, (maxx - x) / b);
    if (x > maxx) {
        shift(x, y, a, b, -sign_b);
    }
    int rx1 = x;
    shift(x, y, a, b, (y - miny) / a);
    if (y < miny) {
        shift(x, y, a, b, -sign_a);
    }
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift(x, y, a, b, (y - maxy) / a);
    if (y > maxy) {
        shift(x, y, a, b, sign_a);
    }
    int rx2 = x;
    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);
    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    int minx, miny, maxx, maxy;
    cin >> minx >> maxx >> miny >> maxy;
    if (maxx < minx || maxy < miny) {
        cout << 0 << endl;
        exit(0);
    }
    if (a == 0 && b == 0) {
        if (c == 0) {
            cout << (maxy - miny + 1) * (maxx - minx + 1) << endl;
        } else {
            cout << 0 << endl;
        }
    } else if (a == 0 || b == 0) {
        if (a == 0) {
            if (c % b == 0 && (c / b) >= miny && (c / b) <= maxy) {
                cout << maxx - minx + 1 << endl;
            } else {
                cout << 0 << endl;
            }
        } else {
            if (c % a == 0 && (c / a) >= minx && (c / a) <= maxx) {
                cout << maxy - miny + 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
    } else
        cout << solve_all(a, b, c, minx, maxx, miny, maxy) << endl;
}
