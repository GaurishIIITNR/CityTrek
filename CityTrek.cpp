#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map 

umap<string, int> cityValue;
umap<int, string> valueCity;



class CityGraph {
    public:
    umap<int, vector<vector<int>>> adj;
    umap<long long, long long> dist, path;
    string source, destination;

    void convert(string& a) {
        a[0] = toupper(a[0]);
        for (int i = 1; i < a.size(); i++) {
            a[i] = tolower(a[i]);
        } return;
    }

    void city_value_mapper(string& a) {
        if (cityValue.find(a) == cityValue.end()) {
            int n = cityValue.size();
            cityValue[a] = n;
            valueCity[n] = a;
        }  return;
    }

    void addEdge(string a, string b, int distance, int cost, int time) {
        convert(a); convert(b);
        city_value_mapper(a);
        city_value_mapper(b);
        int u = cityValue[a], v = cityValue[b];
        adj[u].push_back({ v, distance, cost, time });
        adj[v].push_back({ u, distance, cost, time });
        return;
    }
    void addCity(string a) {
        convert(a);
        city_value_mapper(a);
        return;
    }

    void viewCity() {
        int cnt = 1;
        for (auto [name, _] : cityValue) {
            cout << cnt << ". " << name << "\n"; cnt++;
        }  return;
    }

    void viewRouteMap() {
        for (auto [name, value] : cityValue) {
            for (auto nbrDetail : adj[value]) {
                cout << name << " ==> ";
                cout << "{ city = " << valueCity[nbrDetail[0]] << ", dist = " << nbrDetail[1] << ", cost = " << nbrDetail[2] << ", time = " << nbrDetail[3] << " }" << endl;
            }
        } return;
    }

    void printRoute() {
        if (source == destination) {
            cout << "===> Route : " << source << " ==> " << source << endl;
            return;
        }
        int u = cityValue[source], v = cityValue[destination];
        cout << "===> Route : ";
        vector<string> route;
        while (v != u) {
            route.push_back(valueCity[v]);
            v = path[v];
        }
        reverse(route.begin(), route.end());
        cout << valueCity[v];
        for (auto city : route) cout << " ==> " << city;
        cout << endl;  return;
    }

    int shortest(int idx) {
        if (source == destination) return 0;
        dist.clear(); path.clear();
        priority_queue<int> q; q.push(cityValue[source]);
        int dest = cityValue[destination];
        dist[cityValue[source]] = 0;

        bool flag = false;
        while (!q.empty()) {
            int u = q.top(); q.pop();
            for (auto nbrDetail : adj[u]) {
                int v = nbrDetail[0], value = nbrDetail[idx];
                if (dist.find(v) == dist.end() || dist[v] > dist[u] + value) {
                    // cout << "dist[" << valueCity[v] << "] = " << "dist[" << valueCity[u] << "] " << " + " << value << endl;
                    dist[v] = dist[u] + value;
                    path[v] = u;  q.push(v);
                }
            }
        }
        if (dist.find(dest) != dist.end()) return dist[dest];
        return -1;
    }
}; CityGraph g;

class MapRoute {
    public:
    string choice;

    void menu() {
        cout << "1. View complete route map !!" << endl;
        cout << "2. View route map from a city !!" << endl;
        cout << "3. Go back to main menu !!" << endl;
        cout << "Enter your choice from above options: ";
        cin >> choice;
        return;
    }

    void options() {
        menu();
        if (choice.size() > 1) invalid();
        else if (choice[0] == '3') return;
        else if (choice[0] == '1') {
            cout << "--------------------Complete route map---------------------" << endl;
            g.viewRouteMap();
            cout << "-----------------------------------------------------------" << endl;
        }
        else if (choice[0] == '2') {
            viewRouteFromSoure();
            cout << "-----------------------------------------------------------" << endl;
        }
        else invalid();
        options(); return;
    }
    void invalid() {
        cout << "------Invalid choice! choice should b/w [1, 3]-----------------" << endl;
        return;
    }
    void viewRouteFromSoure() {
        cout << "Enter source city : "; string name; cin >> name;
        g.convert(name); g.addCity(name);
        cout << "-------------------Route map from " << name << "--------------------" << endl;
        int value = cityValue[name];
        for (auto nbrDetail : g.adj[value]) {
            cout << name << " ==> ";
            cout << "{ city = " << valueCity[nbrDetail[0]] << ", dist = " << nbrDetail[1] << ", cost = " << nbrDetail[2] << ", time = " << nbrDetail[3] << " }" << endl;
        } return;
    }
}; MapRoute mpr;

class CityTrek {
    public:
    string choice;

    void menu() {
        cout << "1. View all cities !!" << endl;
        cout << "2. View route map !!" << endl;
        cout << "3. View path b/w two cities with minimum distance !!" << endl;
        cout << "4. View path b/w two cities with minimum cost !!" << endl;
        cout << "5. View path b/w two cities with minimum time !!" << endl;
        cout << "6. Contact Us !!" << endl;
        cout << "7. Exit !!" << endl;
        cout << "Enter your choice from above options: ";
        cin >> choice;
        return;
    }

    void options() {
        menu();
        if (choice.size() > 1) invalid();
        else if (choice[0] == '7') {
            choice7(); return;
        }
        else if (choice[0] == '6')choice6();
        else if (choice[0] == '1')choice1();
        else if (choice[0] == '2')  choice2();
        else if (choice[0] > '2' && choice[0] < '6')choice3_5(choice[0] - '2');
        else invalid();
        options();  return;
    }

    void invalid() {
        cout << "------Invalid choice! choice should b/w [1, 7]-----------------" << endl;
        return;
    }

    void choice1() {
        cout << "-------------------------City List------------------------------" << endl;
        g.viewCity();
        cout << "----------------------------------------------------------------" << endl;
        return;
    }

    void choice2() {
        cout << "-------------------------Route Map------------------------------" << endl;
        mpr.options();
        cout << "----------------------------------------------------------------" << endl;
        return;
    }

    bool checkSrcDest(string a, string b) {
        if (cityValue.find(a) == cityValue.end() || cityValue.find(b) == cityValue.end())return false;
        return true;
    }

    void choice3_5(int idx) {
        cout << "----------------------------------------------------------------" << endl;
        cout << "Enter source city      : "; cin >> g.source;
        cout << "Enter destination city : "; cin >> g.destination;
        g.convert(g.source); g.convert(g.destination);

        if (checkSrcDest(g.source, g.destination) == false) {
            cout << "===> source or destination city not in map! please re-enter" << endl;
            choice3_5(idx);
            return;
        }

        int dis = g.shortest(idx);
        if (dis == -1) noPath();
        else if (idx == 1)pathPrint("distance", dis);
        else if (idx == 2)pathPrint("cost", dis);
        else if (idx == 3)pathPrint("time", dis);

        cout << "-----------------------------------------------------------------" << endl;
        return;
    }
    void choice6() {
        cout << "------------------------Contact Us-------------------------------" << endl;
        cout << "===>   Email : gaurish210@gmail.com" << endl;
        cout << "===>   Phone : +91-6394079252" << endl;
        cout << "-------------------------Connect Us------------------------------" << endl;
        cout << "===>   LinkedIn :  https://www.linkedin.com/in/gaurish-ojha/" << endl;
        cout << "===>   Github   :  https://www.github.com/gaurishiiitnr/" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        return;
    }

    void choice7() {
        cout << "-------------------Thank you for using CityTrek!-----------------" << endl;
        return;
    }

    void noPath() {
        cout << "===>  No path exists between " << g.source << " and " << g.destination << endl;
        return;
    }

    void pathPrint(string type, int val) {
        cout << "===> Minimum " << type << " between " << g.source << " and " << g.destination << " is = " << val << endl;
        g.printRoute();
        return;
    }

}; CityTrek ct;




void city() {
    g.addCity("Delhi"), g.addCity("Mumbai"), g.addCity("Kolkata"), g.addCity("Chennai"), g.addCity("Bengaluru");
    g.addCity("Hyderabad"), g.addCity("Pune"), g.addCity("Ahmedabad"), g.addCity("Jaipur"), g.addCity("Lucknow");
    g.addCity("Kanpur"), g.addCity("Nagpur"), g.addCity("Patna"), g.addCity("Indore"), g.addCity("Thane");
    g.addCity("Bhopal"), g.addCity("Visakhapatnam"), g.addCity("Vadodara"), g.addCity("Surat"), g.addCity("Agra");
    g.addCity("Varanasi"), g.addCity("Faridabad"), g.addCity("Rajkot"), g.addCity("Meerut"), g.addCity("Noida");
    g.addCity("Chandigarh"), g.addCity("Ghaziabad"), g.addCity("Ludhiana"), g.addCity("Jalandhar"), g.addCity("Amritsar");
    g.addCity("Kochi"), g.addCity("Coimbatore"), g.addCity("Madurai"), g.addCity("Nashik"), g.addCity("Vijayawada");
    g.addCity("Warangal"), g.addCity("Srinagar"), g.addCity("Aurangabad"), g.addCity("Dhanbad"), g.addCity("Amravati");
    g.addCity("Allahabad"), g.addCity("Gorakhpur"), g.addCity("Aligarh"), g.addCity("Meerut"), g.addCity("Bareilly");
    g.addCity("Moradabad"), g.addCity("Ghaziabad"), g.addCity("Saharanpur"), g.addCity("Muzaffarnagar"), g.addCity("Bijnor");
    g.addCity("Kanpur"), g.addCity("Lucknow"), g.addCity("Varanasi"), g.addCity("Agra"), g.addCity("Mathura");
    g.addCity("Firozabad"), g.addCity("Mainpuri"), g.addCity("Etawah"), g.addCity("Jhansi"), g.addCity("Rampur");
    g.addCity("Shahjahanpur"), g.addCity("Ayodhya"), g.addCity("Faizabad"), g.addCity("Sultanpur"), g.addCity("Ambedkar Nagar");
    g.addCity("Basti"), g.addCity("Azamgarh"), g.addCity("Ballia"), g.addCity("Ghazipur"), g.addCity("Jaunpur");
    g.addCity("Mirzapur"), g.addCity("Prayagraj"), g.addCity("Raebareli"), g.addCity("Sitapur"), g.addCity("Hardoi");
    g.addCity("Unnao"), g.addCity("Lakhimpur Kheri"), g.addCity("Gonda"), g.addCity("Bahraich"), g.addCity("Sultanpur");
    g.addCity("Banda"), g.addCity("Fatehpur"), g.addCity("Varanasi"), g.addCity("Gorakhpur"), g.addCity("Deoria");
    g.addCity("Maharajganj"), g.addCity("Padrauna"), g.addCity("Kushinagar"), g.addCity("Mau"), g.addCity("Sant Kabir Nagar");
    g.addCity("Azamgarh"), g.addCity("Jaunpur"), g.addCity("Sultanpur"), g.addCity("Amethi"), g.addCity("Barabanki");
    g.addCity("Balrampur"), g.addCity("Shravasti"), g.addCity("Bahraich"), g.addCity("Hardoi"), g.addCity("Sitapur");
    return;
}

void Edges() {
    g.addEdge("Delhi", "Mumbai", 1447, 3825, 19), g.addEdge("Mumbai", "Bengaluru", 980, 2100, 10), g.addEdge("Chennai", "Kolkata", 1669, 4500, 22), g.addEdge("Pune", "Ahmedabad", 664, 1475, 7), g.addEdge("Jaipur", "Lucknow", 476, 1050, 5), g.addEdge("Kolkata", "Kanpur", 1000, 2200, 11), g.addEdge("Lucknow", "Nagpur", 774, 1705, 8), g.addEdge("Patna", "Indore", 1356, 3000, 15), g.addEdge("Thane", "Bhopal", 803, 1775, 9), g.addEdge("Visakhapatnam", "Vadodara", 903, 2000, 10),
        g.addEdge("Kochi", "Coimbatore", 190, 420, 2), g.addEdge("Madurai", "Nashik", 1510, 3335, 14), g.addEdge("Vijayawada", "Warangal", 270, 600, 3), g.addEdge("Srinagar", "Aurangabad", 1733, 3830, 19), g.addEdge("Amritsar", "Varanasi", 846, 1870, 9), g.addEdge("Gorakhpur", "Aligarh", 490, 1080, 5), g.addEdge("Meerut", "Bareilly", 172, 380, 2), g.addEdge("Moradabad", "Ghaziabad", 75, 165, 1), g.addEdge("Saharanpur", "Muzaffarnagar", 63, 140, 1), g.addEdge("Bijnor", "Kanpur", 402, 890, 4),
        g.addEdge("Kanpur", "Varanasi", 324, 715, 3), g.addEdge("Agra", "Mathura", 54, 120, 1), g.addEdge("Firozabad", "Mainpuri", 64, 140, 1), g.addEdge("Etawah", "Jhansi", 164, 365, 2), g.addEdge("Rampur", "Shahjahanpur", 86, 190, 1), g.addEdge("Ayodhya", "Faizabad", 6, 15, 1), g.addEdge("Sultanpur", "Ambedkar Nagar", 62, 140, 1), g.addEdge("Basti", "Azamgarh", 44, 100, 1), g.addEdge("Ballia", "Ghazipur", 91, 202, 1), g.addEdge("Jaunpur", "Mirzapur", 130, 290, 1),
        g.addEdge("Prayagraj", "Raebareli", 112, 250, 1), g.addEdge("Sitapur", "Hardoi", 54, 120, 1), g.addEdge("Unnao", "Lakhimpur Kheri", 80, 178, 1), g.addEdge("Gonda", "Bahraich", 79, 175, 1), g.addEdge("Sultanpur", "Banda", 144, 320, 2), g.addEdge("Fatehpur", "Varanasi", 266, 590, 3), g.addEdge("Gorakhpur", "Deoria", 48, 107, 1), g.addEdge("Maharajganj", "Padrauna", 32, 72, 1), g.addEdge("Kushinagar", "Mau", 49, 108, 1), g.addEdge("Sant Kabir Nagar", "Azamgarh", 56, 125, 1),
        g.addEdge("Rajkot", "Meerut", 1151, 2550, 12), g.addEdge("Noida", "Chandigarh", 252, 560, 3), g.addEdge("Ghaziabad", "Ludhiana", 354, 785, 4), g.addEdge("Jalandhar", "Amritsar", 79, 175, 1), g.addEdge("Kochi", "Coimbatore", 190, 420, 2), g.addEdge("Bhopal", "Visakhapatnam", 1082, 2395, 12), g.addEdge("Vadodara", "Surat", 134, 295, 1), g.addEdge("Agra", "Varanasi", 620, 1375, 6), g.addEdge("Faridabad", "Rajkot", 1043, 2305, 11), g.addEdge("Kolkata", "Noida", 1451, 3205, 14),
        g.addEdge("Bareilly", "Meerut", 194, 430, 2), g.addEdge("Noida", "Chandigarh", 252, 560, 3), g.addEdge("Ghaziabad", "Ludhiana", 354, 785, 4), g.addEdge("Jalandhar", "Amritsar", 79, 175, 1), g.addEdge("Kochi", "Coimbatore", 190, 420, 2), g.addEdge("Bhopal", "Visakhapatnam", 1082, 2395, 12), g.addEdge("Vadodara", "Surat", 134, 295, 1), g.addEdge("Agra", "Varanasi", 620, 1375, 6), g.addEdge("Faridabad", "Rajkot", 1043, 2305, 11), g.addEdge("Kolkata", "Noida", 1451, 3205, 14),
        g.addEdge("Meerut", "Noida", 78, 175, 1), g.addEdge("Chandigarh", "Ghaziabad", 275, 610, 3), g.addEdge("Ludhiana", "Jalandhar", 62, 140, 1), g.addEdge("Amritsar", "Kochi", 2043, 4515, 21), g.addEdge("Coimbatore", "Bhopal", 1426, 3155, 14), g.addEdge("Visakhapatnam", "Vadodara", 1252, 2770, 13), g.addEdge("Surat", "Agra", 997, 2205, 11), g.addEdge("Varanasi", "Faridabad", 852, 1885, 9), g.addEdge("Rajkot", "Noida", 1080, 2385, 12), g.addEdge("Bareilly", "Meerut", 194, 430, 2),
        g.addEdge("Noida", "Chandigarh", 252, 560, 3), g.addEdge("Ghaziabad", "Ludhiana", 354, 785, 4), g.addEdge("Jalandhar", "Amritsar", 79, 175, 1), g.addEdge("Kochi", "Coimbatore", 190, 420, 2), g.addEdge("Bhopal", "Visakhapatnam", 1082, 2395, 12), g.addEdge("Vadodara", "Surat", 134, 295, 1), g.addEdge("Agra", "Varanasi", 620, 1375, 6), g.addEdge("Faridabad", "Rajkot", 1043, 2305, 11), g.addEdge("Kolkata", "Noida", 1451, 3205, 14), g.addEdge("Meerut", "Noida", 78, 175, 1),
        g.addEdge("Chandigarh", "Ghaziabad", 275, 610, 3), g.addEdge("Ludhiana", "Jalandhar", 62, 140, 1), g.addEdge("Amritsar", "Kochi", 2043, 4515, 21), g.addEdge("Coimbatore", "Bhopal", 1426, 3155, 14), g.addEdge("Visakhapatnam", "Vadodara", 1252, 2770, 13), g.addEdge("Surat", "Agra", 997, 2205, 11), g.addEdge("Varanasi", "Faridabad", 852, 1885, 9), g.addEdge("Rajkot", "Noida", 1080, 2385, 12), g.addEdge("Bareilly", "Meerut", 194, 430, 2), g.addEdge("Noida", "Chandigarh", 252, 560, 3),
        g.addEdge("Ghaziabad", "Ludhiana", 354, 785, 4), g.addEdge("Jalandhar", "Amritsar", 79, 175, 1), g.addEdge("Kochi", "Coimbatore", 190, 420, 2), g.addEdge("Bhopal", "Visakhapatnam", 1082, 2395, 12), g.addEdge("Vadodara", "Surat", 134, 295, 1), g.addEdge("Agra", "Varanasi", 620, 1375, 6), g.addEdge("Faridabad", "Rajkot", 1043, 2305, 11), g.addEdge("Kolkata", "Noida", 1451, 3205, 14), g.addEdge("Meerut", "Noida", 78, 175, 1), g.addEdge("Chandigarh", "Ghaziabad", 275, 610, 3),
        g.addEdge("Ludhiana", "Jalandhar", 62, 140, 1), g.addEdge("Amritsar", "Kochi", 2043, 4515, 21), g.addEdge("Coimbatore", "Bhopal", 1426, 3155, 14), g.addEdge("Visakhapatnam", "Vadodara", 1252, 2770, 13), g.addEdge("Surat", "Agra", 997, 2205, 11), g.addEdge("Varanasi", "Faridabad", 852, 1885, 9), g.addEdge("Rajkot", "Noida", 1080, 2385, 12), g.addEdge("Bareilly", "Meerut", 194, 430, 2), g.addEdge("Noida", "Chandigarh", 252, 560, 3), g.addEdge("Ghaziabad", "Ludhiana", 354, 785, 4),
        g.addEdge("Jalandhar", "Amritsar", 79, 175, 1), g.addEdge("Kochi", "Coimbatore", 190, 420, 2), g.addEdge("Bhopal", "Visakhapatnam", 1082, 2395, 12), g.addEdge("Vadodara", "Surat", 134, 295, 1), g.addEdge("Agra", "Varanasi", 620, 1375, 6), g.addEdge("Faridabad", "Rajkot", 1043, 2305, 11), g.addEdge("Kolkata", "Noida", 1451, 3205, 14), g.addEdge("Meerut", "Noida", 78, 175, 1), g.addEdge("Chandigarh", "Ghaziabad", 275, 610, 3), g.addEdge("Ludhiana", "Jalandhar", 62, 140, 1),
        g.addEdge("Amritsar", "Kochi", 2043, 4515, 21), g.addEdge("Coimbatore", "Bhopal", 1426, 3155, 14), g.addEdge("Visakhapatnam", "Vadodara", 1252, 2770, 13), g.addEdge("Surat", "Agra", 997, 2205, 11), g.addEdge("Varanasi", "Faridabad", 852, 1885, 9), g.addEdge("Rajkot", "Noida", 1080, 2385, 12), g.addEdge("Bareilly", "Meerut", 194, 430, 2), g.addEdge("Noida", "Chandigarh", 252, 560, 3), g.addEdge("Ghaziabad", "Ludhiana", 354, 785, 4), g.addEdge("Jalandhar", "Amritsar", 79, 175, 1);
    g.addEdge("delhi", "noida", 5, 10, 10000), g.addEdge("ghaziabad", "noida", 5, 10000, 10000), g.addEdge("ghaziabad", "raipur", 5, 10000, 10000);
    g.addEdge("vadodara", "raipur", 5, 10, 10000), g.addEdge("vadodara", "hyderabad", 5, 10, 10000), g.addEdge("bangalore", "hyderabad", 5, 10, 10000), g.addEdge("bangalore", "jaipur", 5, 10, 10000), g.addEdge("lucknow", "jaipur", 5, 10, 10000);
    g.addEdge("delhi", "lakhimpur", 100000, 5, 10000), g.addEdge("ranchi", "lakhimpur", 100000, 5, 10000), g.addEdge("ranchi", "lucknow", 10000, 10, 10000);
    g.addEdge("delhi", "jaunpur", 100000, 100000, 5), g.addEdge("jaunpur", "allahabad", 100000, 500000, 10), g.addEdge("allahabad", "lucknow", 1000000, 1000000, 10);

}

int main() {
    cout << "Welcome to CityTrek!" << endl;
    city(); Edges();
    ct.options();
}


