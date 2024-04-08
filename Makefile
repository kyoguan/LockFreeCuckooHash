all:
	g++ -pthread -ggdb -O3 -I ../L4/inc/ -I ../L4/inc/L4 src/benchmark/main.cpp src/lockfree_hash_table.cpp -L ../L4 -lL4 -ltbb -o benchmark
debug:
	g++ -pthread -ggdb -O3 -I ../L4/inc/ -I ../L4/inc/L4 src/benchmark/main.cpp src/lockfree_hash_table.cpp -L ../L4 -lL4 -ltbb -o benchmark
clean:
	rm benchmark
