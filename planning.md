Icons:



## Plan:
  - Dungeon crawler roguelike
  - Random procedural room generation
  - Fight monsters
  - Levels beaten by escaping each level/dungeon
  - Chests and loot
  - Health and armor bar on top
  - Story/dialogue

  If I have time:
  - Classes (mana for a mage class, maybe?)
  - 

## Suggestions:
   - I should maybe try handling the user inputs in a function, if I can figure
    that out.
   - Going off that previous suggestion, I just need to make the main function
    cleaner overall
  - Should probably add more documentation (doc comment for each file, maybe?)


## TODO:
   - FIX MULTIPLE DEFINITIONS OF PLAYER_SETUP AND MAP_SETUP
   - Get the player '@' rendered to the screen
   - Create screen borders
   - Get basic rendering and movement functionality implemented
   - Create a splash screen, and get it working
   - Get procedural room generation working
     - Ensure that the map is random each time it's generated
     - Ensure that the player spawns on a valid "floor" tile
     - Place an exit somewhere on the map
     - Generate a new level once the player reaches the exit
     - Populate the rooms with chests and stuff (placeholders for now)
   - Get pausing to work 
   - Prompt the user if they're sure they want to quit
   - Turn the input handler code into a function for cleanliness
   - Turn the initial game rendering code (that super dense code block) into a 
   function as well.
  - Get combat working


### From the project instructions PDF:
  Milestone 1:
     - Question 1: Make a group
     - Question 2: Create project structure
     - Question 3: Develop game idea
     - Question 4: Create main function and file
     - Question 5: Create a splash screen
     - Question 6: Code levels (I will generate them procedurally)

  Milestone 2:
    - Player movement (already done)
    - Pausing
    - Quit prompt (are you sure you want to quit?)
    - Make some more interactable stuff, or things that affect the map
