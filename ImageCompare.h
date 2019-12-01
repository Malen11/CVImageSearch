#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>

namespace CVImageSearch {

	enum DescriptorType {
		ORB = 0,
		KAZE = 1,
		AKAZE = 2,
		BRISK = 3
	};

	enum ComparisionType {
		BRUTEFORCE = 0,
		HAMMING = 1,
		HAMMINGLUT = 2,
		//FLANNBASED = 3,
		//L1 = 4,
		//SL2 = 5
	};

	ref class ImageCompare
	{
	public:
		static double ImageSimilarity(
			std::string searchedImageName,
			std::string checkedImageName,
			int descriptorType,
			int ComparisionType,
			int distanceWindow
		);

		static std::vector<std::string> GetSimilarityImages(
			std::string searchedImageName,
			std::vector<std::string> checkedImageNames,
			double threshold,
			int descriptorType,
			int ComparisionType,
			double checkedPointsProc, 
			double allowedError
		);

		static std::map<DescriptorType, std::string> GetDescriptorTypeAsMap();

		static std::map<ComparisionType, std::string> GetComparisionTypeAsMap();

	private:
		static cv::Ptr<cv::Feature2D> createDetector(
			int descriptorType,
			int featuresNum
		);

		static cv::Ptr<cv::DescriptorMatcher> createMatcher(
			int ComparisionType
		);
	};
}

