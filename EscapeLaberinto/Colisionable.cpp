#include "Colisionable.h"

bool Colisionable::isColisionable(Colisionable& obj) const {
	return getBounds().intersects(obj.getBounds());
}