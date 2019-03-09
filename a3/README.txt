by:Clayton Provan
	Assignement 3
	march 8th,2019

Run program by compiling with make command then run with command line argument coresponding to following values.

1:run brute force anagram
2:run presorting anagram
3:run brute force string searching 
4:run Horspool's algorithm for string searching
5:run Boyer-Moore's alrgorithm for string searching

for string search the data must be in data_5.txt file
for anagram finding the data must be in data_4.txt

example to run brute force anagram:
./test 1



2.4 algorithm analysis:
	Clearly in can be seen that when looking for any longer word the Horspool's agorithm is
	much faster. On average the Horspool's agorithm is around 20% faster than the brute force 
	algorithm. This is clearly because the Horspool's agorithm will move forward further when 
	an unmatchable letter appears and therefore makes less comparisons, and therefore shifts.
	


brute force
searched word| number shifts| run time(milliseconds)| ratio shifts/runtime
w		3335671		28			11988.25
ss		3321318		30			110710.6
res		3308501		29			114086.24
house		3300552		26			126944.3
pest		3300524		26			126943.2
degree		623152		27			23079.7
million		3300526		27			122241.7
programs	3302880		27			122328.88
curricula	3304598		29			113951.65
university	3302282		27			122306.74

							880281.26/10 = 88028.126

Hoors
searched word| number shifts| run 1time(milliseconds) | ratio shifts/runtime
w		3265354		31			105334
ss		1679254		19			88381	
res		1183437		15			78895.8
house		716245		11			65113.18
pest		901082		13			69314
degree		623152		10			62315.2
million		528991		9			58776.77
programs	471245		7			67320.71
curricula	420699		8			52587.38
university	431197		8			53899.63

							701937.665 / 10 = 70193.7665




