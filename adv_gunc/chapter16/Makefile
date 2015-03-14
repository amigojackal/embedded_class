all: gtk1 gtk2 container buttons spinbutton entry buttons list tree menu1 menu2 

gtk1: gtk1.c
	gcc -Wall -o gtk1 gtk1.c `pkg-config --cflags --libs gtk+-2.0`

gtk2: gtk2.c
	gcc -Wall -o gtk2 gtk2.c `pkg-config --cflags --libs gtk+-2.0`

container: container.c
	gcc -Wall -o container container.c `pkg-config --cflags --libs gtk+-2.0`

buttons: buttons.c
	gcc -Wall -o buttons buttons.c `pkg-config --cflags --libs gtk+-2.0`

spinbutton: spinbutton.c
	gcc -Wall -o spinbutton spinbutton.c `pkg-config --cflags --libs gtk+-2.0`

entry: entry.c
	gcc -Wall -o entry entry.c `pkg-config --cflags --libs gtk+-2.0`
  
list: list.c
	gcc -Wall -o list list.c `pkg-config --cflags --libs gtk+-2.0`

tree: tree.c
	gcc -Wall -o tree tree.c `pkg-config --cflags --libs gtk+-2.0`

menu1: menu1.c
	gcc -Wall -o menu1 menu1.c `pkg-config --cflags --libs libgnome-2.0 libgnomeui-2.0`

menu2: menu1.c
	gcc -Wall -o menu2 menu2.c `pkg-config --cflags --libs libgnome-2.0 libgnomeui-2.0`

clean:
	rm -f gtk1 gtk2 container buttons spinbutton entry list tree menu1 menu2  
