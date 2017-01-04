#pragma  once
namespace cd
{
	enum class CollisionDirections
	{
		ANY,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
}

namespace gs
{
	enum class GameStates
	{
		SPLASH_SCREEN,
		PLAY,
		MENU,
		EXIT
	};
}