#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 80
#define MAP_HEIGHT 24

typedef struct {
  char tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

void draw_map(const Map *map);
void map_setup(void);

#endif // MAP_H
