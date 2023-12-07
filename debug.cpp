#include <bits/stdc++.h>
using namespace std;
// Tên chương trình
const string NAME = "Ten file";
// Số test kiểm tra
const int NTEST = 100;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {return l + rng() % (r - l + 1);}

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp((NAME + ".inp").c_str());
        // Code phần sinh test ở đây
        inp.close();

        ifstream out1(NAME + ".out"), out2(NAME + ".ans");
		// Viết checker. Output của code chuẩn đọc ở out1, của code trâu (code chắc chắn đúng) đọc ở out2.
		out1.close(); out2.close();

        system((NAME + ".exe").c_str());
        system((NAME + "_debug.exe").c_str());
        if (system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}
