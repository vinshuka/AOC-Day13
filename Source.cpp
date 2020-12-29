#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>
//Day13 Part 1
//Given a timestamp and a list of buses represented by an ID number find the bus that leaves the closest to the time stamp, a bus's departure times are multiples 
//of its ID, for example a bus with id 11 would leave at 0, 11, 22, 33, etc... Once you have the closest departure time, subtract it from the timestamp and multiply 
//the bus ID by the difference.

//For this I think we can use a simple for loop where for each bus ID we add it until we hit the first value greater than the timestamp and store it, then we can do 
//each on and check if its less than the stored value.


//Part 2
//We need to find the first value where the timestamps line up based on the offset denoted by x, so 7,13,x,x,59,x,31,19 have the offsets, 0,1,4,6,7 from the first 
//timestamp, the first timestamp where they line up is 1068781, followed by 1068782 offset 1, 1068785 offset 4, 10068787 offset 6, and 1068788 offset 7.

//So looking at some examples online, if we start our timestamp at 0 and make our step 1, then for each offset and bus in our vector we add the offset to the 
//timestamp, and mod it by the bus while this value is greater than zero (true) we add our step to the timestamp, if the value equals 0 (false) we multiply our
//step by the bus, and move to the next value, this is because the next value will be a multiple of the previous bus, so we repeat the same process until we reach
//the timestamp plus offset offset mod bus is 0 for all the buses, this means that the timestamp plus each offset has no remainder and all bus times line up 
//according to the offsets.

std::vector<std::string> getPuzzleInput()
{
	std::vector<std::string> input;

	std::ifstream file;
	std::string line;
	file.open("puzzle-input.txt");
	while (std::getline(file, line))
	{
		input.push_back(line);
	}

	return input;
}

std::vector<int> split(const std::string s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<int> tokens;
	while (getline(ss, item, delim))
	{
		if (item == "x")
			continue;
		else
			tokens.push_back(std::stoi(item));
	}

	return tokens;
}

std::vector<std::string> splitOnDelim(const std::string s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, delim))
	{
			tokens.push_back(item);
	}

	return tokens;
}

long findAnswerPart1(int timestamp, std::vector<int> buses)
{
	int closest = INT_MAX;
	int rightBus = 0;

	std::cout << timestamp << '\n';

	for (auto b : buses)
	{
		int x = 0;
		int target = timestamp + b;

		for (int i = 0; i < target; i += b)
		{
			x = i;
		}

		std::cout << closest << ":" << x << '\n';

		if (x < closest)
		{
			closest = x;
			rightBus = b;
		}
			
	}

	 long diff = closest - timestamp;
	 std::cout << closest << " - " << timestamp << " = " << diff << '\n';

	 long result = rightBus * diff;

	 return result;
}

std::vector<std::pair<int, int>> createPairs(std::vector<std::string> input)
{
	std::vector<std::pair<int, int>> pairs;

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == "x")
			continue;

		int x = std::stoi(input[i]);

		pairs.push_back(std::make_pair(i, x));
	}

	return pairs;
}

long long findAnswerPart2(std::vector<std::pair<int, int>> input)
{

	long long timestamp = 0;
	long long inc = 1;

	for (auto i : input)
	{
		while ((timestamp + i.first) % i.second) 
		{
			timestamp += inc;
		}
		inc *= i.second;
	}

	return timestamp;
}


int main()
{
	std::vector<std::string> input = getPuzzleInput();

	int timestamp = std::stoi(input[0]);

	std::vector<int> buses = split(input[1], ',');

	std::string bus = input[1];

	std::sort(buses.begin(), buses.end());

	std::vector<std::string> busesP2 = splitOnDelim(input[1], ',');

	std::vector<std::pair<int, int>> busPairs = createPairs(busesP2);

	//std::cout << findAnswerPart1(timestamp, buses) << '\n';

	std::cout << findAnswerPart2(busPairs) << '\n';

	return 0;
}