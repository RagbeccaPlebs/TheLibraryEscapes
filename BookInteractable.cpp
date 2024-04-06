#include "BookInteractable.h"

#include <unordered_map>

#include "TiledMapLoader.h"

#include "Constants.h"

using namespace std;
using namespace sf;

pair<string, Vector2f> BookInteractable::Interact()
{
	b_Active = false;

	SavePickupToFile();

	return pair<string, Vector2f>{Constant::EMPTY_STRING, Vector2f(0, 0)};
}

string BookInteractable::Message()
{
	return Message::FOUND_BOOK_MESSAGE;
}

void BookInteractable::Unload()
{
	//Nothing to unload like sounds
}

