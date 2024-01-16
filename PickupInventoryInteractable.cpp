#include "PickupInventoryInteractable.h"

#include <unordered_map>

#include "Constants.h"

using namespace sf;
using namespace std;

PickupType PickupInventoryInteractable::GetPickupType() const
{
	return m_PickupType;
}

PickupType PickupInventoryInteractable::GetPickupTypeFromString(const string& pickupType)
{
	unordered_map<string, PickupType> const table =
	{ {Constant::KEY_UPPERCASE, KEY}, {Constant::BOOK_UPPERCASE, BOOK} };
	const auto it = table.find(pickupType);
	if (it != table.end()) {
		return it->second;
	}
	return KEY;
}
