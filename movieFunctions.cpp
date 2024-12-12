/******************************************************************************

Names: Alecxander Cooper
Date: 10/29/2024
Class: CISP 360

Version: 1.002

*******************************************************************************/
#include "movieHeader.h"

void movieMain() {
    movieStruct* movie = new movieStruct[NUM_OF_MOVIES]; // Dynamically allocate memory for movie array
    char userInput;
    int mid;
    std::string fileName = "MovieData.txt";
    std::ifstream inFile;

    // runs through the program once, checks if quit was entered,
    // if not, keep running
    do {
        displayMovieMenu(); // menu text
        std::cin >> userInput;
        userInput = toupper(userInput);

        openFile(fileName, inFile); // opens the file
        readMoviesFromFile(inFile, movie); // stores data in the movie struct
        selectionSort(movie, NUM_OF_MOVIES); // sorts the movies by year

        switch(userInput) {
        case 'D': // display movies
            // Output the movie data
            for (int i = 0; i < 6; ++i) {
                std::cout << std::left << std::setw(30) << movie[i].title
                          << std::setw(10) << movie[i].releaseYear
                          << std::setw(24) << movie[i].director
                          << std::setw(18) << movie[i].genre
                          << std::setw(12) << movie[i].leadActor
                          << std::setw(12) << movie[i].coActor  << "\n";
            }
            break;
        case 'S': // search a specific movie
            mid = binarySearchMovieYear(movie, NUM_OF_MOVIES);
            std::cout << "Movie found at index " << mid << "\n";
            break;
        case 'Q':
            std::cout << "Quitting...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }

    } while (userInput != 'q' && userInput != 'Q');

    delete[] movie; // Free dynamically allocated memory
}

// menu
void displayMovieMenu() {
    std::cout << "\n*********************\n";
    std::cout << " Movie Selector Menu\n";
    std::cout << "*********************\n";
    std::cout << "Display Available Movies  :D\n";
    std::cout << "Search a Movie by Year    :S\n";
    std::cout << "Quit                      :Q\n";
    std::cout << "Enter your choice: ";
}

// function to open the movies file
void openFile(std::string& fileName, std::ifstream& inFile) {
    inFile.open(fileName); // opens movie.txt
    if (!inFile) { // check if the file opened successfully
        std::cerr << "Issue opening file: " << fileName << "\n";
    }
}

int readMoviesFromFile(std::ifstream& inFile, movieStruct* movies) { // points to location in memory
    int count = 0;
    std::string line;

    while (std::getline(inFile, line) && count < 6) {
        std::stringstream storeVariables(line);


        //already pointed at the memory so I do not have to define in the function
        movieStruct movie;

        std::getline(storeVariables, movie.title, ',');
        storeVariables >> movie.releaseYear; 
        storeVariables.ignore();
        std::getline(storeVariables, movie.director, ',');
        std::getline(storeVariables, movie.genre, ',');
        std::getline(storeVariables, movie.leadActor, ',');
        std::getline(storeVariables, movie.coActor, ',');

        movies[count] = movie; // Store the movie in the array
        count++; // Increment count
    }

    inFile.close(); // Close the file after reading
    return count; // Return the number of movies read
}

// user will give the year of the movie they want to see, this function will go
// through the array movie year and compare each instance to the user input
int binarySearchMovieYear(movieStruct* movie, int NUM_OF_MOVIES) {
    int userMovieYear;
    std::cout << "What is the year of the movie you want to see?: ";
    std::cin >> userMovieYear;

    int left = 0;
    int right = NUM_OF_MOVIES - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if the target is at the middle
        if (movie[mid].releaseYear == userMovieYear) {
            return mid; // Target found, return the index
        }

        // If target is greater, ignore the left half
        if (movie[mid].releaseYear < userMovieYear) {
            left = mid + 1;
        }
        // If target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    // Target not found
    return -1;
}


// sorts the years from decending to accending.
void selectionSort(movieStruct* movie, int NUM_OF_MOVIES) {
    for (int i = 0; i < NUM_OF_MOVIES - 1; i++) { // sets min index to the number of times its ran through
        int minIndex = i;

        // each interation, compare all the years of the movies to eachother
        for (int j = i + 1; j < NUM_OF_MOVIES; j++) {
            if (movie[j].releaseYear < movie[minIndex].releaseYear) {
                minIndex = j;
            }
        }
        
        // if the number is smaller than the one it started at.
        // Swap the found smallest element with the element at the current position
        if (minIndex != i) {
            int temp = movie[i].releaseYear;
            movie[i].releaseYear = movie[minIndex].releaseYear;
            movie[minIndex].releaseYear = temp;
        }
    }
}
