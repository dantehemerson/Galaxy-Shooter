#include "FileScores.hpp"

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

#include <fstream>
#include <algorithm>

#include "Gallery.hpp"

using namespace std;

/* Función para comparar y ordenar los puntajes.
Ordenará de mayor a menor ya que asi se clasifican los puntajes de los jugadores.*/
bool compare(ScorePlayer a, ScorePlayer b) {
	return a.score > b.score;
}

const int FileScores::maxPlayers = 15; // Maximo numero de Puntajes de los jugadores que se guardarán en el archivo.
const string FileScores::filename = "data/scores"; /*Ubicación del archivo de scores.*/
list<ScorePlayer> FileScores::listScores;

FileScores::FileScores(const float& x, const float& y) : Actor(x, y) {

}

void FileScores::draw() const {
	static Gallery& gallery = Gallery::getSingleton();
	static int separator;

	/*Titulo de las Columnas*/
	al_draw_text(gallery.getFont(R::Font::VENUS_20), R::Color::WHITE, position.X() + 100, position.Y() + 10, ALLEGRO_ALIGN_CENTER, "RANK");
	al_draw_text(gallery.getFont(R::Font::VENUS_20), R::Color::WHITE, position.X() + 230, position.Y() + 10, ALLEGRO_ALIGN_CENTER, "NAME");
	al_draw_text(gallery.getFont(R::Font::VENUS_20), R::Color::WHITE, position.X() + 430, position.Y() + 10, ALLEGRO_ALIGN_CENTER, "SCORE");
	al_draw_text(gallery.getFont(R::Font::VENUS_20), R::Color::WHITE, position.X() + 580, position.Y() + 10, ALLEGRO_ALIGN_CENTER, "LEVEL");
	separator = 54;

	for (auto it = listScores.begin(); it != listScores.end(); it++, separator += 27) {
		/*Rank Number*/
		al_draw_textf(gallery.getFont(R::Font::VENUS_18), R::Color::WHITE, position.X() + 87, position.Y() + separator, NULL, "%i", separator / 27 - 1);
		/*Name*/
		al_draw_textf(gallery.getFont(R::Font::VENUS_18), R::Color::WHITE, position.X() + 180, position.Y() + separator, NULL, "%s", it->name.c_str());
		/*Score*/
		al_draw_textf(gallery.getFont(R::Font::VENUS_18), R::Color::WHITE, position.X() + 380, position.Y() + separator, NULL, "%i", it->score);
		/*Level*/
		al_draw_textf(gallery.getFont(R::Font::VENUS_18), R::Color::WHITE, position.X() + 560, position.Y() + separator, NULL, "%i", it->level);


	}
}

void FileScores::update() {


}

void FileScores::loadScores() {
	ifstream file;
	file.open(filename, ios::in);
	int scoreIn;
	int levelIn;
	string nameIn;
	if (file) {
		while (file >> scoreIn >> levelIn >> nameIn) {
			listScores.push_back({ scoreIn, levelIn, nameIn });
		}
		file.close();
	}
	else {

	}
	listScores.sort(compare);
}

void FileScores::saveScores() {
	ofstream fileOut(filename, ios::out);
	/*For test*/
	/*listScores.push_back({ 99992, 20, "DANTE" });
	listScores.push_back({ 32323, 18, "KATHERINE" });
	listScores.push_back({ 325431, 16, "FABIAN" });
	listScores.push_back({ 3234321, 1, "DAENERYS" });
	listScores.push_back({ 3253321, 1, "TYRYON" });
	listScores.push_back({ 321535, 2, "JON" });
	listScores.push_back({ 8787321, 3, "ARYA" });
	listScores.push_back({ 7655321, 5, "CERCEI" });
	listScores.push_back({ 635251, 6, "MELISSANDRE" });
	listScores.push_back({ 754321, 3, "ROBERT" });
	listScores.push_back({ 36621, 6, "RENLY" });
	listScores.push_back({ 3251, 3, "LIANNA" });
	listScores.push_back({ 3261, 5, "ROBB" });
	listScores.push_back({ 3421, 8, "VARYS" });
	listScores.push_back({ 32343441,9, "LITTLE_FINGER" });
	listScores.push_back({ 32341, 5, "BENJEN" });
	listScores.push_back({ 324541, 5, "BRAN" });
	listScores.push_back({ 324541, 14, "EDDARK" });
	listScores.push_back({ 32541, 3, "HOT_PIE" });
	listScores.push_back({ 32541, 13, "JONAS" });
	listScores.push_back({ 324541, 3, "MARGERY" });
	listScores.push_back({ 325451, 2, "LORAS" });
	listScores.sort(compare);*/
	if (fileOut) {
		int i = 1;
		/*Solo se guardaran los primeros y mas altos 15 punajes*/
		for (auto it = listScores.begin(); it != listScores.end() && i <= maxPlayers; it++, i++) {
			fileOut << it->score << ' ' << it->level << ' ' << it->name << endl;
		}
		fileOut.close();
	}
}

/*Limpia todos los scores de la lista. */
void FileScores::clearScores() {
	listScores.clear();
}

/*Agrega un nuevo puntaje y luego ordena la lista. */
void FileScores::pushScore(int score, int level, string name) {
	listScores.push_back({ score, level, name });
	listScores.sort(compare);
}

FileScores::~FileScores() {
	// Al finalizar el programa se llamará a la función saveScores() para guardar los puntajes en el archivo.
	saveScores();
}
