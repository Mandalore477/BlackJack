#include "FDealer.h"
#include"FBlackJackGame.h"



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
			SetCardInHand();
			hand[cardInHand] = deck[currentCard];
			currentCard++;
		}
		if (handTotal < 21)
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
	cardInHand -= 2;
	return cardInHand;
}

void FDealer::SetCardInHand()
{
	cardInHand++;
}

bool FDealer::CheckInsurance(Card hand[])
{
	if (hand[1].value == 10 || hand[1].value == 11)
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
	std::cout << "Dealer hand value :" << hand[0].value<< std::endl;

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
	std::cout << "Dealer hand value :" << CalculateValue(hand) << std::endl;
}