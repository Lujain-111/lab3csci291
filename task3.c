#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define NUM_TEAMS 6          // Maximum number of teams
#define SQUAD_SIZE 20        // Maximum number of players per team

// Structure to store player details
typedef struct {
    char name[26];            // Player's full name
    int kit_number;           // Player's kit number
    char club[30];            // Club to which the player belongs
    struct {                  // Player's birthdate
        int day;
        int month;
        int year;
    } birthdate;
    char position[20];        // Player's position
} player_t;

// Structure to store team details
typedef struct {
    char name[21];            // Team's name
    player_t players[SQUAD_SIZE];  // Array of players in the team
    int active_size;          // Number of active players in the team
} team_t;

// Array of teams
team_t teams[NUM_TEAMS];
// Variable to track the number of teams enrolled
int team_count = 0;

// Function declarations
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void clear_input_buffer();
bool validate_string_input(const char input[]);
bool validate_club_name(const char input[]);
bool validate_birthdate(int day, int month, int year);
void handle_error(char message[]);

int main() {
    int choice;

    while (1) {
        // Display menu and prompt user for input
        display_menu();
        
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            handle_error("Invalid input! Please enter an integer.");
            clear_input_buffer();
            continue;
        }

        // Handle user selection based on input
        switch (choice) {
            case 1:
                enroll_club();      // Enroll a new club
                break;
            case 2:
                add_player();       // Add a new player to a team
                break;
            case 3:
                search_update();    // Search and update player details
                break;
            case 4:
                display_club_statistics(); // Display statistics of all clubs
                break;
            case 0:
                printf("Exiting program.\n");
                return 0;  // Exit the program
            default:
                handle_error("Invalid choice. Please try again.");
        }
    }
}

// Function to clear the input buffer to prevent input issues
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to display the menu options to the user
void display_menu() {
    printf("\nMenu:\n");
    printf("1. Enroll Club\n");
    printf("2. Add Player\n");
    printf("3. Search and Update Player\n");
    printf("4. Display Club Statistics\n");
    printf("0. Exit\n");
}

// Function to handle error messages
void handle_error(char message[]) {
    printf("Error: %s\n", message);
}

// Function to validate if a string has any alphabetic characters
bool validate_string_input(const char input[]) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {  // Check for alphabetic characters
            return true;
        }
    }
    return false;
}

// Function to validate the player's birthdate
bool validate_birthdate(int day, int month, int year) {
    if (year < 1900 || year > 2023) return false; // Check for reasonable year
    if (month < 1 || month > 12) return false;     // Check for valid month
    if (day < 1 || day > 31) return false;         // Check for valid day

    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

    // Check for February with 28 days
    if (month == 2 && day > 28) return false;

    return true;  // If all checks passed, birthdate is valid
}

// Function to enroll a new club
void enroll_club() {
    if (team_count >= NUM_TEAMS) {
        handle_error("Maximum number of teams reached.");
        return;
    }

    printf("Enter team name: ");
    clear_input_buffer();
    if (fgets(teams[team_count].name, sizeof(teams[team_count].name), stdin) == NULL || 
        !validate_string_input(teams[team_count].name)) {
        handle_error("Invalid team name. Please try again.");
        return;
    }

    // Remove newline character from the input
    teams[team_count].name[strcspn(teams[team_count].name, "\n")] = '\0';
    teams[team_count].active_size = 0;  // No players initially
    printf("Club '%s' enrolled successfully.\n", teams[team_count].name);

    team_count++;  // Increase the count of teams
}

// Function to add a player to an existing team
void add_player() {
    if (team_count == 0) {
        handle_error("No teams are enrolled.");
        return;
    }

    // List all available teams
    printf("Available teams:\n");
    for (int i = 0; i < team_count; i++) {
        printf("  %d: %s\n", i, teams[i].name);
    }

    int team_index;
    printf("Select a team (0 to %d): ", team_count - 1);

    // Validate team selection
    while (scanf("%d", &team_index) != 1 || team_index < 0 || team_index >= team_count) {
        handle_error("Invalid team selection. Please enter a valid team number.");
        clear_input_buffer();
        printf("Select a team (0 to %d): ", team_count - 1);
    }

    // Check if the team is full
    if (teams[team_index].active_size >= SQUAD_SIZE) {
        handle_error("This team is at full capacity.");
        return;
    }

    player_t new_player;
    clear_input_buffer();

    // Get player's name
    printf("Enter player's full name: ");
    fgets(new_player.name, sizeof(new_player.name), stdin);
    new_player.name[strcspn(new_player.name, "\n")] = '\0';

    // Check for duplicate player name
    for (int i = 0; i < teams[team_index].active_size; i++) {
        if (strcasecmp(teams[team_index].players[i].name, new_player.name) == 0) {
            handle_error("Duplicate player name. This name is already in the team.");
            return;
        }
    }

    // Get kit number
    printf("Enter kit number (1-99): ");
    while (scanf("%d", &new_player.kit_number) != 1 || new_player.kit_number < 1 || new_player.kit_number > 99) {
        handle_error("Invalid kit number! Please enter a number between 1 and 99.");
        clear_input_buffer();
        printf("Enter kit number (1-99): ");
    }

    // Check for duplicate kit number
    for (int i = 0; i < teams[team_index].active_size; i++) {
        if (teams[team_index].players[i].kit_number == new_player.kit_number) {
            handle_error("Kit number already taken. Please choose another number.");
            return;
        }
    }

    // Get club name
    printf("Enter club name: ");
    clear_input_buffer();
    fgets(new_player.club, sizeof(new_player.club), stdin);
    new_player.club[strcspn(new_player.club, "\n")] = '\0';

    // Get and validate birthdate
    printf("Enter birthdate (day month year): ");
    while (scanf("%d %d %d", &new_player.birthdate.day, &new_player.birthdate.month, &new_player.birthdate.year) != 3 ||
           !validate_birthdate(new_player.birthdate.day, new_player.birthdate.month, new_player.birthdate.year)) {
        handle_error("Invalid birthdate! Please enter a valid date in format: day month year.");
        clear_input_buffer();
        printf("Enter birthdate (day month year): ");
    }

    // Get player's position
    printf("Enter position: ");
    clear_input_buffer();
    fgets(new_player.position, sizeof(new_player.position), stdin);
    new_player.position[strcspn(new_player.position, "\n")] = '\0';

    // Add the new player to the team
    teams[team_index].players[teams[team_index].active_size++] = new_player;
    printf("Player added successfully to team %s.\n", teams[team_index].name);
}

// Function to search and update player details
void search_update() {
    if (team_count == 0) {
        handle_error("No teams are enrolled.");
        return;
    }

    // Loop to allow multiple searches
    while (1) {
        printf("All teams and members:\n");
        for (int i = 0; i < team_count; i++) {
            printf("Team %s:\n", teams[i].name);
            for (int j = 0; j < teams[i].active_size; j++) {
                printf("  Player %d: %s, Kit Number: %d, Position: %s, Club: %s\n",
                       j+1, teams[i].players[j].name, teams[i].players[j].kit_number,
                       teams[i].players[j].position, teams[i].players[j].club);
            }
        }

        char player_name[26];
        printf("Enter player name to search (or type 'exit' to stop): ");
        clear_input_buffer();
        fgets(player_name, sizeof(player_name), stdin);
        player_name[strcspn(player_name, "\n")] = '\0';

        if (strcasecmp(player_name, "exit") == 0) {
            break;  // Exit the search
        }

        // Search for player
        bool found = false;
        for (int i = 0; i < team_count; i++) {
            for (int j = 0; j < teams[i].active_size; j++) {
                if (strcasecmp(teams[i].players[j].name, player_name) == 0) {
                    found = true;
                    printf("Player found: %s, Kit Number: %d, Position: %s, Club: %s\n",
                           teams[i].players[j].name, teams[i].players[j].kit_number,
                           teams[i].players[j].position, teams[i].players[j].club);
                    // Update functionality can be added here
                    break;
                }
            }
            if (found) break;
        }

        if (!found) {
            handle_error("Player not found.");
        }
    }
}

// Function to display club statistics
void display_club_statistics() {
    printf("\nClub Statistics:\n");
    for (int i = 0; i < team_count; i++) {
        printf("Team %s has %d players.\n", teams[i].name, teams[i].active_size);
    }
}
