#include "curves.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <memory>

const double dblPres = .000001;
const int minRndSize = 1, maxRndSize = 50;
const double numPi = 3.1415926535;

CurveType getRandomCurveType() {
    return (CurveType)(std::rand() % (1 + (int)CurveType::helixe - (int)CurveType::circle) + (int)CurveType::circle);
}

double getRandomSize() {
    return double(maxRndSize - minRndSize) / RAND_MAX * std::rand() + minRndSize;
}

double angleDegToRad(const double angleDeg) {
    return angleDeg / 180 * numPi;
}

void outSplitter (char sign = '-') {
    std::string splitter;
    splitter.assign(20, sign);
    std::cout << splitter << std::endl;
}

double dblForOut(const double outVal) {
    return ((outVal + dblPres < 0 || outVal - dblPres > 0) ? outVal : 0.);
}

void vecPartOut(const double outVal, const std::string& suffix, const bool hideZero = true) {
    double outStr = dblForOut(outVal);
    if (outStr != 0 || !hideZero) std::cout << " " << outStr << suffix;
}

void outCoordsByAngle(const std::shared_ptr<Curve>& shape, double angleDegree) {
    Coords3D currCoords = shape->coordsByAngle(angleDegToRad(angleDegree));
    std::cout << "Coords at angle " << angleDegree << " degree: \n";
    std::cout << "X: " << dblForOut(currCoords.X) << "; Y: " << dblForOut(currCoords.Y)
        << "; Z: " << dblForOut(currCoords.Z) << std::endl;
    std::cout << "Vector: ";
    vecPartOut(currCoords.X, "i", false);
    std::cout.setf(std::ios::showpos);
    vecPartOut(currCoords.Y, "j");
    vecPartOut(currCoords.Z, "k");
    std::cout << std::noshowpos << std::endl;
}

void curveOutInfo(const std::shared_ptr<Curve>& shape, const int curveID = -1) {
    std::cout << "Curve ";
    if (curveID >= 0) {
        char buff[3];
        sprintf(buff, "%2d", curveID + 1);
        std::cout << " " << buff << ", ";
    }
    CurveType currType = shape->getType();
    std::cout << "type: ";
    CurveSizeSet sizes = shape->getSizes();
    if (currType == CurveType::circle) std::cout << "circle" << std::endl
        << "radius = " << sizes.radius << std::endl;
    else if (currType == CurveType::ellipse) std::cout << "ellipse" << std::endl
        << "radius X: " << sizes.radiusX << "; radius Y: " << sizes.radiusY << std::endl;
    else if (currType == CurveType::helixe) std::cout << "helixe" << std::endl
        << "radius: " << sizes.radius << "; step: " << sizes.step << std::endl;

}

int main() {

    /*
    // Check curves geometry
    std::shared_ptr<Circle> testCurve = std::make_shared<Circle>(15);
    //std::shared_ptr<Circle> testCurve = std::make_shared<Circle>(0);
    //std::shared_ptr<Circle> testCurve = std::make_shared<Circle>(-1);
    //
    //std::shared_ptr<Ellipse> testCurve = std::make_shared<Ellipse>(20, 5);
    //std::shared_ptr<Ellipse> testCurve = std::make_shared<Ellipse>(0, 0);
    //std::shared_ptr<Ellipse> testCurve = std::make_shared<Ellipse>(-5, -3);
    //
    //std::shared_ptr<Helixe> testCurve = std::make_shared<Helixe>(20, 10);
    //std::shared_ptr<Helixe> testCurve = std::make_shared<Helixe>(0, 0);
    //std::shared_ptr<Helixe> testCurve = std::make_shared<Helixe>(-1, -8);
    //
    outSplitter('=');
    std::cout << "Curve step test:\n";
    outSplitter();
    curveOutInfo(testCurve);
    for(int testAngleDeg = 0; testAngleDeg <= 720; testAngleDeg += 15) {
        outSplitter();
        outCoordsByAngle(testCurve, testAngleDeg);
    }
    return 0;
    */

    std::srand(std::time(nullptr));

    // Create random container
    std::vector<std::shared_ptr<Curve>> curveList;
    for (int i = 0; i < 20; ++i) {
        CurveType currType = getRandomCurveType();
        if (currType == CurveType::circle) curveList.push_back(
                std::make_shared<Circle>(getRandomSize()));
        else if (currType == CurveType::ellipse)  curveList.push_back(
                std::make_shared<Ellipse>(getRandomSize(), getRandomSize()));
        else if (currType == CurveType::helixe)  curveList.push_back(
                std::make_shared<Helixe>(getRandomSize(), getRandomSize()));
    }

    // Set for circle progress
    std::map<double, std::vector<std::shared_ptr<Curve>*>> circleRadiusSeqUp;
    // Out random container & work with circle
    outSplitter('=');
    std::cout << "Random curves list:\n";
    for (int i = 0; i < curveList.size(); ++i) {
        outSplitter();
        std::shared_ptr<Curve> currCurve = curveList[i];
        curveOutInfo(currCurve, i);
        outCoordsByAngle(currCurve, 45); // PI / 4 position
        // Circle sequence size progress...
        if (currCurve->getType() == CurveType::circle) {
            CurveSizeSet circleSizes = currCurve->getSizes();
            circleRadiusSeqUp[circleSizes.radius].emplace_back(&curveList[i]);
        }
    }

    // Create circles ordered list
    std::vector<std::shared_ptr<Curve>*> circleList;
    double circleRadiusTotal = 0;
    for (const auto& currCircleRadPair: circleRadiusSeqUp) {
        for (const auto currCirclePt : currCircleRadPair.second) {
            circleList.push_back(currCirclePt);
            circleRadiusTotal += currCircleRadPair.first;
        }
    }

    // Out circles result
    outSplitter('=');
    std::cout << "Circles list:\n";
    for (int i = 0; i < circleList.size(); ++i) {
        outSplitter();
        curveOutInfo(*circleList[i], i);
        /*
        // Check sync
        CurveSizeSet testSize;
        testSize.radius = 1;
        (*circleList[i])->setSizes(testSize);
        */
    }
    outSplitter('=');
    std::cout << "Total radius sum of circles: " << circleRadiusTotal << std::endl;

    // Sync control
    /*
    outSplitter('=');
    std::cout << "Synchronization control:\n";
    for (int i = 0; i < curveList.size(); ++i) {
        outSplitter();
        curveOutInfo(curveList[i], i);
    }
    */

    return 0;

}
