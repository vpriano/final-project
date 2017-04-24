#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

class Game
{
protected:
	string game_name;
	string game_genre;
	string game_console;
	double game_graphic_score;
	double game_gameplay_score;
	double game_storyline_score;
	double overall_total_score;
	int number_of_scores; //store how many scores we have

public:
	Game(string name = "", string genre = "", string console = "", int graphic_score = 0, int gameplay_score = 0, int story_score = 0) :
		game_name(name), game_console(console),
		game_graphic_score(graphic_score), game_gameplay_score(gameplay_score), game_storyline_score(story_score)
	{
		game_genre = genre;
		overall_total_score = 0;
		number_of_scores = 0;
		next = NULL;
	}

	//-----------------------------------------------------------------------------
	// NOT SURE if this will be needed based on the order of the implementation
	// Linked list is created on ReadGameInfo()

	void setGameName(string name) { game_name = name; }
	void setGameGenre(string genre) { game_genre = genre; }
	void setConsoleName(string console) { game_console = console; }

	//-----------------------------------------------------------------------------

	string getGameName() { return game_name; }
	string getGameGenre() { return game_genre; }
	string getConsoleName() { return game_console; }

	void setScores(double graphic_score, double gameplay_score, double storyline_score)
	{
		if (number_of_scores == 0)//not set yet
		{
			game_graphic_score = graphic_score;
			game_gameplay_score = gameplay_score;
			game_storyline_score = storyline_score;
			number_of_scores = 1;
		}
		else // need average
		{
			game_graphic_score = (game_graphic_score * number_of_scores + graphic_score) / (number_of_scores + 1);
			game_gameplay_score = (game_gameplay_score * number_of_scores + gameplay_score) / (number_of_scores + 1);
			game_storyline_score = (game_storyline_score * number_of_scores + storyline_score) / (number_of_scores + 1);
			number_of_scores++;
		}
	}

	void virtual Compute() {}

	double getGraphicScore() { return game_graphic_score; }
	double getGameplayScore() { return game_gameplay_score; }
	double getStorylineScore() { return game_storyline_score; }
	double getOverallScore() { return overall_total_score; }
	Game* next;
};

class ActionGame : public Game
{
public:
	ActionGame(string name = "", string genre = "", string console = "", int graphic_score = 0, int gameplay_score = 0, int story_score = 0)
		: Game(name, genre, console, graphic_score, gameplay_score, story_score){
	}
	void Compute()
	{
		overall_total_score = (game_graphic_score / 10)*0.2 + (game_gameplay_score / 10) * 0.6 + (game_storyline_score / 10)*0.2;
	}
};

class RoleplayGame : public Game{
public:
	RoleplayGame(string name = "", string genre = "", string console = "", int graphic_score = 0, int gameplay_score = 0, int story_score = 0)
		: Game(name, genre, console, graphic_score, gameplay_score, story_score){
	}
	void Compute()
	{
		overall_total_score = (game_graphic_score / 10)*0.2 + (game_gameplay_score / 10) * 0.4 + (game_storyline_score / 10)*0.4;
	}
};

class StrategyGame : public Game{
public:
	StrategyGame(string name = "", string genre = "", string console = "", int graphic_score = 0, int gameplay_score = 0, int story_score = 0)
		: Game(name, genre, console, graphic_score, gameplay_score, story_score){
	}
	void Compute()
	{
		overall_total_score = (game_graphic_score / 10)*0.2 + (game_gameplay_score / 10) * 0.8;
	}
};

class SportGame : public Game{
public:
	SportGame(string name = "", string genre = "", string console = "", int graphic_score = 0, int gameplay_score = 0, int story_score = 0)
		: Game(name, genre, console, graphic_score, gameplay_score, story_score){
	}
	void Compute()
	{
		overall_total_score = (game_graphic_score / 10)*0.5 + (game_gameplay_score / 10) * 0.5;
	}
};

Game empty;
class Container
{
private:
public:
	Container(Game* game = NULL)
	{
		head = game;
	}

	Game* head;

	// lookup an existing game in the linked list. 
	Game* Search(string name)
	{
		Game* temp;
		//temp iterater
		temp = head;
		//loop the temp pointer
		while (temp != NULL)
		{
			if (temp->getGameName() == string(name))
				return temp;
			temp = temp->next;
		}
		return temp;
	}

	//add a new a game
	void AddGame(Game* game)
	{
		if (head == NULL)
			head = game;
		else
		{
			game->next = head;
			head = game;
		}
	}

	void DeleteList()
	{
		Game* temp = head;
		while (temp != NULL)
		{
			head = head->next;
			delete temp;
			temp = head;
		}
	}

	void Display(string genre1)
	{
		cout << "looking for the top game for " << genre1 << endl;
		Game* output = NULL;
		double score1 = 0;
		Game* temp = head;
		while (temp != NULL)
		{
			if (temp->getGameGenre() == genre1 && temp->getOverallScore() > score1)
			{
				output = temp;
				score1 = temp->getOverallScore();
			}
			temp = temp->next;
		}

		if (output == NULL)
		{
			cout << "can not find the game for " << genre1 << endl;
		}
		else
		{
			cout << "the highest score for " << genre1 << " is " << output->getGameName() << endl;
			cout << "game graphic score: " << output->getGraphicScore() << endl;
			cout << "game gameplay score: " << output->getGameplayScore() << endl;
			cout << "game storyline score: " << output->getStorylineScore() << endl;
			cout << "game total score: " << output->getOverallScore() << endl;
		}
	}

	void showall(string genre1)
	{
		Game* temp = head;
		while (temp != NULL)
		{
			if (temp->getGameGenre() == genre1)
				cout << temp->getGameName() << "\t" << temp->getOverallScore() << endl;
			temp = temp->next;
		}
	}
};

Container ReadGameInfo()
{
	Container linked_list;
	ifstream file;
	string temp_name, temp_genre, temp_console, name_dump = "";

	file.open("game.csv");
	// NAME DUMP to get the first line (the labels) of the .csv file
	getline(file, name_dump, ',');
	getline(file, name_dump, ',');
	getline(file, name_dump);

	while (getline(file, temp_name, ',')) {
		getline(file, temp_genre, ',');
		getline(file, temp_console);
		Game* newgame;
		//polymorphism usage
		if (temp_genre == "Action")
		{
			newgame = new ActionGame(temp_name, temp_genre, temp_console);
		}
		else if (temp_genre == "Role Playing")
		{
			newgame = new RoleplayGame(temp_name, temp_genre, temp_console);
		}
		else if (temp_genre == "Strategy")
		{
			newgame = new StrategyGame(temp_name, temp_genre, temp_console);
		}
		else
		{
			newgame = new SportGame(temp_name, temp_genre, temp_console);
		}
		linked_list.AddGame(newgame);
	}
	file.close();

	return linked_list;
}

void ReadScore(Container& linkedlist)
{
	ifstream file;
	string name_dump, string_graphics_score, string_gameplay_score, string_storyline_score = "";
	double double_graphics_score, double_gameplay_score, double_storyline_score = 0;

	file.open("score.csv");
	if (file.is_open())
	{
		// NAME DUMP to get the first line (the labels) of the .csv file
		getline(file, name_dump, ',');
		getline(file, name_dump, ',');
		getline(file, name_dump);

		Container* game_to_update = NULL;
		while (getline(file, name_dump, ',')) {
			getline(file, string_graphics_score, ',');
			getline(file, string_gameplay_score, ',');
			getline(file, string_storyline_score);

			double_graphics_score = atof(string_graphics_score.c_str()); // retrieve int from string for gameplay, graphics and storyline
			double_gameplay_score = atof(string_gameplay_score.c_str());
			double_storyline_score = atof(string_storyline_score.c_str());

			//search for the game
			Game* game_to_update = linkedlist.Search(name_dump);
			if (game_to_update == NULL)
			{
				cout << "the game to be scored: " << name_dump << "can not be found" << endl;
			}
			else
			{
				game_to_update->setScores(double_graphics_score, double_gameplay_score, double_storyline_score);
				//calculate total score
				game_to_update->Compute();
			}
		}

		file.close();
	}
	else
	{
		cerr << "Error, File can not be found, Terminate the program!" << endl;
		//terminate program
		exit(1);
	}
}

int main()
{
	Container linkedlist = ReadGameInfo();
	ReadScore(linkedlist);
	string genre1;
	cout << "please input the first genre to recommend: " << endl;
	getline(cin, genre1);
	//linkedlist.showall(genre1);
	linkedlist.Display(genre1);
	cout << "please input the second genre to recommend: " << endl;
	getline(cin, genre1);
	//linkedlist.showall(genre1);
	linkedlist.Display(genre1);
	return 0;
}