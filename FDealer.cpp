#include "FDealer.h"
#include"CardStruct.h"



FDealer::FDealer()
{
}


FDealer::~FDealer()
{
}

void FDealer::Hit(Card hand[], Card deck[], int currentCard)
{
	cardInHand = 2;
	stay = false;
	while (!stay)
	{
		handTotal = CalculateValue(hand);
		std::cout << "dealer total is :" << handTotal << std::endl;
		if (handTotal >= 17)
		{
			stay = true;
		}
		else if (cardInHand == 5)
		{
			stay = true;
		}
		else
		{
			hand[cardInHand] = deck[currentCard];
			SetCardInHand(1);
		}
		if (handTotal > 21)
		{
			bust = true;
		}
	}
}

int FDealer::CalculateValue(Card hand[])
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

int FDealer::GetCardInHand()
{
	return cardInHand;
}

void FDealer::SetCardInHand(int value)
{
	cardInHand+= value;
}

bool FDealer::CheckInsurance(Card hand[])
{
	if (hand[0].value == 11)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FDealer::IsDealerBust()
{
	return bust;
}

bool FDealer::GetStay()
{
	return stay;
}

void FDealer::ResetStay()
{
	blackJack = false;
	stay = false;
	bust = false;
}

bool FDealer::IsBlackJack()
{
	return blackJack;
}

void FDealer::SetBlackJack(bool blackJackResult)
{
	blackJack = blackJackResult;
}

void FDealer::DisplayDealerPre(Card hand[])
{
	std::cout << "Dealer" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value == 0)
		{
			std::cout << std::endl;
		}
		else if (i == 1)
		{
			std::cout << "//* ??? *\\\\"<<std::endl;
		}
		else
		{
			std::cout << "//*" << hand[i].face << " " << hand[i].suit << "*\\\\" << std::endl;
		}
	}
	std::cout << "Dealer hand value :" << hand[0].value<< std::endl << std::endl;

}

void FDealer::DisplayDealerPost(Card hand[])
{
	std::cout << "Dealer" << std::endl;
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
	std::cout << "Dealer hand value :" << CalculateValue(hand)<<"\n" << std::endl;
}
