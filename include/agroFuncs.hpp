#include <string>

// Function Headers

/// @brief Initializes a new folder for storing files
void init();

/// @brief Initializes a git repository in the current folder
void initGit();

/// @brief Checks to see if the user has a .agro folder in their home directory
void checkDotFolder();

/// @brief Displays a message and prompts the user for a response
/// @param buff Buffer to store the response 
/// @param message Message to display to the user
void prompt(std::string& buff, const char* message);

/// @brief Displays a message and prompts the user for a response
/// @param message Message to display to the user
/// @return Users response
std::string prompt(const char* message);

/// @brief Displays the help message
void help();

/// @brief Displays the version of the program
void version();

/// @brief Adds a folder to the agro
/// @param agroName Name of the agro to add the folder to
/// @param folderPath Path to the folder to add
void add(std::string agroName, std::string folderPath);

/// @brief Removes a folder from the agro if it exists
/// @param agro Name of the agro to remove the folder from
/// @param folderPath Path to the folder to remove
void remove(std::string agro, std::string folderPath);

/// @brief Lists all of the agros that the user has
/// @param agro Name of the agro to list
void list(std::string agro);

/// @brief Updates the agro with the latest files
/// @param agro Name of the agro to update
void update(std::string agro);

/// @brief Pushes the agro to the git repository
/// @param agro Name of the agro to push
void push(std::string agro);

/// @brief Pulls the agro from the git repository
/// @param agro Name of the agro to pull
void pull(std::string agro);

/// @brief Searches the agro list for a specific agro
/// @param agro Name of the agro to search for
/// @return Returns true if the agro exists
bool searchAgro(std::string agro);

/// @brief Checks to see if the agro .include file includes a specific folder
/// @param agro Name of the agro to search
/// @return Returns true if the agro includes the folder
bool searchAgroIncludes(std::string agro);

/// @brief Gets the path to the agro
/// @param agro Name of the agro to get the path for
std::string getAgroPath(std::string agro);