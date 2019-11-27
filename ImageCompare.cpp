#include "ImageCompare.h"

using namespace cv;
using namespace CVImageSearch;

double ImageCompare::ImageSimilarity(std::string searchedImageName, std::string checkedImageName, int DescriptorType, int ComparisionType, int distanceWindow)
{
	Mat searchedImage = imread(searchedImageName, CV_LOAD_IMAGE_COLOR);
	cvtColor(searchedImage, searchedImage, CV_RGB2GRAY);

	Mat checkedImage = imread(checkedImageName, CV_LOAD_IMAGE_COLOR);
	cvtColor(checkedImage, checkedImage, CV_RGB2GRAY);

	std::vector<KeyPoint> kpts0, kpts1;
	Ptr<Feature2D> detector0, detector1;

	detector0 = ORB::create();
	Mat descriptors0;
	detector0->detectAndCompute(searchedImage, noArray(), kpts0, descriptors0);
	
	detector1 = ORB::create();
	Mat descriptors1;
	detector1->detectAndCompute(checkedImage, noArray(), kpts1, descriptors1);
	
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
	std::vector< DMatch > matches;
	matcher->match(descriptors0, descriptors1, matches);

	int matchesInDistance = 0;
	for each (DMatch match in matches)
	{
		if (match.distance < distanceWindow) {
			++matchesInDistance;
		}
	}

	return (double)matchesInDistance / kpts1.size();
}

std::vector<std::string> ImageCompare::GetSimilarityImages(std::string searchedImageName, std::vector<std::string> checkedImageNames, double threshold, int descriptorType, int ComparisionType, int distanceWindow, int featuresNum)
{
	Ptr<Feature2D> detector = ImageCompare::createDetector(descriptorType, featuresNum);
	Ptr<DescriptorMatcher> matcher = ImageCompare::createMatcher(ComparisionType);

	std::vector<KeyPoint> kpts0, kpts1;
	Mat descriptors0, descriptors1;

	std::vector<std::string> similarImages;

	Mat searchedImage = imread(searchedImageName, CV_LOAD_IMAGE_COLOR);
	cvtColor(searchedImage, searchedImage, CV_RGB2GRAY);
	detector->detectAndCompute(searchedImage, noArray(), kpts0, descriptors0);

	for each (std::string checkedImageName in checkedImageNames)
	{
		Mat checkedImage = imread(checkedImageName, CV_LOAD_IMAGE_COLOR);
		cvtColor(checkedImage, checkedImage, CV_RGB2GRAY);

		detector->detectAndCompute(checkedImage, noArray(), kpts1, descriptors1);

		std::vector< DMatch > matches;
		matcher->match(descriptors0, descriptors1, matches);

		int matchesInDistance = 0;
		for each (DMatch match in matches)
		{
			if (match.distance < distanceWindow) {
				++matchesInDistance;
			}
		}

		if ((double)matchesInDistance / kpts1.size() > threshold) {
			similarImages.push_back(checkedImageName);
		}
	}

	return similarImages;
}

std::map<DescriptorType, std::string> CVImageSearch::ImageCompare::GetDescriptorTypeAsMap()
{
	std::map<DescriptorType, std::string> descriptorTypeMap = {
		{ DescriptorType::ORB, "ORB" },
		{ DescriptorType::KAZE, "KAZE" },
		{ DescriptorType::AKAZE, "AKAZE" }
	};

	return descriptorTypeMap;
}

std::map<ComparisionType, std::string> CVImageSearch::ImageCompare::GetComparisionTypeAsMap()
{

	std::map<ComparisionType, std::string> comparisionTypeMap = {
		{ ComparisionType::FLANNBASED, "FLANNBASED" },
		{ ComparisionType::BRUTEFORCE, "BRUTEFORCE" },
		{ ComparisionType::L1, "L1" },
		{ ComparisionType::HAMMING, "HAMMING" },
		{ ComparisionType::HAMMINGLUT, "HAMMINGLUT" },
		{ ComparisionType::SL2, "SL2" }
	};

	return comparisionTypeMap;
}

Ptr<Feature2D> ImageCompare::createDetector(int descriptorType, int featuresNum)
{
	Ptr<Feature2D> detector;

	switch (descriptorType)
	{
	case DescriptorType::ORB:
		detector = ORB::create(featuresNum);
		break;

	case DescriptorType::KAZE:
		detector = KAZE::create();
		break;

	case DescriptorType::AKAZE:
		detector = AKAZE::create();
		break;

	default:
		throw new std::invalid_argument("Выбран несуществующий тип дескриптора");
	}

	return detector;
}

Ptr<DescriptorMatcher> ImageCompare::createMatcher(int ComparisionType)
{
	Ptr<DescriptorMatcher> matcher;

	switch (ComparisionType)
	{
	case ComparisionType::BRUTEFORCE:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
		break;

	case ComparisionType::FLANNBASED:
		matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
		break;

	case ComparisionType::HAMMING:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
		break;

	case ComparisionType::HAMMINGLUT:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
		break;

	case ComparisionType::L1:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_L1);
		break;

	case ComparisionType::SL2:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_SL2);
		break;

	default:
		throw new std::invalid_argument("Выбран несуществующий тип сопоставления");
	}

	return matcher;
}
