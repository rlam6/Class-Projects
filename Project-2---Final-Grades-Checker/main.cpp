#import <iostream>
#import <sstream>
#import "listHelper.hpp"
#import "student.hpp"
#import "outputs.hpp"


int main()
{
	int numOfGradedArtifacts;
	int numOfStudents;
	int numOfRawScores;
	int numOfCutpoints;
	
	std::cin >> numOfGradedArtifacts;
	int* points = new int[numOfGradedArtifacts];
	int* weights = new int	[numOfGradedArtifacts];
	fillIntList(numOfGradedArtifacts, points);
	fillIntList(numOfGradedArtifacts, weights);

	std::cin >> numOfStudents;
	Student* students = new Student[numOfStudents];
	fillStudentList(numOfStudents, students);

	std::cin >> numOfRawScores;
	fillStudentScoreList(numOfRawScores, numOfStudents, students);

	outputTotalScores(students, numOfStudents, points, weights, numOfGradedArtifacts);

	std::cin >> numOfCutpoints;
	std::string* cutpoints = new std::string[numOfCutpoints];
	fillStrList(numOfCutpoints, cutpoints);

	outputCutpointSet(numOfCutpoints, students, numOfStudents, points, weights,
						numOfGradedArtifacts, cutpoints);

	delete[] points;
	delete[] weights;
	delete[] students;
	delete[] cutpoints;

    return 0;
}
