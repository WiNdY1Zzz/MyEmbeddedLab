x=$(y)
y=hello

a:=$(b)

y += !

z?= new_value
y?=value

.PHONY:all
all:
	@echo "Delay: x=$(x),y=$(y)"
	@echo "Rightnow: x=$(x),a=$(a)"
	@echo "Plus: y=$(y)"
	@echo "condition: z=$(z),y=$(y)"
