namespace NTT {
    const int M = 998244353;
    int mul(int a, int b) { return (long long)a * b % M; }
    int sub(int a, int b) { return b > a ? a - b + M : a - b; }
    int add(int a, int b) { return a + b >= M ? a + b - M : a + b; }
    long long binpow(long long a, long long b){
        long long ret = 1;
        while(b){
            if(b&1) ret = mul(ret,a);
            a = mul(a,a);
            b >>= 1;
        }
        return ret;
    }
    void ntt(vector<int>& a, bool inv){
        const int root = binpow(3, (M-1)>>__lg(a.size()));
        const int root_1 = binpow(root, M-2);
        int n = a.size();
        for(int i=1,j=0;i<n;i++){
            int b = n >> 1;
            for(;j&b;b>>=1){
                j ^= b;
            }
            j ^= b;
            if(i < j){
                swap(a[i], a[j]);
            }
        }
        for(int l=2;l<=n;l<<=1){
            int wl = inv ? root_1 : root;
            for (int i = l; i < n; i <<= 1){
                wl = mul(wl, wl);
            }
            for(int i=0;i<n;i+=l){
                int w = 1;
                for(int j=0;j<l/2;j++){
                    int v = a[i+j], u = mul(a[i+j+l/2], w);
                    a[i+j] = add(v, u);
                    a[i+j+l/2] = sub(v, u);
                    w = mul(w, wl);
                }
            }
        }
        if(inv){
            int in = binpow(n, M-2);
            for(auto& v : a){
                v = 1LL * v * in % M;
            }
        }
    }
    vector<int> multiply(vector<int> &a, vector<int> &b) {
        int sz = 1;
        while(sz < (int)a.size() + (int)b.size()) sz <<= 1;
        a.resize(sz); b.resize(sz);
        ntt(a, 0); ntt(b, 0);
        vector<int> res(sz);
        for(int i=0;i<sz;i++){
            res[i] = mul(a[i], b[i]);
        }
        ntt(res, 1);
        return res;
    }
}