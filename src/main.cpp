#include "Globals.h"
#include "tools/Logger.h"
#include "GameApp.h"


int main()
{
	{
		Logger logger;
		Globals::Get()->SetLogger(&logger);
		GameApp app(1024, 768, "TestGame");
		Globals::Get()->SetGame(&app);
		app.Initialize();
		app.MainLoop();
	}

	return 0;
}
