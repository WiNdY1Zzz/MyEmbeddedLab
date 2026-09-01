CC := gcc
CFLAGS := -Wall
TARGET := asmd
RM := rm -rf

$(TARGET):asmd.o main.o
	@$(CC) $(CFLAGS) $^ -o $@
asmd.o:asmd.c amsd.h
	@$(CC) $(CFLAGS) -c $< -o $@
main.o:main.c amsd.h
	@$(CC) $(CFLAGS) -c $< -o $@
.PHONY: clean
clean:
	$(RM) *.o asmd
	@echo "DEL SUCCSESS"
