make:
	g++ *.cpp -std=c++11 -o main
	
run:
	./main

clean:
	rm *.o *.gcov *.gcda *.gcno *.gz *.json *.html *.css output.txt coverage.txt valgrind.txt -f main

coverage:
	make clean
	g++ -g --coverage -dumpbase '' *.cpp -o main
	./main > output.txt
	gcov -f -m -r -j main > coverage.txt 
	gcovr --html-details output.html

valgrind:
	make clean
	make
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --keep-stacktraces=alloc-and-free --error-exitcode=1 -s --log-file=valgrind.txt ./main > output.txt

gdb:
	make clean
	make
	gdb ./main
