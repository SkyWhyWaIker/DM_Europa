#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

enum Country {
    Albania = 0,
    Andorra,
    Armenia,
    Austria,
    Azerbaijan,
    Belarus,
    Belgium,
    BosniaAndHerzegovina,
    Bulgaria,
    Croatia,
    Cyprus,
    CzechRepublic,
    Denmark,
    Estonia,
    Finland,
    France,
    Germany,
    Georgia,
    Greece,
    Hungary,
    Iceland,
    RepublicOfIreland,
    Italy,
    Latvia,
    Liechtenstein,
    Lithuania,
    Luxembourg,
    Malta,
    Moldova,
    Monaco,
    Montenegro,
    Netherlands,
    RepublicOfMacedonia,
    Norway,
    Poland,
    Portugal,
    Romania,
    Russia,
    SanMarino,
    Serbia,
    Slovakia,
    Slovenia,
    Spain,
    Sweden,
    Switzerland,
    Turkey,
    Ukraine,
    UnitedKingdom,
    VaticanCity
};

std::string cot[49] = {"Albania", "Andorra",
        "Armenia",
        "Austria",
        "Azerbaijan",
        "Belarus",
        "Belgium",
        "BosniaAndHerzegovina",
        "Bulgaria",
        "Croatia",
        "Cyprus",
        "CzechRepublic",
        "Denmark",
        "Estonia",
        "Finland",
        "France",
        "Germany",
        "Georgia",
        "Greece",
        "Hungary",
        "Iceland",
        "RepublicOfIreland",
        "Italy",
        "Latvia",
        "Liechtenstein",
        "Lithuania",
        "Luxembourg",
        "Malta",
        "Moldova",
        "Monaco",
        "Montenegro",
        "Netherlands",
        "RepublicOfMacedonia",
        "Norway",
        "Poland",
        "Portugal",
        "Romania",
        "Russia",
        "SanMarino",
        "Serbia",
        "Slovakia",
        "Slovenia",
        "Spain",
        "Sweden",
        "Switzerland",
        "Turkey",
        "Ukraine",
        "UnitedKingdom",
        "VaticanCity"};
const int numCountries = 49;
const int INF = INT_MAX;

std::vector<std::vector<int>> adjacencyMatrix(numCountries, std::vector<int>(numCountries, INF));

void initializeGraph(const std::unordered_map<Country, std::unordered_set<Country>>& graph) {
    for (const auto& [country, neighbors] : graph) {
        int from = static_cast<int>(country);
        for (const auto& neighbor : neighbors) {
            int to = static_cast<int>(neighbor);
            adjacencyMatrix[from][to] = 1;
        }
    }

    for (int i = 0; i < numCountries; ++i) {
        adjacencyMatrix[i][i] = 0;
    }
}

void dijkstra(int source) {
    std::vector<int> dist(numCountries, INF);
    std::vector<bool> visited(numCountries, false);

    dist[source] = 0;

    for (int count = 0; count < numCountries - 1; ++count) {
        int u = -1;

        // Find the vertex with the minimum distance value among unvisited vertices
        for (int i = 0; i < numCountries; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = true;

        // Update distance values of the neighboring vertices of the picked vertex
        for (int v = 0; v < numCountries; ++v) {
            if (!visited[v] && adjacencyMatrix[u][v] != INF && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjacencyMatrix[u][v];
            }
        }
    }

    // Update the adjacency matrix with the computed distances
    for (int i = 0; i < numCountries; ++i) {
        adjacencyMatrix[source][i] = dist[i];
    }
}

int main() {
        std::unordered_map<Country, std::unordered_set<Country>> graph = {
            {Albania, {Montenegro, Greece, Serbia, RepublicOfMacedonia}},
            {Andorra, {France, Spain}},
            {Armenia, {Azerbaijan, Georgia, Turkey}},
            {Austria, {Germany, CzechRepublic, Slovakia, Hungary, Slovenia, Italy, Switzerland, Liechtenstein}},
            {Azerbaijan, {Russia, Georgia, Armenia, Turkey}},
            {Belarus, {Latvia, Lithuania, Poland, Russia, Ukraine}},
            {Belgium, {France, Luxembourg, Germany, Netherlands}},
            {BosniaAndHerzegovina, {Croatia, Montenegro, Serbia}},
            {Bulgaria, {Romania, Serbia, RepublicOfMacedonia, Greece, Turkey}},
            {Croatia, {Slovenia, Hungary, Serbia, BosniaAndHerzegovina, Montenegro}},
            {Cyprus, {}},
            {CzechRepublic, {Germany, Austria, Slovakia, Poland}},
            {Denmark, {Germany}},
            {Estonia, {Latvia, Russia}},
            {Finland, {Sweden, Russia, Norway}},
            {France, {Belgium, Luxembourg, Germany, Switzerland, Italy, Spain, Andorra, Monaco}},
            {Germany, {Denmark, Netherlands, Belgium, Luxembourg, France, Switzerland, Austria, CzechRepublic, Poland}},
            {Georgia, {Russia, Azerbaijan, Armenia, Turkey}},
            {Greece, {Albania, RepublicOfMacedonia, Bulgaria, Turkey}},
            {Hungary, {Slovakia, Ukraine, Romania, Serbia, Croatia, Slovenia, Austria}},
            {Iceland, {}},
            {RepublicOfIreland, {UnitedKingdom}},
            {Italy, {France, Switzerland, Austria, Slovenia, SanMarino, VaticanCity}},
            {Latvia, {Estonia, Lithuania, Russia, Belarus}},
            {Liechtenstein, {Switzerland, Austria}},
            {Lithuania, {Latvia, Belarus, Poland, Russia}},
            {Luxembourg, {Belgium, Germany, France}},
            {Malta, {}},
            {Moldova, {Romania, Ukraine}},
            {Monaco, {France}},
            {Montenegro, {Croatia, BosniaAndHerzegovina, Serbia, Albania}},
            {Netherlands, {Germany, Belgium}},
            {RepublicOfMacedonia, {Serbia, Bulgaria, Greece, Albania}},
            {Norway, {Sweden, Finland, Russia}},
            {Poland, {Germany, CzechRepublic, Slovakia, Ukraine, Belarus, Lithuania, Russia}},
            {Portugal, {Spain}},
            {Romania, {Hungary, Serbia, Bulgaria, Moldova, Ukraine}},
            {Russia, {Azerbaijan, Norway, Finland, Estonia, Latvia, Lithuania, Poland, Belarus, Ukraine, Georgia}},
            {SanMarino, {Italy}},
            {Serbia, {Hungary, Croatia, BosniaAndHerzegovina, Montenegro, Albania, RepublicOfMacedonia, Romania, Bulgaria}},
            {Slovakia, {CzechRepublic, Poland, Ukraine, Hungary, Austria}},
            {Slovenia, {Austria, Italy, Hungary, Croatia}},
            {Spain, {Portugal, France, Andorra}},
            {Sweden, {Norway, Finland}},
            {Switzerland, {Germany, France, Italy, Austria, Liechtenstein}},
            {Turkey, {Greece, Bulgaria, Georgia, Armenia, Azerbaijan}},
            {Ukraine, {Poland, Slovakia, Hungary, Romania, Moldova, Belarus, Russia}},
            {UnitedKingdom, {RepublicOfIreland}},
            {VaticanCity, {Italy}}
    };

    initializeGraph(graph);

    // Apply Dijkstra's algorithm for each country as the source
    for (int i = 0; i < numCountries; ++i) {
        dijkstra(i);
    }

    std::cout << "Shortest paths matrix:" << '\n';
    for (int i = 0; i < numCountries; ++i) {
        std::cout << cot[i] << " ";
        for (int j = 0; j < numCountries; ++j) {
            if (adjacencyMatrix[i][j] == INF or adjacencyMatrix[i][j] < 0) {
                std::cout << "- ";
            } else {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
        }
        std::cout << '\n';
    }

    return 0;
}