#include "bowling_frame.h"
#include <random>

std::random_device dev;
std::mt19937 rng(dev());

Bowling_Frame::Bowling_Frame(int fnum)
{
	score1_ = 0;
	score2_ = 0;
	score3_ = 0;
	strike_ = false;
	spare_ = false;
	frame_num_ = fnum;
	frame_score_ = 0;
	roll_one_ = false;
	roll_two_ = false;
	roll_three_ = false;

	next_frame_ = NULL;
	prev_frame_ = NULL;

}

Bowling_Frame::~Bowling_Frame()
{
 	//free(next_frame_);
	//free(prev_frame_);
}

Bowling_Frame* Bowling_Frame::next_frame() { return next_frame_; }
void Bowling_Frame::next_frame( Bowling_Frame * new_frame ) { next_frame_ = new_frame; }

Bowling_Frame* Bowling_Frame::prev_frame() { return prev_frame_; }
void Bowling_Frame::prev_frame( Bowling_Frame * new_frame ) { prev_frame_ = new_frame; }

int Bowling_Frame::score1()				{ return score1_; }
void Bowling_Frame::score1( int score )	{ score1_ = score; }

int Bowling_Frame::score2()				{ return score2_; }
void Bowling_Frame::score2( int score )	{ score2_ = score; }

int Bowling_Frame::score3()				{ return score3_; }

bool Bowling_Frame::strike() 			{ return strike_; }
void Bowling_Frame::strike(bool value )	{ strike_ = value; }

bool Bowling_Frame::spare() 			{ return spare_; }
void Bowling_Frame::spare(bool value )	{ spare_ = value; }

int Bowling_Frame::frame_num()
{
	return frame_num_;
}

int Bowling_Frame::frame_score()
{
	return frame_score_; 
}

void Bowling_Frame::calc_frame_score()
{
	frame_score_ = score1_ + score2_;

	//last frame has no bonus, just the extra roll
	if (!next_frame_) {
		frame_score_ += score3_;
		return;
	}

	//spare: bonus is the next roll
	if (spare_) frame_score_ += next_frame_->score1();
	//strike: bonus is the next two rolls
	else if (strike_) {
		frame_score_ += next_frame_->score1();
		//next frame was a strike too, so the second roll is in the frame after
		if (next_frame_->strike() && next_frame_->next_frame())
			frame_score_ += next_frame_->next_frame()->score1();
		else
			frame_score_ += next_frame_->score2();
	}
}

void Bowling_Frame::update_scores()
{
	std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10);
	bool last_frame = (next_frame_ == NULL);

	if (!roll_one_)
	{
		score1_ = dist10(rng);
		roll_one_ = true;

		if(score1_ == 10) {
		    strike_ = true;
		    //strike ends the frame unless it is the last frame
		    if (!last_frame) roll_two_ = true;
		}
	}
	else if (!roll_two_)
	{
		//pins are reset after a strike in the last frame
		int pins = strike_ ? 10 : 10 - score1_;
		std::uniform_int_distribution<std::mt19937::result_type> distX(0, pins);
		score2_ = distX(rng);
		roll_two_ = true;

		if (!strike_ && (score1_ + score2_) == 10) spare_ = true;

		//last frame only gets a third roll after a strike or spare
		if (last_frame && !strike_ && !spare_) roll_three_ = true;
	}
	else if (last_frame && !roll_three_)
	{
		//pins are reset after a spare, or after two strikes
		int pins = (spare_ || score2_ == 10) ? 10 : 10 - score2_;
		std::uniform_int_distribution<std::mt19937::result_type> distX(0, pins);
		score3_ = distX(rng);
		roll_three_ = true;
	}
	else
	{
		if (next_frame_) next_frame_->update_scores();
		return;
	}

	//a new roll can change the bonus of this frame and the two before it
	calc_frame_score();
	if (prev_frame_) {
		prev_frame_->calc_frame_score();
		if (prev_frame_->prev_frame()) prev_frame_->prev_frame()->calc_frame_score();
	}
}
