/*
FileName: Ants_and_Doodlebugs.h
Written by: Joe Gelsomini
Time spent: A few hours
Challenges: Move took some time to figure out a working method for
Purpose of this assignment: Practice with inheritance
*/
#ifndef ANTS_AND_DOODLEBUGS_H
#define ANTS_AND_DOODLEBUGS_H
#include<iostream>
#include<vector>
#include<windows.h>
#include<time.h>

const int MAX_WIDTH = 20;
const int MAX_HEIGHT = 20;

struct Coord {
	int x;
	int y;
};

void gotoxy(Coord index)
{
	COORD c{ index.x,index.y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class World {
	friend class Organism;
	friend class Ant;
	friend class Doodlebug;
public:
	//2d array holding all the creatures and empty tiles of the world
	Organism* organisms[MAX_WIDTH][MAX_HEIGHT];
	void init_world();
	void init_critters();
	//void init_doodlebugs();
	void run_simulation();
	
	int world_width() { return MAX_WIDTH; }
	int world_height() { return MAX_HEIGHT; }
};

//typedef Organism* World[MAX_WIDTH][MAX_HEIGHT];

//the standard empty tile class
class Organism {
	Coord location;
	char tag;//the char that will be printed at the organisms location
	World* home;
public:
	Coord random_adj_cell();
	Organism() {}//default constructor
	Organism(Coord loc, World* board) { location = loc; home = board; tag = ' '; }
	virtual ~Organism() {}
	Coord get_loc() { return location; }
	void set_loc(Coord loc) { location = loc; }
	char get_tag() { return tag; }
	World* get_world() { return home; }
	void set_world(World* world) { home = world; }
	void set_tag(char c) { tag = c; }

	//virtual move function. Base class does not move, though it may swap with other tiles
	virtual void move() {}
};


class Ant : public Organism {
	//char tag = 'O';
	int breedTimer;

	//swap an ant with an empty tile only
	void swap(Organism* tile)
	{
		Coord temp_coord = this->get_loc();

		//copy the ant to the new location
		this->set_loc(tile->get_loc());
		get_world()->organisms[tile->get_loc().x][tile->get_loc().y] = new Ant(*this);
		//delete this;
		//this = new Organism(temp_coord, get_world());
		get_world()->organisms[temp_coord.x][temp_coord.y] = new Organism(temp_coord, get_world());
		return;//?
	}
	//only used after an entity moves
	//repetitive gross syntax, try to clean up
	void breed() {
		Coord adjacent_loc;
		//4 locations to check
		for (int i = 0; i <= 3; i++)
		{
			adjacent_loc = get_loc();

			switch (i) {
			//look up
			case 0: 
				++adjacent_loc.y;
				break;
			//look down
			case 1:
				--adjacent_loc.y;
				break;
			//look right
			case 2:
				++adjacent_loc.x;
				break;
			//look left
			case 3:
				--adjacent_loc.x;
				break;
			}//end switch

			if (adjacent_loc.y < MAX_HEIGHT && adjacent_loc.y >= 0 &&
				adjacent_loc.x < MAX_WIDTH && adjacent_loc.x >= 0 &&
				get_world()->organisms[adjacent_loc.x][adjacent_loc.y]->get_tag() == ' ' )
				{
				//delete the empty tile and create a new organism
				delete get_world()->organisms[adjacent_loc.x][adjacent_loc.y];
				get_world()->organisms[adjacent_loc.x][adjacent_loc.y] = new Ant(adjacent_loc, get_world());
				break;
				}	

		}//end for loop

		breedTimer = 0;
		return;
	}//end breed

public:

	Ant(Coord loc, World* world) { set_loc(loc); breedTimer = 0; set_world(world); set_tag('O'); }

	//copy constructor
	Ant(Ant& old) { set_loc(old.get_loc()); breedTimer = old.breedTimer; ++breedTimer; set_world(old.get_world()); set_tag('O'); }

	virtual void move() {
		//4 possible locations to move
		int i = rand() % 4;
		Coord adjacent_loc = get_loc();
		
		switch (i) {
			//look up
		case 0:
			++adjacent_loc.y;
			break;
			//look down
		case 1:
			--adjacent_loc.y;
			break;
			//look right
		case 2:
			++adjacent_loc.x;
			break;
			//look left
		case 3:
			--adjacent_loc.x;
			break;
		}//end switch

		//check these new coords, if they are out of bounds, or occupied by another ant or doodlebug, give up and stay put
		if(adjacent_loc.x >= 0 && adjacent_loc.x < MAX_WIDTH && adjacent_loc.y >= 0 && adjacent_loc.y < MAX_HEIGHT)
			if (get_world()->organisms[adjacent_loc.x][adjacent_loc.y]->get_tag() == ' ')
			{
				//swap the empty tile with our little ant
				swap(get_world()->organisms[adjacent_loc.x][adjacent_loc.y]);
			}
		//stay put otherwise

		if (breedTimer >= 2)
			breed();
		return;
	}//end move
	
};

class Doodlebug : public Organism {
	int starveTimer;//starves after 3 time steps
	int breedTimer;//breeds after 8 time steps

	//returns coord of an adjacent ant
	//if no ants are adjacent, returns a random coord that it will move to
	//if no space is available, will return the doodlebugs current position
	Coord look_for_ants();
	void breed();
	void swap(Organism* tile);
public:
	virtual void move();

	Doodlebug(Coord loc, World* world);
	//copy constructor
	Doodlebug(Doodlebug& old, Coord newCoord);

};

////////////////////////World functions///////////////////////

void World::init_world()
{
	Coord index;
	//fill the world with tiles
	for (index.x = 0; index.x < world_width(); index.x++)
	{
		for (index.y = 0; index.y < world_height(); index.y++)
		{
			organisms[index.x][index.y] = new Organism(index, this);
		}
	}
}//end init world

void World::init_critters()
{
	Coord index{ 0,0 };
	std::vector<int> x;
	std::vector<int> y;
	srand(time(NULL));
	for (int i = 0; i < 105; i++)
		x.push_back(rand() % 20);
	for (int i = 0; i < 105; i++)
		y.push_back(rand() % 20);

	int count = 0;
	for (int i = 0; i < 100; i++)
	{
		index.x = x[i]; index.y = y[i];
		organisms[index.x][index.y] = new Ant(index, this);		
	}
	for (int i = 100; i < 105; i++)
	{
		index.x = x[i]; index.y = y[i];
		organisms[index.x][index.y] = new Doodlebug(index, this);
	}
}//end init critters



void World::run_simulation()
{
	std::vector<Organism*> movers;
	int num_db = 20;
	char tag;
	Coord index{ 0,0 };
	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{


			//display the world
			for (index.x = 0; index.x < world_width(); index.x++)
			{
				for (index.y = 0; index.y < world_height(); index.y++)
				{

					gotoxy(index);
					tag = organisms[index.x][index.y]->get_tag();
					if (tag == 'X')
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					}
					else if (tag == 'O')
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					}
					std::cout << tag;

				}
			}

			//std::cout << num_db << " Doodlebugs";

			// gather the Doodlebugs to move
			for (index.x = 0; index.x < world_width(); index.x++)
			{
				for (index.y = 0; index.y < world_height(); index.y++)
				{

					if (organisms[index.x][index.y]->get_tag() == 'X')
						movers.push_back(organisms[index.x][index.y]);


				}
			}
			num_db = movers.size();
			//move the Doodlebugs
			for (auto i = movers.begin(); i != movers.end(); i++)
				(*i)->move();
			movers.clear();

			//gather the ants to move
			for (index.x = 0; index.x < 20; index.x++)
			{
				for (index.y = 0; index.y < 20; index.y++)
				{

					if (organisms[index.x][index.y]->get_tag() == 'O')
						movers.push_back(organisms[index.x][index.y]);


				}
			}
			//movers.size();
			//move the ants
			for (auto i = movers.begin(); i != movers.end(); i++)
				(*i)->move();
			movers.clear();


			Sleep(500);
		}
	}//end loop
}

//////////////////////Organism functions///////////////////////

Coord Organism::random_adj_cell()
{
	//4 possible locations to move
	int i = rand() % 4;
	Coord adjacent_loc = get_loc();

	switch (i) {
		//look up
	case 0:
		++adjacent_loc.y;
		break;
		//look down
	case 1:
		--adjacent_loc.y;
		break;
		//look right
	case 2:
		++adjacent_loc.x;
		break;
		//look left
	case 3:
		--adjacent_loc.x;
		break;
	}//end switch

	if (adjacent_loc.x >= 0 && adjacent_loc.y >= 0 &&
		adjacent_loc.x < MAX_WIDTH && adjacent_loc.y < MAX_HEIGHT &&
		home->organisms[adjacent_loc.x][adjacent_loc.y]->tag == ' ')
		return adjacent_loc;
	else
		return location;
}



//////////////////////Doodlebug functions//////////////////////

Doodlebug::Doodlebug(Coord loc, World* world)
{
	set_loc(loc);
	set_world(world);
	set_tag('X');
	breedTimer = 0;
	starveTimer = 0;
}

//copy constructor
Doodlebug::Doodlebug(Doodlebug& old, Coord newCoord) {
	starveTimer = old.starveTimer;
	++starveTimer;
	breedTimer = old.breedTimer;
	++breedTimer;
	set_world(old.get_world());
	set_loc(newCoord);
	set_tag('X');
}//end copy constructor

void Doodlebug::breed()
{
	Coord adjacent_loc;

	//4 locations to check
	for (int i = 0; i <= 3; i++)
	{
		adjacent_loc = get_loc();

		switch (i) {
			//look up
		case 0:
			++adjacent_loc.y;
			break;
			//look down
		case 1:
			--adjacent_loc.y;
			break;
			//look right
		case 2:
			++adjacent_loc.x;
			break;
			//look left
		case 3:
			--adjacent_loc.x;
			break;
		}//end switch

		if (adjacent_loc.y < MAX_HEIGHT && adjacent_loc.y >= 0 &&
			adjacent_loc.x < MAX_WIDTH && adjacent_loc.x >= 0 &&
			get_world()->organisms[adjacent_loc.x][adjacent_loc.y]->get_tag() == ' ')
		{
			delete get_world()->organisms[adjacent_loc.x][adjacent_loc.y];
			get_world()->organisms[adjacent_loc.x][adjacent_loc.y] = new Doodlebug(adjacent_loc, get_world());
			break;//forgot this break,caused multiple Doodlebugs to spawn, looked cooler though
		}
	}//end for loop
}//end breed

void Doodlebug::swap(Organism* tile)
{
	Coord temp_coord = this->get_loc();
	Doodlebug* temp = this;

	//delete get_world()->organisms[tile->get_loc().x][tile->get_loc().y];
	get_world()->organisms[tile->get_loc().x][tile->get_loc().y] = new Doodlebug(*temp, tile->get_loc());

	//delete get_world()->organisms[temp_coord.x][temp_coord.y];
	get_world()->organisms[temp_coord.x][temp_coord.y] = new Organism(temp_coord, get_world());
	return;//?
}//end swap

Coord Doodlebug::look_for_ants()
{
	Coord adjacent_loc;

	//4 locations to check
	for (int i = 0; i <= 3; i++)
	{
		adjacent_loc = get_loc();

		switch (i) {
		//look up
		case 0:
			++adjacent_loc.y;
			break;
		//look down
		case 1:
			--adjacent_loc.y;
			break;
		//look right
		case 2:
			++adjacent_loc.x;
			break;
		//look left
		case 3:
			--adjacent_loc.x;
			break;
		}//end switch

		if (adjacent_loc.y < MAX_HEIGHT && adjacent_loc.y >= 0 &&
			adjacent_loc.x < MAX_WIDTH && adjacent_loc.x >= 0 &&
			get_world()->organisms[adjacent_loc.x][adjacent_loc.y]->get_tag() == 'O')
		{
			//found food
			starveTimer = 0;
			return adjacent_loc;
		}
	}//end for loop

	//no ants nearby, go somewhere random
	return random_adj_cell();
}

void Doodlebug::move() {


	if (starveTimer > 2)//he finna starve to death?
	{
		get_world()->organisms[get_loc().x][get_loc().y] =  new Organism(get_loc(),get_world());
		return;
	}
	
	//look for ants returns the coord of an adjacent ant, but if none are found
	//will return an adjacent random cell , or the current position if it chooses an occupied cell
	Coord loc = get_loc();
	Coord adj_loc = look_for_ants();
	if (adj_loc.x != loc.x || adj_loc.y != loc.y)
	{
		//move the Doodlebug to the new loc
		//get_world()->organisms[adj_loc.x][adj_loc.y] = new Doodlebug(*this, adj_loc);
		swap(get_world()->organisms[adj_loc.x][adj_loc.y]);
	}
	else
	{
		//starve and breed timer would be incremented in above constructor call
		++breedTimer;
		++starveTimer;
	}
	if (breedTimer > 7)
	{
		breed();
		breedTimer = 0;
	}
	return;
}//end move


#endif 

