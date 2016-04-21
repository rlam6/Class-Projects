//// Submitter: cmorte(Morte, Christian)
//
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <limits>                           //I used std::numeric_limits<int>::max()
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArrayQueue<std::string>         WordQueue;
//typedef ics::ArraySet<std::string>           FollowSet;
//typedef ics::pair<WordQueue,FollowSet>       CorpusEntry;
//typedef ics::ArrayPriorityQueue<CorpusEntry> CorpusPQ;     //Convenient to supply gt at construction
//typedef ics::ArrayMap<WordQueue,FollowSet>   Corpus;
//
//
////Return a random word in the words set (use in produce_text)
//std::string random_in_set(const FollowSet& words) {
//  int index = ics::rand_range(1, words.size());
//  int i = 0;
//  for (const std::string& s : words)
//    if (++i == index)
//      return s;
//  return "?";
//}
//
//
////Read an open file of lines of words (separated by spaces) and return a
////  Corpus (Map) of each sequence (Queue) of os (Order-Statistic) words
////  associated with the Set of all words that follow them somewhere in the
////  file.
//Corpus read_corpus(int os, std::ifstream &file) {
//	Corpus corpus;
//	WordQueue wordQueue;
//
//	std::string line;
//	while (getline(file, line)) {
//		wordQueue.enqueue_all( ics::split(line, " ") );
//	}
//
//	for (auto i = wordQueue.begin(); i != wordQueue.end(); i++) {
//		WordQueue targetWord;
//
//		for (auto n = i; n != wordQueue.end(); n++) {
//			if (targetWord.size() == os) {
//				corpus[targetWord].insert(*n);
//				break;
//			}
//			else {
//				targetWord.enqueue(*n);
//			}
//		}
//	}
//	return corpus;
//}
//
//
////Print "Corpus" and all entries in the Corpus, in lexical alphabetical order
////  (with the minimum and maximum set sizes at the end).
////Use a "can be followed by any of" to separate the key word from the Set of words
////  that can follow it.
//
////One queue is lexically greater than another, if its first value is smaller; or if
////  its first value is the same and its second value is smaller; or if its first
////  and second values are the same and its third value is smaller...
////If any of its values is greater than the corresponding value in the other queue,
////  the first queue is not greater.
////Note that the queues sizes are the same: each stores Order-Statistic words
////Important: Use iterators for examining the queue values: DO NOT CALL DEQUEUE.
//
//bool queue_gt(const CorpusEntry& a, const CorpusEntry& b) {
//	auto bIter = b.first.begin();
//
//	for (auto aIter = a.first.begin(); aIter != a.first.end(); (aIter++, bIter++)) {
//
//		if (*aIter < *bIter) { return true;}
//		else if (*aIter > *bIter) { return false;}
//	}
//	return false;
//}
//
//void print_corpus(const Corpus& corpus) {
//	CorpusPQ corpusPQ(queue_gt);
//	int min = 0, max;
//
//	corpusPQ.enqueue_all(corpus);
//
//	std::cout << "Corpus of " << corpus.size() << " entries" << std::endl;
//	for (const CorpusEntry& entry : corpusPQ) {
//		std::cout << "  " << entry.first << " -> " << entry.second << std::endl;
//		if (entry.second.size() > max) { max = entry.second.size();}
//		if (entry.second.size() < min || min == 0) { min = entry.second.size();}
//	}
//	std::cout << "Corpus of " << corpus.size() << " entries" << std::endl;
//	std::cout << "min/max = " << min << "/" << max << std::endl;
//}
//
//
////Return a Queue of words, starting with those in start and including count more
////  randomly selected words using corpus to decide which word comes next.
////If there is no word that follows the previous ones, put "None" into the queue
////  and return immediately this list (whose size is <= start.size() + count).
//WordQueue produce_text(const Corpus& corpus, const WordQueue& start, int count) {
//	WordQueue result {start};
//	WordQueue current = start;
//
//	while (result.size() < count + start.size()) {
//		if ( corpus.has_key(current) ) {
//			const std::string& toBeEnqueued = random_in_set(corpus[current]);
//
//			result.enqueue( toBeEnqueued );
//			current.dequeue();
//			current.enqueue(toBeEnqueued);
//		} else {
//			result.enqueue( "None" );
//			break;
//		}
//	}
//	return result;
//}
//
//
//
////Prompt the user for (a) the order statistic and (b) the file storing the text.
////Read the text as a Corpus and print it appropriately.
////Prompt the user for order statistic words from the text.
////Prompt the user for number of random words to generate
////Call the above functions to solve the problem, and print the appropriate information
//int main() {
//  try {
//	  std::ifstream wordFile;
//	  const int os = ics::prompt_int("Enter the order statistic", 2);
//
//	  ics::safe_open(wordFile,"Enter the name of a file to process","wginput1.txt");
//	  std::cout << std::endl;
//
//	  Corpus corpus = read_corpus(os, wordFile);
//	  print_corpus(corpus);
//
//	  WordQueue start;
//
//	  std::cout << std::endl << "Enter " << os << " words to start with" << std::endl;
//	  for (int i = 1; i <= os; ++i) {
//		  std::stringstream ss;		ss << i;
//		  const std::string word = ics::prompt_string("Enter word " + ss.str());
//
//		  start.enqueue(word);
//	  }
//
//	  const int count = ics::prompt_int("Enter # of words to generate");
//	  const WordQueue producedResult = produce_text(corpus, start, count);
//
//	  std::cout << "Random text = " << producedResult << std::endl;;
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
