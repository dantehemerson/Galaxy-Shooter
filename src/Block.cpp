#include "Block.hpp"

#include "Gallery.hpp"
#include "Sprite.hpp"


Vector2 Block::referencePosition; /* Por defecto se inicia en (0, 0)*/

Block::Block(const float& coordX, const float& coordY, BlockType type) :
	type{ type },
	sprite(nullptr),
	bonusType(BonusType::NONE) {
	setCoord(coordX, coordY); /* Pasa las coordenadas a la posición en la que se pintara*/
	initType(); // Inicia el tipo
}


void Block::draw() const {
	if (lives > 0) {
		if (type == BlockType::SILVER) {
			if (sprite->animationFinish()) {
				if (lives == 1) { /*Agregar al último del sprite el ladrillo roto.*/
					al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), 812, 0, dimen.X(), dimen.Y(),
						position.X(), position.Y(), NULL);
				}
				else {
					al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), initPos.X(), initPos.Y(), dimen.X(), dimen.Y(),
						position.X(), position.Y(), NULL);
				}
			}
			else {
				sprite->draw();
			}
		}
		else if (type == BlockType::GOLD) {
			if (sprite->animationFinish()) {
				al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), initPos.X(), initPos.Y(), dimen.X(), dimen.Y(),
					position.X(), position.Y(), NULL);
			}
			else {
				sprite->draw();
			}
		}
		else {
			al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), initPos.X(), initPos.Y(), dimen.X(), dimen.Y(),
				position.X(), position.Y(), NULL);
		}
	}
}

void Block::update() {
	if (type == BlockType::SILVER || type == BlockType::GOLD) {
		sprite->update();
	}
}

void Block::setLives(short lives) {
	this->lives = lives;
}

short Block::getLives() const {
	return lives;
}

void Block::initType() {
	this->type = type;
	switch (type) {
	case BlockType::WHITE:
		initPos.setPosition(0, 0);
		lives = 1;
		break;
	case BlockType::ORANGE:
		initPos.setPosition(58, 0);
		lives = 1;
		break;
	case BlockType::LIGTH_BLUE:
		initPos.setPosition(116, 0);
		lives = 1;
		break;
	case BlockType::GREEN:
		initPos.setPosition(174, 0);
		lives = 1;
		break;
	case BlockType::RED:
		initPos.setPosition(0, 36);
		lives = 1;
		break;
	case BlockType::BLUE:
		initPos.setPosition(58, 36);
		lives = 1;
		break;
	case BlockType::PINK:
		initPos.setPosition(116, 36);
		lives = 1;
		break;
	case BlockType::YELLOW:
		initPos.setPosition(174, 36);
		lives = 1;
		break;
	case BlockType::SILVER:
		initPos.setPosition(232, 0); // Posición Inicial Normal
		lives = 2;
		sprite = new Sprite(this);

		/* Animación cuando colisione con la pelota.*/
		sprite->addFrame(R::Image::ITEMS, 290, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 348, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 406, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 464, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 522, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 580, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 638, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 696, 0, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 754, 0, 57, 35, 1);
		break;
	case BlockType::GOLD:
		initPos.setPosition(232, 36);
		lives = 3; /*Esto no se verifica en este tipo */
		sprite = new Sprite(this);

		/* Animación cuando colisione con la pelota.*/
		sprite->addFrame(R::Image::ITEMS, 290, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 348, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 406, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 464, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 522, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 580, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 638, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 696, 36, 57, 35, 1);
		sprite->addFrame(R::Image::ITEMS, 754, 36, 57, 35, 1);
		break;
	default:
		lives = 0;
		break;
	}
	// Ancho y alto		
	dimen.setPosition(57, 35);
}

float Block::getHeight() const {
	return 22;
}

float Block::getWidth() const {
	return 44;
}

BlockType Block::getType() const {
	return type;
}

void Block::setBonusType(BonusType bonus) {
	bonusType = bonus;
}

BonusType Block::getBonusType() const {
	return bonusType;
}

int Block::getValue() const {
	if (type != BlockType::GOLD) {
		return BlockValue[static_cast<size_t>(type)];
	}
	return 0;
}

void Block::setCoord(int x, int y) {
	position.setPosition(referencePosition.X() + x * getWidth(), referencePosition.Y() + y * getHeight());
}


void Block::die() {
	if (type != BlockType::GOLD) {
		lives--;
	}

	if (type == BlockType::SILVER) {
		sprite->reinit();
	}
	else if (type == BlockType::GOLD) {
		sprite->reinit();
	}
}

Block::~Block() {
	if (sprite) { delete sprite; }
}