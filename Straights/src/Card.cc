#include "Card.h"
#include <string>
#include <cassert>

using std::ostream;
using std::istream;
using std::string;

Card::Card(Card::Rank r, Card::Suit s) : suit_(s), rank_(r) {}

string Card::suits = "CDHS";
string Card::ranks = "A23456789TJQK";


Card::Suit Card::suit() const
{
	return suit_;
}

bool Card::Suit::operator==(const Card::Suit& s) const
{
	return suit_ == s.suit();
}

Card::Suit::operator int() const { return suit_; }

std::string Card::Suit::toString() const
{
	switch (suit_) 
	{
		case 0:
			return "Clubs";
		case 1:
			return "Diamonds";
		case 2:
			return "Hearts";
		case 3:
			return "Spades";
		default:
			return "Error";
	}
}

Card::Rank Card::rank() const
{
	return rank_;
}

bool Card::Rank::operator==(const Card::Rank& r) const
{
	return rank_ == r.rank();
}

Card::Rank::operator int() const
{
	return rank_;
}

bool Card::operator==(const Card& c) const
{
	return (suit().suit() == c.suit().suit() && rank().rank() == c.rank().rank());
}

bool Card::operator<(const Card& c) const { return rank_.rank() < c.rank().rank(); }

Card::operator std::string() const
{
	return std::string(1, Card::ranks[rank_.rank()]) + std::string(1, Card::suits[suit_.suit()]);
}

ostream& operator<<(ostream& out, const Card::Suit& s)
{
	out << Card::suits[s.suit()];
	return out;
}

ostream& operator<<(ostream& out, const Card::Rank& r)
{
	out << Card::ranks[r.rank()];
	return out;
}

ostream& operator<<(ostream& out, const Card& c)
{
	out << c.rank() << c.suit();	
	return out;
}

istream& operator>>(istream& in, Card::Rank& r)
{
	char c;
	in >> c;
	assert (!in.fail());

	//Read in the rank, make sure it's valid
    int index = Card::ranks.find(c);
	assert (index != string::npos);
	r = Card::Rank(index);
	return in;
}

istream & operator>>(istream& in, Card::Suit& s)
{
	char c;
	in >> c;
	assert (!in.fail());

	// Read in the suit, make sure it's valid
    int index = Card::suits.find(c);
	assert (index != string::npos);
	s = Card::Suit(index);
	return in;
}

istream& operator>>(istream& in, Card& c)
{
	Card::Rank r{0};
	Card::Suit s{0};
	in >> r >> s;
	assert (!in.fail());
	
	c = Card(r, s);
	return in;
} 

Card::Suit::Suit(int s)
{
	if (s < 0 || s >= Card::Suit::MAX_SUIT)
	{
		throw "Invalid suit";
	}
	suit_ = s;
}

Card::Suit::Suit(char s)
{
	bool found = false;
	for (size_t i = 0; i < Card::suits.size(); ++i)
	{
		if (Card::suits[i] == s)
		{
			suit_ = i;
			found = true;
		}
	}
	
	if (!found)
	{
		throw "Invalid suit";
	}
}

int Card::Suit::suit() const
{
	return suit_;
}

Card::Rank::Rank(int r)
{
	if (r < 0 || r >= Card::Rank::MAX_RANK)
	{
		throw "Invalid rank";
	}
	rank_ = r;	
}

Card::Rank::Rank(char r)
{
	bool found = false;
	for (size_t i = 0; i < Card::ranks.size(); ++i)
	{
		if (Card::ranks[i] == r)
		{
			rank_ = i;
			found = true;
		}
	}

	if (!found)
	{
		throw "Invalid rank";
	}
}

int Card::Rank::rank() const
{
	return rank_;
}

std::string Card::getSuits()
{
	return suits;
}

std::string Card::getRanks()
{
	return ranks;
}
