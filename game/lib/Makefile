#########################################################
### MACROS
#########################################################
# $(1) : Source file
# $(2) : Additional instructions
define MAKELIB
$(MAKE) $(2) -C $(1)

endef

#########################################################
### CONFIG
#########################################################
LIBSUBDIRS := $(shell find . -maxdepth 1 -mindepth 1 -type d)# Con las instrucciones "-maxdepth 1" y "-mindepth 1" se le indica al find que el numero de hijo que quieero que obtenga cuando realiza la busqueda sea el correspondiente a la carpeta raiz actual, es decir, que no me saque como resultado un subdirectorio que no sea un subdirectorio immediato de la carpeta raiz actual. Con "-mindepth 1" se le indica que se quieren los hijos (subdirectorios) correspondientes a la carpeta actual, y con "-maxdepth 1" se le indica que solo quiero esos, que no quiero que expanda mas y me obtenga subdirectorios que no sean inmediatos al directorio raiz actual. Con "." se le indica a find que empieze a buscar a partir del directorio raiz actual en el que se encuentra este archivo makefile.

.PHONY:	all clean cleanall info

all:
	$(foreach F,$(LIBSUBDIRS),$(call MAKELIB,$(F)))

clean:
	$(foreach F,$(LIBSUBDIRS),$(call MAKELIB,$(F),clean))

cleanall:
	$(foreach F,$(LIBSUBDIRS),$(call MAKELIB,$(F),cleanall))

info:
	$(info $(LIBSUBDIRS))

# Notas:
#
# En este caso, como la instruccion que se utiliza se corresponde con una que, basicamente, llama a otros makefiles "$(MAKE)" no hay ninguna
# expresion que evaluar ya que en este makefile no se esta generando ningun fichero de salida ya que, lo unico que hace es llamar, tal y como
# ya se ha comentado anteriormente, a otros makefiles de manera recursiva. Es por esto por lo que no se puede utilizar la instruccion "$(eval)"
# en los "foreach" utilizados.
#
# El enter es necesario en la definicion de la macro "MAKELIB" ya que, como esto es un lenguaje de sustitucion, el bucle foreach expande tal
# cual lo que se le indique, y si le ponemos todas las instrucciones make en la misma linea seguidos, el makefile lo interpreta tal cual, por
# lo que se le esta pidiendo al makefile que ejecute un comando que no existe, por eso hay que ponerselo para que expanda una instruccion
# make linea a linea.
#