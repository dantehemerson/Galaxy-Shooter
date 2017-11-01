#pragma once

#ifndef FILESCORES_HPP
#define FILESCORES_HPP

#include <string>
#include <list>

#include "Actor.hpp"

struct ScorePlayer {
	int score; /*El puntaje que obtuvo hasta que terminó el juego*/
	int level; /* El nivel al que llegó el jugador. */
	std::string name; /*Nombre del jugador.*/
};



class FileScores : public Actor {
public:
	FileScores(const float& x, const float& y);

	virtual void draw() const override;
	virtual void update() override;

	/* Carga los puntajes del archivo, solo se ejecutá al iniciar el programa. */
	void loadScores();

	/*Guarda los puntajes en el archivo.*/
	void saveScores();

	// Añade un nuevo score.
	static void pushScore(int score, int level, std::string name);

	/*Borra todos los datos de la lista de puntajes, normalmente es llamado
	desde  Options->clear scores */
	static void clearScores();

	~FileScores();
private:
	static const int maxPlayers; // Máximo de puntajes que se guardarán y mostrarán en la pantalla.
	static const std::string filename; // Nombre del archivo donde se guardarán los puntajes.
	static std::list<ScorePlayer> listScores;
};
#endif // !FILESCORES_HPP
