target=server
src = $(wildcard *.cpp ./http/*.cpp)
obj = $(patsubst %.cpp, %.o, $(src))

include = ./include
CXX = g++
CFLAGS =  -Wall -g 
LDFLAGS = -lpthread



$(target):$(obj)
	$(CXX)  -o $(target) $(obj) -I $(include) $(CFLAGS) $(LDFLAGS)



.PHONY:clean all
clean:
	-rm -rf $(target) 

