######################################################################
### MACROS
######################################################################
# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2): $(3) $(4)
	$(1) -o $(2) -c $(3) $(5)
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
APP       := ejemplo.a
CFLAGS    := -Wall -pedantic
CCFLAGS   := $(CFLAGS) -std=c++14
CC        := g++# C++ Compiler
C         := gcc# C Compiler
RM        := rm -f
AR        := ar
ARFLAGS   := -crs
RANLIB    := ranlib
MKDIR     := mkdir -p# con el -p se crean todas las carpetas con todas las subcarpetas de manera seguida. Si no se especifica el -p, tocaria poner muchas veces mkdir (una por casa carpeta) para que se creara la estructura de carpetas deseada.
SRC       := src
OBJ       := obj
INCDIRS   := -I.

ifdef DEBUG
	CCFLAGS += -g
	CFLAGS  += -g
else
	CCFLAGS += -O3
	CFLAGS  += -O3
endif

ALLCPPS       := $(shell find $(SRC)/ -type f -iname *.cpp)# se le anyade shell para especificar que es un shell scripting (utilizable desde consola) para que asi pueda ejecutar la instruccion find.
ALLCS         := $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ        := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS       := $(shell find $(SRC) -type d)
OBJSUBDIRS    := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: all clean cleanall e info $(DEBUG)

$(APP): $(OBJSUBDIRS) $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)

# Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),,$(CCFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),,$(CFLAGS))))

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
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLOBJ))


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
# La instruccion AR lo que hace es comprimir en un solo archivo "abierto", es decir, no llega a hacer una compresion como haria GZIP por ejemplo
# de todos los .o de la libreria. Una vez se tienen todos puestos uno detras de otro en un fichero .a se le aplica ranlib con tal de crear
# indices que serviran para poder acceder rapidamente de un fichero ".obj" a otro. De esta forma se crean las llamadas librerias estaticas.
#
# A la hora de crear una libreria estatica no se necesitan los enlaces a las librerias dinamicas de las que pueden depender la o las librerias
# estaticas que este generando ya que esos enlaces solo son necesarios en el enlazado final (es decir, en nuestro makefile principal). Es por
# que, en estos makefiles que simplemente compilan una librerias de manera estatica, no hay que incluir las librerias dinamicas que utilizan
# (o pueden utilizar) la libreria que tratamos de compilar de manera estatica.
#
# Con el if-else se anyaden mas flags a la hora de realizar la compilacion de la libreria. En este caso, y dado que quiero hacerlo asi debido
# a uqe es una libreria que ya esta hecha y testeada y si yo no la toco debe de funcionar como deberia, hago que se compile por defecto en
# "-O3" que es una optimizacion de la compilacion (es para que vaya mas rapido). Si yo efectuara un cambio puedo compilar yo a mano en DEBUG
# con tal de observar que puede estar pasando en mi libreria una vez la he modificado yo a mano.
#
