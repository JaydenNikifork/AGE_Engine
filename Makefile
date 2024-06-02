CXX = g++-11
CXXFLAGS = -std=c++20 -Wall -g
TARGET = vm
SRCS = *.cc controller/*.cc model/components/*.cc model/handlers/*.cc model/*.cc utility/*.cc view/*.cc
OBJS = $(SRCS:.cpp=.o)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lncurses
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -lncurses
clean:
	rm -f $(TARGET) $(OBJS)