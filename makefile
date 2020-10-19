CC=g++
CFLAGS=-I. -std=c++11
LDFLAGS=-l glut -l GL -l GLU -l stdc++

# Triangle
TRIANGLE_BINARY=triangle
TRIANGLE_INPUT=triangle.cpp

# Sphere
SPHERE_BINARY=sphere
SPHERE_INPUT=sphere.cpp

# All
BINARIES=$(TRIANGLE_BINARY) $(SPHERE_BINARY)

all: triangle sphere

triangle: $(TRIANGLE_INPUT)
	 $(CC) -o $(TRIANGLE_BINARY) $(TRIANGLE_INPUT) $(LDFLAGS) $(CFLAGS)

sphere: $(INPUT)
	 $(CC) -o $(SPHERE_BINARY) $(SPHERE_INPUT) $(LDFLAGS) $(CFLAGS)

spherec: $(INPUT)
	 $(CC) -o $(SPHEREC_BINARY) $(SPHEREC_INPUT) $(LDFLAGS) $(CFLAGS)

.PHONY: clean_triangle
clean_triangle:
	rm -rf $(TRIANGLE_BINARY)

.PHONY: clean_sphere
clean_sphere:
	rm -rf $(SPHERE_BINARY)

.PHONY: clean_spherec
clean_spherec:
	rm -rf $(SPHEREC_BINARY)

.PHONY: clean
clean:
	rm -rf $(BINARIES)
