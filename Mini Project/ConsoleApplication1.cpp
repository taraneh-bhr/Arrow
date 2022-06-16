#include <iostream> 
#include "SBDL.h"
using namespace std;

int main(int argc, const char* argv[])
{
	int deg = -45;
	SDL_Rect backgroundrec = { 0,0,500,500 };
	SDL_Rect arrowrec = { 235,350,25,30 };
	SDL_Rect gemrec = { 250,-120,25,25 };
	SDL_Rect diamondrec = { 200,-500,30,25 };

	SDL_Rect boxrecR[10];
	for (int i = 0,y=-100; i < 10; i++,y-=70)
	{
		boxrecR[i] = {(rand()%200)+270,y,500,70 };
	}

	SDL_Rect boxrecL[10];
	for (int i = 0, y = -100; i < 10; i++, y -= 70)
	{
		boxrecL[i] = { 0,y,rand()%200,70 };
	}
	
	int framecount = 0;
	int score = 0;
	int movebox = 5;
	int movegem = 5;
	int movearrow = -5;
	int scoreSave = 0;
	int distance = 0;
	int distanceSave = 0;

	SDL_Rect scoreboxrec = { 0,50,600,50 };

	SBDL::InitEngine("Test", 500, 500);

	Font* font = SBDL::loadFont("CenturyGothic.ttf", 24);
	Sound* crashSound = SBDL::loadSound("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets2/sounds/crash.mp3");
	Sound* gemSound = SBDL::loadSound("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets2/sounds/gem.mp3");
	Music* music = SBDL::loadMusic("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets2/sounds/chilled_v1.mp3");
	Texture background = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/ground_1.png");
	Texture arrow = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets/arrow.png");
	Texture gem = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets/gem.png");
	Texture box = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets/box.png");
	Texture diamond = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets/gem2.png");
	Texture scorebox = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets/score.png");
	Texture arrowTitle = SBDL::createFontTexture(font, "Arrow", 0, 0, 0);
	SDL_Rect arrowTitleRec = { 180,80,160,75 };
	SDL_Rect scorebox2rect = { 100,55,130,35 };
	SDL_Rect distanceboxrect = { 300,55,130,30 };
	Texture sheep = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/sheep.png");
	Texture hedgehog = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets/arrow.png");
	SDL_Rect arrowChange = { 310,350,50,50 };

	bool arrowChangeCheck = true;
	SBDL::playMusic(music, -1);

	bool onMenu = true;
	SDL_Rect menu = { 0,0,500,500 };
	Texture menutex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets2/img/ground_1.png");
	SDL_Rect playbutton = { 160,240,200,70 };
	Texture playbuttontex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets2/img/wall_5.png");
	Texture startbutton = SBDL::createFontTexture(font, "START", 254, 254, 254);
	Texture exitbuttonTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/wall_2.png");
	Texture exitbutton = SBDL::createFontTexture(font, "EXIT", 254, 254, 254);
	SDL_Rect exitRec = { 160,350,90,50 };

	bool gameOver = false;
	SDL_Rect gameOverRec = { 0,0,500,500 };
	Texture gameOvertex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets2/img/ground_1.png");
	SDL_Rect replayRec = { 160,240,200,70 };
	Texture replayButton =SBDL::loadTexture ("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/wall_3.png");
	SDL_Rect endRec = { 100,100,320,50 };
	Texture endButton = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/SpriteAtlasTexture_2048x1024_fmt13.png");
	Texture restartbutton = SBDL::createFontTexture(font, "RESTART", 254, 254, 254);
	Texture gotoMenuTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/ConsoleApplication1/assets2/img/wall_6.png");
	Texture gotoMenu = SBDL::createFontTexture(font, "MENU", 254, 254, 254);
	SDL_Rect gotoMenuRec = { 210,330,90,50 };
	SDL_Rect scoreNUmRec = { 50,50,100,50 };
	SDL_Rect distanceNUmRec = { 350,60,100,30 };
	SDL_Rect exitRec2 = { 210,400,90,50 };

	bool pause = false;
	SDL_Rect resumeBackground = { 0,0,500,500 };
	Texture resumeBackgroundTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/ground_3.png");
	SDL_Rect resumeButton = { 160,140,200,70 };
	Texture resumeButtonTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/wall_1.png");
	Texture resumeButtonWord = SBDL::createFontTexture(font, "RESUME", 254, 254, 254);

	SDL_Rect pausebutton = { 10,440,50,50 };
	SDL_Rect pausebuttonShape = { 10,440,50,50 };
	Texture pausebuttonBackTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/back.png");
	Texture pausebuttonTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/pauseSign.png");
	
	while (SBDL::isRunning())
	{
		SBDL::updateEvents();
		SBDL::clearRenderScreen();

		//if the PLAY button is hit
		if (SBDL::mouseInRect(playbutton) && SBDL::Mouse.clicked())
		{
			onMenu = false;
		}

		//the main-menu
		if (onMenu)
		{
			SBDL::showTexture(menutex, menu);
			SBDL::showTexture(arrowTitle, arrowTitleRec);
			SBDL::showTexture(playbuttontex, playbutton);
			SBDL::showTexture(startbutton, playbutton);
			SBDL::showTexture(exitbuttonTex, exitRec);
			SBDL::showTexture(exitbutton, exitRec);
			SBDL::showTexture(arrow, arrowChange);
			if (SBDL::mouseInRect(arrowChange) && SBDL::Mouse.clicked())
			{
				arrow = sheep;
				arrowChangeCheck = false;
			}
			if (!arrowChangeCheck && SBDL::mouseInRect(arrowChange) && SBDL::Mouse.clicked())
			{
				sheep = hedgehog;
				arrowChangeCheck = true;
			}
			if (arrowChangeCheck && SBDL::mouseInRect(arrowChange) && SBDL::Mouse.clicked())
			{
				hedgehog = arrow;
				arrowChangeCheck = false;
			}
			if (SBDL::mouseInRect(exitRec) && SBDL::Mouse.clicked())
			{
				SBDL::stop();
			}
			if (SBDL::mouseInRect(playbutton) && SBDL::Mouse.clicked())
			{
				onMenu = false;
			}
			SBDL::updateRenderScreen();
			SBDL::delay(30);
			continue;
		}

		if (SBDL::mouseInRect(replayRec) && SBDL::Mouse.clicked())
		{
			gameOver = false;
		}

		Texture scoreNum = SBDL::createFontTexture(font, "score:" + to_string(scoreSave), 0, 0, 200);
		Texture dostanceNum = SBDL::createFontTexture(font, "distance:" + to_string(distanceSave), 0, 0, 200);

		//game-over menu
		if (gameOver)
		{
			SBDL::showTexture(gameOvertex, gameOverRec);
			SBDL::showTexture(replayButton, replayRec);
			SBDL::showTexture(restartbutton, replayRec);
			SBDL::showTexture(endButton, endRec);
			SBDL::showTexture(gotoMenuTex, gotoMenuRec);
			SBDL::showTexture(gotoMenu, gotoMenuRec);
			SBDL::showTexture(scoreNum, scoreNUmRec);
			SBDL::showTexture(dostanceNum, distanceNUmRec);
			SBDL::showTexture(exitbuttonTex, exitRec2);
			SBDL::showTexture(exitbutton, exitRec2);
			if (SBDL::mouseInRect(exitRec2) && SBDL::Mouse.clicked())
			{
				SBDL::stop();
			}
			if (SBDL::mouseInRect(gotoMenuRec) && SBDL::Mouse.clicked())
			{
				onMenu = true;
			}
			if (SBDL::mouseInRect(replayRec) && SBDL::Mouse.clicked())
			{
				gameOver = true;
			}
			for (int i = 0, y = -100; i < 10; i++, y -= 70)
			{
				boxrecR[i] = { (rand() % 200) + 270,y,500,70 };
			}

			for (int i = 0, y = -100; i < 10; i++, y -= 70)
			{
				boxrecL[i] = { 0,y,rand() % 200,70 };
			}
			arrowrec.x = 235;
			arrowrec.y = 350;
			gemrec.x = 250;
			gemrec.y = -120;
			diamondrec.x = 200;
			diamondrec.y = -900;

			framecount = 0;
			score = 0;
			distance = 0;
			movebox = 5;
			movegem = 5;
			movearrow = -5;

			SBDL::updateRenderScreen();
			SBDL::delay(30);
			continue;
		}

		if (pause)
		{
			SBDL::showTexture(resumeBackgroundTex, resumeBackground);
			SBDL::showTexture(resumeButtonTex, resumeButton);
			SBDL::showTexture(resumeButtonWord, resumeButton);
			SBDL::showTexture(replayButton, replayRec);
			SBDL::showTexture(restartbutton, replayRec);
			SBDL::showTexture(gotoMenuTex, gotoMenuRec);
			SBDL::showTexture(gotoMenu, gotoMenuRec);
			if (SBDL::mouseInRect(resumeButton) && SBDL::Mouse.clicked())
			{
				pause = false;
			}
			if (SBDL::mouseInRect(gotoMenuRec) && SBDL::Mouse.clicked())
			{
				onMenu = true;
			}
			if (SBDL::mouseInRect(replayRec) && SBDL::Mouse.clicked())
			{
				pause = false;
				for (int i = 0, y = -100; i < 10; i++, y -= 70)
				{
					boxrecR[i] = { (rand() % 200) + 270,y,500,70 };
				}

				for (int i = 0, y = -100; i < 10; i++, y -= 70)
				{
					boxrecL[i] = { 0,y,rand() % 200,70 };
				}
				arrowrec.x = 235;
				arrowrec.y = 350;
				gemrec.x = 250;
				gemrec.y = -120;
				diamondrec.x = 200;
				diamondrec.y = -900;

				framecount = 0;
				score = 0;
				distance = 0;
				movebox = 5;
				movegem = 5;
				movearrow = -5;
			}
			SBDL::updateRenderScreen();
			SBDL::delay(30);
			continue;
		}

		//moving the gems and diamonds & frame-count
		gemrec.y += movegem;
		diamondrec.y += movegem;
		framecount++;
		distance += movebox;

		SBDL::showTexture(background, backgroundrec);

		//moving the boxes down-wards
		for (int i = 0; i < 10; i++)
		{
			SBDL::showTexture(box, boxrecR[i]);
			boxrecR[i].y +=movebox;
			if (boxrecR[i].y >= 600)
				boxrecR[i].y = -70;

		}
		for (int i = 0; i < 10; i++)
		{
			SBDL::showTexture(box, boxrecL[i]);
			boxrecL[i].y += movebox;
			if (boxrecL[i].y>= 600)
				boxrecL[i].y = -70;

		}

		SBDL::showTexture(gem, gemrec);

		//increasing speed
		if (framecount == 500)
		{
			movearrow--;
			movebox++;
			movegem++;
			framecount = 0;
		}

		//arrow & arrow's intersection with the sides
		if (SBDL::keyHeld(SDL_SCANCODE_SPACE))
		{
			SBDL::showTexture(arrow, -deg, arrowrec);
			arrowrec.x -= movearrow;
			if (arrowrec.x > 500 || arrowrec.x < 0)
			{
				scoreSave = score;
				distanceSave = distance;
				gameOver = true;
				SBDL::playSound(crashSound, 1);
			}
		}
		else
		{
			SBDL::showTexture(arrow, deg, arrowrec);
			arrowrec.x += movearrow;
			if (arrowrec.x > 500 || arrowrec.x < 0)
			{
				scoreSave = score;
				distanceSave = distance;
				gameOver = true;
				SBDL::playSound(crashSound, 1);
			}
		}
		
		SBDL::showTexture(diamond,diamondrec);
		SBDL::showTexture(scorebox, scoreboxrec);
		Texture scorebox2 = SBDL::createFontTexture(font, "score:            " + to_string(score), 254, 254, 254);
		SBDL::showTexture(scorebox2, scorebox2rect);
		Texture distancebox = SBDL::createFontTexture(font, "distance:            " + to_string(distance), 254, 254, 254);
		SBDL::showTexture(distancebox, distanceboxrect);
		
		for (int i = 0; i < 10; i++)
		{
			if (SBDL::hasIntersectionRect(arrowrec, boxrecR[i]))
			{
				scoreSave = score;
				distanceSave = distance;
				gameOver = true;
				SBDL::playSound(crashSound, 1);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (SBDL::hasIntersectionRect(arrowrec, boxrecL[i]))
			{
				scoreSave = score;
				distanceSave = distance;
				gameOver = true;
				SBDL::playSound(crashSound, 1);
			}
		}

		//pause button
		SBDL::showTexture(pausebuttonBackTex, pausebutton);
		SBDL::showTexture(pausebuttonTex, pausebuttonShape);

		if (SBDL::mouseInRect(pausebutton) && SBDL::Mouse.clicked())
		{
			pause = true;
		}

		//gem
		if (SBDL::hasIntersectionRect(arrowrec, gemrec))
		{
			gemrec = { (rand() % 70)+200,-600,25,25 }; 
			score++;
			SBDL::playSound(gemSound, 1);
		}
		else if(gemrec.y==600)
			gemrec = { (rand() % 70) + 200,-600,25,25 };

		//diamind
		if (SBDL::hasIntersectionRect(arrowrec, diamondrec))
		{
			diamondrec = { (rand() % 70) + 200,-2200,25,20 };
			score+=10;
			SBDL::playSound(gemSound, 1);
		}
		else if(diamondrec.y==600)
			diamondrec = { (rand() % 70) + 200,-2200,25,20 };

		SBDL::updateRenderScreen();
		SBDL::delay(30);

	}
}