#ifndef INITIALMENU_H
#define INITIALMENU_H

#include "AnimationObject.h"
#include <time.h>

struct HeroValues {
	int herotype;//1 - sword, 2 - spear, 3 - bow
	int HP;
	int damage;
	int speed;//in seconds/1000
};

enum MenuState {Start,
				HeroSelect, 
				StatSelect, 
				Story 
			   };

class InitialMenu {
public:
	InitialMenu();
	void update(double, sf::Event);
	void draw(sf::RenderWindow&);
	HeroValues getValues();
	bool done;
private:
	sf::VideoMode desktop;
	sf::FloatRect fr, fr1, fr2, fr3;
	sf::Vector2f vec;
	sf::Vector2i mousepos;
	bool overSword, overSpear, overBow, overRand, overCont;
	bool randdone;

	AnimationObject startscreen;
	sf::Texture introwalk;
	sf::Font pixelfont, normalfont;
	bool showSwordText, showSpearText, showBowText;

	//add text for Title, play button, and credits
	sf::Text title, play;
	//add text describing role of herotype
	sf::Text swordd, speard, bowd;
	//add textures/sprites for swordsman/spearman/archer select menu
	sf::Texture sword, spear, bow;
	sf::Sprite swords, spears, bows;
	//add text for stats (HP, damage, speed)(vision if possible)
	sf::Text hp, damage, speed;
	sf::Text hpv, damagev, speedv;
	std::string hpn, damagen, speedn;
	//add textbutton to randomize above values
	sf::Text randomize;
	//add textbutton to continue (use same button for story screen)
	sf::Text cont;
	//add story text
	MenuState currentState;
	HeroValues v;
};

#endif INITIALMENU_H