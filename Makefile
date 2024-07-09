build:
	gcc -c -I./raylib/include main.c
	gcc -o ef-pomodoro main.o -L./raylib/lib -l:libraylib.a -lm

run:
	./ef-pomodoro

clean:
	-rm main.o
	-rm ef-pomodoro

install:
	cp ef-pomodoro /usr/local/bin/ef-pomodoro
