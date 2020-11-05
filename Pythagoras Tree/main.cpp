#include <iostream>
#include <sstream>
#include "pTree.hpp"


int main(int argc, char* argv[])
{
  std::stringstream s;
  pTree tree;
  double l;
  int n;
  sf::Vector2f left, right;
  float num;

  //process command line args
  s << argv[1];
  s >> l;
  s.clear();
  s.str("");
  s << argv[2];
  s >> n;
  
  num = (6*l)/2 - (l/2);
  left.x = num;
  num = 4 * l;
  left.y = num;
  right.y = num;
  num = (((6*l)/2) - (l/2)) + l;
  right.x = num;
  
  tree.drawSquare(left, right);
  left = tree.getLeft();
  right = tree.getMid();
  tree.generate(n,left, right);
 
  sf::RenderWindow window(sf::VideoMode(6*l, 4*l), "ps2");
 
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
	window.close();
      }
    }
    window.clear(sf::Color(50,50,50));
    window.draw(tree);
    window.display();
  }
  return 0;
}


