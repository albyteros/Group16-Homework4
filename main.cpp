
#include <iostream>
#include "bowling_frame.h"
#include <random>

using namespace std;

std::random_device dev_main;
std::mt19937 rng_main(dev_main());

int current_game_total(Bowling_Frame * first_frame)
{
    Bowling_Frame * temp = first_frame;
    int game_total = 0;
    while(temp)
    {
        game_total += temp->frame_score();
        temp = temp->next_frame();
    }
    return game_total;
}

int main(int argcount, char* args[])
{
    //check therrrrre arrrre arrrrgs
    if (argcount != 2){
        std::cerr << "Pass number of players as an argument" << std::endl;
        return 1;
    }

    //get playercount + convert arg to int
    int playerCount = 0;
    try {
        playerCount = std::stoi(args[1]);
    } catch (...) {
        std::cerr << "Number of players must be a number" << std::endl;
        return 1;
    }

    //general error handling
    if (playerCount < 1){
        std::cerr << "Please put in a sensical number of players" << std::endl;
        return 1;
    }
    Bowling_Frame** players = new Bowling_Frame*[playerCount]; // create array of pointers

    // for each player, create 10 frames and link them together
    for (int i = 0; i < playerCount; i++) {
        players[i] = new Bowling_Frame(1); // makes first frame and stores its pointer in the array

        Bowling_Frame* current = players[i]; // temporary pointer to the current frame

        for (int j = 2; j <= 10; j++) {
            // create a new frame and doubly link it
            Bowling_Frame* newFrame = new Bowling_Frame(j);
            current->next_frame(newFrame);
            newFrame->prev_frame(current);
            current = newFrame;
        }
    }

    cout << "Player count is: " << playerCount << endl;

    //set frame scores
    for (int i = 0; i < playerCount; i++) {
        Bowling_Frame* curr = players[i];

        // simulate up to 21 rolls for each player
        for (int j = 0; j < 21; j++) {
            curr->update_scores();
        }
    }

    //iterate through linked list and print values
    for (int i = 0; i < playerCount; i++) {
        Bowling_Frame * traverse = players[i];

        while (traverse != nullptr)	 {
            cout << "Frame " << traverse->frame_num() << ":" << endl
                 << " Score 1: " << traverse->score1() << endl
                 << " Score 2: " << traverse->score2() << endl;

            //last frame gets a third roll after a strike or spare
            if (!traverse->next_frame() && (traverse->strike() || traverse->spare()))
                cout << " Score 3: " << traverse->score3() << endl;

            traverse = traverse->next_frame();
        }

        cout << endl << "Total Game Score for player " << i + 1 << ": "
             << current_game_total(players[i]) << endl << endl;
    }
	// for both players, delete the allocated bowling frames and free the memory used by the array
    for (int i = 0; i < playerCount; i++) {
        Bowling_Frame* current = players[i];
        while (current) {
            Bowling_Frame* next = current->next_frame();
            delete current;
            current = next;
        }
    }
    delete[] players;

    return 0;
}
