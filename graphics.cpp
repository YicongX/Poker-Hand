#include <iostream>
#include <cmath>
#include <string>

#include "graphics.h"
#include "generic.h"
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "ysglfontdata.h"


MainData::MainData() {
	nPics = 0;
	png = nullptr;
	texId = nullptr;
}
MainData::MainData(const int num) {
	nPics = num;
	png = new YsRawPngDecoder[num];
	texId = new GLuint[num];
}
void MainData::CleanUp() {
	if (png != nullptr || texId != nullptr) {
		delete[] png;
		delete[] texId;
		png = nullptr;
		texId = nullptr;
	}
}
MainData::~MainData() {
	CleanUp();
}
YsRawPngDecoder* MainData::getPNGPointer() const
{
	if (png != nullptr) {
		return png;
	}
}
GLuint* MainData::getTexPointer() const
{
	if (texId != nullptr) {
		return texId;
	}
}
int MainData::getNumPics() const
{
	return nPics;
}
void MainData::Create(const int x)
{
	if (png != nullptr || texId != nullptr) {
		CleanUp();
	}
	nPics = x;
	png = new YsRawPngDecoder[nPics];
	texId = new GLuint[nPics];
}
void MainData::DecodeImages() {

	// These indices have to be used to display images.
	// Line 242 -> graphics.cpp -> Function to recover these indices from rank and suit.

	std::cout << "Reading the images, please wait...\n";

	getPNGPointer()[0].Decode("red_back.png");
	// rank = 1, all suits
	getPNGPointer()[1].Decode("AC.png");
	getPNGPointer()[2].Decode("AD.png");
	getPNGPointer()[3].Decode("AH.png");
	getPNGPointer()[4].Decode("AS.png");
	// rank = 2, all suits
	getPNGPointer()[5].Decode("2C.png");
	getPNGPointer()[6].Decode("2D.png");
	getPNGPointer()[7].Decode("2H.png");
	getPNGPointer()[8].Decode("2S.png");
	// rank = 3, all suits
	getPNGPointer()[9].Decode("3C.png");
	getPNGPointer()[10].Decode("3D.png");
	getPNGPointer()[11].Decode("3H.png");
	getPNGPointer()[12].Decode("3S.png");
	// rank = 4, all suits
	getPNGPointer()[13].Decode("4C.png");
	getPNGPointer()[14].Decode("4D.png");
	getPNGPointer()[15].Decode("4H.png");
	getPNGPointer()[16].Decode("4S.png");
	// rank = 5, all suits
	getPNGPointer()[17].Decode("5C.png");
	getPNGPointer()[18].Decode("5D.png");
	getPNGPointer()[19].Decode("5H.png");
	getPNGPointer()[20].Decode("5S.png");
	// rank = 6, all suits
	getPNGPointer()[21].Decode("6C.png");
	getPNGPointer()[22].Decode("6D.png");
	getPNGPointer()[23].Decode("6H.png");
	getPNGPointer()[24].Decode("6S.png");
	// rank = 7, all suits
	getPNGPointer()[25].Decode("7C.png");
	getPNGPointer()[26].Decode("7D.png");
	getPNGPointer()[27].Decode("7H.png");
	getPNGPointer()[28].Decode("7S.png");
	// rank = 8, all suits
	getPNGPointer()[29].Decode("8C.png");
	getPNGPointer()[30].Decode("8D.png");
	getPNGPointer()[31].Decode("8H.png");
	getPNGPointer()[32].Decode("8S.png");
	// rank = 9, all suits
	getPNGPointer()[33].Decode("9C.png");
	getPNGPointer()[34].Decode("9D.png");
	getPNGPointer()[35].Decode("9H.png");
	getPNGPointer()[36].Decode("9S.png");
	// rank = 10, all suits
	getPNGPointer()[37].Decode("10C.png");
	getPNGPointer()[38].Decode("10D.png");
	getPNGPointer()[39].Decode("10H.png");
	getPNGPointer()[40].Decode("10S.png");
	// rank = 11, all suits
	getPNGPointer()[41].Decode("JC.png");
	getPNGPointer()[42].Decode("JD.png");
	getPNGPointer()[43].Decode("JH.png");
	getPNGPointer()[44].Decode("JS.png");
	// rank = 12, all suits
	getPNGPointer()[45].Decode("QC.png");
	getPNGPointer()[46].Decode("QD.png");
	getPNGPointer()[47].Decode("QH.png");
	getPNGPointer()[48].Decode("QS.png");
	// rank = 13, all suits
	getPNGPointer()[49].Decode("KC.png");
	getPNGPointer()[50].Decode("KD.png");
	getPNGPointer()[51].Decode("KH.png");
	getPNGPointer()[52].Decode("KS.png");

	getPNGPointer()[53].Decode("png1.png");
	getPNGPointer()[54].Decode("welcome.png");
	getPNGPointer()[55].Decode("sevenup.png");
	

	for (int i = 0; i < getNumPics(); ++i) {
		getPNGPointer()[i].Flip();
	}
}

std::vector<int> MainData::getWindowDimensions() const
{
	return windowDims;
}

void MainData::setWindowDimensions(const int w, const int h)
{
	windowDims.push_back(w); windowDims.push_back(h);
}

void MainData::setPlayerName(std::string str) {
	playerName = str;
}
void MainData::setMoney(const int num) {
	// send num as the amount you want to decrease or increase the money
	money += num;
}
int MainData::getMoney() const {
	return money;
}
std::string MainData::getPlayerName() const {
	return playerName;
}
std::string MainData::getMoneyChar() const {
	auto m = std::to_string(money);
	return m;
}

void Render(const MainData& dat, const double x, const double y, const int index) {

	// Main function to display each card at given position

	glGenTextures(1, &dat.getTexPointer()[index]);
	glBindTexture(GL_TEXTURE_2D, dat.getTexPointer()[index]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		dat.getPNGPointer()[index].wid,
		dat.getPNGPointer()[index].hei,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		dat.getPNGPointer()[index].rgba);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dat.getTexPointer()[index]);

	// To scale and translate images use this code below -- 

	double scale = 1.;
	int xSize = dat.getPNGPointer()[index].wid * scale;
	int ySize = dat.getPNGPointer()[index].hei * scale;

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(x, y);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(x + xSize, y);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(x + xSize, y - ySize);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(x, y - ySize);
	glEnd();

	/*glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(x, y);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(x + dat.getPNGPointer()[index].wid, y);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(x + dat.getPNGPointer()[index].wid, y - dat.getPNGPointer()[index].hei);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(x, y - dat.getPNGPointer()[index].hei);
	glEnd();*/

	glDisable(GL_TEXTURE_2D);
}

void ColorBackGround()
{
	// Green background. will be replaced with image later

	glColor3ub(0, 90, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 800);
	glVertex2i(0, 800);
	glEnd();
	glFlush();
}

void PrintCardSolitaire(const MainData& dat, const Card c, double cx1, double cy1)
{
	Render(dat, cx1, cy1 + 100, getIndexForGraphics(c));

	auto r = std::to_string(c.getRank());

	char const* rchar = r.c_str();

	glColor3ub(255, 100, 100);
	glRasterPos2i(cx1, cy1);
	YsGlDrawFontBitmap10x14(rchar);
	glRasterPos2i(cx1, cy1 + 20);
	if (c.getSuit() == 0)
	{
		char const* schar = "Clubs";
		YsGlDrawFontBitmap10x14(schar);
	}
	else if (c.getSuit() == 1)
	{
		char const* schar = "Diamonds";
		YsGlDrawFontBitmap10x14(schar);
	}
	else if (c.getSuit() == 2)
	{
		char const* schar = "Hearts";
		YsGlDrawFontBitmap10x14(schar);
	}
	else if (c.getSuit() == 3)
	{
		char const* schar = "Spades";
		YsGlDrawFontBitmap10x14(schar);
	}
}

int getIndexForGraphics(const Card card)
{
 // To correspond the rank and suit to the indices in which the images are decoded. Line 56 -> graphics.cpp
 
	int r = card.getRank();
	int s = card.getSuit();
	int start_ind = 0 * std::pow(r, 0) + 1.29352467e+00 * std::pow(r, 1) + 1.56013800e+00 * std::pow(r, 2) + 3.42561238e-01 * std::pow(r, 3) +
		-8.22833655e-01 * std::pow(r, 4) + 4.46845893e-01 * std::pow(r, 5) + -1.33165320e-01 * std::pow(r, 6) + 2.50205427e-02 * std::pow(r, 7) +
		-3.09091570e-03 * std::pow(r, 8) + 2.51138004e-04 * std::pow(r, 9) + -1.29372905e-05 * std::pow(r, 10) + 3.83363400e-07 * std::pow(r, 11) +
		-4.97902763e-09 * std::pow(r, 12);


	int graphicsIndex = start_ind + s - 1;

	return graphicsIndex;
}

void DisplayGames() {
	glColor3ub(255, 0, 0);

	glRasterPos2d(20, 200);
	YsGlDrawFontBitmap16x20("Choose the game you want to play -- ");

	glRasterPos2d(20, 230);
	YsGlDrawFontBitmap16x20("1: BlackJack");

	glRasterPos2d(20, 260);
	YsGlDrawFontBitmap16x20("2: Poker");

	glRasterPos2d(20, 290);
	YsGlDrawFontBitmap16x20("3: Solitaire");

	glRasterPos2d(20, 320);
	YsGlDrawFontBitmap16x20("4: Seven Up");
}

void DisplayMoneyAndName(const MainData& dat)
{
	// player Name
	glColor3ub(255, 0, 0);
	glRasterPos2d(20, 50);
	YsGlDrawFontBitmap16x20("Player: ");
	glRasterPos2d(150, 50);
	YsGlDrawFontBitmap16x20(dat.getPlayerName().c_str());

	// show money
	glColor3ub(255, 0, 0);
	glRasterPos2d(20, 80);
	YsGlDrawFontBitmap16x20("Money remaining: $");
	glRasterPos2d(310, 80);
	YsGlDrawFontBitmap16x20(dat.getMoneyChar().c_str());
}

void EndGameOptions()
{
	// After each game give the user these options to continue playing the game (New game) or choose a different game in the main menu
	glColor3ub(0, 0, 0);
	glRasterPos2d(10, 790);
	YsGlDrawFontBitmap16x20("N: New Game");

	glRasterPos2d(230, 790);
	YsGlDrawFontBitmap16x20("M: Main Menu");

	glRasterPos2d(460, 790);
	YsGlDrawFontBitmap16x20("ESC: Quit Program");
}