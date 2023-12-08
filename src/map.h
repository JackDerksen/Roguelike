#ifndef MAP_H
#define MAP_H

#include "setup.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROOM_MIN_SIZE 5
#define ROOM_MAX_SIZE 15
#define MAP_WIDTH 80
#define MAP_HEIGHT 25
#define MAX_ROOMS 15
#define MAX_CHESTS 5

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define CUSTOM_ABS(x) ((x) < 0 ? -(x) : (x))

/**
 * @brief Structure representing a room in the game.
 */
typedef struct {
  int x, y;          ///< X and Y coordinates of the room's top-left corner.
  int width, height; ///< Width and height of the room.
} Room;

/**
 * @brief Structure representing the game map.
 */
typedef struct {
  char tiles[MAP_HEIGHT][MAP_WIDTH]; ///< 2D array of map tiles.
  Room rooms[MAX_ROOMS];             ///< Array of rooms on the map.
  int room_count;                    ///< Number of rooms on the map.
} Map;

/**
 * @brief Initializes the map with default values.
 * @param map Pointer to the Map structure to initialize.
 */
void initialize_map(Map *map);

/**
 * @brief Creates a random room within the map's size constraints.
 * @return The randomly created Room.
 */
Room create_random_room();

/**
 * @brief Attempts to place a room on the map without overlapping.
 * @param map Pointer to the Map structure.
 * @param room The Room to be placed.
 * @return True if room is successfully placed, false otherwise.
 */
bool place_room(Map *map, Room room);

/**
 * @brief Connects two rooms with a corridor.
 * @param map Pointer to the Map structure.
 * @param room1 The first Room to connect.
 * @param room2 The second Room to connect.
 */
void connect_rooms(Map *map, Room room1, Room room2);

/**
 * @brief Generates the entire map with rooms and corridors.
 * @param map Pointer to the Map structure to be generated.
 */
void generate_map(Map *map);

/**
 * @brief Renders the map to the screen.
 * @param map Pointer to the constant Map structure to render.
 */
void render_map(const Map *map);

/**
 * @brief Clears the dialogue area on the game screen.
 */
void clear_dialogue(void);

#endif // MAP_H
