# Makefile

CPP = g++
CPPFLAGS = -g -Wall

# Link Libraries including Eigen
CPPOPTS = -c -I ./

LDFLAGS = -L./ -lfreeimage

# Final Files and Intermediate .o files
SOURCES = Vector.cpp Coordinate.cpp Sample.cpp Sampler.cpp Color.cpp BRDF.cpp Ray.cpp Intersection.cpp PointLight.cpp DirectionLight.cpp GeometricPrimitive.cpp LocalGeo.cpp Sphere.cpp Triangle.cpp Camera.cpp Film.cpp RayTracer.cpp Scene.cpp

OBJECTS = Vector.o Coordinate.o Sample.o Sampler.o Color.o BRDF.o Ray.o Intersection.o PointLight.o DirectionLight.o GeometricPrimitive.o LocalGeo.o Sphere.o Triangle.o Camera.o Film.o RayTracer.o Scene.o

TARGET = scene

scene: $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

scene.o :
	$(CPP) $(CPPFLAGS) $(CPPOPTS) $(SOURCES)


default : $(TARGET)

clean : 


