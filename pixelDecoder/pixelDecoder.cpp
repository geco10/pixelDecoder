#include<SFML/Graphics.hpp>
#include<cstring>
#pragma warning(disable: 4996);
using namespace sf;
char map[101][101];
char nwMap[101][101];
int x, y;
bool st = false;
void drawMap(RenderWindow& window, int n, int m, int len) {	
	for (int i = 0; i < n; ++i) {		
		for (int j = 0; j < m; ++j) {
			RectangleShape square(sf::Vector2f(len, len));
			square.setFillColor(sf::Color(250, 250, 250));		
			square.setOutlineColor(Color(0, 0, 0));			
			window.draw(square);
		}	
	}
}
void drawPause(RenderWindow& u, bool st, int n, int m, int len) {	
	if (st == false)
		setFillColor(255, 0, 0);
	else		
		setFillColor(0, 225, 0);	
	rectangle(u, len, len, m * len + len, (len * n) / 2);
}
int cOne(int i, int j, int n, int m) {
	int c = 0;	
	if (i - 1 >= 0 && map[i - 1][j] == '#')++c;
	if (i + 1 < n && map[i + 1][j] == '#')++c;
	if (j + 1 < m && map[i][j + 1] == '#')++c;	
	if (j - 1 >= 0 && map[i][j - 1] == '#')++c;	
	if (i - 1 >= 0 && j - 1 >= 0 && map[i - 1][j - 1] == '#')++c;	
	if (i + 1 < n && j + 1 < m && map[i + 1][j + 1] == '#')++c;
	if (i - 1 >= 0 && j + 1 < m && map[i - 1][j + 1] == '#')++c;
	if (i + 1 < n && j - 1 >= 0 && map[i + 1][j - 1] == '#')++c;	
	return c;
}
void newGen(int n, int m) {
	for (int i = 0; i < n; ++i) {		
		for (int j = 0; j < m; j++) {			
			nwMap[i][j] = ' ';		
		}
	}	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int c = cOne(i, j, n, m);
			if (c > 1 && c < 4 && map[i][j] == '#') {	
				nwMap[i][j] = '#';			
			}			
			else			
				if (c == 3 && map[i][j] != '#')nwMap[i][j] = '#';
				else {
					nwMap[i][j] = ' ';
				}		
		}
	}
	for (int i = 0; i < n; ++i) {	
		for (int j = 0; j < m; j++) {	
			map[i][j] = nwMap[i][j];	
		}
	}
}
void newMap(RenderWindow& window, int n, int m, int len) {
	for (int i = 0; i < n; i++) {	
		for (int j = 0; j < m; j++) {		
			if (map[i][j] == '#') {			
				setFillColor(0, 0, 0);		
				rectangle(window, len, len, j * len, i * len);	
			}		
		}	
	}
}
int main() {
	int n = 0;	
	int m = 0;
	int mode;
	int len;
	printf("Mode of program:");
	scanf_s("%i", &mode);	
	while (mode != 1 && mode != 2) {
		printf("There is no mode that you entered,renter the mode:");
		scanf_s("%i", &mode);
	}
	for (int i = 0; i < n; ++i) {		
		for (int j = 0; j < m; j++) {		
			map[i][j] = ' ';		
		}	
	}	
	if (mode == 1) {
		printf("How many squares is x_axis:");
		scanf_s("%i", &m);
		printf("How many squares is y_axis:");	
		scanf_s("%i", &n);		
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; j++) {			
				map[i][j] = ' ';			
			}
		}
	}
	else {
		char name[100];		
		printf("Wich map do you want: ");
		scanf("%s", name);
		char path[20] = "./maps/";
		strcat(path, name);
		strcat(path, ".txt");	
		FILE* f = fopen(path, "r");	
		if (f == NULL) {
			printf("ERROR!");		
			return 1;	
		}		
		int i = 0;		
		for (; fgets(map[i], 100, f)[1] != '\0'; ++i) {}
		n = i;	
		m = strlen(map[0]);	
		fclose(f);	
	}
	printf("How much pixels in square:");
	scanf_s("%i", &len);
	RenderWindow window(VideoMode(1250, 650), "Start!");	
	while (window.isOpen()) {
		int pauseLen = 1000;
		Event event;
		while (window.pollEvent(event)) {	
			if (event.type == sf::Event::Closed) {
				window.close();
			}			
			if (event.key.code == sf::Keyboard::Enter) {
				st = true;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {					
					pauseLen += 100;
				}
				if (event.key.code == sf::Keyboard::Down) {
					pauseLen -= 100;
				}			
			}			
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {	
					if (st == true) {	
						st = false;	
					}					
					else {	
						st = true;		
					}			
				}		
			}
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					/*clear(window);	
					pause(1990);*/	
					x = event.mouseButton.x / len;				
					y = event.mouseButton.y / len;				
					if (map[y][x] == '#') {
						map[y][x] = ' ';
					}				
					else {
						map[y][x] = '#';	
					}			
					//event.mouseButton.x			
					// event.mouseButton.y	
				}		
			}		
		}		
		if (st != true) {		
			clear(window);
			drawPause(window, st, n, m, len);
			drawMap(window, n, m, len);
			newMap(window, n, m, len);			
			window.display();			
			pause(1);
		}	
		else {		
			if (st == true) {				
				clear(window);
				drawMap(window, n, m, len);	
				drawPause(window, st, n, m, len);
				newGen(n, m);
				newMap(window, n, m, len);
				window.display();	
				pause(pauseLen);			
			}		
		}
	}
	return 0;
}