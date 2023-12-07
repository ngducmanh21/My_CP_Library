#include <cstdio>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

#define TR(v, it) for(typeof((v).begin()) it = (v).begin(), _e = (v).end(); it != _e; ++it )
#define INF 1000000000

vvii g;
int t[105][105], d[105][105];
int n, m, k;

void dijkstra( vvii & g, int s, int d[], int t[] ) {
    priority_queue<ii> q; q.push(ii(0, s));
    for( int i = 0; i < n; ++i ) d[i] = INF;
    d[s] = 0; t[s] = s;
    while( !q.empty() ) {
        int du = q.top().first, u = q.top().second; q.pop();
        if (du > d[u]) continue;
        TR(g[u], it) {
            int v = it->first, l = it->second;
            if (d[v] > du + l) {
                d[v] = du + l; t[v] = u;
                q.push(ii(d[v], v));
            }
        }
    }
}

int main() {
    scanf( "%d%d%d", &n, &m, &k );
    g = vvii(n, vii());
    while(m--) {
        int u, v, l; scanf( "%d%d%d", &u, &v, &l );
        g[--u].push_back(ii(--v, l));
        g[v].push_back(ii(u, l));
    }
    for( int i = 0; i < n; ++i ) dijkstra(g, i, d[i], t[i]);
    while(k--) {
        int q, u, v; scanf( "%d%d%d", &q, &u, &v );
        --u; --v;
        if(q) {
            stack<int> st; int x = v; st.push(x);
            do {
                x = t[u][x];
                st.push(x);
            } while( x != u );
            printf( "%d", st.size() );
            while(!st.empty()) {
                printf( " %d", st.top()+1 );
                st.pop();
            }
            printf("\n");
        } else printf("%d\n", d[u][v]);
    }
    return 0;
}