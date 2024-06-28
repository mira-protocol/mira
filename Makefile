SRC   = $(wildcard source/*.c) $(wildcard source/**/*.c)
DEPS  = $(wildcard source/*.h) $(wildcard source/**/*.h)
OBJ   = $(addsuffix .o,$(subst source/,bin/,$(basename ${SRC})))
OUT   = mira
FLAGS = -std=c99 -Wall -Wextra -pedantic -g
LIBS  = -lreadline

compile: ./bin $(OBJ) $(SRC) $(DEPS)
	$(CC) $(OBJ) $(LIBS) -o $(OUT)

./bin:
	mkdir -p bin

bin/%.o: source/%.c $(DEPS)
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm -r bin/* $(OUT)
	if [ -f bin ]; then rm -r bin; fi
	if [ -f $(OUT) ]; then rm $(OUT); fi


