#include <bits/stdc++.h>
using namespace std;
#define ll long long 

map<string, ll>lebel;
map<ll, string>revlebel;
vector<pair<ll, ll>>adj[1000005];

void addPlace(string s) {
    if (lebel.find(s) == lebel.end()) {
        lebel[s] = lebel.size();
        revlebel[lebel.size()] = s;
    } return;
}

void addEdge(string s1, string s2, ll dist) {
    addPlace(s1); addPlace(s2);
    adj[lebel[s2]].push_back({ lebel[s1], dist });
    adj[lebel[s1]].push_back({ lebel[s2], dist });
}

int main() {
    cout << "-------------- Welcome to CityTrek ----------\n";

    addPlace("New Delhi");
    addPlace("Rajiv Chowk");
    addPlace("Dwarka");
    addPlace("Noida City Centre");
    addPlace("Vaishali");
    addPlace("Kashmere Gate");
    addPlace("Central Secretariat");
    addPlace("Lajpat Nagar");
    addPlace("Huda City Centre");
    addPlace("Chhatarpur");
    addPlace("Badarpur");
    addPlace("Saket");
    addPlace("Gurugram");
    addPlace("Nehru Place");
    addPlace("Botanical Garden");

    addEdge("New Delhi", "Rajiv Chowk", 2);
    addEdge("Rajiv Chowk", "Dwarka", 5);
    addEdge("Rajiv Chowk", "Noida City Centre", 5);
    addEdge("Noida City Centre", "Vaishali", 5);
    addEdge("Rajiv Chowk", "Kashmere Gate", 10);
    addEdge("Kashmere Gate", "Central Secretariat", 15);
    addEdge("Central Secretariat", "Lajpat Nagar", 10);
    addEdge("Lajpat Nagar", "Huda City Centre", 20);
    addEdge("Huda City Centre", "Chhatarpur", 15);
    addEdge("Chhatarpur", "Badarpur", 10);
    addEdge("Lajpat Nagar", "Saket", 5);
    addEdge("Saket", "Gurugram", 10);
    addEdge("Saket", "Nehru Place", 5);
    addEdge("Nehru Place", "Botanical Garden", 5);

    cout << "-----------selct below options to continue----------\n";
    cout << "select 1 for View all places\n";
    cout << "select 2 View all routes\n";
    cout << "select 3 for Exit\n";
    cout << "--------------------------------------------------------\n";
    ll x;
    while (cin >> x) {
        if (x == 3) {
            cout << "----------------- Thank you -----------------\n"; break;
        }
        if (x == 1) {
            cout << "---------------- place list ----------------\n";
            ll cnt = 1;
            for (auto x : lebel) {
                cout << cnt << ". " << x.first << endl;
                cnt++;
            }
            cout << "--------------------------------------------\n";
        }
        else if (x == 2) {
            cout << "----------------- route list ----------------\n\n";
            for (auto x : lebel) {
                cout << "-----------you can go from " << x.first << " to below places--------\n";
                for (auto y : adj[x.second]) {
                    cout << "city = " << revlebel[y.first] << " dist = " << y.second << endl;
                }
                cout << "--------------------------------------------\n";
            }
            cout << endl;
            cout << "-----------selct new options to continue----------\n";
            cout << "select 1 for View all places\n";
            cout << "select 2 View all routes\n";
            cout << "select 3 for Exit\n";
            cout << "--------------------------------------------------------\n";

        }
    } return 0;
}
