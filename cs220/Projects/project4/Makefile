all:
	gcc -std=c89 -m32 -Os phase2Answer.c -o phase2Answer
	objdump -d -M intel phase2Answer > phase2Answer.disas

clean:
	rm -f phase2Answer.disas phase2Answer
