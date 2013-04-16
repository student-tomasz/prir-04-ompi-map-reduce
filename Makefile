compiler=mpicc
flags=-Wall
objects=map_reduce.o logs.o jobs.o

all: map_reduce

run: all
	mpiexec -n 4 map_reduce abc.txt

clean:
	rm -rf map_reduce

map_reduce: $(objects)
	$(compiler) $(flags) -o $@ $(objects)

%.o:  %.c %.h
	$(compiler) $(flags) -c $<
