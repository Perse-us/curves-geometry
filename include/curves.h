#pragma once

#include <cmath>

enum CurveType {
    circle, ellipse, helixe
};

struct Coords3D {
    double X = 0;
    double Y = 0;
    double Z = 0;
    Coords3D(double X, double Y, double Z) : X(X), Y(Y), Z(Z) {};
};

struct CurveSizeSet {
    double radius = -1;
    double radiusX = -1;
    double radiusY = -1;
    double step = -1;
};

class Curve {
public:
    static constexpr double numPi = 3.1415926535;
    static double returnCorrectSize(double size) {
        return (size > 0 ? size : 0);
    }
    virtual CurveType getType() const = 0;
    virtual Coords3D coordsByAngle(double t) const = 0;
    virtual CurveSizeSet getSizes() const = 0;
    virtual void setSizes(CurveSizeSet newSizes) = 0;
    virtual ~Curve() = default;
};

class Circle : public Curve {
    double radius = 0;
    template<typename Source>
    void copyAction(const Source& source);
public:
    // Constructors
    Circle(double radius);
    Circle(const Circle& source);
    Circle& operator=(const Circle& source);
    // Interface
    Coords3D coordsByAngle(double t) const override;
    // Getter/setter set
    double getRadius() const;
    void setRadius(double value);
    CurveType getType() const override;
    CurveSizeSet getSizes() const override;
    void setSizes(CurveSizeSet newSizes) override;
};

class Ellipse : public Curve {
    double radiusX = 0, radiusY = 0;
    template<typename Source>
    void copyAction(const Source& source);
public:
    // Constructors
    Ellipse(double  radiusX, double radiusY);
    Ellipse(const Ellipse& source);
    Ellipse& operator=(const Ellipse& source);
    // Interface
    Coords3D coordsByAngle(double t) const override;
    // Getter/setter set
    CurveType getType() const override;
    double getRadiusX() const;
    double getRadiusY() const;
    CurveSizeSet getSizes() const override;
    void setRadiusX(double value);
    void setRadiusY(double value);
    void setSizes(CurveSizeSet newSizes) override;
};

class Helixe : public Curve {
    double radius = 0, step = 0;
    template<typename Source>
    void copyAction(const Source& source);
public:
    // Constructors
    Helixe(double radius, double step);
    Helixe(const Helixe& source);
    Helixe& operator=(const Helixe& source);
    // Interface
    Coords3D coordsByAngle(double t) const override;
    // Getter/setter set
    CurveType getType() const override;
    double getRadius() const;
    double getStep() const;
    CurveSizeSet getSizes() const override;
    void setRadius(double value);
    void setStep(double value);
    void setSizes(CurveSizeSet newSizes) override;
};
