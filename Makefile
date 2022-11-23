СС = g++

FLAGS = -g -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations       \
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fno-exceptions -Wcast-qual -Wconversion \
		-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wmissing-field-initializers          \
		-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel      \
		-Wtype-limits -Wwrite-strings -D_DEBUG

debug:
	$(CC) $(FLAGS) main.cpp src/stack.cpp src/dump.cpp -DMODE_DEBUG -o stack.exe
release:
	$(CC) $(FLAGS) main.cpp src/stack.cpp -DMODE_RELEASE -o stack.exe

clean:
	rm -rf stack.exe log.txt