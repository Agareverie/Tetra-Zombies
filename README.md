## PlantCLI v0.1 (Beta)

**Overview:**
PlantCLI is a command-line interface (CLI) based game inspired by "Plants vs. Zombies." In this initial beta release, you can plant various static plants in a lawn grid. The focus is on setting up the basic interface and multithreading to increment the sun count over time.

PlantCLI can also be seen as a sequel to Python vs Zombies, a similar project written in Python.

The library used, Tetra, is a namespace alias for the C++ standard library (Ex. te::Time::time() = std::chrono::high_resolution_clock_now()), it's a WIP.

**Features:**
- Basic CLI interface with a menu to select different plants.
- Multithreading to update the sun count every 5 seconds.
- Ability to navigate the lawn and plant different types of plants.
- Options to swap escape roots and use a shovel to remove plants.
- Sun count display updates in real-time.

**How to Play:**
1. Run the CLI interface.
2. Use the arrow keys to navigate through the menu and lawn.
3. Select plants and place them on the lawn.
4. Watch the sun count increase over time.
5. Use the shovel option to remove plants if needed.
6. Press 'ESC' to exit the game.

**Known Limitations:**
- No zombie entities are present yet; the plants are static.
- The interface may require further refinements for smoother user experience.
- Initializing the lawn and managing threads can be further optimized.

**Future Plans:**
- Adding dynamic elements such as zombies and interactions between plants and zombies.
- Improving the user interface and adding more plant types.
- Optimizing the threading model and exploring asynchronous options.

**Credits:**
Developed by Agari (Agareverie).

Feel free to report any bugs or provide feedback to help improve the game!


