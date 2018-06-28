exec:
	gcc -std=c99 -g quiz.c -o quiz3

test:exec
	valgrind ./quiz3

report:exec
	valgrind ./quiz3 2> Valgrind_output.txt

.PHONY:clean

clean:
	-rm quiz3 Valgrind_output.txt
