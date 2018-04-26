#pragma once

enum class ItemState
{
	HELD,
	THROWN,
	WAIT,
	ARMED,
	ATTACKING


};

enum class ItemType
{
	SINGLE_USE,
	THROWABLE,
	MELEE_WEAPON,
	RANGED_WEAPON,
	EXPLOSIVE
};