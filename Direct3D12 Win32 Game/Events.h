#pragma once

enum Event {
	GAME_OVER,
	PLAYER_COLLIDE,
	PLAYER_HIT,
	PLAYER_DEAD,
	PLAYER_ELIMINATED,
	PLAYER_SPAWN,
	PLAYER_MOVE,
	PLAYER_PICKUP_ITEM,
	CHANGE_SCENE,
	CHANGE_SCENE_MAIN_MENU,
	CHANGE_SCENE_GAME,
	CHANGE_SCENE_MELEE_MENU,
	CHANGE_SCENE_CHARACTER_SELECT,
	CHANGE_SCENE_SYSTEM_SETTINGS,
	CHANGE_SCENE_GAME_SETTINGS,
	CHANGE_SCENE_STAGE_SELECT,
	CHANGE_SCENE_DEMO_SCREEN,
	CHANGE_SCENE_EDITOR_MENU,
	PLAYER_SELECTED,
	AI_ADDED,
	GAME_PAUSED,
	APPLICATION_LOADED,
	GAME_START,
	OBJECT_INSTANTIATED,
	OBJECT_DESTROYED,
	GAME_SETTINGS_INCREASE_LIVES,
	GAME_SETTINGS_DECREASE_LIVES,
	GAME_SETTINGS_INCREASE_TIME,
	GAME_SETTINGS_DECREASE_TIME,
	GAME_SETTINGS_ITEM_ACTIVATION,
	GAME_SETTING_STAGE_SELECT,
	GAME_SETTINGS_INCREASE_SOUND,
	GAME_SETTINGS_DECREASE_SOUND,
	GAME_SETTINGS_INCREASE_MUSIC,
	GAME_SETTINGS_DECREASE_MUSIC,
	BUTTON_PRESSED,
	QUIT_GAME
};