#import <iostream>
#import <string>
#import <sstream>
#import "student.hpp"

Student getStudent(){
	int ID;
	std::string gradeOpt;
	std::string name;

	std::cin >> ID >> gradeOpt;
	std::cin.ignore(1);
	std::getline(std::cin, name);
	Student student{ID, gradeOpt, name};
	return student;
}

void fillStudentList(int len, Student* array){
	for (int i=0; i < len; i++){
		array[i] = getStudent();
	}
}

void fillStudentScoreList(int numOfRawScores, int numOfStudents, Student* studentArray){
	for (int i=0; i < numOfRawScores; i++){
		int ID;
		std::string rawScores;

		std::cin >> ID;
		std::cin.ignore(1);
		std::getline(std::cin, rawScores);

		for (int i=0; i < numOfStudents; i++){
			if (ID == studentArray[i].ID){
				studentArray[i].scores = rawScores;
			}
		}
	}
}

void fillRawScoresList(const std::string& s, int len, int* array){
	std::stringstream ss;
	ss << s;
	for (int i=0; i < len; i++){
		int num;
		ss >> num;
		array[i] = num;
	}
}

double calculateTotalScore(const Student& student, const int* points, const int* weights, int numArtifacts){
	int* rawScores = new int[numArtifacts];
	double result = 0;
	fillRawScoresList(student.scores, numArtifacts, rawScores);
	for (int i=0; i < numArtifacts; i++){
		double rawScore = rawScores[i];
		double pointAmount = points[i];
		double weight = weights[i];
		result += (rawScore / pointAmount) * weight;
	}
	delete[] rawScores;
	return result;

}
