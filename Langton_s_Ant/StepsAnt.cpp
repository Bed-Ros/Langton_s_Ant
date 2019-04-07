#include <SFML/Graphics.hpp>
#include <iostream>

struct step
{
	sf::Color color;
	std::string turn;
	step *Next;
};

class StepsAnt
{
	step *Head;
public:
	StepsAnt() { Head = NULL; }
	~StepsAnt()
	{
		while (Head != NULL)
		{
			step *temp = Head->Next;
			delete Head;
			Head = temp;
		}
	}

	void Add(sf::Color color, std::string turn)
	{
		step *temp = new step;
		temp->color = color;
		temp->turn = turn;
		temp->Next = Head;
		Head = temp;
	}

	step* NextStep(sf::Color current_color)
	{
		step *temp = Head;

		while (temp->color != current_color)
		{
			temp = temp->Next;			
		}
		return temp->Next;
	}

	void LoopList()
	{
		step* temp = Head;

		while (temp->Next != NULL)
		{
			temp = temp->Next;
		}
		temp->Next = Head;
	}

	void Show()
	{
		step *temp = Head;
		while (temp != NULL)
		{
			std::cout << temp->turn << " ";
			temp = temp->Next;
		}
	}
};

