all: all1 all2


all1: compile1 exe1 output1
all2: compile2 exe2 output2

compile1:
	g++ main1.cpp -o main1 -std=c++11
exe1: 
	./main1
output1:
	./main1 > ../output/question1

compile2:
	g++ main2.cpp -o main2 -std=c++11
exe2:
	./main2
output2:
	./main2 > ../output/question2




clean :
	rm main1 main2