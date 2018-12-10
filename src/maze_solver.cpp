#include "maze_solver.h"

void MazeSolver::Init() {
	map = &entity->GetComponent<Map>();
	maze_height = map->GetHeight();
	maze_width = map->GetWidth();
	std::cout << map->GetWidth();
	visit_arr = new bool *[maze_height];
	for (int i = 0; i < maze_height; i++) {
		visit_arr[i] = new bool[maze_width];
	}
	for (int i = 0; i < maze_height; i++) {
		for (int j = 0; j < maze_width; j++) {
			visit_arr[i][j] = false;
		}
	}
}
void MazeSolver::SolveMaze() {
	if (map->GetVal(1, 0) != 1) {
		if (RecursiveSolver(1, 0)) { map->ChangeVal(1, 0, 3); }
	}
	if (map->GetVal(0, 1) != 1) {
		if (RecursiveSolver(0, 1)) { map->ChangeVal(0, 1, 3); }
	}
}
bool MazeSolver::RecursiveSolver(int x, int y) {
	visit_arr[x][y] = true;
	if (map->GetVal(x, y) == 2) { return true; }

	if (x < maze_height - 1) {
		if (map->GetVal(x + 1, y) != 1 && visit_arr[x + 1][y] == false) {
			if (RecursiveSolver(x + 1, y)) {
				map->ChangeVal(x + 1, y, 3);
				return true;
			}
		}
	}
	if (x > 0) {
		if (map->GetVal(x - 1, y) != 1 && visit_arr[x - 1][y] == false) {
			if (RecursiveSolver(x - 1, y)) {
				map->ChangeVal(x - 1, y, 3);
				return true;
			}
		}
	}
	if (y > 0) {
		if (map->GetVal(x, y - 1) != 1 && visit_arr[x][y - 1] == false) {
			if (RecursiveSolver(x, y - 1)) {
				map->ChangeVal(x, y - 1, 3);
				return true;
			}
		}
	}
	if (y < maze_width - 1) {
		if (map->GetVal(x, y + 1) != 1 && visit_arr[x][y + 1] == false) {
			if (RecursiveSolver(x, y + 1)) {
				map->ChangeVal(x, y + 1, 3);
				return true;
			}
		}
	}
	return false;
}
