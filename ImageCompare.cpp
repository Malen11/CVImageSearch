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

std::vector<std::string> ImageCompare::GetSimilarityImages(std::string searchedImageName, std::vector<std::string> checkedImageNames, double threshold, int descriptorType, int ComparisionType, double checkedPointsProc, double allowedError)
{
	Ptr<Feature2D> detector = ImageCompare::createDetector(descriptorType, 100);
	Ptr<DescriptorMatcher> matcher = ImageCompare::createMatcher(ComparisionType);

	std::vector<KeyPoint> kpts0, kpts1;
	Mat queryDescriptors, trainDescriptors;

	std::vector<std::string> similarImages;
	int matchesInDistance, goodMatches;

	Mat searchedImage = imread(searchedImageName, CV_LOAD_IMAGE_COLOR);
	cvtColor(searchedImage, searchedImage, CV_RGB2GRAY);
	detector->detectAndCompute(searchedImage, noArray(), kpts0, queryDescriptors);

	for each (std::string checkedImageName in checkedImageNames)
	{
		Mat checkedImage = imread(checkedImageName, CV_LOAD_IMAGE_COLOR);
		cvtColor(checkedImage, checkedImage, CV_RGB2GRAY);

		//find PoI
		detector->detectAndCompute(checkedImage, noArray(), kpts1, trainDescriptors);

		//find matches
		std::vector<std::vector< DMatch >> matches;
		std::vector<std::vector< DMatch >> sortedMatches;
		matcher->knnMatch(queryDescriptors, trainDescriptors, matches, 2);

		//sort matches nndr
		for (size_t i = 0; i < matches.size(); i++) {

			double distDiff = matches[i][0].distance / matches[i][1].distance;
			int pos = sortedMatches.size();

			for (size_t j = 0; j < sortedMatches.size(); j++) {

				if (sortedMatches[j][0].distance / sortedMatches[j][1].distance > distDiff) {

					pos = j;
					break;
				}
			}

			sortedMatches.insert(sortedMatches.begin() + pos, matches[i]);
		}

		//take checkedPointsProc * matches.size() matches to check similarity
		//std::vector< DMatch > good_matches;
		std::vector<Point2f> matchedPts0, matchedPts1, testPts;
		for (size_t i = 0; i < checkedPointsProc * sortedMatches.size(); i++) {
			//good_matches.push_back(sortedMatches[i][0]);
			matchedPts0.push_back(kpts0[sortedMatches[i][0].queryIdx].pt);
			matchedPts1.push_back(kpts1[sortedMatches[i][0].trainIdx].pt);
		}

		//calc homography, if we can't, count as missmatch
		Mat homography = cv::findHomography(matchedPts0, matchedPts1, CV_RANSAC, allowedError);
		if (homography.empty()) {
			continue;
		}

		//find good matches
		int goodMatches = 0;
		perspectiveTransform(matchedPts0, testPts, homography);

		for (size_t i = 0; i < matchedPts0.size(); i++) {

			if (sqrt(pow(matchedPts1[i].x - testPts[i].x, 2) + pow(matchedPts1[i].y - testPts[i].y, 2)) < allowedError * allowedError) {

				++goodMatches;
			}
		}
		/*Mat img_matches;
		cv::drawMatches(searchedImage, kpts0, checkedImage, kpts1,
				good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
				std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		resize(img_matches, img_matches, cv::Size(800, 800));
		cv::imshow("ss", img_matches);
		cv::waitKey();*/
		if ((double)goodMatches / matchedPts0.size() >= threshold) {

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
		{ DescriptorType::AKAZE, "AKAZE" },
		{ DescriptorType::BRISK, "BRISK" }
	};

	return descriptorTypeMap;
}

std::map<ComparisionType, std::string> CVImageSearch::ImageCompare::GetComparisionTypeAsMap()
{

	std::map<ComparisionType, std::string> comparisionTypeMap = {
		//{ ComparisionType::FLANNBASED, "FLANNBASED" },
		{ ComparisionType::BRUTEFORCE, "BRUTEFORCE" },
		//{ ComparisionType::L1, "L1" },
		{ ComparisionType::HAMMING, "HAMMING" },
		{ ComparisionType::HAMMINGLUT, "HAMMINGLUT" },
		//{ ComparisionType::SL2, "SL2" }
	};

	return comparisionTypeMap;
}

Ptr<Feature2D> ImageCompare::createDetector(int descriptorType, int featuresNum)
{
	Ptr<Feature2D> detector;

	switch (descriptorType)
	{
	case DescriptorType::ORB:
		detector = ORB::create();
		break;

	case DescriptorType::KAZE:
		detector = KAZE::create();
		break;

	case DescriptorType::AKAZE:
		detector = AKAZE::create();
		break;

	case DescriptorType::BRISK:
		detector = BRISK::create();
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
		matcher = cv::BFMatcher::create(DescriptorMatcher::BRUTEFORCE);
		break;

	/*case ComparisionType::FLANNBASED:
		matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
		break;*/

	case ComparisionType::HAMMING:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
		break;

	case ComparisionType::HAMMINGLUT:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
		break;

	/*case ComparisionType::L1:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_L1);
		break;*/

	/*case ComparisionType::SL2:
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_SL2);
		break;*/

	default:
		throw new std::invalid_argument("Выбран несуществующий тип сопоставления");
	}

	return matcher;
}
