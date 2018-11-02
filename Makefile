
OBJECTS = testes.o estruturas.o matrizes.o \
          algebra.o quadratura.o geometrias.o

DEPEND = testes.cpp estruturas.h matrizes.h \
		 algebra.h ponto.h graus.h no.h apoio.h\
		 materiais.h quadratura.h geometrias.h

all: teste

teste: testes.o
	$(CXX) testes.o -o teste

testes.o: testes.cpp

# estruturas.o: estruturas.h
# 	$(CXX) $(CFLAGS) estruturas.h
#
# matrizes.o: matrizes.h
# 	$(CXX) $(CFLAGS) matrizes.h
#
# algebra.o: algebra.h
# 	$(CXX) $(CFLAGS) algebra.h
#
# quadratura.o: quadratura.h
# 	$(CXX) $(CFLAGS) quadratura.h
#
# geometrias.o: geometrias.h
# 	$(CXX) $(CFLAGS) geometrias.h

# move:
# 	mv *.o arquivos0

.PHONY : clean

clean:
	$(RM) $(OBJECTS) teste
