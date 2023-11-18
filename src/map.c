#include "map.h"

#include <stdlib.h>

void initialize_map(Map *map) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      map->tiles[y][x] = '#'; // Default to wall
    }
  }
  map->room_count = 0; // Reset room count
}

Room create_random_room() {
  Room room;

  room.width = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1) + ROOM_MIN_SIZE;
  room.height = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1) + ROOM_MIN_SIZE;

  // Ensure room fits within the map boundaries
  room.x = rand() % (MAP_WIDTH - room.width - 1) + 1;
  room.y = rand() % (MAP_HEIGHT - room.height - 1) + 1;

  return room;
}

// In map.c

bool place_room(Map *map, Room room) {
  // Check for overlap with existing rooms
  for (int i = 0; i < map->room_count; i++) {
    Room existing = map->rooms[i];
    if (!(room.x + room.width < existing.x ||
          room.x > existing.x + existing.width ||
          room.y + room.height < existing.y ||
          room.y > existing.y + existing.height)) {
      return false; // Room overlaps, cannot place
    }
  }

  // Place room
  for (int y = room.y; y < room.y + room.height; y++) {
    for (int x = room.x; x < room.x + room.width; x++) {
      map->tiles[y][x] = '.'; // Set floor
    }
  }

  // Add room to the map's room list
  map->rooms[map->room_count++] = room;
  return true;
}

void connect_rooms(Map *map, Room room1, Room room2) {
  // Find center points of each room
  int center1_x = room1.x + room1.width / 2;
  int center1_y = room1.y + room1.height / 2;
  int center2_x = room2.x + room2.width / 2;
  int center2_y = room2.y + room2.height / 2;

  // Draw horizontal corridor
  for (int x = min(center1_x, center2_x); x <= max(center1_x, center2_x); x++) {
    map->tiles[center1_y][x] = '.';
  }

  // Draw vertical corridor
  for (int y = min(center1_y, center2_y); y <= max(center1_y, center2_y); y++) {
    map->tiles[y][center2_x] = '.';
  }
}

void generate_map(Map *map) {
  initialize_map(map);
  while (map->room_count < MAX_ROOMS) {
    Room new_room = create_random_room();
    if (place_room(map, new_room)) {
      if (map->room_count > 1) {
        connect_rooms(map, map->rooms[map->room_count - 2], new_room);
      }
    }
  }
}
