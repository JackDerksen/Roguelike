#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 40
#define MAX_ROOMS 20

// Room structure
typedef struct {
  int x, y;          // Top-left corner coordinates of the room
  int width, height; // Dimensions of the room
} Room;

// Map structure
typedef struct {
  char tiles[MAP_HEIGHT][MAP_WIDTH];
  Room rooms[MAX_ROOMS];
  int room_count;
} Map;

// Utility macros
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// Function prototypes
void initialize_map(Map *map);
Room create_random_room();
bool place_room(Map *map, Room room);
void connect_rooms(Map *map, Room room1, Room room2);
void generate_map(Map *map);

#endif // MAP_H
