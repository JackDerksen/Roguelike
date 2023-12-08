#include "map.h"
#include "orc.h"
#include "setup.h"

/*
I'm basically generating my maps by creating a big rectangle of wall tiles
and then "digging out" the rooms and the tunnels that connect them.
Procedural map generation felt like a more fun approach to me than simply
hard-coding my map layouts. This will also obviously keep things feeling
fresh when I play the game over and over again for testing :)
*/

/**
 * @brief Initializes the map with wall tiles.
 *
 * This function fills the entire map with wall tiles ('#') and resets the room
 * count to zero. It serves as the starting point for the procedural map
 * generation process.
 *
 * @param map Pointer to the Map structure that will be initialized.
 */
void initialize_map(Map *map) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      map->tiles[y][x] = '#'; // Default to a wall tile
    }
  }
  map->room_count = 0; // Reset room count
}

/**
 * @brief Creates a random room within specified size constraints.
 *
 * Generates a room with random dimensions, ensuring the room's size is within
 * the defined minimum and maximum size constraints. Also ensures that the room
 * fits within the map boundaries.
 *
 * @return Room structure containing the dimensions and position of the newly
 * created room.
 */
Room create_random_room(void) {
  Room room;

  room.width = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1) + ROOM_MIN_SIZE;
  room.height = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1) + ROOM_MIN_SIZE;

  // Ensure room fits within the map boundaries
  room.x = rand() % (MAP_WIDTH - room.width - 1) + 1;
  room.y = rand() % (MAP_HEIGHT - room.height - 1) + 1;

  return room;
}

/**
 * @brief Attempts to place a room on the map.
 *
 * Places a room on the map if it doesn't overlap with existing rooms. If the
 * room can be placed, it updates the map structure with the room's tiles and
 * adds the room to the map's list of rooms.
 *
 * @param map Pointer to the Map structure where the room will be placed.
 * @param room The Room structure to be placed on the map.
 * @return True if the room was placed successfully, false if it overlaps with
 * existing rooms.
 */
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

/**
 * @brief Connects two rooms with a passage.
 *
 * Creates a passage between two rooms by setting a path of floor tiles between
 * their center points. This function is used to ensure that all rooms are
 * accessible in the generated map.
 *
 * @param map Pointer to the Map structure on which the rooms are located.
 * @param room1 The first Room structure to be connected.
 * @param room2 The second Room structure to be connected.
 */
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

/**
 * @brief Generates the entire game map with rooms, passages, an exit, and
 * chests.
 *
 * This function generates the game map by repeatedly creating and placing rooms
 * until the maximum number of rooms is reached. It connects these rooms with
 * passages and then randomly places an exit and a set number of chests within
 * the rooms.
 *
 * @param map Pointer to the Map structure where the map will be generated.
 */
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

  // Place an exit in a random room
  if (map->room_count > 0) {
    int random_room_index = rand() % map->room_count;
    Room exit_room = map->rooms[random_room_index];
    int exit_x = rand() % exit_room.width + exit_room.x;
    int exit_y = rand() % exit_room.height + exit_room.y;
    map->tiles[exit_y][exit_x] = 'E';
  }

  // Populate the rooms with chests
  int chests_placed = 0;
  while (chests_placed < MAX_CHESTS && chests_placed < map->room_count) {
    int random_room_index = rand() % map->room_count;
    Room chest_room = map->rooms[random_room_index];
    int chest_x = rand() % chest_room.width + chest_room.x;
    int chest_y = rand() % chest_room.height + chest_room.y;

    // Make sure the spot isn't taken by something else
    if (map->tiles[chest_y][chest_x] == '.') {
      map->tiles[chest_y][chest_x] = 'C';
      chests_placed++;
    }
  }
}

/**
 * @brief Renders the game map to the screen.
 *
 * Iterates over each tile of the map and displays it using the appropriate
 * character and color. It also checks for orcs at each position and renders
 * them if present. This function is responsible for visually representing the
 * game world to the player.
 *
 * @param map Pointer to the constant Map structure that is to be rendered.
 */
void render_map(const Map *map) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      char display_char = map->tiles[y][x];

      // Check for orc at this position
      for (int i = 0; i < num_orcs; i++) {
        if (orcs[i].is_alive) {
          if (orcs[i].x == x && orcs[i].y == y) {
            display_char = 'O';
            break;
          }
        }
      }

      if (display_char == '#') {
        attron(COLOR_PAIR(COLOR_PAIR_WALLS));
        mvprintw(y, x, "#");
        attroff(COLOR_PAIR(COLOR_PAIR_WALLS));
      } else if (display_char == '.') {
        attron(COLOR_PAIR(COLOR_PAIR_FLOORS));
        mvprintw(y, x, ".");
        attroff(COLOR_PAIR(COLOR_PAIR_FLOORS));
      } else if (display_char == 'E') {
        attron(COLOR_PAIR(COLOR_PAIR_EXIT));
        mvprintw(y, x, "E");
        attroff(COLOR_PAIR(COLOR_PAIR_EXIT));
      } else if (display_char == 'C') {
        attron(COLOR_PAIR(COLOR_PAIR_CHEST));
        mvprintw(y, x, "C");
        attroff(COLOR_PAIR(COLOR_PAIR_CHEST));
      } else if (display_char == 'O') {
        attron(COLOR_PAIR(COLOR_PAIR_ORC));
        mvprintw(y, x, "O");
        attroff(COLOR_PAIR(COLOR_PAIR_ORC));
      }
    }
  }
}

/**
 * @brief Clears the dialogue area of the game screen.
 *
 * Moves the cursor to the start of the dialogue area and clears it. This
 * function is used to ensure that old messages are not left on the screen when
 * new messages are displayed.
 */
void clear_dialogue(void) {
  move(MAP_HEIGHT, 2);
  clrtoeol();
}
