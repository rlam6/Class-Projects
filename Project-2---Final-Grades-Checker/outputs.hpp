#ifndef OUTPUTS_HPP
#define OUTPUTS_HPP

void outputTotalScores(const Student* students, int len, const int* points, const int* weights, int numArtifacts);

void outputCutpoints(const Student* students, int len, const int* points, const int* weights, 
					int numArtifacts, const std::string& cutpoint);

std::string outputGrade(const Student& student, double A, double B, double C, double D, 
											int* points, int* weights, int numArtifacts);

void outputCutpointSet(int numOfCutpoints, const Student* students, int numOfStudents, const int* points, const int* weights,
													int numArtifacts, const std::string* cutpoints);

#endif //OUTPUTS_HPP
