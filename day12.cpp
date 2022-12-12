struct P {
    int x;
    int y;
};

int main() {

    std::ifstream infile("day12.txt");

    std::vector<std::vector<char>> map;
    std::string line;
    while (std::getline(infile, line)) {
        std::vector<char> row;
        for (auto c : line) {
            row.push_back(c);
        }
        map.push_back(std::move(row));
    }

    std::vector<P> starts;
    const P end{0, 0};
    
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (map[i][j] == 'a') {
                starts.push_back({i, j});
            }
            if (map[i][j] == 'E') {
                map[i][j] = 'z';
                end = {i, j};
            }
        }
    }
    auto in = [&](P pos) { return pos.x >= 0 && pos.x < map.size() && pos.y >= 0 && pos.y < map[0].size(); };
    int min = 1000000000;
    for (auto start : starts) {
        std::vector<std::pair<P, int>> heap = {{start, 0}};
        std::map<std::pair<P, P>, int> visited;
        while(!heap.empty()) {
            auto [current, depth] = heap.back();
            heap.pop_back();
            if (current == end && depth < min) {
                min = depth;
            }

            const std::array<P, 4> positions = {P{current.x - 1, current.y}, P{current.x + 1, current.y}, P{current.x, current.y - 1}, P{current.x, current.y + 1}};
            for (auto new_pos : positions) {
                if (in(new_pos)) {
                    if (visited.find(std::pair{current, new_pos}) != visited.end()) {
                        if (visited.at(std::pair{current, new_pos}) <= depth) {
                            continue;
                        }
                    }
                    visited[std::pair{current, new_pos}] = depth;
                    if (map[new_pos.x][new_pos.y] - map[current.x][current.y] <= 1) {
                        heap.push_back({new_pos, depth + 1});
                    }
                }
            }
        }
    }
    std::cout << "min steps = " << min;
}
