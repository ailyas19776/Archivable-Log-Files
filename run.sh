g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG -c impl.cpp
g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG -c logman.cpp
g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG impl.o logman.o -o logman
