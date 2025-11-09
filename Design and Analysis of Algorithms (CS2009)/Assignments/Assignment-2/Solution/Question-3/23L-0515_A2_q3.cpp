#include <complex>
#include <iostream>
#include <numbers>
#include <vector>
using namespace std;

void fft(vector<complex<double>> &a, bool invert)
{
    int n = a.size();
    if (n == 1)
        return;

    vector<complex<double>> even(n / 2), odd(n / 2);

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[i * 2];
        odd[i] = a[i * 2 + 1];
    }

    fft(even, invert);
    fft(odd, invert);

    double angle = 2 * numbers::pi / n;
    if (invert)
        angle *= -1;

    complex<double> w(1), wn = polar(1.0, angle);

    for (int i = 0; i < n / 2; i++)
    {
        complex<double> t = w * odd[i];
        a[i] = even[i] + t;
        a[i + n / 2] = even[i] - t;
        w *= wn;
    }

    if (invert)
        for (int i = 0; i < n; i++)
            a[i] /= 2.0;
}

vector<long long> convolution(const vector<int> &A, const vector<int> &B)
{
    int n = 1;

    while (n < A.size() + B.size())
        n <<= 1;

    vector<complex<double>> ffta(A.begin(), A.end());
    vector<complex<double>> fftb(B.begin(), B.end());

    ffta.resize(n);
    fftb.resize(n);

    fft(ffta, false);
    fft(fftb, false);

    vector<complex<double>> res(n);

    for (int i = 0; i < n; i++)
        res[i] = ffta[i] * fftb[i];

    fft(res, true);
    vector<long long> result(A.size() + B.size() - 1);

    for (int i = 0; i < result.size(); i++)
        result[i] = llround(res[i].real());

    return result;
}

int main()
{
    freopen("q3_input.txt", "r", stdin);
    freopen("q3_output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<int> A(n), B(m);
    for (int i = 0; i < n; i++)
        cin >> A[i];
    for (int i = 0; i < m; i++)
        cin >> B[i];

    vector<long long> result = convolution(A, B);

    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i];
        if (i + 1 != result.size())
            cout << " ";
    }
    cout << "\n";

    return 0;
}
