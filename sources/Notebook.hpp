
#include "Direction.hpp"
using ariel::Direction;

#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;
namespace ariel{
    class Notebook{
        private:
            map<int,map<int,vector<int>>> m;
            int min;
            int max;
        public:
            Notebook();
            void write(int page, int row, int column, Direction d, string s);
            string read(int page, int row, int column, Direction d, int length);
            void erase(int page, int row, int column, Direction d, int length);
            void show(int page);
            int findmin(int page);
            int findmax(int page);
    };

}
