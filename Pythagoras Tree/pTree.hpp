#ifndef pTree_hpp
#define PTree_hpp

#include <SFML/Graphics.hpp>
#include <vector>



class pTree : public sf::Drawable
{
public:
  pTree();
  void generate(int n, sf::Vector2f left, sf::Vector2f right);
  void drawSquare(sf::Vector2f left, sf::Vector2f right);
  void pop();
  sf::Vector2f getLeft();
  sf::Vector2f getRight();
  sf::Vector2f getMid();
  void color();

private:
  struct points {
    sf::Vector2f left;
    sf::Vector2f right;
    sf::Vector2f mid;
  };
  std::vector<points> coordinates;
  std::vector<sf::ConvexShape> squares;
  std::vector<sf::ConvexShape> squaresToPop;
  
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    unsigned int i;
    for(i = 0; i < squares.size(); i++) {  
      target.draw(squares[i],states);
    }
  }
  
};

#endif

