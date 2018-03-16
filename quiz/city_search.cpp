#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

using namespace std;

unordered_map<string, int> getCityMap(const string input, vector<string> &cityArray)
{
    ifstream fin(input);
    string str, start, end;
    int i, j;
    set<string> citySet;
    while (getline(fin, str))
    {
        i = str.find_first_of(',');
        j = str.find_last_of(',');
        start = str.substr(0, i) ;
        end = str.substr(i + 1, j - i - 1);
        if (!citySet.count(start)) citySet.insert(start);
        if (!citySet.count(end)) citySet.insert(end);
    }
    unordered_map<string, int> cityMap;
    i = 0;
    for (auto it = citySet.begin(); it != citySet.end(); it++, i++)
    {
        cityArray.push_back(*it);
        cityMap[*it] = i;
    }
    return cityMap;
}

vector<int> dfs(const vector<vector<int> > &matrix, int start, int end, int nCity)
{
    vector<int> list;
    unordered_set<int> visited;
    stack<int> frontier;
    frontier.push(start);
    int cur, i;
    while (!frontier.empty())
    {
        cur = frontier.top();
        frontier.pop();
        const vector<int>& row = matrix[cur];
        for (i = 0; i < nCity; i++)
        {
            if (row[i] == 0 || visited.count(i)) continue;
            if (i == end)
            {
                list.push_back(i);
                return list;
            }
            frontier.push(i);
        }
        list.push_back(cur);
        visited.insert(cur);
    }
    return vector<int>();
}

vector<int> bfs(const vector<vector<int> > &matrix, int start, int end, int nCity)
{
    vector<int> list;
    unordered_set<int> visited;
    queue<int> frontier;
    frontier.push(start);
    int cur, i;
    while (!frontier.empty())
    {
        cur = frontier.front();
        frontier.pop();
        list.push_back(cur);
        visited.insert(cur);
        const vector<int>& row = matrix[cur];
        for (i = 0; i < nCity; i++)
        {
            if (row[i] == 0 || visited.count(i)) continue;
            if (i == end)
            {
                while(!frontier.empty()){
                    list.push_back(frontier.front());
                    frontier.pop();
                }
                list.push_back(i);
                return list;
            }
            frontier.push(i);
        }
    }
    return vector<int>();
}

int main(int argc, char *argv[])
{
    vector<string> cityArray;
    auto cityMap = getCityMap("test.in", cityArray);
    int nCity = cityMap.size();
    ifstream fin("test.in");
    vector<vector<int> > matrix(nCity, vector<int>(nCity, 0));
    int i, j, dis;
    string str, start, end;
    while (getline(fin, str))
    {
        i = str.find_first_of(',');
        j = str.find_last_of(',');
        start = str.substr(0, i) ;
        end = str.substr(i + 1, j - i - 1);
        dis = stoi(str.substr(j + 1));
        matrix[cityMap[start]][cityMap[end]] = dis;
        matrix[cityMap[end]][cityMap[start]] = dis;
    }
    start = argv[1];
    end = argv[2];
    cout << "DFS" << endl;
    for (auto index : dfs(matrix, cityMap[start], cityMap[end], nCity))
        cout << cityArray[index] << ",";
    cout << endl;
    cout << "BFS" << endl;
    for (auto index : bfs(matrix, cityMap[start], cityMap[end], nCity))
        cout << cityArray[index] << ",";
    cout << endl;
    return 0;
}
