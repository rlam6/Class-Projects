//// Submitter: cmorte(Morte, Christian)
//
//
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArrayQueue<std::string>                InputsQueue;
//typedef ics::ArrayMap<std::string,std::string>      InputStateMap;
//
//typedef ics::ArrayMap<std::string,InputStateMap>    FA;
//typedef ics::pair<std::string,InputStateMap>        FAEntry;
//
//bool gt_FAEntry (const FAEntry& a, const FAEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<FAEntry,gt_FAEntry> FAPQ;
//
//typedef ics::pair<std::string,std::string>          Transition;
//typedef ics::ArrayQueue<Transition>                 TransitionQueue;
//
//
////Read an open file describing the finite automaton (each line starts with
////  a state name followed by pairs of transitions from that state: (input
////  followed by new state, all separated by semicolons), and return a Map
////  whose keys are states and whose associated values are another Map with
////  each input in that state (keys) and the resulting state it leads to.
//const FA read_fa(std::ifstream &file) {
//	FA fa;
//	std::string line;
//
//	while (getline(file, line)){
//		std::vector<std::string> words = ics::split(line, ";");
//		const std::string& state = words[0];
//		std::string input;
//		int index = 1;
//
//		for (auto i = words.begin() + 1; i != words.end(); i++){
//			if (index % 2 == 1) {
//				input = *i;
//			} else {
//				fa[state][input] = *i;
//			}
//			++index;
//		}
//	}
//	return fa;
//}
//
//
////Print a label and all the entries in the finite automaton Map, in
////  alphabetical order of the states: each line has a state, the text
////  "transitions:" and the Map of its transitions.
//void print_fa(const FA& fa) {
//	FAPQ faPQ(gt_FAEntry);
//	faPQ.enqueue_all(fa);
//
//	std::cout << "Finite Automaton Description" << std::endl;
//
//	for (const FAEntry& state : faPQ) {
//		std::cout << "  " << state.first << " transitions: " << state.second << std::endl;
//	}
//}
//
//
////Return a queue of the calculated transition pairs, based on the finite
////  automaton, initial state, and queue of inputs; each pair in the returned
////  queue is of the form: input, new state.
////The first pair contains "" as the input and the initial state.
////If any input i is illegal (does not lead to a state in the finite
////  automaton), then the last pair in the returned queue is i,"None".
//TransitionQueue process(const FA& fa, std::string state, const InputsQueue& inputs) {
//	TransitionQueue transitionQueue;
//	transitionQueue.enqueue( Transition("", state) );
//
//	for (const std::string& input : inputs) {
//
//		if ( fa[state].has_key(input) ) {
//			state = fa[state][input];
//			transitionQueue.enqueue( Transition(input, state) );
//		} else {
//			transitionQueue.enqueue( Transition(input, "None") );
//			break;
//		}
//	}
//	return transitionQueue;
//}
//
//
////Print a TransitionQueue (the result of calling the process function above)
//// in a nice form.
////Print the Start state on the first line; then print each input and the
////  resulting new state (or "illegal input: terminated", if the state is
////  "None") indented on subsequent lines; on the last line, print the Stop
////  state (which may be "None").
//void interpret(TransitionQueue& tq) {  //or TransitionQueue or TransitionQueue&&
//	std::string lastState;
//
//	for (const Transition& transition : tq) {
//		if (transition.first.empty()) {
//			std::cout << "Start state = " << transition.second << std::endl;
//		} else {
//			if (transition.second == "None") {
//					std::cout << "  Input = " << transition.first << "; illegal input: terminated" << std::endl;
//			} else {
//				std::cout << "  Input = " << transition.first << "; new state = " << transition.second << std::endl;
//			}
//		}
//		lastState = transition.second;
//	}
//	std::cout << "Stop state = " << lastState << std::endl;
//}
//
//
//
////Prompt the user for a file, create a finite automaton Map, and print it.
////Prompt the user for a file containing any number of simulation descriptions
////  for the finite automaton to process, one description per line; each
////  description contains a start state followed by its inputs, all separated by
////  semicolons.
////Repeatedly read a description, print that description, put each input in a
////  Queue, process the Queue and print the results in a nice form.
//int main() {
//	try {
//		std::ifstream fa_file;
//		ics::safe_open(fa_file,"Enter the name of a file with a Finite Automaton","faparity.txt");
//		std::cout << std::endl;
//
//		const FA fa = read_fa(fa_file);
//		print_fa(fa);
//		std::cout << std::endl;
//
//		std::ifstream inputs_file;
//		std::string line;
//		ics::safe_open(inputs_file,"Enter the name of a file with the start-state and input","fainputparity.txt");
//
//		while (getline(inputs_file, line)){
//			std::cout << std::endl;
//			InputsQueue inputsQueue;
//			std::vector<std::string> words = ics::split(line, ";");
//			const std::string& startState = words[0];
//
//			std::cout << "Starting new simulation with description: " << line;
//
//			for (auto i = words.begin() + 1; i != words.end(); i++) {
//				inputsQueue.enqueue(*i);
//			}
//
//			TransitionQueue transitionQueue = process(fa, startState, inputsQueue);
//			interpret(transitionQueue);
//		}
//	}
//
//	catch (ics::IcsError& e) {
//		std::cout << e.what() << std::endl;
//	}
//
//	return 0;
//}

//#include <iostream>
//template<class T>
//class TN {
//  public:
//    TN ()                        : left(nullptr), right(nullptr){}
//    TN (const TN<T>& tn)         : value(tn.value), left(tn.next), right(tn.right){}
//    TN (T v, TN<T>* l = nullptr,
//             TN<T>* r = nullptr) : value(v), left(l), right(r){}
//
//    T      value;
//    TN<T>* left;
//    TN<T>* right;
//};
//
//template<class T>
//bool all_less(TN<T>* t, const T& v) {
//	if (t == nullptr)
//		return true;
//	return t->value <= v && all_less(t->left, v) && all_less(t->right, v);
//}
//
//template<class T>
//bool all_greater(TN<T>* t, const T& v) {
//	if (t == nullptr)
//		return true;
//	return t->value >= v && all_greater(t->left, v) && all_greater(t->right, v);
//}
//
//template<class T>
//bool is_BST(TN<T>* t) {
//	if (t == nullptr)
//		return true;
//	return all_less(t->left, t->value) && all_greater(t->right, t->value)
//			&& is_BST(t->left) && is_BST(t->right);
//}
//
//int main() {
////	TN<int>* t = new TN<int>(1, new TN<int>(2, new TN<int>(4)), new TN<int>(3, new TN<int>(5)));
//	TN<int>* t = new TN<int>(40, new TN<int>(15, new TN<int>(10), new TN<int>(26)), new TN<int>(54));
//	TN<char>* ta = new TN<char>('a', new TN<char>('b', new TN<char>('c')), new TN<char>('d', new TN<char>('e')));
//	if (is_BST(t))
//		std::cout << "hey" << std::endl;
//	else
//		std::cout <<"no" << std::endl;
//	return 0;
//}
