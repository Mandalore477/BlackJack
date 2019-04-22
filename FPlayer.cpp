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
	cardInHand = GetCardInHand(hand);
	bust = false;
	handTotal = CalculateValue(hand);
	if (cardInHand == 2)
	{
		if (handTotal == 21)
		{
			stay = true;
			std::cout << "Player Gets BlackJack!!"<< std::endl;
			playBlackJack = true;
		}
		else
		{
			DoubleDownOpt(hand, deck, currentCard, cardInHand);
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
				Hit(hand, deck, currentCard,cardInHand);
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
	splitBust = false;
	// play split hand
	if (!splitStay)
	{
		splitCardInHand=GetCardInHand(splitHand);
		handTotal = CalculateValue(splitHand);
		if (cardInHand == 2)
		{
			if (handTotal == 21)
			{
				splitStay = true;
			}
			else
			{
				SplitDoubleDownOpt(splitHand, deck, currentCard,splitCardInHand);
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
					std::cout << "Split Hand A: Hit   S:Stay   ";
					std::cin >> response;
					response = tolower(response);
				} while (response != 'a' && response != 's');
				if (response == 'a')
				{
					SplitHit(splitHand, deck, currentCard,splitCardInHand);
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
		cardInHand = GetCardInHand(hand);
		bust = false;
		handTotal = CalculateValue(hand);
		if (cardInHand == 2)
		{
			if (handTotal == 21)
			{
				stay = true;
			}
			else
			{
				DoubleDownOpt(hand, deck, currentCard,cardInHand);
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
					Hit(hand, deck, currentCard, cardInHand);
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
		if (hand[i].value > 0)
		{
			cardInHand++;
		}
	}
	return cardInHand;
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

void FPlayer::DisplayPlayerPre()
{
	system("cls");
	std::cout << "Player" << std::endl;
	std::cout << "Chips :" << chips << "        Bet :" << bet << std::endl;
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
	std::cout << "Chips :" << chips << "        Bet :" << bet << "        Split Bet:"<<splitBet << std::endl;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "//*" << hand[i].face << " " << hand[i].suit << "*\\\\           " << "//*" << splitHand[i].face << " " << splitHand[i].suit << "*\\\\"<< std::endl;
		}
	}
	std::cout << "Player hand value :" << CalculateValue(hand) << "          Split Hand value :"<< CalculateValue(splitHand)<< std::endl;
}

bool FPlayer::IsSplit(Card hand[],int chips, int bet)
{
	isSplit = false;
	char response = ' ';
	if (hand[0].value == hand[1].value || hand[0].face == hand[1].face)
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
				splitBet = bet;
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

void FPlayer::ResetPlayer(Card hand[], Card splitHand[])
{
	stay = false;
	bust = false;
	value = 0;
	bet = 0;
	isSplit = false;
	splitBust = true;
	splitStay = false;
	splitValue = 0;
	splitBet = 0;
	cardInHand = 0;
	playBlackJack = false;
	for (int i = 0; i < 5; i++)
	{
		hand[i] = blank;
		splitHand[i] = blank;
	}
}

bool FPlayer::GetStay()
{
	return stay;
}

void FPlayer::Hit(Card hand[], Card deck[], int currentCard, int cardInHand)
{
	hand[cardInHand] = deck[currentCard];
	cardInHand++;
	if (CalculateValue(hand) > 21)
	{
		stay = true;
		bust = true;
	}
}

void FPlayer::SplitHit(Card splitHand[], Card deck[], int currentCard, int cardInHand)
{
	splitHand[cardInHand] = deck[currentCard];
	cardInHand++;
	if (CalculateValue(hand) > 21)
	{
		splitStay = true;
		splitBust = true;
	}
}

bool FPlayer::IsPlayerBust()
{
	return bust;
}

bool FPlayer::IsSplitBust()
{
	return splitBust;
}

bool FPlayer::GetSplitHandBust()
{
	return splitBust;
}

void FPlayer::DoubleDownOpt(Card hand[],Card deck[],int currentCard, int cardInHand)
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
			Hit(hand, deck, currentCard, cardInHand);
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
			Hit(hand, deck, currentCard, cardInHand);
			std::cout << "You double down" << std::endl;
			ReBet();
			bet += bet;
			stay = true;
		}
		else if (response == 'a')
		{
			Hit(hand, deck, currentCard, cardInHand);
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

void FPlayer::SplitDoubleDownOpt(Card splitHand[], Card deck[], int currentCard, int splitCardInHand)
{
	splitBust = false;
	char response;
	if (bet > chips)
	{
		do
		{
			std::cout << "not enough chips for double down" << std::endl;
			std::cout << "Split Hand   A: Hit   S:Stay ";
			std::cin >> response;
			response = tolower(response);
		} while (response != 'a' && response != 's' && response != 'f');
		if (response == 'a')
		{
			SplitHit(splitHand, deck, currentCard, cardInHand);
		}

		else
		{
			std::cout << "You Stay" << std::endl;
			splitStay = true;
		}
	}
	else
	{
		do
		{
			std::cout << "Split hand   A: Hit   S:Stay    D:DoubleDown ";
			std::cin >> response;
			response = tolower(response);
		} while (response != 'a' && response != 's' && response != 'd' && response != 'f');
		if (response == 'd')
		{
			SplitHit(splitHand, deck, currentCard, cardInHand);
			std::cout << "You double down" << std::endl;
			ReBet();
			splitBet += splitBet;
			splitStay = true;
		}
		else if (response == 'a')
		{
			SplitHit(splitHand, deck, currentCard, cardInHand);
		}
		else
		{
			std::cout << "You Stay" << std::endl;
			splitStay = true;
		}
	}
}

int FPlayer::GetSplitValue()
{
	return splitValue;
}

int FPlayer::GetSplitBet()
{
	return splitBet;
}

bool FPlayer::IsPlayBJ()
{
	return playBlackJack;
}





