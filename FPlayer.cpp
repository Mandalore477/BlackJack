#include"FBlackJackGame.h"
#include "FPlayer.h"
#include<string>





FPlayer::FPlayer()
{
}


FPlayer::~FPlayer()
{
}

void FPlayer::Play(Card hand[], Card deck[], int currentCard)
{
	bust = false;
	handTotal = CalculateValue(hand);
	if (cardInHand == 2)
	{
		if (handTotal == 21)
		{
			stay = true;
			std::cout << "BlackJack!! You get " << (GetBet()*2.5) << " Chips" << std::endl;
			GetWinnings(GetBet()*2.5);
			bet = 0;
		}
		else
		{
			DoubleDownOpt(hand, deck, currentCard);
		}

	}
	else
	{
		if (handTotal == 21)
		{
			stay = true;
			std::cout << "You got 21" << std::endl;
		}
		else if (handTotal > 21)
		{
			stay = true;
			bust = true;
			std::cout << "Player bust" << std::endl;
		}
		else if (cardInHand == 5)
		{
			stay = true;
			if (handTotal > 21)
			{
				bust = true;
				std::cout << "Player bust" << std::endl;
			}
		}
		else
		{
			char response;
			do
			{
				std::cout << "A: Hit   S:Stay   ";
				std::cin >> response;
				response = tolower(response);
			} while (response != 'a' && response != 's');
			if (response == 'a')
			{
				Hit(hand, deck, currentCard);
			}
			else
			{
				std::cout << "You Stay" << std::endl;
				stay = true;
			}
		}
	}

}

void FPlayer::SplitPlay(Card hand[], Card splitHand[], Card deck[], int currentCard)
{
	// play split hand
	if (!splitStay)
	{
		splitBust = false;
		handTotal = CalculateValue(splitHand);
		if (cardInHand == 2)
		{
			if (handTotal == 21)
			{
				splitStay = true;
				std::cout << "BlackJack!! You get " << (GetBet()*2.5) << " Chips" << std::endl;
				GetWinnings(GetBet()*2.5);

			}
			else
			{
				DoubleDownOpt(splitHand, deck, currentCard);
			}

		}
		else
		{
			if (handTotal == 21)
			{
				splitStay = true;
				std::cout << "You got 21" << std::endl;
			}
			else if (handTotal > 21)
			{
				splitStay = true;
				splitBust = true;
				std::cout << "Split Hand Bust" << std::endl;
			}
			else if (cardInHand == 5)
			{
				splitStay = true;
				if (handTotal > 21)
				{
					splitBust = true;
					std::cout << "Split Hand bust" << std::endl;
				}
			}
			else
			{
				char response;
				do
				{
					std::cout << "A: Hit   S:Stay   ";
					std::cin >> response;
					response = tolower(response);
				} while (response != 'a' && response != 's');
				if (response == 'a')
				{
					Hit(splitHand, deck, currentCard);
				}
				else
				{
					std::cout << "Split Hand Stay" << std::endl;
					splitStay = true;
				}
			}
		}


	}
	//Back to Player hand
	else
	{
		bust = false;
		handTotal = CalculateValue(hand);
		if (cardInHand == 2)
		{
			if (handTotal == 21)
			{
				stay = true;
				std::cout << "BlackJack!! You get " << (GetBet()*2.5) << " Chips" << std::endl;
				GetWinnings(GetBet()*2.5);
				bet = 0;
			}
			else
			{
				DoubleDownOpt(hand, deck, currentCard);
			}

		}
		else
		{
			if (handTotal == 21)
			{
				stay = true;
				std::cout << "You got 21" << std::endl;
			}
			else if (handTotal > 21)
			{
				stay = true;
				bust = true;
				std::cout << "Player bust" << std::endl;
			}
			else if (cardInHand == 5)
			{
				stay = true;
				if (handTotal > 21)
				{
					bust = true;
					std::cout << "Player bust" << std::endl;
				}
			}
			else
			{
				char response;
				do
				{
					std::cout << "A: Hit   S:Stay   ";
					std::cin >> response;
					response = tolower(response);
				} while (response != 'a' && response != 's');
				if (response == 'a')
				{
					Hit(hand, deck, currentCard);
				}
				else
				{
					std::cout << "You Stay" << std::endl;
					stay = true;
				}
			}
		}
	}
}

int FPlayer::CalculateValue(Card hand[])
{
	value = hand[0].value + hand[1].value + hand[2].value + hand[3].value + hand[4].value;
	if (value > 21)
	{
		for (int i = 0; i < 5; i++)
		{
			if (hand[i].value == 11)
			{
				hand[i].value = 1;
				break;
			}
		}
		value = hand[0].value + hand[1].value + hand[2].value + hand[3].value + hand[4].value;
	}
	
	return value;
}
//return extra cards minus the original 2 dealt
int FPlayer::GetCardInHand(Card hand[])
{
	cardInHand = 0;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value < 0)
		{
			cardInHand++;
		}
	}
	return cardInHand;
}
// add one to cardinhand
void FPlayer::SetCardInHand(int value)
{
	cardInHand += value;
}

void FPlayer::MakeBet()
{
	std::cout << "Bet amount:";
	std::cin >> bet;
	if (bet > chips)
	{
		bet = chips;
	}
	chips -= bet;

}

int FPlayer::GetBet()
{
	return bet;
}

void FPlayer::GetWinnings(int winnings)
{
	chips += winnings;
}

void FPlayer::DisplayPlayer(Card hand[])
{
	std::cout << "Player" << std::endl;
	std::cout << "Chips :" << chips << "        Bet :" << bet << std::endl;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "//*" << hand[i].face << " " << hand[i].suit << "*\\\\" << std::endl;
		}
	}
	std::cout << "Player hand value :" << CalculateValue(hand) << std::endl;
	
}

//Display both player and split hand
void FPlayer::DisplaySplit(Card hand[], Card splitHand[])
{
	std::cout << "Player                        SplitHand" << std::endl;
	std::cout << "Chips :" << chips << "        Bet :" << bet << std::endl;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "//*" << hand[i].face << " " << hand[i].suit << "*\\\\           " <<<< "//*" << splitHand[i].face << " " << splitHand[i].suit << "*\\\\"<< std::endl;
		}
	}
	std::cout << "Player hand value :" << CalculateValue(hand) << "          Split Hand value :"<< CalculateValue(splitHand)<< std::endl;
}

bool FPlayer::IsSplit(Card hand[],int chips, int bet)
{
	isSplit = false;
	char response = ' ';
	if (hand[0].value == hand[1].value)
	{
		if (bet <= chips)
		{
			while (response != 'y' && response != 'n')
			{
				std::cout << "would you like to split (Y/N)" << std::endl;
				std::cin >> response;
				response = tolower(response);
			}
			if (response == 'y')
			{
				isSplit = true;
				ReBet();
			}
		}
		else
		{
			std::cout << "Not enough chips to split" << std::endl;
		}
	}
	return isSplit;
}

int FPlayer::GetChips()
{
	return chips;
}

void FPlayer::ReBet()
{
	chips = chips - bet;
}

bool FPlayer::GetStay()
{
	return stay;
}

void FPlayer::Hit(Card hand[], Card deck[], int currentCard)
{
	hand[cardInHand] = deck[currentCard];
	SetCardInHand(1);
	if (CalculateValue(hand) > 21)
	{
		stay = true;
		bust = true;
	}
}

bool FPlayer::IsPlayerBust()
{
	return bust;
}

bool FPlayer::GetSplitHandBust()
{
	return splitBust;
}

void FPlayer::DoubleDownOpt(Card hand[],Card deck[],int currentCard)
{
	bust = false;
	char response;
	if (bet > chips)
	{
		do
		{
			std::cout << "not enough chips for double down" << std::endl;
			std::cout << "A: Hit   S:Stay       F:Surrender ";
			std::cin >> response;
			response = tolower(response);
		} while (response != 'a' && response != 's' && response != 'f');
		if (response == 'a')
		{
			Hit(hand, deck, currentCard);
		}
		else if (response == 'f')
		{
			std::cout << "You surrender. You get " << (bet / 2) << " Chips back" << std::endl;
			GetWinnings((bet / 2));
			stay = true;
			bet = 0;
		}
		else
		{
			std::cout << "You Stay" << std::endl;
			stay = true;
		}
	}
	else
	{
		do
		{
			std::cout << "A: Hit   S:Stay    D:DoubleDown    F:Surrender ";
			std::cin >> response;
			response = tolower(response);
		} while (response != 'a' && response != 's' && response != 'd' && response != 'f');
		if (response == 'd')
		{
			Hit(hand, deck, currentCard);
			std::cout << "You double down" << std::endl;
			ReBet();
			bet += bet;
			stay = true;
		}
		else if (response == 'a')
		{
			Hit(hand, deck, currentCard);
		}
		else if (response == 'f')
		{
			std::cout << "You surrender. You get " << (bet / 2) << " Chips back" << std::endl;
			GetWinnings((bet / 2));
			stay = true;
			bet = 0;
		}
		else
		{
			std::cout << "You Stay" << std::endl;
			stay = true;
		}
	}
}

int FPlayer::GetSplitValue()
{
	return splitValue;
}



