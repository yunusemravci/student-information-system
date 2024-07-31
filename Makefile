# kullanilan derleyici
CC   = gcc

OBJ=PR_111044040.o
OBJ1=PR_111044040_Main.o
# derleyici flaglerimiz
CFLAGS = -c -ansi -pedantic-errors

#source dosyamiz
SOURCES= PR_111044040.c
SOURCES1 = PR_111044040_Main.c
#executable dosyamiz
BIN  = proje
BIN1 = Instructors.bin
BIN2 =	Students.bin
BIN3 =	Users.bin
BIN4 =	Courses.bin
#silmek icin flaglerimiz
RM = rm -f

all: obj

derle:
	$(CC) $(CFLAGS) $(SOURCES) $(SOURCES1)
	
obj: derle
	$(CC) $(OBJ) $(OBJ1) -o $(BIN)

test: obj
	./$(BIN)
test1: obj
	./$(BIN) 23342234123 1234
test2: obj
	./$(BIN) 12334356557 sdffds
calistir: derle
	./$(BIN)
val: derle
	valgrind --leak-check=full ./$(BIN)

clean: 
	${RM} $(OBJ) $(BIN) $(BIN1) $(BIN2) $(BIN3) $(BIN4) 
