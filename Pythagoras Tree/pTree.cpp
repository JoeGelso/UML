#include "pTree.hpp"

pTree::pTree()
{
}
void pTree::generate(int n, sf::Vector2f left, sf::Vector2f right)
{
  if (n == 0)
  {
    return;
  }
  sf::Vector2f newLeft, newRight, newMid;
  //draw tree base
  drawSquare(left, right);

  //draw left
  newLeft = getLeft();
  newMid = getMid();
  generate(n - 1, newLeft, newMid);
  pop();

  //draw right
  newRight = getRight();
  newMid = getMid();
  drawSquare(newMid, newRight);

  newLeft = getLeft();
  newMid = getMid();
  generate(n - 1, newLeft, newMid);
  pop();
}

void pTree::drawSquare(sf::Vector2f left, sf::Vector2f right)
{
  points newPoints;
  //draw square
  sf::ConvexShape square(4);
  square.setPoint(0, sf::Vector2f(left));
  square.setPoint(1, sf::Vector2f(right));
  square.setPoint(2, sf::Vector2f((right.x - (left.y - right.y)), (right.y - (right.x - left.x))));
  square.setPoint(3, sf::Vector2f((left.x - (left.y - right.y)), (left.y - (right.x - left.x))));

  square.setFillColor(sf::Color(0, 255, 0));

  //set new points for next square
  newPoints.left.x = (left.x - (left.y - right.y));
  newPoints.left.y = (left.y - (right.x - left.x));
  newPoints.right.x = (right.x - (left.y - right.y));
  newPoints.right.y = (right.y - (right.x - left.x));
  newPoints.mid.x = newPoints.left.x + (((right.x - left.x) - (left.y - right.y)) / 2);
  newPoints.mid.y = newPoints.left.y - ((right.x - left.x + left.y - right.y) / 2);

  // push it to back of vectors
  squares.push_back(square);
  squaresToPop.push_back(square);
  coordinates.push_back(newPoints);
}

void pTree::pop()
{
  squaresToPop.pop_back();
  coordinates.pop_back();
}

sf::Vector2f pTree::getLeft()
{
  return coordinates[coordinates.size() - 1].left;
}

sf::Vector2f pTree::getRight()
{
  return coordinates[coordinates.size() - 1].right;
}

sf::Vector2f pTree::getMid()
{
  return coordinates[coordinates.size() - 1].mid;
}
