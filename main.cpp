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
	int temp_total = 0;
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
    std::cerr << "Pass number of players as an arugment" << std::endl;
    return 1;
    }

    //general error handling
    if (std::stoi(args[1]) < 1){
    std::cerr << "Please put in a sensical number of players" << std::endl;
    return 1;
    }

    //get playercount + convert arg to int
    int playerCount = std::stoi(args[1]);

	//make frames
		Bowling_Frame * f1 = new Bowling_Frame(1);
	Bowling_Frame * f2 = new Bowling_Frame(2);
	Bowling_Frame * f3 = new Bowling_Frame(3);
	Bowling_Frame * f4 = new Bowling_Frame(4);
	Bowling_Frame * f5 = new Bowling_Frame(5);
	Bowling_Frame * f6 = new Bowling_Frame(6);
	Bowling_Frame * f7 = new Bowling_Frame(7);
	Bowling_Frame * f8 = new Bowling_Frame(8);
	Bowling_Frame * f9 = new Bowling_Frame(9);
	Bowling_Frame * f10 = new Bowling_Frame(10);

	//link frames together
	f1->next_frame(f2);
	f2->prev_frame(f1);
	f2->next_frame(f3);
	f3->prev_frame(f2);
	f3->next_frame(f4);
	f4->prev_frame(f3);
	f4->next_frame(f5);
	f5->prev_frame(f4);
	f5->next_frame(f6);
	f6->prev_frame(f5);
	f6->next_frame(f7);
	f7->prev_frame(f6);
	f7->next_frame(f8);
	f8->prev_frame(f7);
	f8->next_frame(f9);
	f9->prev_frame(f8);
	f9->next_frame(f10);
	f10->prev_frame(f9);

	//set frame scores	
	f1->update_scores();
	f1->update_scores();
	cout << "Frame 1 Total: " << current_game_total(f1) << endl;

	f1->update_scores();
	f1->update_scores();
	cout << "Frame 1 and 2 Total: " << current_game_total(f1) << endl;


	f1->update_scores();
	f1->update_scores();
	cout << "Frame 1,2,and 3 Total: " << current_game_total(f1) << endl;

	//print values
	cout << "Frame " << f1->frame_num() << ": " << endl
		 << " Score 1: " << f1->score1() << endl
		 << " Score 2: " << f1->score2() << endl;

	cout << "Frame " << f2->frame_num() << ": " << endl
	     << " Score 1: " << f2->score1() << endl
		 << " Score 2: " << f2->score2() << endl;

	cout << "Frame " << f3->frame_num() << ": " << endl
	     << " Score 1: " << f3->score1() << endl
		 << " Score 2: " << f3->score2() << endl;

	//iterate through linked list and print values
	Bowling_Frame * traverse = f1;
	
	while(traverse)
	{
		cout << "Frame " << traverse->frame_num() << ": " << endl
		 	 << " Score 1: " << traverse->score1() << endl
		 	 << " Score 2: " << traverse->score2() << endl;

		traverse = traverse->next_frame();
	}

}
