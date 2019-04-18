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
	stay = false;
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
					bet += bet;
					stay = true;
					splitResults[GetSplitNum()][1] = 1;
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
				std::cout << "A: Hit   S:Stay       F:Surrender ";
				std::cin >> response;
				response = tolower(response);
			} while (response != 'a' && response != 's' && response != 'f');
			if (response == 'a')
			{
				Hit(hand, deck, currentCard);
			}
			else if(response == 'f')
			{
				std::cout << "You surrender. You get "<< (bet/2)<<" Chips back" << std::endl;
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
			}
		}
		value = hand[0].value + hand[1].value + hand[2].value + hand[3].value + hand[4].value;
	}
	
	return value;
}
//return extra cards minus the original 2 dealt
int FPlayer::GetCardInHand()
{
	cardInHand -= 2;
	return cardInHand;
}
// add one to cardinhand
void FPlayer::SetCardInHand()
{
	cardInHand++;
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

bool FPlayer::IsSplit(Card hand[],int chips, int bet)
{
	bool split = false;
	char response = 'a';
	if (hand[0].value = hand[1].value)
	{
		if (bet <= chips)
		{
			while (response != 'y' || response != 'n')
			{
				std::cout << "would you like to split (Y/N)" << std::endl;
				std::cin >> response;
				response = tolower(response);
			}
			if (response == 'y')
			{
				split = true;
			}
		}
		else
		{
			std::cout << "Not enough chips to split" << std::endl;
		}
	}
	return split;
}

int FPlayer::GetChips()
{
	return chips;
}

void FPlayer::ReBet()
{
	chips = chips - bet;
}

void FPlayer::CheckSplitResults(int dealerValue,bool dealerBust)
{

	for (int i = 0; i < 96; i++)
	{
		if (dealerValue == splitResults[i][0] && splitResults[i][0] <22)
		{
			splitPush++;
			if (splitResults[i][1] == 1)
			{
				splitPush++;
			}
		}
		else if ((dealerValue < splitResults[i][0] && splitResults[i][0] < 22)||(dealerBust&&splitResults[i][0] < 22))
		{
			splitWins++;
			if (splitResults[i][1] == 1)
			{
				splitWins++;
			}
		}
		else
		{
			splitLosses++;
		}
	}
	int winnings = (splitWins * bet * 2) + (splitPush * bet);
	std::cout << "Splits resulted in " << winnings<< " chips" <<std::endl;
}

void FPlayer::AddSplitResult(int value)
{
	splitResults[GetSplitNum()][0] = value;
	AddSplitNum();
}

int FPlayer::GetSplitNum()
{
	return splitNum;
}

void FPlayer::AddSplitNum()
{
	splitNum++;
}

void FPlayer::ResetSplit()
{
	for (int i = 0; i < 96; i++)
	{
		splitResults[i][0] = 0;
		splitResults[i][1] = 0;
	}
	splitNum = 0;
	splitWins = 0;
	splitPush = 0;
	splitLosses = 0;
	bet = 0;
}

bool FPlayer::GetStay()
{
	return stay;
}

void FPlayer::Hit(Card hand[], Card deck[], int currentCard)
{
	SetCardInHand();
	hand[cardInHand] = deck[currentCard];
	currentCard++;
}

bool FPlayer::IsPlayerBust()
{
	return bust;
}


