#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TARGETS 10000

typedef struct {
    int x, y;
} Point;

Point targets[MAX_TARGETS];
int target_count = 0;

// Чтение координат из файла
int read_targets(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    while (fscanf(file, "%d,%d", &targets[target_count].x, &targets[target_count].y) == 2) {
        target_count++;
        if (target_count >= MAX_TARGETS) break;
    }

    fclose(file);
    return 1;
}

// Проверка попадания точки в круг
int is_inside_circle(int cx, int cy, int tx, int ty, int radius) {
    int dx = cx - tx;
    int dy = cy - ty;
    return dx * dx + dy * dy <= radius * radius;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <radius>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int radius = atoi(argv[2]);

    if (!read_targets(filename)) {
        printf("Failed to read target file: %s\n", filename);
        return 1;
    }

    int max_hit = 0;
    int best_x = 0, best_y = 0;

    // Поиск на всей сетке 100x100
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            int count = 0;
            for (int i = 0; i < target_count; i++) {
                if (is_inside_circle(x, y, targets[i].x, targets[i].y, radius)) {
                    count++;
                }
            }
            if (count > max_hit) {
                max_hit = count;
                best_x = x;
                best_y = y;
            }
        }
    }

    printf("Launch coordinates: %d,%d\n", best_x, best_y);
    printf("Targets hit: %d\n", max_hit);

    return 0;
}
