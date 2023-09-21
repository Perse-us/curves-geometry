
#include "curves.h"

///////////////////////////////
/// Circle

// Constructors
Circle::Circle(const double radius) { setRadius(radius); };
Circle::Circle(const Circle& source) { copyAction(source); }
Circle& Circle::operator=(const Circle& source) {
    if (this != &source) copyAction(source);
    return *this;
}

// Interface
Coords3D Circle::coordsByAngle(const double t) const {
    double X = cos(t) * radius;
    double Y = sin(t) * radius;
    return Coords3D{X, Y, 0};
}

// Getter/setter set
double Circle::getRadius() const {return radius; }
void Circle::setRadius(const double value) { radius = returnCorrectSize(value); }
CurveType Circle::getType() const {return CurveType::circle; }
CurveSizeSet Circle::getSizes() const {
CurveSizeSet sizes;
    sizes.radius = getRadius();
    return sizes;
}
void Circle::setSizes(const CurveSizeSet newSizes) { setRadius(newSizes.radius); }

// Private
template<typename Source>
void Circle::copyAction(const Source& source) { setRadius(source.radius); }

///////////////////////////////
/// Ellipse

// Constructors
Ellipse::Ellipse(const double  radiusX, const double radiusY) {
    setRadiusX(radiusX);
    setRadiusY(radiusY);
};
Ellipse::Ellipse(const Ellipse& source) { copyAction(source); }
Ellipse& Ellipse::operator=(const Ellipse& source) {
    if (this != &source) copyAction(source);
    return *this;
}
// Interface
Coords3D Ellipse::coordsByAngle(const double t) const {
    double largeRadiusAngle = t, largeRadius = radiusX, smallRadius = radiusY;
    if (radiusY > radiusX) {
        largeRadius = radiusY;
        smallRadius = radiusX;
        largeRadiusAngle = numPi / 2 - t;
    };
    double tRadius = 0;
    if (largeRadius != 0 || smallRadius != 0) tRadius = largeRadius * smallRadius /
            std::sqrt(smallRadius * smallRadius * std::pow(std::cos(largeRadiusAngle), 2)
            + largeRadius * largeRadius * std::pow(std::sin(largeRadiusAngle), 2));
    if (tRadius < 0) tRadius = -tRadius;
    double X = cos(t) * tRadius;
    double Y = sin(t) * tRadius;
    return Coords3D{X, Y, 0};
}
// Getter/setter set
CurveType Ellipse::getType() const {return CurveType::ellipse; }
double Ellipse::getRadiusX() const {return radiusX; }
double Ellipse::getRadiusY() const {return radiusY; }
CurveSizeSet Ellipse::getSizes() const {
    CurveSizeSet sizes;
    sizes.radiusX = getRadiusX();
    sizes.radiusY = getRadiusY();
    return sizes;
}
void Ellipse::setRadiusX(const double value) { radiusX = returnCorrectSize(value); }
void Ellipse::setRadiusY(const double value) { radiusY = returnCorrectSize(value); }
void Ellipse::setSizes(const CurveSizeSet newSizes) { copyAction(newSizes); }

// Private
template<typename Source>
void Ellipse::copyAction(const Source& source) {
    setRadiusX(source.radiusX);
    setRadiusY(source.radiusY);
}

///////////////////////////////
/// Ellipse

// Constructors
Helixe::Helixe(const double radius, const double step) {
    setRadius(radius);
    setStep(step);
};
Helixe::Helixe(const Helixe& source) { copyAction(source); }
Helixe& Helixe::operator=(const Helixe& source) {
    if (this != &source) copyAction(source);
    return *this;
}
// Interface
Coords3D Helixe::coordsByAngle(const double t) const {
    double X = cos(t) * radius;
    double Y = sin(t) * radius;
    double Z = t / 2 / numPi * step;
    return Coords3D{X, Y, Z};
}
CurveType Helixe::getType() const {return CurveType::helixe; }
double Helixe::getRadius() const {return radius; }
double Helixe::getStep() const {return step; }
// Getter/setter set
CurveSizeSet Helixe::getSizes() const {
    CurveSizeSet sizes;
    sizes.radius = getRadius();
    sizes.step = getStep();
    return sizes;
}
void Helixe::setRadius(const double value) { radius = returnCorrectSize(value); }
void Helixe::setStep(const double value) { step = returnCorrectSize(value); }
void Helixe::setSizes(const CurveSizeSet newSizes) { copyAction(newSizes); }

// Private
template<typename Source>
void Helixe::copyAction(const Source& source) {
    setRadius(source.radius);
    setStep(source.step);
}

