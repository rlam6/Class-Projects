#ifndef STUDENT_HPP
#define STUDENT_HPP

struct Student{
	int ID;
	std::string gradeOpt;
	std::string name;
	std::string scores;
};

Student getStudent();

void fillStudentList(int len, Student* array);

void fillStudentScoreList(int numOfRawScores, int numOfStudents, Student* studentArray);

void fillRawScores(const std::string& s, int len, int* array);

double calculateTotalScore(const Student& student, const int* points, const int* weights, int numArtifacts);

#endif //STUDENT_HPP
