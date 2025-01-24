debug: cartridgedebug.o debugger.o lookups.o
	g++ -o debug.exe cartridgedebug.o debugger.o lookups.o

cartridgedebug.o: cartridgedebug.cpp
	g++ -c cartridgedebug.cpp

debugger.o: debugger.cpp
	g++ -c debugger.cpp

lookups.o: lookups.cpp
	g++ -c lookups.cpp

	
# Clean Target to Remove Build Artifacts
clean:
	del /f /q *.o *.exe

# Phony Targets
.PHONY: all clean