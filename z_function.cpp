// z_function
vector<int> z_function(string s) {
    int n = s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        // khoi tao z[i] theo thuat toan toi uu
        if (i <= r)  
            z[i] = min(r - i + 1, z[i - l]);
        // tinh z[i]
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        // cap nhat doan [l,r]
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        } 
    }
    return z;
}
