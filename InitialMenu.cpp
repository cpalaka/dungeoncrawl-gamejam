#include "InitalMenu.h"

InitialMenu::InitialMenu() :
	showSwordText(0),
	showSpearText(0),
	showBowText(0),
	overSword(0),
	overSpear(0),
	overBow(0),
	randdone(1)
{
	
	desktop = sf::VideoMode::getDesktopMode();
	currentState = Start;
	done = false;

	//add the startscreen animation and set current anim
	introwalk.loadFromFile("resources/graphics/startwalk.png");
	startscreen.addAnimation(introwalk, "walk", 8, 0);
	startscreen.setCurrentAnim("walk");
	startscreen.xpos = desktop.width/2 -50;
	startscreen.ypos = desktop.height/2 - 40;

	pixelfont.loadFromFile("resources/fonts/Pixelated.ttf");
	normalfont.loadFromFile("resources/fonts/Semibold.ttf");

	sword.loadFromFile("resources/graphics/sword.png");
	spear.loadFromFile("resources/graphics/spear.png");
	bow.loadFromFile("resources/graphics/bow.png");
	swords.setTexture(sword);
	spears.setTexture(spear);
	bows.setTexture(bow);

	//set title screen text
		title.setFont(normalfont);
		title.setString("T I T L E");
		title.setCharacterSize(42);
		title.setColor(sf::Color::White);	
		fr = title.getLocalBounds();
		title.setOrigin(fr.width/2, fr.height/2);
		title.setPosition(desktop.width/2, desktop.height/2 -200);

		play.setFont(normalfont);
		play.setString("PRESS TO PLAY");
		play.setCharacterSize(28);
		play.setColor(sf::Color::White);
		fr = play.getLocalBounds();
		play.setOrigin(fr.width/2, fr.height/2);
		play.setPosition(desktop.width/2, desktop.height/2 +300);

		//set hero description text
		swordd.setFont(normalfont);
		swordd.setString("A powerful melee\nfighter with a\nslash type attack\ndirectly in front of him");
		swordd.setCharacterSize(16);
		swordd.setColor(sf::Color::White);
		fr = swordd.getLocalBounds();
		swordd.setOrigin(fr.width/2, fr.height/2);
		
		speard.setFont(normalfont);
		speard.setString("A moderately powerful\nfighter with a ranged\nthrust attack\ndirectly in front of him");
		speard.setCharacterSize(16);
		speard.setColor(sf::Color::White);
		fr = speard.getLocalBounds();
		speard.setOrigin(fr.width/2, fr.height/2);
		
		bowd.setFont(normalfont);
		bowd.setString("A modestly fierce\nranged fighter with\nan attack defined\nby his proficieny with\nthe bow");
		bowd.setCharacterSize(16);
		bowd.setColor(sf::Color::White);
		fr = bowd.getLocalBounds();
		bowd.setOrigin(fr.width/2, fr.height/2);

		//set stats text font
		hp.setFont(normalfont);
		hp.setString("Hit Points");
		hp.setCharacterSize(32);
		hp.setColor(sf::Color::White);
		hp.setPosition(500, desktop.height/2 - 40);

		damage.setFont(normalfont);
		damage.setString("Damage");
		damage.setCharacterSize(32);
		damage.setColor(sf::Color::White);
		damage.setPosition(500, desktop.height/2);

		speed.setFont(normalfont);
		speed.setString("Speed");
		speed.setCharacterSize(32);
		speed.setColor(sf::Color::White);
		speed.setPosition(500, desktop.height/2 + 40);

		randomize.setFont(normalfont);
		randomize.setString("Randomize");
		randomize.setCharacterSize(40);
		randomize.setColor(sf::Color::White);
		randomize.setPosition(400, desktop.height/2 + 80);

		cont.setFont(normalfont);
		cont.setString("I'm happy");
		cont.setCharacterSize(40);
		cont.setColor(sf::Color::White);
		cont.setPosition(650, desktop.height/2 + 80);

		hpv.setFont(normalfont);
		hpv.setCharacterSize(32);
		hpv.setColor(sf::Color::White);
		hpv.setPosition(450, desktop.height/2 - 40);

		damagev.setFont(normalfont);
		damagev.setCharacterSize(32);
		damagev.setColor(sf::Color::White);
		damagev.setPosition(450, desktop.height/2);

		speedv.setFont(normalfont);
		speedv.setCharacterSize(32);
		speedv.setColor(sf::Color::White);
		speedv.setPosition(450, desktop.height/2 + 40);
}

void InitialMenu::update(double deltatime, sf::Event evt)
{
	srand(time(0));
	switch(currentState)
	{
	case Start:
		startscreen.update(deltatime);
		
		//if we click play, go to next state
		if(evt.type == sf::Event::MouseButtonPressed)
		{
			currentState = HeroSelect;
		}
		break;
	case HeroSelect:
		fr = swords.getGlobalBounds();
		fr1 = spears.getGlobalBounds();
		fr2 = bows.getGlobalBounds();
		
		if(evt.type == sf::Event::MouseMoved)
		{
			mousepos = sf::Mouse::getPosition();
			overSword =mousepos.x > fr.left && mousepos.x < fr.left+100 && mousepos.y > fr.top && mousepos.y < fr.top +100;
			overSpear=mousepos.x > fr1.left && mousepos.x < fr1.left+100 && mousepos.y > fr1.top && mousepos.y < fr1.top +100;
			overBow=mousepos.x > fr2.left && mousepos.x < fr2.left+100 && mousepos.y > fr2.top && mousepos.y < fr2.top +100;
		}

		if(overSword)
		{
			showSwordText = true;
		} else {
			showSwordText = false;
		}

		if(overSpear)
		{
			showSpearText = true;
		} else {
			showSpearText = false;
		}

		if(overBow)
		{
			showBowText = true;
		} else {
			showBowText = false;
		}

		if(evt.type == sf::Event::MouseButtonPressed)
		{
			//if mouse is clicked over hero type,
			//save that hero type (int HeroValues struct)so player starts as it
			if(overSword)
			{
				v.herotype = 1;
				currentState = StatSelect;
			}
			else if(overSpear)
			{
				v.herotype =2;
				currentState = StatSelect;
			}
			else if(overBow)
			{
				v.herotype = 3;
				currentState = StatSelect;
			}
		}
		break;
	case StatSelect:
		fr = randomize.getGlobalBounds();
		fr1 = cont.getGlobalBounds();
		if(evt.type == sf::Event::MouseMoved)
		{
			mousepos = sf::Mouse::getPosition();
			overRand = mousepos.x < fr.left+fr.width;
			overCont = mousepos.x > fr1.left;
		}

		if(randdone)
		{
		if(v.herotype == 1)
		{
			v.HP = 90 + rand()%20;
			v.damage = 8 + rand()%8;
			v.speed = 8 + rand()%5;
		} 
		if(v.herotype == 2)
		{
			v.HP = 70 + rand()%30;
			v.damage = 7 + rand()%8;
			v.speed = 9 + rand()%5;
		}
		if(v.herotype == 3)
		{
			v.HP = 50 + rand()%30;
			v.damage = 7 + rand()%5;
			v.speed = 10 + rand()%5;
		}
		randdone = false;
		}
		if(evt.type == sf::Event::MouseButtonPressed)
		{
			//check if mouse is clicked over 
			//stat randomize or continue
			//save values in HeroValues
			if(overRand) randdone = true;
			if(overCont) {
				//currentState = Story;
				done = true;
			}

		}
		break;
	case Story:
		if(evt.type == sf::Event::MouseButtonPressed)
		{
			//check if continue is clicked
			//if it is, pass generated values back to level class
			done = true;
		}
		break;
	}
}

void InitialMenu::draw(sf::RenderWindow& window)
{
	switch(currentState)
	{
	case Start:
		startscreen.draw(window);
		//draw text
		window.draw(title);
		window.draw(play);
		break;
	case HeroSelect:
		//draw sprites of herotypes
		fr = swords.getLocalBounds();
		swords.setOrigin(fr.width/2, fr.height/2);
		swords.setPosition(desktop.width/2 - 300, 200);

		fr = spears.getLocalBounds();
		spears.setOrigin(fr.width/2, fr.height/2);
		spears.setPosition(desktop.width/2, 200);

		fr = bows.getLocalBounds();
		bows.setOrigin(fr.width/2, fr.height/2);
		bows.setPosition(desktop.width/2+300, 200);

		//draw hero descriptions
		vec = swords.getPosition();
		swordd.setPosition(vec.x, vec.y + 120);
		if(showSwordText) window.draw(swordd);

		vec = spears.getPosition();
		speard.setPosition(vec.x, vec.y + 120);
		if(showSpearText) window.draw(speard);

		vec = bows.getPosition();
		bowd.setPosition(vec.x, vec.y + 120);
		if(showBowText) window.draw(bowd);

		window.draw(swords);
		window.draw(spears);
		window.draw(bows);

		//draw hero role text
		//draw text description

		break;
	case StatSelect:
		//draw all text and textbuttons
		hpn = std::to_string(v.HP);
		damagen = std::to_string(v.damage);
		speedn = std::to_string(v.speed);

		window.draw(hp);
		window.draw(damage);
		window.draw(speed);
		window.draw(randomize);
		window.draw(cont);

		hpv.setString(hpn);
		damagev.setString(damagen);
		speedv.setString(speedn);
		window.draw(hpv);
		window.draw(damagev);
		window.draw(speedv);

		
		break;
	case Story:
		//generate story
		break;
	}
}

HeroValues InitialMenu::getValues()
{
	return v;
}