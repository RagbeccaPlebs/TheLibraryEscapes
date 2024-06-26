﻿#pragma once
#include <string>

class Keywords
{
public:
	static const inline std::string ACTIVATED_KEYWORD = "activated";
	static const inline std::string AMOUNT_INTERACTED_KEYWORD = "amount-interacted";
	static const inline std::string BOOK_KEYWORD = "book";
	static const inline std::string CONDITIONS_KEYWORD = "conditions";
	static const inline std::string DATA_KEYWORD = "data";
	static const inline std::string DOOR_KEYWORD = "door";
	static const inline std::string EMOTION_KEYWORD = "emotion";
	static const inline std::string HEIGHT_KEYWORD = "height";
	static const inline std::string ID_KEYWORD = "id";
	static const inline std::string INACTIVE_SOUND_KEYWORD = "inactive-sound";
	static const inline std::string INACTIVE_TEXTURE_KEYWORD = "inactive-texture";
	static const inline std::string KEY_KEYWORD = "key";
	static const inline std::string KEY_ID_KEYWORD = "key-id";
	static const inline std::string LAYERS_KEYWORD = "layers";
	static const inline std::string MAP_KEYWORD = "map";
	static const inline std::string MAP_X_KEYWORD = "map-x";
	static const inline std::string MAP_Y_KEYWORD = "map-y";
	static const inline std::string MAX_X_KEYWORD = "max-x";
	static const inline std::string MAX_Y_KEYWORD = "max-y";
	static const inline std::string MIN_X_KEYWORD = "min-x";
	static const inline std::string MIN_Y_KEYWORD = "min-y";
	static const inline std::string MOVABLE_SPEED_KEYWORD = "movable-speed";
	static const inline std::string NAME_KEYWORD = "name";
	static const inline std::string OBJECT_KEYWORD = "object";
	static const inline std::string OPERATION_KEYWORD = "operation";
	static const inline std::string OPERATIONS_KEYWORD = "operations";
	static const inline std::string PICKUP_KEYWORD = "pickup";
	static const inline std::string PLAYER_BASE_KEYWORD = "player-base";
	static const inline std::string PLAYER_CLOAK_KEYWORD = "player-cloak";
	static const inline std::string PLAYER_FACE_ITEM_KEYWORD = "player-face-item";
	static const inline std::string PLAYER_HAIR_KEYWORD = "player-hair";
	static const inline std::string PLAYER_HAT_KEYWORD = "player-hat";
	static const inline std::string PLAYER_LOWER_LAYER_KEYWORD = "player-lower-layer";
	static const inline std::string PLAYER_LOCATION_KEYWORD = "player-location";
	static const inline std::string PLAYER_KEYWORD = "player";
	static const inline std::string PUSHABLE_OBJECT_KEYWORD = "pushable-object";
	static const inline std::string PUSH_SOUND_KEYWORD = "push-sound";
	static const inline std::string SETTINGS_KEYWORD = "settings";
	static const inline std::string SOUND_KEYWORD = "sound";
	static const inline std::string SUB_TYPE_KEYWORD = "sub-type";
	static const inline std::string TEMPLATE_ID_KEYWORD = "template-id";
	static const inline std::string TEXTURE_KEYWORD = "texture";
	static const inline std::string TEXTURE_LOCATION_KEYWORD = "texture-location";
	static const inline std::string TILEWIDTH_KEYWORD = "tilewidth";
	static const inline std::string TIME_LEFT_KEYWORD = "time-left";
	static const inline std::string TYPE_KEYWORD = "type";
	static const inline std::string WIDTH_KEYWORD = "width";
	static const inline std::string X_KEYWORD = "x";
	static const inline std::string Y_KEYWORD = "y";
	static const inline std::string ZOOM_KEYWORD = "zoom";
};

class Message
{
public:
	static const inline std::string CLOAK_MESSAGE = "Cloak";
	static const inline std::string CLOTHES_MESSAGE = "Clothes";
	static const inline std::string CONTINUE_MESSAGE = "Continue";
	static const inline std::string CORRECT_LOCATION_MESSAGE = "The object has been placed in the correct position!";
	static const inline std::string DOOR_LOCKED_MESSAGE_1 = "The door is locked! Get key ";
	static const inline std::string DOOR_LOCKED_MESSAGE_2 = " to open it!";
	static const inline std::string EXCLAMATION_MARK = "!";
	static const inline std::string EXIT_MESSAGE = "Exit";
	static const inline std::string EXIT_TO_MENU_MESSAGE = "Exit To Menu";
	static const inline std::string FACE_ITEM_MESSAGE = "Face Item";
	static const inline std::string FOUND_BOOK_MESSAGE =  "You found a book!";
	static const inline std::string HAIR_MESSAGE = "Hair";
	static const inline std::string HAT_MESSAGE = "Hat";
	static const inline std::string KEY_FOUND_MESSAGE_1 = "You found key ";
	static const inline std::string LEFT_MESSAGE = "Left";
	static const inline std::string LOST_MESSAGE = "You have lost the game :/";
	static const inline std::string PRESS_E_TO_INTERACT_MESSAGE = "Press E To Interact!";
	static const inline std::string RESET_GAME_MESSAGE = "Reset Game";
	static const inline std::string RIGHT_MESSAGE = "Right";
	static const inline std::string SKIN_COLOR_MESSAGE = "Skin Color";
	static const inline std::string START_MESSAGE = "Start";
	static const inline std::string TIP_ONE = "You can walk by using SHIFT";
	static const inline std::string TIP_TWO = "Don't forget to grab keys!";
	static const inline std::string TIP_THREE = "Press E to interact";
	static const inline std::string TIP_FOUR = "Basics: WASD for movement";
	static const inline std::string WON_MESSAGE = "You have won the game! Click reset in the main menu to restart!";
};

class Files
{
public:
	//Files
	static const inline std::string GAME_DATA_FILE = "assets/data/gameData.json";
	static const inline std::string BOOKS_DATA_FILE = "assets/data/books.json";
	static const inline std::string DOORS_DATA_FILE = "assets/data/doors.json";
	static const inline std::string FONT_FILE = "assets/fonts/PixelifySans-Regular.ttf";

	//Standard Types
	static const inline std::string SLASH = "/";
	static constexpr inline char CHAR_SLASH = '/';

	//Searchable Folders
	static const inline std::string BASE_PLAYER_GRAPHICS_SEARCH_FOLDER = "assets/graphics/player/base";
	static const inline std::string CLOAK_PLAYER_GRAPHICS_SEARCH_FOLDER = "assets/graphics/player/cloak";
	static const inline std::string FACE_ITEM_PLAYER_GRAPHICS_SEARCH_FOLDER = "assets/graphics/player/face";
	static const inline std::string HAIR_PLAYER_GRAPHICS_SEARCH_FOLDER = "assets/graphics/player/hair";
	static const inline std::string HAT_ITEM_PLAYER_GRAPHICS_SEARCH_FOLDER = "assets/graphics/player/hat";
	static const inline std::string LOWER_LAYER_PLAYER_GRAPHICS_SEARCH_FOLDER = "assets/graphics/player/lower";

	//Folders
	static const inline std::string ASSETS_FOLDER = "assets";
	static const inline std::string ASSETS_DATA_FOLDER = "assets/data";
	static const inline std::string MAP_GRAPHICS_FOLDER = "assets/graphics/map/";
	static const inline std::string MAP_FOLDER = "assets/map/";
	static const inline std::string MAP_DETAILS_FOLDER = "assets/map/details/";
	static const inline std::string MAP_DETAILS_INITIAL_FOLDER = "assets/map/details/initial/";
	static const inline std::string BASE_PLAYER_GRAPHICS_FOLDER = BASE_PLAYER_GRAPHICS_SEARCH_FOLDER + SLASH;
	static const inline std::string CLOAK_PLAYER_GRAPHICS_FOLDER = CLOAK_PLAYER_GRAPHICS_SEARCH_FOLDER + SLASH;
	static const inline std::string FACE_ITEM_PLAYER_GRAPHICS_FOLDER = FACE_ITEM_PLAYER_GRAPHICS_SEARCH_FOLDER + SLASH;
	static const inline std::string HAIR_PLAYER_GRAPHICS_FOLDER = HAIR_PLAYER_GRAPHICS_SEARCH_FOLDER + SLASH;
	static const inline std::string HAT_ITEM_PLAYER_GRAPHICS_FOLDER = HAT_ITEM_PLAYER_GRAPHICS_SEARCH_FOLDER + SLASH;
	static const inline std::string LOWER_LAYER_PLAYER_GRAPHICS_FOLDER = LOWER_LAYER_PLAYER_GRAPHICS_SEARCH_FOLDER + SLASH;

	//Extensions
	static const inline std::string DOT_JSON_EXTENSION = ".json";
	static const inline std::string JSON_EXTENSION = ".json";
	static const inline std::string DOT_PNG_EXTENSION = ".png";
};

class Constant
{
public:
	//Global Variables
	static const inline std::string EMPTY_STRING = "";
	static const inline std::string GAME_TITLE = "The Library Escapes";
	static const inline std::string MAP_COLLISION_LEVEL_NAME = "Collision";

	//Actions
	static const inline std::string SHOW_UPPERCASE = "SHOW";

	//Emotions
	static const inline std::string SHY_UPPERCASE = "SHY";
	static const inline std::string SHY_CAMELCASE = "Shy";
	static const inline std::string SAD_UPPERCASE = "SAD";
	static const inline std::string SAD_CAMELCASE = "Sad";

	//Interactable Types
	static const inline std::string DOOR_UPPERCASE = "DOOR";
	static const inline std::string PUSH_OBJECT_UPPERCASE = "PUSH-OBJECT";
	static const inline std::string PICKUP_UPPERCASE = "PICKUP";

	//Pickup Types
	static const inline std::string BOOK_UPPERCASE = "BOOK";
	static const inline std::string KEY_UPPERCASE = "KEY";

	//Push Types
	static const inline std::string RANDOM_UPPERCASE = "RANDOM";
	static const inline std::string LOCATION_UPPERCASE = "LOCATION";
	static constexpr float MAX_DISTANCE_FROM_FINAL_POSITION = 2.f;

	//Map
	static constexpr int STANDARD_TILE_SIZE = 16;
	static constexpr int VERTS_IN_QUAD = 4;

	//Collisions
	static constexpr int MAX_RANGE_COLLISIONS_DETECTION = 5;

	//Timings
	static constexpr float TIME_OF_CENTER_OVERLAY_ON_SCREEN_IN_SECONDS = 5.f;

	//Player
	static constexpr float PLAYER_RUN_SPEED = 80.f;
	static constexpr float PLAYER_WALK_SPEED = 50.f;

	//Initial Player Files
	static const inline std::string INITIAL_BASE_LAYER = "char_a_p1_0bas_humn_v00.png";
	static const inline std::string INITIAL_LOWER_LAYER_LAYER = "char_a_p1_1out_pfpn_v01.png";
	static const inline std::string INITIAL_CLOAK_LAYER = "char_a_p1_2clo_lnpl_v07.png";
	static const inline std::string INITIAL_HAT_LAYER = "char_a_p1_5hat_pnty_v03.png";

	//Timer
	static constexpr inline float INITIAL_TIMER = 230.f;
};


enum Side
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

enum GameState
{
	STARTED,
	DOING,
	CHANGED,
	STOPPED,
	NOTHING
};