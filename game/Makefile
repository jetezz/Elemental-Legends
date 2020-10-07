######################################################################
### MACROS
######################################################################
# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
# $(6) : Optimizacion de compilacion con cache: ccache
define COMPILE
$(2): $(3) $(4)
	$(6) $(1) -o $(2) -c $(3) $(5)
endef

# $(1) : Source file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# $(1) : Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

######################################################################
### CONFIG
######################################################################
APP            := game
CFLAGS         := -Wall -pedantic
CCFLAGS        := $(CFLAGS) -std=c++17
CC             := g++# C++ Compiler
C              := gcc# C Compiler
CPU            := x86_64# CPU por defecto para los include y las libs de fmod studio
MKDIR          := mkdir -p# con el -p se crean todas las carpetas con todas las subcarpetas de manera seguida. Si no se especifica el -p, tocaria poner muchas veces mkdir (una por casa carpeta) para que se creara la estructura de carpetas deseada.
CP             := cp
RM             := rm -f
SRC            := src
OBJ            := obj
LIBDIR         := lib
IRRDIR         := makeStaticLib/irrlichtMakeStLib/source/Irrlicht
IRRSTLIB       := libIrrlicht.a
IRRSTLIBLOC    := makeStaticLib/irrlichtMakeStLib/lib/Linux
IRRFOLDER      := $(LIBDIR)/irrlicht
ALLAS          := $(shell find $(LIBDIR)/ -type f -iname *.a)# con esto, obtenemos todas las librerias estaticas que tenemos que enlazar en "LIBS" a la hora de realizar el enlazado de nuestro juego una vez se ha compilado todo y se han obtenido todos los ficheros ".o" necesarios.
LIBS           := $(ALLAS) -lfmod -lfmodL -lfmodstudio -lfmodstudioL -lglut -lGL -lGLU -lXxf86vm -lXext -lX11# aqui se anyadirian antes de las librerias qque empiezan por "-l", las librerias estaticas (archivos ".a") localizadas en "ALLAS".
INCFMODDIRS    := \
    -I$(LIBDIR)/fmodstudio/api/core/inc \
    -I$(LIBDIR)/fmodstudio/api/studio/inc#aqui se incluyen las cabeceras de fmod studio tanto para la api de bajo nivel como para la de alto nivel
INCDIRS        := -I$(SRC) -I$(LIBDIR) $(INCFMODDIRS)

ifdef RELEASE
	CCFLAGS += -O3
	CFLAGS  += -O3
else
	CCFLAGS += -g
	CFLAGS  += -g
endif

ifdef CACHE
	CCACHE := ccache
else 
	CCACHE :=
endif


# Include shared libs
LOWLEVELFMODLIB   := $(LIBDIR)/fmodstudio/api/core/lib/$(CPU)#librerias de la api de bajo nivel de fmod studio
FMODSTUDIOLIB     := $(LIBDIR)/fmodstudio/api/studio/lib/${CPU}#librerias de la api de alto nivel de fmod studio
INCSHAREDLIBS     := -L$(LOWLEVELFMODLIB) -L$(FMODSTUDIOLIB)#aqui se incluyen tanto las librerias de fmod studio de la api de bajo nivel como de la de alto nivel
LFLAGS            := -Wl,-rpath=\$$ORIGIN/$(dir ${LOWLEVELFMODLIB}),-rpath=\$$ORIGIN/$(dir ${FMODSTUDIOLIB}) -fuse-ld=gold#flags de linkado para poder enlazar la libreria de fmod. El flag "-fuse-ld=gold" sirve para ocultar los warning logicos que aparecen al enlazar la libreria de FMOD para que asi no se muestren errores

# Find cpps, cs, objs, directories and sub-directories
ALLCPPS       := $(shell find $(SRC)/ -type f -iname *.cpp)# se le anyade shell para especificar que es un shell scripting (utilizable desde consola) para que asi pueda ejecutar la instruccion find.
ALLCS         := $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ        := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS       := $(shell find $(SRC) -type d)
OBJSUBDIRS    := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: all clean cleanall e info libs libs-clean libs-cleanall

$(APP): $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(INCSHAREDLIBS) $(LIBS) $(LFLAGS)

# Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),,$(CCFLAGS) $(INCDIRS), $(CCACHE))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),,$(CFLAGS) $(INCDIRS), $(CCACHE))))

# If the directory doesn't exits, I create it, Para que esto se dispare, alguien tiene que requerir la carpeta obj, ya que si no, no se disparara.
$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)

all: $(APP)

e: all
	./$(APP)

clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"

info:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLAS))
	$(info $(LIBS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLOBJ))

## LIB rules
libs:
	$(MAKE) -C $(LIBDIR)

libs-clean:
	$(MAKE) -C $(LIBDIR) clean

libs-cleanall:
	$(MAKE) -C $(LIBDIR) cleanall

## IRRLICHT ENGINE STATIC LIB
irr:
	$(MAKE) -C $(IRRDIR)
	$(MKDIR) $(IRRFOLDER)
	$(CP) $(IRRSTLIBLOC)/$(IRRSTLIB) $(IRRFOLDER)

irr-clean:
	$(MAKE) -C $(IRRDIR) clean

irr-cleanall: irr-clean
	rm $(IRRFOLDER)/$(IRRSTLIB)
	rm $(IRRSTLIBLOC)/$(IRRSTLIB)



# Notas:
#
# El -c indica solo compila. Si se pone primero el archivo y despues el -c, el compilador entiende que tiene que solo compilar el fichero
# de la izquierda. Si se pone otro archivo a la derecha que se corresponda con el nombre del fichero de salida (el cual sera distinto del
# estandar), hay que especificarle la instruccion -o antes del nombre del fichero para que el compilador lo entienda correctamente. Si se
# pone primero el fichero de salida poniendo primero el -o y despues el -c con el fichero de entrada, funciona de la misma manera.
#
# Find me coge todo lo que hay por debajo del directorio que yo le especifique, y de eso, si yo le hago un -type d, le digo que solo me
# coja los directorios que hay por debajo de ese directorio, incluyendo al mismo. Si yo, en lugar de pasarle un -type d, le paso un -type f,
# le digo que me saque todos los ficheros que haya. Si yo quiero filtrar por un tipo en concreto de fichero, es decir, por su extension, le
# coloco la directiva -iname (iname porque me permite sacar el fichero tanto si esta en mayusculas como en minusculas a diferencia de name
# que lo saca solo si esta en minusculas, util para cuando no se sabe como esta guardado el fichero) seguido de *.cpp para indicarle que
# quiero todos los ficheros con la extension ".cpp".
#
# A la hora de crear la estructura de carpetas de obj, yo he de poner que el objetivo es generar todos los subdirectorios que tiene obj y
# no obj solo ya que, que se ejecute mkdir solo dependeria de que no se haya creado la carpeta obj cuando deberia de saltar si alguno de
# los subdirectorios que hay dentro de dicha carpeta no existe, con el fin de siempre tenerlos todos.
#
# La instruccion $(OBJ)/%.o es un shell script que ejecute 2 partes por separado, de manera que, tiene en cuenta los ficheros que comiencen con
# la ruta obj/ y despues cualquier cosa .o, por lo que puedo realizar la comparacion de equivalencias entre los ficherso cpp ubicados en src y
# los ubicados en obj.
#
# En el clean es TRASCENDENTAL indicar en el rm -rf el "./" ya que si por un casual OBJ vale cadena vacia BORRAS el disco duro al completo ya que
# -rf indica un borrado de todos los ficheros junto con sus directorios de manera recursiva. Es por eso que hay que indicarle que lo haga a
# partir del directorio actual en el que se encuentra el makefile ya que, si tal caso llegara a producirse, solo se borraria todo lo que contiene
# el directorio actual y no todo el disco duro al completo como pasaba antes si no se especificaba la ruta relativa mediante "./".
# 
# En esta version del makefile no creo dependencia con los archivos ".h" o ".hpp" del juego, pero la macro esta hecha por si se quiere emplear
# dicha dependencia con la consecuencia de que necesitaremos siempre un fichero ".h" o ".hpp" por cada fichero ".c" o ".cpp" que tengamos en
# el juego. Simplemente, habria que colocar la siguiente llamada entre el espacio vacio de las 2 comas del foreach en donde se crean todas las
# reglas para cada archivo ".c" y ".cpp", para crear esa dependencia con los archivos ".h" y ".hpp" respectivamente: $(call C2H,$(F)).
#
# Con if-else se especifica en mi makefile principal (el cual compilara mi codigo) que compile por defecto en DEBUG anyadiendo su flag
# correspondiente a los flags que se utilizaran durante la compilacion de cada archivo por separado. Esto es asi ya que, como es mi codigo,
# me interesa compilarlo durante el desarrollo en modo DEBUG para ser mas rapido y eficiente para asi poder ir analizando lo que sucede en mi
# codigo mientras lo voy desarrollando. Cuando el juego estuviera terminado, se compilaria mediante RELEASE para asi compilar con optimizaciones
# mediante el flag "-O3" y que asi compilara todos los ficheros mas rapidamente.
#
# A las variables que he definido, a la hora de realizar una prueba puntual, le puedo pasar yo mediante linea de comandos en la terminal, el
# valor que quiero que tengan durante la compilacion de la siguiente manera: "make CC=clang++". De esta manera no tengo que modificar mi
# makefile cada vez que quiero hacer diferentes pruebas para distintos compiladores que seran en momentos puntuales durante el desarrollo del
# juego. Esta es la manera de pasarle parametros al make cuando se necesite en un momento puntual del desarrollo del juego.
#
# Hay que expecificarle tambien como flag a los archivos de c++ el estandar de c++ que debemos utilizar para compilar el juego, ya que,
# actualmente, hay bastantes versiones distintas y es por eso por lo que hay que especificarle con cual queremos compilar los archivos de c++.
# Utilizaremos c++17 (ya que es la ultima version mas actualizada estable) para compilar los archivos de c++, y eso lo indicamos de la siguiente
# manera: "-std:c++17". Esto ultimo se la anyadimos a los flags de c++ y con esto ya compilariamos nuestro juego en esta version del compilador.
# Si no lo especificamos, cada ordenador compilaria el juego con la version de compilador que tuviera por defecto, la cual podria ser c++98,
# c++11 o c++14 (tambien es posible que fuese c++17, pero es menos probable al ser la mas actual). Esto provocaria numerosos errores como el
# denominado "comportamiento indefinido" ya que no todos los compiladores soportan y hacen lo mismo lo que puede provocar resultados extranyos
# a la hora de compilar y ejecutar el juego (eso si te deja compilarlo, ya que pueden haber instrucciones no definidas en el compilador por
# defecto que se este usando que si que esten en c++17, lo que puede provocar incluso errores de compilacion estando el codigo bien 
# implementado, aunque ese seria un error menor comparado con el "comportamiento indefinido" que puede producirse si no se especifica desde un
# principio, la version del compilador que debe utilizarse para compilar el juego en c++).
#
# La libreria dinamica de -lIrrlicht ya no hace falta anyadirla si utilizas la libreria estatica de irrlicht, la he quitado precisamente porque
# utilizo irrlicht como libreria estatica, incluyendola mediante la macro "ALLAS" creada.
#
# Todos los -l incluidos son las librerias dinamicas que utiliza irrlicht para poder funcionar (entre ellas se destacan las propias de OpenGL,
# entre otras).
#
