CC=g++
CFLAGS= -fopenmp
all: sec par
sec: clasificador_sec.cpp
	$(CC) $(CFLAGS) clasificador_sec.cpp -o clasificador_sec
par: par_ini par_final
par_ini: clasificador_par_ini.cpp
	$(CC) $(CFLAGS) clasificador_par_ini.cpp -o clasificador_par_ini
par_final: clasificador_par_final.cpp
	$(CC) $(CFLAGS) clasificador_par_final.cpp -o clasificador_par_final
clean:
	$(RM) -f *.csv clasificador_par_ini clasificador_par_final clasificador_sec
