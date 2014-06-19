#ifndef MouseReleaseEvent_H
#define MouseReleaseEvent_H

#include "cad/geometry/geocoordinate.h"
#include "cad/vo/entitydistance.h"

/**
  * Event that get's dispatched each time the mouse is moved.
  */
class MouseReleaseEvent  {
    public:
        MouseReleaseEvent() {
        }
        MouseReleaseEvent(const lc::geo::Coordinate& mousePosition, std::vector<lc::EntityDistance> entities) : _mousePosition(mousePosition), _entities(entities) {
        }

        lc::geo::Coordinate  mousePosition() const {
            return _mousePosition;
        }

        std::vector<lc::EntityDistance> entities() const {
            return _entities;
        }

    private:
         lc::geo::Coordinate _mousePosition;
         std::vector<lc::EntityDistance> _entities;
};

#endif // MouseReleaseEvent_H
