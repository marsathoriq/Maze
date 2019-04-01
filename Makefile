da:
	g++ main.cpp DrawingArea.cpp -o main `pkg-config gtkmm-3.0 --cflags --libs`
	
ma:
	g++ m.cpp myarea.cpp -o main `pkg-config gtkmm-3.0 --cflags --libs`

d:
	g++ drive.cpp -o main `pkg-config gtkmm-3.0 --cflags --libs`	

