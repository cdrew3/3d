CC=g++
CFLAGS=-I. -std=c++11
LDFLAGS=-l glut -l GL -l GLU -l stdc++

# Triangle
TRIANGLE_BINARY=triangle
TRIANGLE_INPUT=triangle.cpp

# Sphere
SPHERE_BINARY=sphere
SPHERE_INPUT=sphere.cpp

# Sphere_basic
SPHERE_BASIC_BINARY=sphere_basic
SPHERE_BASIC_INPUT=sphere_basic.cpp

# All
BINARIES=$(TRIANGLE_BINARY) $(SPHERE_BINARY) $(SPHERE_BASIC_BINARY)

all: triangle sphere sphere_basic

triangle: $(TRIANGLE_INPUT)
	 $(CC) -o $(TRIANGLE_BINARY) $(TRIANGLE_INPUT) $(LDFLAGS) $(CFLAGS)

sphere: $(SPHERE_INPUT)
	 $(CC) -o $(SPHERE_BINARY) $(SPHERE_INPUT) $(LDFLAGS) $(CFLAGS)

sphere_basic: $(SPHERE_BASIC_INPUT)
	 $(CC) -o $(SPHERE_BASIC_BINARY) $(SPHERE_BASIC_INPUT) $(LDFLAGS) $(CFLAGS)

.PHONY: clean_triangle
clean_triangle:
	rm -rf $(TRIANGLE_BINARY)

.PHONY: clean_sphere
clean_sphere:
	rm -rf $(SPHERE_BINARY)

.PHONY: clean_spherec
clean_sphere_basic:
	rm -rf $(SPHERE_BASIC_BINARY)

.PHONY: clean
clean:
	rm -rf $(BINARIES)
