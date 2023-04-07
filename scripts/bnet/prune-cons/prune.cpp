#include <bits/stdc++.h>
using namespace std;

char nc(){ static char buf[1000000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1000000,stdin),p1 == p2) ? EOF : *p1++; }
#define nc getchar
void read(string& s){ static char tp[1000005]; char ch = nc(); int num = 0; while(ch != ' ' && ch != '\n' && ch != '\r' && ch != EOF){tp[num++] = ch;ch = nc();} tp[num] = '\0';    s = (string)tp; }


int main(int argc, char* argv[]){
	unordered_set<string> queries;
	freopen(argv[1], "r", stdin);
	while(1){
		string s;
		read(s);
		if(s.empty()) break;
		queries.insert(s);
	}
	freopen(argv[2], "r", stdin);
	unordered_map<string, int> tuple2Id;
	vector<string> id2Tuple;
	vector<vector<int> > edge;
	vector<int> isOut;
	vector<string> clauses;
	vector<vector<int> > clause2Tuples;
	vector<vector<int> > in2Clauses;
	vector<int> w;
	string clause;
	while(1){
		string s;
		read(s);
		if(s.empty() || s.back() == ':'){
			if(!w.empty()){
				for(int i = 0;i + 1 < w.size();i++){
					in2Clauses[w[i]].emplace_back(clauses.size());
				}
				clauses.emplace_back(clause);
				clause2Tuples.emplace_back(w);
				isOut[w.back()] = true;
				w.clear();
			}
			if(s.empty()) break;
			clause = s;
			continue;
		}
		if(s == "NOT"){
			clause += " " + s;
			read(s);
		}
		clause += " " + s;
		if(s.back() == ',') s.pop_back();
		if(!tuple2Id.count(s)){
			tuple2Id[s] = id2Tuple.size();
			id2Tuple.emplace_back(s);
			edge.emplace_back(vector<int>());
			in2Clauses.emplace_back(vector<int>());
			isOut.emplace_back(false);
		}
		w.emplace_back(tuple2Id[s]); 
	}
	vector<int> dis(id2Tuple.size(), 1e9);
	queue<int> q;
	for(int i = 0;i < id2Tuple.size();i++){
		if(!isOut[i]){
			dis[i] = 0, q.push(i);
		}
	}
	vector<int> cnt(clauses.size()), tag(clauses.size());
	while(!q.empty()){
		int x = q.front();q.pop();
		for(auto i : in2Clauses[x]){
			cnt[i]++;
			if(cnt[i] + 1 == clause2Tuples[i].size()){
				int to = clause2Tuples[i].back();
				if(dis[to] > dis[x] + 1){
					dis[to] = dis[x] + 1;
					q.push(to);
				}
				if(dis[to] == dis[x] + 1){
					tag[i] = true;
					for(int j = 0;j + 1 < clause2Tuples[i].size();j++){
						edge[to].emplace_back(clause2Tuples[i][j]);
					}
				}
			}
		}
	}
	vector<int> vis(id2Tuple.size());
	for(auto s : queries){
		int id = tuple2Id[s];
		vis[id] = true, q.push(id);
	}
	while(!q.empty()){
		int x = q.front();q.pop();
		for(auto to : edge[x]){
			if(!vis[to]){
				q.push(to), vis[to] = true;
			}
		}
	}
	for(int i = 0;i < clauses.size();i++){
		if(tag[i] && vis[clause2Tuples[i].back()]){
			printf("%s\n", clauses[i].c_str());
		}
	}
}