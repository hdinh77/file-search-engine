all: wordsearchcount wordsearchunion

wordsearchcount: bag.cpp file.cpp word.cpp wordsearchcount.cpp
	g++ -std=c++11 -o wordsearchcount bag.cpp file.cpp word.cpp wordsearchcount.cpp

wordsearchunion: bag.cpp file.cpp word.cpp wordsearchunion.cpp
	g++ -std=c++11 -o wordsearchunion bag.cpp file.cpp word.cpp wordsearchunion.cpp


.PHONY: clean
clean:
	rm -f wordsearchunion wordsearchcount
