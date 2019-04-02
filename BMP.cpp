#include<bits/stdc++.h>
using namespace std;
#define max_resources 200

int rd;
default_random_engine gen;
uniform_real_distribution<double> dis(0,1);

class Request
{
    int id;
    bool matched = 0;
    int resourceId;
    double weight;

public:
    friend class Resource;
    void giveId(int Id)
    {
        id = Id;
        return ;
    }
    void printId()
    {
        cout << id << "\n";
        return ;
    }
    void assignweight()
    {
        weight = dis(gen);
        return ;
    }
    double getweight()
    {
        return weight;
    }
};

class Resource
{
    int id;
    bool matched = 0;
    int requestId;

public:
    void giveId(int Id)
    {
        id = Id;
        return ;
    }
    bool operator->* (Request &b)
    {
        if(b.matched || matched)
            return false;
        matched = b.matched = 1;
        return true;
    }
    bool getmatched()
    {
        return matched;
    }
};

vector<Resource> resource;
vector<Request> request;
vector<int> edge[max_resources];
priority_queue<pair<double, int> > ReRo[max_resources];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > ans;
void solve();

int main(int argc, char** argv)
{
    rd = atoi(argv[1]);
    gen.seed(rd);
    freopen("request_test.txt", "r", stdin);
    int ntimeslots;
    cin >> ntimeslots;
    while(ntimeslots--)
        solve();
    pair<int, int> tmp;
    cout << ans.size() << "\n";
    while(!ans.empty())
    {
        tmp = ans.top();
        ans.pop();
        cout << tmp.first << " " << tmp.second << "\n";
    }
    return 0;
}

void solve()
{
    int timeslot, nrequests, nresources, nedges;
    cin >> timeslot >> nrequests >> nresources;
    for(int i = 0; i < nrequests; i++)
    {
        Request tmp;
        int Id;
        cin >> Id;
        tmp.giveId(Id);
        tmp.assignweight();
        request.push_back(tmp);
    }
    for(int i = 0; i < nresources; i++)
    {
        Resource tmp;
        int Id;
        cin >> Id;
        tmp.giveId(Id);
        resource.push_back(tmp);
    }
    cin >> nedges;
    for(int i = 0; i < nedges; i++)
    {
        int num, reId, roId;
        cin >> num >> reId >> roId;
        edge[roId].push_back(reId);
        ReRo[roId].push(make_pair(request[reId].getweight(), reId));
    }
    for(int i = 0; i < resource.size(); i++)
    {
        if(resource[i].getmatched())
            continue;
        while(!ReRo[i].empty())
        {
            pair<double, int> tmp = ReRo[i].top();
            ReRo[i].pop();
            if(resource[i]->*request[tmp.second])
            {
                ans.push(make_pair(tmp.second, i));
                break;
            }
        }
    }
    return ;
}
