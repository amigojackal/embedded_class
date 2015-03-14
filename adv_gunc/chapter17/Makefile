all: qt1 ButtonWindow Layout Buttons LineEdit ComboBox ListView

# May need to change this to suit your Qt installation path
#QTDIR = /usr/lib/qt-3.1

# For SuSE 8.2 
QTDIR = /usr/lib/qt3

# May need to explicitly include moc in your path
#MOC = moc

# For SuSE 8.2
MOC = $(QTDIR)/bin/moc

qt1: qt1.cpp
	g++ -Wall -o qt1 qt1.cpp -I$(QTDIR)/include -L$(QTDIR)/lib -lqt

ButtonWindow: ButtonWindow.cpp ButtonWindow.h
	$(MOC) ButtonWindow.h -o ButtonWindow.moc
	g++ -Wall -o button ButtonWindow.cpp -I$(QTDIR)/include -L$(QTDIR)/lib -lqt

Layout: LayoutWindow.cpp LayoutWindow.h
	$(MOC) LayoutWindow.h -o LayoutWindow.moc
	g++ -Wall -o layout LayoutWindow.cpp -I$(QTDIR)/include -L$(QTDIR)/lib -lqt

Buttons: Buttons.cpp Buttons.h
	$(MOC) Buttons.h -o Buttons.moc
	g++ -Wall -o buttons Buttons.cpp -I$(QTDIR)/include -L$(QTDIR)/lib -lqt
  
LineEdit: LineEdit.cpp LineEdit.h
	$(MOC) LineEdit.h -o LineEdit.moc
	g++ -Wall -o lineedit LineEdit.cpp -I$(QTDIR)/include -L$(QTDIR)/lib -lqt

ComboBox: ComboBox.cpp ComboBox.h
	$(MOC) ComboBox.h -o ComboBox.moc
	g++ -Wall -o combo ComboBox.cpp -I$(QTDIR)/include -L$(QTDIR)/lib -lqt

ListView: ListView.cpp ListView.h
	$(MOC) ListView.h -o ListView.moc
	g++ -Wall -o listview ListView.cpp -I$(QTDIR)/include -L$(QTDIR)/lib -lqt



clean:
	rm -f *.moc qt1 button layout buttons lineedit combo listview
