#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int minOperations(const std::vector<int> &locations) {
    int result = 0;

    std::map<int, int> locMap;
    std::vector<std::pair<int, int>> locRank;

    // Populate hash map with count of items at each location
    for (const auto &location : locations)
        locMap[location]++;

    // allocate space in the rank vector
    locRank.reserve(locMap.size());

    // Push all pairs to locRank
    for (const auto &kv : locMap)
        locRank.emplace_back(kv);

    // Sort the pairs in locRank in descending order by greatest count
    std::sort(locRank.begin(), locRank.end(),
        [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
            return a.second < b.second;
    });

    while (!locRank.empty()) {
        bool poppedX{ false };

        // get x and decrement count
        int x = locRank.back().first;
        std::cout << "x: " << x;

        // Decrement the count
        locRank.back().second--;

        // if x was the last of this location, remove it from locRank
        if (locRank.back().second == 0) {
            locRank.pop_back();
            poppedX = true;
        }

        // see if there is still a y value
        if (poppedX && !locRank.empty()) {
            int y = locRank.back().first;
            std::cout << " y: " << y << '\n';

            // Decrease count
            locRank.back().second--;

            // if y was the last of this location, remove it from locRank
            if (locRank.back().second == 0)
                locRank.pop_back();

        } else if (locRank.size() > 1) {
            // y is the second to last value
            int y_idx = locRank.size() - 2;
            int y = locRank[y_idx].first;
            std::cout << " y: " << y << '\n';

            // Decrease count
            locRank[y_idx].second--;

            // if y was the last of this location, remove it from locRank
            if (locRank[y_idx].second == 0)
                locRank.erase(locRank.begin() + y_idx);
        } else {
            std::cout << '\n';
        }

        result++;
    }

    std::cout << "minOperations: " << result << std::endl;
    return result;
}

int main() {
    std::vector<int> locations = { 1, 8, 6, 7, 7};

    minOperations(locations);
    return 0;
}

