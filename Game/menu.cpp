
#include "menu.h"
#include "../Framework/framework.h"

void Menu::Begin()
{
	selectedItem = 0;

	fontTitle = spFontLoad( "Resource/title.ttf", 42 );
	spFontAdd( fontTitle, SP_FONT_GROUP_ASCII, spGetFastRGB( 255, 255, 255 ) );

	fontMenuUnselected = spFontLoad( "Resource/title.ttf", 24 );
	spFontAdd( fontMenuUnselected, SP_FONT_GROUP_ASCII, spGetFastRGB( 255, 255, 255 ) );
	fontMenuSelected = spFontLoad( "Resource/title.ttf", 24 );
	spFontAdd( fontMenuSelected, SP_FONT_GROUP_ASCII, spGetFastRGB( 255, 192, 80 ) );
	fontMenuDisabled = spFontLoad( "Resource/title.ttf", 24 );
	spFontAdd( fontMenuDisabled, SP_FONT_GROUP_ASCII, spGetFastRGB( 0, 0, 0 ) );

}

void Menu::Pause()
{
}

void Menu::Resume()
{
}

void Menu::Finish()
{
	spFontDelete( fontTitle );
	spFontDelete( fontMenuSelected );
	spFontDelete( fontMenuUnselected );
	spFontDelete( fontMenuDisabled );
}

void Menu::EventOccurred(Event *e)
{

	if( e->Type == EVENT_KEY_DOWN )
	{
		switch( e->Data.Keyboard.keysym.sym )
		{
			case SDLK_ESCAPE:
				delete Framework::System->ProgramStages->Pop();
				return;

			case SDLK_DOWN:
				selectedItem = (selectedItem + 1) % 4;
				break;
			case SDLK_UP:
				selectedItem = (selectedItem + 3) % 4;
				break;

			case SDLK_RETURN:
			case SDLK_SPACE:
#ifdef PANDORA
			case SDLK_PAGEDOWN:
#endif
				switch( selectedItem )
				{
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						delete Framework::System->ProgramStages->Pop();
						break;
				}
				break;

		}

	}

}

void Menu::Update()
{
}

void Menu::Render()
{

	spClearTarget( spGetFastRGB( 5, 64, 171 ) );

	spSetHorizontalOrigin( SP_CENTER );
	spSetVerticalOrigin( SP_CENTER );

	spFontDrawMiddle( Framework::System->GetDisplayWidth() / 2, 6, -1, "Battle Pong", fontTitle );

	int yPos = Framework::System->GetDisplayHeight() - ((24.0f) * 5.0f);
	spFontDraw( 10, yPos, -1, "Single Player", ( selectedItem == 0 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;
	spFontDraw( 10, yPos, -1, "Local Two Player", ( selectedItem == 1 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;
	spFontDraw( 10, yPos, -1, "Network Two Player", ( selectedItem == 2 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;
	spFontDraw( 10, yPos, -1, "Quit", ( selectedItem == 3 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;

}
