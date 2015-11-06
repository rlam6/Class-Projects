#import <iostream>
#import <sstream>
#import "student.hpp"

void outputTotalScores(const Student* students, int len, const int* points, const int* weights, int numArtifacts){
	std::cout << "TOTAL SCORES" << std::endl;
	for (int i=0; i < len; i++){
		Student student = students[i];
		std::cout << student.ID << " " << student.name << " " <<
		calculateTotalScore(student, points, weights, numArtifacts) << std::endl;
	}
}

std::string outputGrade(const Student& student, double A, double B, double C, double D, 
											const int* points, const int* weights, int numArtifacts){

	double score = calculateTotalScore(student, points, weights, numArtifacts);
	if (student.gradeOpt == "G"){
		if (score >= A){ 
			return "A";
		} 
		else if (score >= B){
			return "B";
		}
		else if (score >= C){
			return "C";
		}
		else if (score >= D){
			return "D";
		}
		else {
			return "F";
		}
	} 
	else{
		if (score >= C){
			return "P";
		}
		else {
			return "NP";
		}
	}
}

void outputCutpoints(const Student* students, int len, const int* points, const int* weights, 
								int numArtifacts, const std::string& cutpoint){
	double A, B, C, D;
	std::stringstream ss;
	ss << cutpoint;
	ss >> A >> B >> C >> D;

	for (int i=0; i < len; i++){
		Student student = students[i];
		std::cout << student.ID << " " << student.name << " " <<
		outputGrade(student, A, B, C, D, points, weights, numArtifacts) <<
		std::endl;
	}
}

void outputCutpointSet(int numOfCutpoints, const Student* students, int numOfStudents, const int* points, const int* weights,
													int numArtifacts, const std::string* cutpoints){
	for (int i=0; i < numOfCutpoints; i++){
		std::cout << "CUTPOINT SET " << i + 1 << std::endl;
		outputCutpoints(students, numOfStudents, points, weights, 
					numArtifacts, cutpoints[i]);
	}
}
