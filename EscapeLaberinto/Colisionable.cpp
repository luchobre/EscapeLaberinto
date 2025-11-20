#include "Colisionable.h"

bool Colisionable::isColisionable(Colisionable& col) const {
    return getBounds().intersects(col.getBounds());
}
