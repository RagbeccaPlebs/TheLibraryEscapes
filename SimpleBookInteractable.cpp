#include "SimpleBookInteractable.h"

using namespace std;

SimpleBookInteractable::SimpleBookInteractable(const int id)
{
    m_Id = id;
	m_InteractableType = BOOK;
	m_BookInteractableType = SIMPLE;
}

void SimpleBookInteractable::Update(float dtAsSeconds)
{
	//Simple so no update
}


