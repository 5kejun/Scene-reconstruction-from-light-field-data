#pragma once

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/ocl/ocl.hpp>
#include "lightfield.h"
#include "LfpLoader.h"

using namespace std;
using namespace cv;
using namespace ocl;

/**
 * The data structure for a light-field from a Light Field Picture (raw.lfp) file.
 *
 * @author      Kai Puth <kai.puth@student.htw-berlin.de>
 * @version     0.1
 * @since       2014-05-27
 */
class LightFieldPicture /*:
	public LightField*/
{
	static const Point IMAGE_ORIGIN;

	Mat rawImage;
	vector<oclMat> subapertureImages;
	oclMat subapertureImageAtlas;

	void extractSubapertureImageAtlas();

	Vec2f mlaCenter, nextLens, nextRow;
	Rect validSpartialCoordinates;
	double lensPitchInPixels;
	double microLensRadiusInPixels;
	double rotationAngle;	// in radians
	Vec2f fromLensCenterToOrigin;

	Mat calibrationMatrix;
	double distanceFromImageToLens;

	void generateCalibrationMatrix();

public:
	typedef Vec3f luminanceType;
	static const int IMAGE_TYPE;

	Size SPARTIAL_RESOLUTION;	// TODO should be lower-case
	Size ANGULAR_RESOLUTION;

	LfpLoader loader;	// TODO should be private

	LightFieldPicture(void);
	LightFieldPicture(const string& pathToFile);
	~LightFieldPicture(void);

	luminanceType getLuminanceI(const int x, const int y,
		const int u, const int v) const;
	luminanceType getLuminanceF(const float x, const float y,
		const float u, const float v) const;

	// retrieve an extracted sub-aperture image
	oclMat getSubapertureImageI(const unsigned short u,
		const unsigned short v) const;

	// interpolate an sub-aperture image
	oclMat getSubapertureImageF(const double u, const double v) const;

	Mat getRawImage() const;
	oclMat getSubapertureImageAtlas() const;

	double getRawFocalLength() const;

	Mat getCalibrationMatrix() const;
	double getDistanceFromImageToLens() const;
	double getLambdaInfinity() const;
};