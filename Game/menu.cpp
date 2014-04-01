
#include "menu.h"
#include "../Framework/framework.h"
#include "../Transitions/fade.h"
#include "debugstage.h"
#include "../Shaders/greyscale.h"

int Menu::selectedSway[16] = { -2, -1, -1,
																0, 0, 0,
																1, 1, 2,
																1, 1, 0,
																0, 0, -1,
																-1 };

void Menu::Begin()
{
	selectedItem = 0;
	selectedSwayIndex = 3;
	selectedSwayDelay = 0;

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
						Framework::System->ProgramStages->Push( new TransitionFade( new DebugStage(), 20 ) );
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
	selectedSwayDelay = (selectedSwayDelay + 1) % 3;
	if( selectedSwayDelay == 0 )
	{
		selectedSwayIndex = (selectedSwayIndex + 1) % 16;
	}
}

void Menu::Render()
{

	spClearTarget( spGetFastRGB( 5, 64, 171 ) );

	spSetHorizontalOrigin( SP_CENTER );
	spSetVerticalOrigin( SP_CENTER );

	spFontDrawMiddle( Framework::System->GetDisplayWidth() / 2, 6, -1, "Battle Pong", fontTitle );

	int yPos = (int)(Framework::System->GetDisplayHeight() - ((24.0f) * 5.0f));
	spFontDraw( 10 + ( selectedItem == 0 ? selectedSway[selectedSwayIndex] : 0 ), yPos, -1, "Single Player", ( selectedItem == 0 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;
	spFontDraw( 10 + ( selectedItem == 1 ? selectedSway[selectedSwayIndex] : 0 ), yPos, -1, "Local Two Player", ( selectedItem == 1 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;
	spFontDraw( 10 + ( selectedItem == 2 ? selectedSway[selectedSwayIndex] : 0 ), yPos, -1, "Network Two Player", ( selectedItem == 2 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;
	spFontDraw( 10 + ( selectedItem == 3 ? selectedSway[selectedSwayIndex] : 0 ), yPos, -1, "Quit", ( selectedItem == 3 ? fontMenuSelected : fontMenuUnselected ) );
	yPos += 24;

	//ShaderGreyscale* shader = new ShaderGreyscale();
	//shader->Apply( spGetRenderTarget() );
	//delete shader;
}

bool Menu::StageIsTransition()
{
	return false;
}
