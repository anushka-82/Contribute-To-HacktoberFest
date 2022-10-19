#include <algorithm>
#include <cstdio>
#include <limits>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

struct Edge {
    int Target, U;
};

struct Graph {
    vector<Edge> Edges;
    vector<vector<int>> Out;
    int Source, Target;
    vector<int> H, Begin;

    int AddEdge(int s, int t, int u) {
        Edges.emplace_back(Edge{t, u});
        Edges.emplace_back(Edge{s, 0});
        Out[s].emplace_back(Edges.size() - 2);
        Out[t].emplace_back(Edges.size() - 1);
        return Edges.size() - 2;
    }

    int Augment(int no, int flow) {
        if (no == Target) return flow;
        int left = flow;
        for (int i = Begin[no]; i < Out[no].size(); ++i) {
            int ei = Out[no][i], target = Edges[ei].Target;
            if (Edges[ei].U == 0 || H[target] + 1 != H[no]) continue;
            int delta = Augment(target, min(left, Edges[ei].U));
            Edges[ei].U -= delta;
            Edges[ei ^ 1].U += delta;
            left -= delta;
            if (left == 0) return flow;
            Begin[no] = i + 1;
        }
        return flow - left;
    }

    bool Relabel() {
        for (int& i : H) i = Out.size();
        queue<int> nodes;
        nodes.emplace(Target);
        H[Target] = 0;
        while (!nodes.empty()) {
            int front = nodes.front();
            nodes.pop();
            for (int i : Out[front]) {
                if (Edges[i ^ 1].U == 0) continue;
                if (H[Edges[i].Target] != Out.size()) continue;
                H[Edges[i].Target] = H[front] + 1;
                nodes.emplace(Edges[i].Target);
            }
        }
        for (int& i : Begin) i = 0;
        return H[Source] < Out.size();
    }

    int MaxFlow() {
        H.resize(Out.size());
        Begin.resize(Out.size());
        int flow = 0;
        while (Relabel()) {
            flow += Augment(Source, numeric_limits<int>::max());
        }
        return flow;
    }
};

struct Person {
    int S, T;
    unordered_set<int> Like;
};

struct Event {
    int Time, Person;
    bool Leave;

    bool operator<(const Event& that) const { return Time < that.Time; }
};

struct Solution {
    int B, G, L, Answer;
    vector<Person> Boys, Girls;
    vector<Event> E;
    Graph Gr;
    vector<int> Output;

    void ReadPerson(Person& p) {
        int n, like;
        scanf("%d%d%d", &p.S, &p.T, &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &like);
            p.Like.emplace(like);
        }
    }

    void AddEvent(int no, const Person& p) {
        E.emplace_back(Event{p.S, no, false});
        E.emplace_back(Event{p.T, no, true});
    }

    void Solve() {
        scanf("%d%d%d", &B, &G, &L);
        Boys.resize(B);
        for (int i = 0; i < B; ++i) ReadPerson(Boys[i]);
        Girls.resize(G);
        for (int i = 0; i < G; ++i) ReadPerson(Girls[i]);
        for (int i = 0; i < B; ++i) AddEvent(i, Boys[i]);
        for (int i = 0; i < G; ++i) AddEvent(B + i, Girls[i]);
        sort(E.begin(), E.end());
        Gr.Out.resize(B + G + 2);
        Gr.Source = B + G;
        Gr.Target = B + G + 1;
        for (int i = 0; i < B; ++i) {
            for (int j : Boys[i].Like) {
                if (Girls[j].Like.count(i)) Gr.AddEdge(i, B + j, 1);
            }
        }
        Output.resize(min(G, B) + 1);
        Answer = 0;
        int lastTime = 0;
        for (const Event& i : E) {
            Output[Answer] += i.Time - lastTime;
            lastTime = i.Time;
            bool isGirl = B <= i.Person;
            if (i.Leave == isGirl) {
                Gr.AddEdge(Gr.Source, i.Person, 1);
            } else {
                Gr.AddEdge(i.Person, Gr.Target, 1);
            }
            if (i.Leave) --Answer;
            Answer += Gr.MaxFlow();
        }
        Output[Answer] += L - lastTime;
        bool head = true;
        for (int i : Output) {
            if (!head) printf(" ");
            head = false;
            printf("%d", i);
        }
        printf("\n");
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}
