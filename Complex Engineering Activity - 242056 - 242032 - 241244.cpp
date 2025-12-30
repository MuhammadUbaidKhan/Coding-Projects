#include<iostream>
#include<string>

using namespace std;

class Graph{
    private:
    int no_of_cities;
    string cities[50];
    int adj[50][50];

    public:
    Graph(){ //constructor for start of mapping
        no_of_cities = 0;

        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                adj[i][j] = 0;
            }
        }
    }

    int findacity(string city){ // loop done to make sure cities can be added multiple time
        for (int i = 0; i < no_of_cities; i++)
            if (cities[i] == city)
                return i;
        return -1;
    }

    void addacity(string city){
        if(no_of_cities == 50){
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: Limit of cities has been reached!"<<endl; //error case handling
            cout<<"======================================\n"<<endl;
            return;
        }

        if(findacity(city) != -1){
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: City '"<<city<<"' already exists!"<<endl; // recorring case handling
            cout<<"======================================\n"<<endl;
            return;
        }
        
        cities[no_of_cities] = city;
        no_of_cities++;
        cout<<"\n======================================"<<endl;
        cout<<"SUCCESS: City '"<<city<<"' has been added!"<<endl; //confirmation
        cout<<"======================================\n"<<endl;
    }

    void removeacity(string city){
        int idx = findacity(city);// removes city from data by finding it
        if(idx == -1){
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: City '"<<city<<"' not found!"<<endl;// error handling
            cout<<"======================================\n"<<endl;
            return;
        }
        
        for(int i = idx; i < no_of_cities - 1; i++){// shift city names to the left(for allignment
            cities[i] = cities[i + 1];// and not having an empty space) in the data structure
        }

        for(int i = idx; i < no_of_cities - 1; i++){
            for(int j = 0; j < no_of_cities; j++){
                adj[i][j] = adj[i + 1][j];
            }
        }
        
        for(int j = idx; j < no_of_cities - 1; j++){
            for(int i = 0; i < no_of_cities; i++){
                adj[i][j] = adj[i][j + 1];
            }
        }

        for(int i = 0; i < no_of_cities; i++){
            adj[no_of_cities - 1][i] = 0;// done to remove all other city connections in the data
            adj[i][no_of_cities - 1] = 0;
        }
        
        no_of_cities--;//decreasing total number of cities
        cout<<"\n======================================"<<endl;
        cout<<"SUCCESS: City '"<<city<<"' has been removed!"<<endl;// success message
        cout<<"======================================\n"<<endl;
    }

    void addaroad(string city1, string city2){
        if(findacity(city1) == -1 || findacity(city2) == -1){
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: One or both cities not found!"<<endl;//error handling
            cout<<"======================================\n"<<endl;
            return;
        }
        
        if(city1 == city2){
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: Cannot add road between same city!"<<endl;//error handling
            cout<<"======================================\n"<<endl;
            return;
        }
        
        adj[findacity(city1)][findacity(city2)] = 1;
        adj[findacity(city2)][findacity(city1)] = 1;
        cout<<"\n======================================"<<endl;
        cout<<"SUCCESS: Road added between '"<<city1<<"' and '"<<city2<<"'"<<endl;
        cout<<"======================================\n"<<endl;
    }

    void removearoad(string city1, string city2) {
        if (findacity(city1) == -1 || findacity(city2) == -1) {//checking for empty space
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: One or both cities not found!"<<endl;//error handling
            cout<<"======================================\n"<<endl;
            return;
        }
        
        adj[findacity(city1)][findacity(city2)] = 0;
        adj[findacity(city2)][findacity(city1)] = 0;
        cout<<"\n======================================"<<endl;
        cout<<"SUCCESS: Road removed between '"<<city1<<"' and '"<<city2<<"'"<<endl;
        cout<<"======================================\n"<<endl;
    }

    void showMap() {
        if(no_of_cities == 0){
            cout<<"\n======================================"<<endl;
            cout<<"MAP IS EMPTY!"<<endl;
            cout<<"No cities have been added yet."<<endl;
            cout<<"======================================\n"<<endl;
            return;
        }
        
        cout<<"\n======================================"<<endl;
        cout<<"CITY MAP (Total Cities: "<<no_of_cities<<")"<<endl;
        cout<<"======================================"<<endl;
        
        for (int i = 0; i < no_of_cities; i++) {
            cout<<endl;
            cout<<"City: "<<cities[i]<<endl;//loop applied to show all cities and 
            cout<<"Connections: ";//connections one by one 
            
            bool Connection = false;
            for (int j = 0; j < no_of_cities; j++) {
                if (adj[i][j]) {
                    if(Connection) cout<<", ";
                    cout << cities[j];
                    Connection = true;
                }
            }
            
            if (!Connection) {
                cout << "None (Isolated city)";
            }
            cout<<endl;
        }
        cout<<"\n======================================\n"<<endl;
    }

    void BFS(string start, string end) {
        int starting_point = findacity(start);
        int ending_point = findacity(end);
        
        if (starting_point == -1 || ending_point == -1) {
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: One or both cities not found!"<<endl;//error handling
            cout<<"======================================\n"<<endl;
            return;
        }
        
        if(start == end){
            cout<<"\n======================================"<<endl;
            cout<<"SHORTEST ROUTE: "<<start<<" (Start and end are same)"<<endl;
            cout<<"======================================\n"<<endl;
            return;
        }

        int visited[50];// array to remember citites visisted
        for (int i = 0; i < 50; i++) {
            visited[i] = 0;
        }
        
        int parent[50];
        for (int i = 0; i < 50; i++) {
            parent[i] = -1;
        }
        
        int queue[50], front = 0, rear = 0;// using qeue for shortest route
        
        visited[starting_point] = 1;// visited starting city
        queue[rear++] = starting_point;

        while (front < rear) {
            int v = queue[front++];
            
            for (int i = 0; i < no_of_cities; i++) {// If there is a connection and the city is not yet visited
                if (adj[v][i] && !visited[i]) {// mark city as visited
                    visited[i] = 1;
                    parent[i] = v;
                    queue[rear++] = i;
                }
            }
        }

        if (!visited[ending_point]) {
            cout<<"\n======================================"<<endl;
            cout<<"NO ROUTE FOUND!"<<endl;
            cout<<"No path exists between '"<<start<<"' and '"<<end<<"'"<<endl;
            cout<<"======================================\n"<<endl;
            return;
        }

        cout<<"\n======================================"<<endl;
        cout<<"SHORTEST ROUTE (BFS Algorithm)"<<endl;
        cout<<"From: '"<<start<<"' to '"<<end<<"'"<<endl;
        cout<<"======================================"<<endl;
        
        int path[50], count = 0;
        for (int v = ending_point; v != -1; v = parent[v]) {// done for path tracing
            path[count++] = v;// store in index
        }

        cout<<"Route: ";// rpute display from start to finish
        for (int i = count - 1; i >= 0; i--) {
            cout << cities[path[i]];
            if (i > 0) {
                cout << " -> ";// for direction
            }
        }
        
        cout<<endl;
        cout<<"Total cities in route: "<<count<<endl;
        cout<<"======================================\n"<<endl;
    }

    void DFS(string city1, string city2) {
        int starting_point = findacity(city1);
        int ending_point = findacity(city2);
        
        if (starting_point == -1 || ending_point == -1) {
            cout<<"\n======================================"<<endl;
            cout<<"ERROR: One or both cities not found!"<<endl;
            cout<<"======================================\n"<<endl;
            return;
        }
        
        if(city1 == city2){
            cout<<"\n======================================"<<endl;
            cout<<"CONNECTIVITY RESULT (DFS Algorithm)"<<endl;
            cout<<"Cities '"<<city1<<"' and '"<<city2<<"' are the same city"<<endl;
            cout<<"======================================\n"<<endl;
            return;
        }

        int visited[50];// array to remeber visited cities
        for(int i = 0; i < 50; i++) {
            visited[i] = 0;// Initialize all cities as unvisited

        }
        
        int stack[50], top = -1;// Stack implementation
        
        visited[starting_point] = 1;// mark starting city and put it into stack
        stack[++top] = starting_point;

        while (top >= 0) {
            int v = stack[top--];
            // visting all connected citites to starting point
            for (int i = 0; i < no_of_cities; i++) {
                if (adj[v][i] && !visited[i]) {
                    visited[i] = 1;
                    stack[++top] = i;
                }
            }
        }

        cout<<"\n======================================"<<endl;
        cout<<"CONNECTIVITY RESULT (DFS Algorithm)"<<endl;
        cout<<"Checking: '"<<city1<<"' and '"<<city2<<"'"<<endl;
        cout<<"======================================"<<endl;
        
        if (visited[ending_point]) {
            cout<<"RESULT: CONNECTED ✓"<<endl;
            cout<<"There is a path between these cities"<<endl;
        } else {
            cout<<"RESULT: NOT CONNECTED ✗"<<endl;
            cout<<"No path exists between these cities"<<endl;
        }
        cout<<"======================================\n"<<endl;
    }
};

int main() {
    Graph G;
    int choice;
    string city1, city2;

    do {
        cout<<"\n╔══════════════════════════════════════╗"<<endl;
        cout<<"║     CITY NAVIGATION SYSTEM           ║"<<endl;
        cout<<"╠══════════════════════════════════════╣"<<endl;
        cout<<"║  1. Add a City                       ║"<<endl;
        cout<<"║  2. Remove a City                    ║"<<endl;
        cout<<"║  3. Add a Road                       ║"<<endl;
        cout<<"║  4. Remove a Road                    ║"<<endl;
        cout<<"║  5. Show the Map                     ║"<<endl;
        cout<<"║  6. Find Shortest Route (BFS)        ║"<<endl;
        cout<<"║  7. Check Connection (DFS)           ║"<<endl;
        cout<<"║  8. Exit                             ║"<<endl;
        cout<<"╚══════════════════════════════════════╝"<<endl;
        cout<<"\nEnter your choice (1-8): ";
        cin >> choice;

        switch (choice) {// all choices and option setups for interface
            case 1:
                cout << "\nEnter city name: ";
                cin >> city1;
                G.addacity(city1);
                break;
            case 2:
                cout << "\nEnter city name to remove: ";
                cin >> city1;
                G.removeacity(city1);
                break;
            case 3:
                cout << "\nEnter first city: ";
                cin >> city1;
                cout << "Enter second city: ";
                cin >> city2;
                G.addaroad(city1, city2);
                break;
            case 4:
                cout << "\nEnter first city: ";
                cin >> city1;
                cout << "Enter second city: ";
                cin >> city2;
                G.removearoad(city1, city2);
                break;
            case 5:
                G.showMap();
                break;
            case 6:
                cout << "\nEnter starting city: ";
                cin >> city1;
                cout << "Enter destination city: ";
                cin >> city2;
                G.BFS(city1, city2);
                break;
            case 7:
                cout << "\nEnter first city: ";
                cin >> city1;
                cout << "Enter second city: ";
                cin >> city2;
                G.DFS(city1, city2);
                break;
            case 8:
                cout<<"\n======================================"<<endl;
                cout<<"THANK YOU FOR USING CITY NAVIGATION!"<<endl;
                cout<<"======================================\n"<<endl;
                break;
            default:
                cout<<"\n======================================"<<endl;
                cout<<"ERROR: Invalid choice! Please enter 1-8"<<endl;
                cout<<"======================================\n"<<endl;
        }
    } while (choice != 8);

    return 0;
}