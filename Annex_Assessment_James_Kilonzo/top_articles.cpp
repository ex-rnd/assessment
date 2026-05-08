// James Kilonzo: top_articles.c

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// Fetch URL 
string fetchURL(const string& url) {
    string command = "curl -s \"" + url + "\"";

    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe) {
        return "";
    }

    string result;
    char buffer[512];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;

}

struct Article {
    string name;
    int num_comments;
};

vector<string> topArticles(int limit) {
    string base_url = "https://jsonmock.hackerrank.com/api/articles?page=";

    // Fetch Page 1 
    string first_response = fetchURL(base_url + "1");

    // Check Nullity 
    if (first_response.empty()) return {};
    json first_json = json::parse(first_response);

    int total_pages = first_json["total_pages"];

    //Collect Valid Articles
    vector<Article> articles;

    for (int page=1; page <= total_pages; page++) {
        string raw = fetchURL(base_url + to_string(page));
        json data = json::parse(raw);


        for (auto& item : data["data"]) {

            string name = "";

            if (!item["title"].is_null()) {
                name = item["title"].get<string>();
            }

            else if (!item["story_title"].is_null()) {
                name = item["story_title"].get<string>();
            }

            else {
                continue;
            }

            int comments = 0;

            if (!item["num_comments"].is_null()) {
                comments = item["num_comments"].get<int>();
            }

            articles.push_back({name, comments});
        }
    }

    // Sort 
    sort(articles.begin(), articles.end(), [](const Article& a, const Article& b) {

        if (a.num_comments != b.num_comments) {
            return a.num_comments > b.num_comments;
        }

        return a.name > b.name;
    });

    // Return Top Limit Names 
    vector<string> result; 
    for (int i=0; i<min(limit, (int)articles.size()); i++) {
        result.push_back(articles[i].name);
    } 

    return result; 

}

int main() {
    int limit = 2;

    vector<string> top = topArticles(limit);

    for (const string& article : top) {
        cout << article << "\n";
    }

    return 0;

}
