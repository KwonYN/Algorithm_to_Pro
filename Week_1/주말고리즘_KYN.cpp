// BOJ_1504_특정한 최단 경로
/*
	방향성 없는 그래프!
	1 -> N 최단 거리로 이동!
	  1) 임의로 주어진 두 정점은 반드시 통과해야
	  2) 한 번 이동했던 정점은 물론, 한 번 이동했던 간선도 다시 이동 가능
	  3) 단, 반드시 최단 경로로 이동해야 함
*/
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX	(800)
#define INF	(0x7fffffff)

typedef pair<int, int> pii;
int N, E;
vector<pii> edges[MAX+10];
int dijk[MAX+10];
bool chk;

int dijkstra(int s, int e) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for(int i = 1; i <= N; i++) dijk[i] = INF;
	pq.push({0, s});	dijk[s] = 0;
	while(!pq.empty()) {
		pii cur = pq.top();		pq.pop();
		if(cur.second == e) break;
		for(pii next : edges[cur.second]) {
			if(dijk[next.second] > dijk[cur.second] + next.first) {
				dijk[next.second] = dijk[cur.second] + next.first;
				pq.push({dijk[next.second], next.second});
			}
		}
	}
	return dijk[e];
}

int main() {
	int a, b, c, s, e;
	scanf("%d %d", &N, &E);
	for(int i = 1; i <= E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({c, b});
		edges[b].push_back({c, a}); // a <--(c)--> b
	}
	scanf("%d %d", &s, &e);

	int _1s = dijkstra(1, s);
	int _1e = dijkstra(1, e);
	int se = dijkstra(s, e);
	int sn = dijkstra(s, N);
	int en = dijkstra(e, N);
	int result1 = INF, result2 = INF;
	chk = false;
	if(_1s != INF && se != INF && en != INF) { chk = true; result1 = _1s + se + en; }
	if(_1e != INF && se != INF && sn != INF) { chk = true; result2 = _1e + se + sn; }
	if(chk) printf("%d\n", ( (result1 > result2) ? result2 : result1 ));
	else printf("%d\n", -1);
	return 0;
}

/********************************************************************************************/

// BOJ_1654_랜선 자르기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define KMAX    (10000)

typedef long long ll;
int K, N;
ll max_len, lan[KMAX + 10], result;

bool get_cnt(ll target_len) {
    ll cnt = 0;
    for (int i = 0; i < K; i++) {
        cnt += (lan[i] / target_len);
    }
    if (cnt >= N) return true;
    return false;
}

int main()
{
    freopen("in.txt", "r", stdin);
    max_len = result = -1;
    scanf("%d %d", &K, &N);
    for (int i = 0; i < K; i++) {
        scanf("%lld", &lan[i]);
        max_len = max(max_len, lan[i]);
    }
    sort(lan, lan + K);

    ll s = 1, e = max_len, m;
    while (s <= e) {
        /*if ((s & 1) && (e & 1)) m = s / 2 + e / 2 + 1;
        else m = s / 2 + e / 2;*/
        // => 계속 if문을 통해 검증을 하다 보니 시간 초과...;;

        m = (s + e) / 2; // 여기에서 int 범위를 넘을 수도 있음!!!
        if (get_cnt(m)) {
            s = m + 1;
            if (result < m) result = m;
        }
        else e = m - 1;
    }
    printf("%lld\n", result);
    return 0;
}
#endif

/********************************************************************************************/

// BOJ_10775_공항 : Union-Find
// 뒤에서부터 하는 것을 생각하는 것이 중요!!
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define GMAX    (100000)

int G, P, max_cnt, gi[GMAX+10];
int gate[GMAX + 10]; // parent

int arrange_plane(int no) {
    if (no == gate[no]) return no;
    return gate[no] = arrange_plane(gate[no]);
}

int main()
{
    freopen("in.txt", "r", stdin);
    // initialization
    max_cnt = 0;

    // input
    scanf("%d", &G);
    for (int i = 0; i <= G; i++) gate[i] = i;
    scanf("%d", &P);
    for (int i = 1; i <= P; i++) scanf("%d", &gi[i]);

    // arrange plane
    int gate_num;
    for (int i = 1; i <= P; i++) {
        gate_num = arrange_plane(gi[i]);
        if (gate_num == 0) break;
        gate[gate_num]--;
        max_cnt++;
    }

    // print
    printf("%d\n", max_cnt);
    return 0;
}
#endif
