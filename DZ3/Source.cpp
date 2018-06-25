
#define num 27

#include "Dijkstra.h"
#include "Astar.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<functional>
#include<math.h>
#include<float.h>
#include<sstream>
#include<string.h>
#include<string>
#include<fstream>

using namespace std;
using namespace sf;


//sa 54 ide 20,20 sa 27 ide 40,40

bool converter(string temp) {
	stringstream ss(temp);
	bool t;
	ss >> t;
	return t;
}

int load(string filename, int grid[num][num]) {
	ifstream in(filename);
	
	if (!in) {
		cout << "Error::can not open file" << endl;
		return 1;
	}
	string line;
	int i = 0;
		while (getline(in, line)) {
			stringstream ss(line);
			string temp;
			for (int j = 0; j < num; j++) {
				getline(ss, temp, ',');
				grid[i][j] = converter(temp);
			}
			i++;
		}
	in.close();
	return 0;
}

int save(string filename, int grid[num][num]) {
	ofstream out(filename);
	if (!out) {
		cout << "Error:: can not open file" << endl;
		return 1;
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			out << grid[i][j] << ",";
		}
		out << endl;
	}
	out.close();
	return 0;
}

int main() {
	//int num = 4;
	//int *filled = new int[num * num];
	//int *grid = new int[num * num];
	//bool *sptSet = new bool[num * num];
	//bool *closedList = new bool[num * num];
	int grid[num][num];
	int filled[num][num];
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++) {
			if (i == 0 || i == num - 1 || j == 0 || j == num - 1)        //walls
				grid[i][j] = 0;        //0 == wall
			else
				grid[i][j] = 1;
		}
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++) {
			sptSet[i][j] = false;
			filled[i][j] = 0;
		}

	string filename = "file1.txt";
	bool loadanje = false;
	bool saveanje = false;
	memset(closedList, false, sizeof(closedList));        //Astar all unexplored
	int source_x = 2  , source_y = 3, dest_x = 23, dest_y = 20 ;      //Origin(2,3)->Goal(23,20) ===========>> (num - 2 max)  (1,1 min)
	Thread threadD(std::bind(&dijkstra,source_x, source_y, dest_x, dest_y, grid));
	Thread threadA(std::bind(&Astar, make_pair(source_x, source_y), make_pair(dest_x, dest_y), grid));
	Thread threadL(std::bind(&load,filename,grid));
	Thread threadS(std::bind(&save, filename, grid));

	RenderWindow window(VideoMode().getDesktopMode(), "Suma",Style::Fullscreen);
	//RenderWindow window(VideoMode(800, 600), "Grid", Style::Fullscreen);

	// Background
	Texture frame;
	if (!frame.loadFromFile("background.png"))
	{
		cout << "can not open background texture" << endl;
	}
	RectangleShape background(Vector2f(window.getSize().x, window.getSize().y));
	background.setTexture(&frame);

	// Music
	Music music;
	if (!music.openFromFile("8-bit_reggae.ogg")) {
		cout << "can not load music" << endl;
	}
	music.setLoop(true);
	music.play();

	// Text
	Font font;
	font.loadFromFile("KaushanScript-Regular.otf");
	Text text1("DIJKSTRA", font, 46);
	Text text2("A*", font, 50);
	Text text3("RESET", font, 50);
	Text lengthD(" ", font, 50);
	Text lengthA(" ", font, 50);
	Text Load("Load", font, 50);
	Text Save("Save", font, 50);
	Text Quit("Quit", font, 50);
	Text Back("Back", font, 50);
	text1.setFillColor(Color(185,122,87));
	text1.setOutlineThickness(4);
	text1.setOutlineColor(Color(128, 64, 0));
	//text2.setFillColor(Color::Black);
	text2.setFillColor(Color(185, 122, 87));
	text2.setOutlineThickness(4);
	text2.setOutlineColor(Color(128, 64, 0));
	//text3.setFillColor(Color::Black);
	text3.setFillColor(Color(185, 122, 87));
	text3.setOutlineThickness(4);
	text3.setOutlineColor(Color(128, 64, 0));
	//lengthD.setFillColor(Color::Black);
	lengthD.setFillColor(Color(185, 122, 87));
	//lengthA.setFillColor(Color::Black);
	lengthA.setFillColor(Color(185, 122, 87));
	//load
	Load.setFillColor(Color(185, 122, 87));
	Load.setOutlineThickness(4);
	Load.setOutlineColor(Color(128, 64, 0));
	//save
	Save.setFillColor(Color(185, 122, 87));
	Save.setOutlineThickness(4);
	Save.setOutlineColor(Color(128, 64, 0));
	//quit
	Quit.setFillColor(Color(185, 122, 87));
	Quit.setOutlineThickness(4);
	Quit.setOutlineColor(Color(128, 64, 0));
	//back
	Back.setFillColor(Color(185, 122, 87));
	Back.setOutlineThickness(4);
	Back.setOutlineColor(Color(128, 64, 0));
	//LSfileovi
	Text File1("File1", font, 50);
	File1.setFillColor(Color(185, 122, 87));
	File1.setOutlineThickness(4);
	File1.setOutlineColor(Color(128, 64, 0));
	Text File2("File2", font, 50);
	File2.setFillColor(Color(185, 122, 87));
	File2.setOutlineThickness(4);
	File2.setOutlineColor(Color(128, 64, 0));
	Text File3("File3", font, 50);
	File3.setFillColor(Color(185, 122, 87));
	File3.setOutlineThickness(4);
	File3.setOutlineColor(Color(128, 64, 0));
	Text File4("File4", font, 50);
	File4.setFillColor(Color(185, 122, 87));
	File4.setOutlineThickness(4);
	File4.setOutlineColor(Color(128, 64, 0));
	Text File5("File5", font, 50);
	File5.setFillColor(Color(185, 122, 87));
	File5.setOutlineThickness(4);
	File5.setOutlineColor(Color(128, 64, 0));
	Text File6("File6", font, 50);
	File6.setFillColor(Color(185, 122, 87));
	File6.setOutlineThickness(4);
	File6.setOutlineColor(Color(128, 64, 0));
	Text File7("File7", font, 50);
	File7.setFillColor(Color(185, 122, 87));
	File7.setOutlineThickness(4);
	File7.setOutlineColor(Color(128, 64, 0));
	Text File8("File8", font, 50);
	File8.setFillColor(Color(185, 122, 87));
	File8.setOutlineThickness(4);
	File8.setOutlineColor(Color(128, 64, 0));

	// Shapes
	pair<int, int> velicina_polja = {40,40};  //num,num
	RectangleShape buttonStartD(Vector2f(250, 100));             //75, 25
	Texture gumb1;
	Texture gumb2;
	if (!gumb2.loadFromFile("gumb2.png")) {
		cout << "can not open button texture" << endl;
	}
	if (!gumb1.loadFromFile("gumb1.png")) {
		cout << "can not open button texture" << endl;
	}
	//buttonStartD.setFillColor(Color(0, 175, 0));
	buttonStartD.setTexture(&gumb1);
	RectangleShape buttonStartA(Vector2f(250, 100));
	//buttonStartA.setFillColor(Color(0, 175, 0));
	buttonStartA.setTexture(&gumb1);
	RectangleShape displayD(Vector2f(250, 100));
	displayD.setTexture(&gumb1);
	//displayD.setFillColor(Color::White);
	//displayD.setOutlineThickness(4);
	RectangleShape displayA(Vector2f(250, 100));
	displayA.setTexture(&gumb1);
	//displayA.setFillColor(Color::White);
	//displayA.setOutlineThickness(4);
	//displayA.setOutlineColor(Color(0, 0, 0));

	RectangleShape rectangle(Vector2f(velicina_polja.first, velicina_polja.second));
	Texture grass;
	if (!grass.loadFromFile("grass.png")) {
		cout << "Can not load texture png" << endl;
	}
	//rectangle.setFillColor(Color::White);
	rectangle.setTexture(&grass);
	RectangleShape brectangle(Vector2f(velicina_polja.first, velicina_polja.second));
	Texture tree;
	if (!tree.loadFromFile("tree.png")) {
		cout << "Can not load texture png" << endl;
	}
	brectangle.setTexture(&tree);
	//brectangle.setFillColor(Color::Black);
	RectangleShape grectangle(Vector2f(velicina_polja.first, velicina_polja.second));
	Texture mrvice_kruha;
	if (!mrvice_kruha.loadFromFile("mrvice_kruha.png")) {
		cout << "Can not load texture png" << endl;
	}
	grectangle.setTexture(&mrvice_kruha);
	//grectangle.setFillColor(Color::Green);
	//grectangle.setOutlineThickness(1);
	//grectangle.setOutlineColor(Color::Red);

	RectangleShape mrectangle(Vector2f(velicina_polja.first, velicina_polja.second));
	mrectangle.setTexture(&mrvice_kruha);
	//mrectangle.setFillColor(Color::Magenta);
	//mrectangle.setOutlineThickness(1);
	//mrectangle.setOutlineColor(Color::Red);
	RectangleShape blueRectangle(Vector2f(velicina_polja.first, velicina_polja.second));
	Texture start;
	if (!start.loadFromFile("Ivica.png")) {
		cout << "Can not load texture png" << endl;
	}
	//blueRectangle.setFillColor(Color::Blue);
	//blueRectangle.setOutlineThickness(1);
	//blueRectangle.setOutlineColor(Color::Red);
	blueRectangle.setTexture(&start);
	RectangleShape rrectangle(Vector2f(velicina_polja.first, velicina_polja.second));
	Texture finish;
	if (!finish.loadFromFile("finish.png")) {
		cout << "Can not load texture png" << endl;
	}
	rrectangle.setTexture(&finish);
	//rrectangle.setFillColor(Color::Red);
	//rrectangle.setOutlineThickness(1);
	//rrectangle.setOutlineColor(Color::Red);

	RectangleShape yrectangle(Vector2f(velicina_polja.first, velicina_polja.second));
	Texture grass3;
	if (!grass3.loadFromFile("grass3.png")) {
		cout << "Can not load texture png" << endl;
	}
	yrectangle.setTexture(&grass3);
	//yrectangle.setFillColor(Color::Yellow);

	RectangleShape reset(Vector2f(250, 100));
	//reset.setFillColor(Color::Yellow);
	reset.setTexture(&gumb1);

	RectangleShape load(Vector2f(250, 100));
	load.setTexture(&gumb1);

	RectangleShape save(Vector2f(250, 100));
	save.setTexture(&gumb1);

	RectangleShape quit(Vector2f(250, 100));
	quit.setTexture(&gumb1);

	RectangleShape back(Vector2f(250, 100));
	back.setTexture(&gumb1);

	//LSgumbovi
	RectangleShape file1(Vector2f(250, 100));
	file1.setTexture(&gumb1);
	RectangleShape file2(Vector2f(250, 100));
	file2.setTexture(&gumb1);
	RectangleShape file3(Vector2f(250, 100));
	file3.setTexture(&gumb1);
	RectangleShape file4(Vector2f(250, 100));
	file4.setTexture(&gumb1);
	RectangleShape file5(Vector2f(250, 100));
	file5.setTexture(&gumb1);
	RectangleShape file6(Vector2f(250, 100));
	file6.setTexture(&gumb1);
	RectangleShape file7(Vector2f(250, 100));
	file7.setTexture(&gumb1);
	RectangleShape file8(Vector2f(250, 100));
	file8.setTexture(&gumb1);

	// Display
			while (window.isOpen()) {
				bool set_start = false;
				bool set_end = false;
				int razmak_x = velicina_polja.first;
				int razmak_y = velicina_polja.second;
				int konacna_velicina_x = num * velicina_polja.first - razmak_x;
				int konacna_velicina_y = num * velicina_polja.second - razmak_y;
				Event event;
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyPressed&& event.key.code == Keyboard::Space)
						window.close();
					if (event.type == Event::MouseButtonPressed&&event.mouseButton.button == Mouse::Left) {
						int X = event.mouseButton.x;
						int Y = event.mouseButton.y;
						int col = X / velicina_polja.first;
						int row = Y / velicina_polja.second;
						if (grid[row][col] == 0 && row < num && col < num)
							grid[row][col] = 1;
						else if (row < num && col < num)
							grid[row][col] = 0;
						cout << "Cell " << row << " , " << col << " state is: " << grid[row][col] << endl;
						if (X > buttonStartD.getPosition().x && X < buttonStartD.getPosition().x + buttonStartD.getSize().x && Y>buttonStartD.getPosition().y && Y < buttonStartD.getPosition().y + buttonStartD.getSize().y && !loadanje && !saveanje) {
							for (int i = 0; i <= konacna_velicina_y; i += razmak_y) {
								for (int j = 0; j <= konacna_velicina_x; j += razmak_x) {
									sptSet[(i / razmak_y)][(j / razmak_x)] = false;
									closedList[(i / razmak_y)][(j / razmak_x)] = false;
								}
							}
							if (!pathD.empty()) {
								for (int i = 0; i < pathD.size(); i++) {
									grectangle.setPosition(pathD[i].second * velicina_polja.first, pathD[i].first * velicina_polja.second);     //draw Dpath solved
									window.draw(grectangle);        //final pathD
									filled[pathD[i].first][pathD[i].second] = 0;                     // x < - > y
								}
							}
							if (!pathA.empty()) {
								for (int i = 0; i < pathA.size(); i++) {
									mrectangle.setPosition(pathA[i].second * velicina_polja.first, pathA[i].first * velicina_polja.second);     //draw Apath solved
									window.draw(mrectangle);        //final pathA
									filled[pathA[i].first][pathA[i].second] = 0;
								}
							}
							pathA.clear();
							pathD.clear();
							threadD.launch();
						}
						if (X > buttonStartA.getPosition().x && X < buttonStartA.getPosition().x + buttonStartA.getSize().x && Y>buttonStartA.getPosition().y && Y < buttonStartA.getPosition().y + buttonStartA.getSize().y && !loadanje && !saveanje) {
							for (int i = 0; i <= konacna_velicina_x; i += razmak_x) {
								for (int j = 0; j <= konacna_velicina_y; j += razmak_y) {
									closedList[(i / razmak_y)][(j / razmak_x)] = false;
									sptSet[(i / razmak_y)][(j / razmak_x)] = false;
								}
							}
							if (!pathA.empty()) {
								for (int i = 0; i < pathA.size(); i++) {
									mrectangle.setPosition(pathA[i].second * velicina_polja.first, pathA[i].first * velicina_polja.second);     //draw Apath solved
									window.draw(mrectangle);        //final pathA
									filled[pathA[i].first][pathA[i].second] = 0;
								}
							}
							if (!pathD.empty()) {
								for (int i = 0; i < pathD.size(); i++) {
									grectangle.setPosition(pathD[i].second * velicina_polja.first, pathD[i].first * velicina_polja.second);     //draw Dpath solved
									window.draw(grectangle);        //final pathD
									filled[pathD[i].first][pathD[i].second] = 0;                     // x < - > y
								}
							}
							pathD.clear();
							pathA.clear();
							threadA.launch();
						}
						if (X > reset.getPosition().x && X < reset.getPosition().x + reset.getSize().x && Y>reset.getPosition().y && Y < reset.getPosition().y + reset.getSize().y && !loadanje && !saveanje) {
							//reset
							pathA.clear();
							pathD.clear();
							for (int i = 0; i <= konacna_velicina_y; i += razmak_y) {
								for (int j = 0; j <= konacna_velicina_x; j += razmak_x) {
									//if (grid[(i / razmak_y) ][ (j / razmak_x)] == 0) {
									//	brectangle.setOutlineThickness(2);
									//	brectangle.setOutlineColor(Color::Red);
									//	brectangle.setPosition(j, i);
									//	window.draw(brectangle);        //User's obstacle
									//}
									//grid[i / razmak][j / razmak] = 1;           //grid za SVE zidove
									sptSet[(i / razmak_y)][(j / razmak_x)] = false;
									closedList[(i / razmak_y)][(j / razmak_x)] = false;
									filled[(i / razmak_y)][(j / razmak_x)] = 0;           // popunjen zavrsni put
								}
							}
						}
						if (X > load.getPosition().x && X < load.getPosition().x + load.getSize().x && Y>load.getPosition().y && Y < load.getPosition().y + load.getSize().y && !loadanje && !saveanje) {
							//load
							loadanje = true;
						}
						if (X > save.getPosition().x && X < save.getPosition().x + save.getSize().x && Y>save.getPosition().y && Y < save.getPosition().y + save.getSize().y && !loadanje && !saveanje) {
							//save
							saveanje = true;
						}
						if (X > quit.getPosition().x && X < quit.getPosition().x + quit.getSize().x && Y>quit.getPosition().y && Y < quit.getPosition().y + quit.getSize().y && !loadanje && !saveanje) {
							//quit
							window.close();
						}
						if (X > back.getPosition().x && X < back.getPosition().x + back.getSize().x && Y>back.getPosition().y && Y < back.getPosition().y + back.getSize().y && (loadanje || saveanje)) {
							//back
							loadanje = false;
							saveanje = false;
						}
						//LKONTROLA
						if (X > file1.getPosition().x && X < file1.getPosition().x + file1.getSize().x && Y>file1.getPosition().y && Y < file1.getPosition().y + file1.getSize().y && loadanje && !saveanje) {
							//Lfile1
							filename = "file1.txt";
							threadL.launch();
							loadanje = false;
						}
						if (X > file2.getPosition().x && X < file2.getPosition().x + file2.getSize().x && Y>file2.getPosition().y && Y < file2.getPosition().y + file2.getSize().y && loadanje && !saveanje) {
							//Lfile2
							filename = "file2.txt";
							threadL.launch();
							loadanje = false;
						}
						if (X > file3.getPosition().x && X < file3.getPosition().x + file3.getSize().x && Y>file3.getPosition().y && Y < file3.getPosition().y + file3.getSize().y && loadanje && !saveanje) {
							//Lfile3
							filename = "file3.txt";
							threadL.launch();
							loadanje = false;
						}
						if (X > file4.getPosition().x && X < file4.getPosition().x + file4.getSize().x && Y>file4.getPosition().y && Y < file4.getPosition().y + file4.getSize().y && loadanje && !saveanje) {
							//Lfile4
							filename = "file4.txt";
							threadL.launch();
							loadanje = false;
						}
						if (X > file5.getPosition().x && X < file5.getPosition().x + file5.getSize().x && Y>file5.getPosition().y && Y < file5.getPosition().y + file5.getSize().y && loadanje && !saveanje) {
							//Lfile5
							filename = "file5.txt";
							threadL.launch();
							loadanje = false;
						}
						if (X > file6.getPosition().x && X < file6.getPosition().x + file6.getSize().x && Y>file6.getPosition().y && Y < file6.getPosition().y + file6.getSize().y && loadanje && !saveanje) {
							//Lfile6
							filename = "file6.txt";
							threadL.launch();
							loadanje = false;
						}
						if (X > file7.getPosition().x && X < file7.getPosition().x + file7.getSize().x && Y>file7.getPosition().y && Y < file7.getPosition().y + file7.getSize().y && loadanje && !saveanje) {
							//Lfile7
							filename = "file7.txt";
							threadL.launch();
							loadanje = false;
						}
						if (X > file8.getPosition().x && X < file8.getPosition().x + file8.getSize().x && Y>file8.getPosition().y && Y < file8.getPosition().y + file8.getSize().y && loadanje && !saveanje) {
							//Lfile8
							filename = "file8.txt";
							threadL.launch();
							loadanje = false;
						}
						//SKONTROLA
						if (X > file1.getPosition().x && X < file1.getPosition().x + file1.getSize().x && Y>file1.getPosition().y && Y < file1.getPosition().y + file1.getSize().y && !loadanje && saveanje) {
							//Sfile1
							filename = "file1.txt";
							threadS.launch();
							saveanje = false;
						}
						if (X > file2.getPosition().x && X < file2.getPosition().x + file2.getSize().x && Y>file2.getPosition().y && Y < file2.getPosition().y + file2.getSize().y && !loadanje && saveanje) {
							//Sfile2
							filename = "file2.txt";
							threadS.launch();
							saveanje = false;
						}
						if (X > file3.getPosition().x && X < file3.getPosition().x + file3.getSize().x && Y>file3.getPosition().y && Y < file3.getPosition().y + file3.getSize().y && !loadanje && saveanje) {
							//Sfile3
							filename = "file3.txt";
							threadS.launch();
							saveanje = false;
						}
						if (X > file4.getPosition().x && X < file4.getPosition().x + file4.getSize().x && Y>file4.getPosition().y && Y < file4.getPosition().y + file4.getSize().y && !loadanje && saveanje) {
							//Sfile4
							filename = "file4.txt";
							threadS.launch();
							saveanje = false;
						}
						if (X > file5.getPosition().x && X < file5.getPosition().x + file5.getSize().x && Y>file5.getPosition().y && Y < file5.getPosition().y + file5.getSize().y && !loadanje && saveanje) {
							//Sfile5
							filename = "file5.txt";
							threadS.launch();
							saveanje = false;
						}
						if (X > file6.getPosition().x && X < file6.getPosition().x + file6.getSize().x && Y>file6.getPosition().y && Y < file6.getPosition().y + file6.getSize().y && !loadanje && saveanje) {
							//Sfile6
							filename = "file6.txt";
							threadS.launch();
							saveanje = false;
						}
						if (X > file7.getPosition().x && X < file7.getPosition().x + file7.getSize().x && Y>file7.getPosition().y && Y < file7.getPosition().y + file7.getSize().y && !loadanje && saveanje) {
							//Sfile7
							filename = "file7.txt";
							threadS.launch();
							saveanje = false;
						}
						if (X > file8.getPosition().x && X < file8.getPosition().x + file8.getSize().x && Y>file8.getPosition().y && Y < file8.getPosition().y + file8.getSize().y && !loadanje && saveanje) {
							//Sfile8
							filename = "file8.txt";
							threadS.launch();
							saveanje = false;
						}
					}
					int X = Mouse::getPosition().x;
					int Y = Mouse::getPosition().y;
					if (X > buttonStartA.getPosition().x && X < buttonStartA.getPosition().x + buttonStartA.getSize().x && Y>buttonStartA.getPosition().y && Y < buttonStartA.getPosition().y + buttonStartA.getSize().y && !loadanje && !saveanje) {
						//buttonStartA.setFillColor(Color(0, 255, 0));
						buttonStartA.setTexture(&gumb2);
					}
					else {
						//buttonStartA.setFillColor(Color(0, 128, 0));
						buttonStartA.setTexture(&gumb1);
					}
					if (X > buttonStartD.getPosition().x && X < buttonStartD.getPosition().x + buttonStartD.getSize().x && Y>buttonStartD.getPosition().y && Y < buttonStartD.getPosition().y + buttonStartD.getSize().y && !loadanje && !saveanje) {
						//buttonStartA.setFillColor(Color(0, 255, 0));
						buttonStartD.setTexture(&gumb2);
					}
					else {
						//buttonStartA.setFillColor(Color(0, 128, 0));
						buttonStartD.setTexture(&gumb1);
					}
					if (X > reset.getPosition().x && X < reset.getPosition().x + reset.getSize().x && Y>reset.getPosition().y && Y < reset.getPosition().y + reset.getSize().y && !loadanje && !saveanje) {
						//buttonStartA.setFillColor(Color(0, 255, 0));
						reset.setTexture(&gumb2);
					}
					else {
						//buttonStartA.setFillColor(Color(0, 128, 0));
						reset.setTexture(&gumb1);
					}
					if (X > load.getPosition().x && X < load.getPosition().x + load.getSize().x && Y>load.getPosition().y && Y < load.getPosition().y + load.getSize().y && !loadanje && !saveanje) {
						//load
						load.setTexture(&gumb2);
					}
					else {
						load.setTexture(&gumb1);
					}
					if (X > save.getPosition().x && X < save.getPosition().x + save.getSize().x && Y>save.getPosition().y && Y < save.getPosition().y + save.getSize().y && !loadanje && !saveanje) {
						//save
						save.setTexture(&gumb2);
					}
					else {
						save.setTexture(&gumb1);
					}
					if (X > quit.getPosition().x && X < quit.getPosition().x + quit.getSize().x && Y>quit.getPosition().y && Y < quit.getPosition().y + quit.getSize().y && !loadanje && !saveanje) {
						//quit
						quit.setTexture(&gumb2);
					}
					else {
						quit.setTexture(&gumb1);
					}
					if (X > back.getPosition().x && X < back.getPosition().x + back.getSize().x && Y>back.getPosition().y && Y < back.getPosition().y + back.getSize().y && (loadanje || saveanje)) {
						//back
						back.setTexture(&gumb2);
					}
					else {
						back.setTexture(&gumb1);
					}
					//lijepi SL_gumbi
					if (X > file1.getPosition().x && X < file1.getPosition().x + file1.getSize().x && Y>file1.getPosition().y && Y < file1.getPosition().y + file1.getSize().y && (loadanje || saveanje)) {
						file1.setTexture(&gumb2);
					}
					else {
						file1.setTexture(&gumb1);
					}
					if (X > file2.getPosition().x && X < file2.getPosition().x + file2.getSize().x && Y>file2.getPosition().y && Y < file2.getPosition().y + file2.getSize().y && (loadanje || saveanje)) {
						file2.setTexture(&gumb2);
					}
					else {
						file2.setTexture(&gumb1);
					}
					if (X > file3.getPosition().x && X < file3.getPosition().x + file3.getSize().x && Y>file3.getPosition().y && Y < file3.getPosition().y + file3.getSize().y && (loadanje || saveanje)) {
						file3.setTexture(&gumb2);
					}
					else {
						file3.setTexture(&gumb1);
					}
					if (X > file4.getPosition().x && X < file4.getPosition().x + file4.getSize().x && Y>file4.getPosition().y && Y < file4.getPosition().y + file4.getSize().y && (loadanje || saveanje)) {
						file4.setTexture(&gumb2);
					}
					else {
						file4.setTexture(&gumb1);
					}
					if (X > file5.getPosition().x && X < file5.getPosition().x + file5.getSize().x && Y>file5.getPosition().y && Y < file5.getPosition().y + file5.getSize().y && (loadanje || saveanje)) {
						file5.setTexture(&gumb2);
					}
					else {
						file5.setTexture(&gumb1);
					}
					if (X > file6.getPosition().x && X < file6.getPosition().x + file6.getSize().x && Y>file6.getPosition().y && Y < file6.getPosition().y + file6.getSize().y && (loadanje || saveanje)) {
						file6.setTexture(&gumb2);
					}
					else {
						file6.setTexture(&gumb1);
					}
					if (X > file7.getPosition().x && X < file7.getPosition().x + file7.getSize().x && Y>file7.getPosition().y && Y < file7.getPosition().y + file7.getSize().y && (loadanje || saveanje)) {
						file7.setTexture(&gumb2);
					}
					else {
						file7.setTexture(&gumb1);
					}
					if (X > file8.getPosition().x && X < file8.getPosition().x + file8.getSize().x && Y>file8.getPosition().y && Y < file8.getPosition().y + file8.getSize().y && (loadanje || saveanje)) {
						file8.setTexture(&gumb2);
					}
					else {
						file8.setTexture(&gumb1);
					}
				}

				window.clear();
				window.draw(background);
				//set_button
				buttonStartD.setPosition(num * velicina_polja.first + 100, 90);  // num * num
				buttonStartA.setPosition(num * velicina_polja.first + 100, 265);
				displayD.setPosition(num * velicina_polja.first + 500, 90);        //Dijkstra length Background
				displayA.setPosition(num * velicina_polja.first + 500, 265);//                                             265
				reset.setPosition(num* velicina_polja.first + 100, 895);              //reset 100,440                          280
				load.setPosition(num* velicina_polja.first + 100, 720);
				save.setPosition(num* velicina_polja.first + 500, 720);                              //615
				quit.setPosition(num* velicina_polja.first + 500, 895);
				back.setPosition(num* velicina_polja.first + 300, 895);
				//lsgumbovi
				file1.setPosition(num * velicina_polja.first + 100, 100);
				file2.setPosition(num * velicina_polja.first + 500, 100);
				file3.setPosition(num * velicina_polja.first + 100, 275);
				file4.setPosition(num * velicina_polja.first + 500, 275);
				file5.setPosition(num * velicina_polja.first + 100, 450);
				file6.setPosition(num * velicina_polja.first + 500, 450);
				file7.setPosition(num * velicina_polja.first + 100, 625);
				file8.setPosition(num * velicina_polja.first + 500, 625);
				//set_text
				text1.setPosition(num * velicina_polja.first + 110, 110);       //Dijkstra text
				text2.setPosition(num * velicina_polja.first + 195, 285);
				text3.setPosition(num * velicina_polja.first + 135, 910);              //reset_text 135,455
				lengthD.setPosition(num * velicina_polja.first + 595, 105);     //Display Dijkstra length
				lengthA.setPosition(num * velicina_polja.first + 595, 280);                                             //280
				Load.setPosition(num * velicina_polja.first + 170, 735);     //Display Dijkstra length             //630
				Save.setPosition(num * velicina_polja.first + 570, 735);//                                     630
				Quit.setPosition(num * velicina_polja.first + 575, 905);
				Back.setPosition(num * velicina_polja.first + 370, 910);
				//lstextovi
				File1.setPosition(num * velicina_polja.first + 170, 115);//                    +70;+15
				File2.setPosition(num * velicina_polja.first + 570, 115);
				File3.setPosition(num * velicina_polja.first + 170, 290);
				File4.setPosition(num * velicina_polja.first + 570, 290);
				File5.setPosition(num * velicina_polja.first + 170, 465);
				File6.setPosition(num * velicina_polja.first + 570, 465);
				File7.setPosition(num * velicina_polja.first + 170, 640);
				File8.setPosition(num * velicina_polja.first + 570, 640);


				if (!loadanje && !saveanje) {
					//button draw
					window.draw(buttonStartD);      //Dijkstra launch
					window.draw(buttonStartA);      //Astar launch
					window.draw(reset);
					window.draw(displayD);
					window.draw(displayA);
					window.draw(load);
					window.draw(save);
					window.draw(quit);
					//text draw
					window.draw(text1);
					window.draw(text2);
					window.draw(text3);
					window.draw(Load);
					window.draw(Save);
					window.draw(Quit);
				}
				if (loadanje || saveanje) {
					//gumbi za loadanje 
					window.draw(file1);
					window.draw(file2);
					window.draw(file3);
					window.draw(file4);
					window.draw(file5);
					window.draw(file6);
					window.draw(file7);
					window.draw(file8);
					//tekst
					window.draw(File1);
					window.draw(File2);
					window.draw(File3);
					window.draw(File4);
					window.draw(File5);
					window.draw(File6);
					window.draw(File7);
					window.draw(File8);
				}
				if (loadanje || saveanje) {
					//Back button
					window.draw(back);
					window.draw(Back);
				}

				//draw path length
				stringstream ss1, ss2;
				ss1 << pathD.size();       //int2string
				lengthD.setString(ss1.str());
				ss2 << pathA.size();
				lengthA.setString(ss2.str());

				if (!loadanje && !saveanje) {
					window.draw(lengthD);
					window.draw(lengthA);
				}

				blueRectangle.setPosition(source_y * velicina_polja.first, source_x * velicina_polja.second);
				window.draw(blueRectangle);     //source
				filled[source_x][source_y] = 1;                    // x < - > y
				rrectangle.setPosition(dest_y * velicina_polja.first, dest_x * velicina_polja.second);
				window.draw(rrectangle);        //destination
				filled[dest_x][dest_y] = 1;                     // x < - > y

				//draw final destination path
				if (!pathA.empty()) {
					for (int i = 0; i < pathA.size(); i++) {
						mrectangle.setPosition(pathA[i].second * velicina_polja.first, pathA[i].first * velicina_polja.second);     //draw Apath solved
						window.draw(mrectangle);        //final pathA
						filled[pathA[i].first][pathA[i].second] = 1;
					}
				}
				if (!pathD.empty()) {
					for (int i = 0; i < pathD.size(); i++) {
						grectangle.setPosition(pathD[i].second * velicina_polja.first, pathD[i].first * velicina_polja.second);     //draw Dpath solved
						window.draw(grectangle);        //final pathD
						filled[pathD[i].first][pathD[i].second] = 1;                     // x < - > y
					}
				}
				for (int i = 0; i <= konacna_velicina_y; i += razmak_y)
					for (int j = 0; j <= konacna_velicina_x; j += razmak_x) {
						if (sptSet[(i / razmak_y)][(j / razmak_x)] == true && filled[(i / razmak_y)][(j / razmak_x)] == 0) {
							//yrectangle.setOutlineThickness(1);
							//yrectangle.setOutlineColor(Color::Black);
							yrectangle.setPosition(j, i);
							window.draw(yrectangle);        // Explored Cells by dijkstra
						}
						if (closedList[(i / razmak_y)][(j / razmak_x)] == true && filled[(i / razmak_y)][(j / razmak_x)] == 0) {
							//yrectangle.setOutlineThickness(1);
							//yrectangle.setOutlineColor(Color::Black);
							yrectangle.setPosition(j, i);
							window.draw(yrectangle);        // Explored  Cells by A*
						}
						if (grid[(i / razmak_y)][(j / razmak_x)] == 0) {
							//brectangle.setOutlineThickness(1);
							//brectangle.setOutlineColor(Color::White);
							brectangle.setPosition(j, i);
							window.draw(brectangle);        //User's obstacle
						}
						if (grid[(i / razmak_y)][(j / razmak_x)] == 1 && sptSet[(i / razmak_y)][(j / razmak_x)] == false && closedList[(i / razmak_y)][(j / razmak_x)] == false && filled[(i / razmak_y)][(j / razmak_x)] == 0) {     //not in dijkstra & A*
							//rectangle.setOutlineThickness(1);
							//rectangle.setOutlineColor(Color::Black);
							rectangle.setPosition(j, i);
							window.draw(rectangle);     //default white cells
						}
					}
				window.display();
			}
			//delete[] filled;
			//delete[] grid;
			//delete[] sptSet;
			//delete[] closedList;
	return 0;
}