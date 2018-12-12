#pragma once
#include "maze_solver.h"

void MazeSolver::Init() {
	map = &entity->GetComponent<Map>();
	maze_height = map->GetHeight();
	maze_width = map->GetWidth();
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
	map->ChangeVal(maze_height - 1, maze_width - 1, 2);
}

bool MazeSolver::RecursiveSolver(int col, int row) {
	visit_arr[col][row] = true;
	if (map->GetVal(col, row) == 2) { return true; }

	if (col < maze_height - 1) {
		if (map->GetVal(col + 1, row) != 1 && visit_arr[col + 1][row] == false) {
			if (RecursiveSolver(col + 1, row)) {
				map->ChangeVal(col + 1, row, 3);
				return true;
			}
		}
	}
	if (col > 0) {
		if (map->GetVal(col - 1, row) != 1 && visit_arr[col - 1][row] == false) {
			if (RecursiveSolver(col - 1, row)) {
				map->ChangeVal(col - 1, row, 3);
				return true;
			}
		}
	}
	if (row > 0) {
		if (map->GetVal(col, row - 1) != 1 && visit_arr[col][row - 1] == false) {
			if (RecursiveSolver(col, row - 1)) {
				map->ChangeVal(col, row - 1, 3);
				return true;
			}
		}
	}
	if (row < maze_width - 1) {
		if (map->GetVal(col, row + 1) != 1 && visit_arr[col][row + 1] == false) {
			if (RecursiveSolver(col, row + 1)) {
				map->ChangeVal(col, row + 1, 3);
				return true;
			}
		}
	}
	return false;
}
