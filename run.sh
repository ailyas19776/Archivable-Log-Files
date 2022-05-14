g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG -c archive.cpp
g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG -c main.cpp
g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG archive.o main.o -o logfile
