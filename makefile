build:
	g++ main.cpp cli.cpp ui.cpp clipboard.cpp file_collector.cpp file_ignore_list.cpp -o cf --std=c++20 -Wall