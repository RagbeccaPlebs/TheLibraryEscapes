#include "BookInteractable.h"

using namespace std;

pair<InteractableType, int> BookInteractable::Interact()
{
    //TODO save to file that book is found

    pair<InteractableType, int> pair(BOOK, m_Id);
    return pair;
}

bool BookInteractable::CanInteract(Player& player)
{
    return m_CollisionBox.intersects(player.GetInteractableBox());
}

BookInteractableType BookInteractable::GetBookInteractableType()
{
    return m_BookInteractableType;
}
