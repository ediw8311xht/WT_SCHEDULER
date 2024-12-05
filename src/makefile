CXX = g++
CXXFLAGS = -Wall -std=c++20
LDLIBS = -lwthttp -lwt -lwtdbo -lwtdbosqlite3

main: main.o User.o Spot.o Calendar.o ScheduleApplication.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

utils.o: utils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp

# clean:
# 	rm -f *.o myprogram
