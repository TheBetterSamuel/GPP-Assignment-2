#include "level.h"

const void Level::loadData(string filePath) {
	ifstream data(filePath);

	if (data.is_open()) {
		for (string row_line; getline(data, row_line);) {
			map.emplace_back();
			istringstream row_stream(row_line);
			for (string column; getline(row_stream, column, ',');)
				map.back().push_back(column);
		}
	}
	return;
}

const void Level::clearMap() {
	map.clear();
}