#ifndef DAY_H
#define DAY_H

#include <iostream>
// #include <vector>
#include <SFML/Graphics.hpp>

class Day {
private:
    struct Task {
        int tStartTime; 
        int tEndTime;
        std::string tName;
        char tColor; // FOR TESTING
        sf::RectangleShape tShape; 
    };

    std::vector<Task> _vDayTasks; 
    sf::Text _dayName; // for displaying the day of the week 
    sf::RectangleShape _dayShape; // for displaying the day shape
    int _dayValue; // for which day of the week the day is 

public:
    Day(const int DAY_VALUE); // create a day based on which day of the week it is
    ~Day();
    void createTask (); // create a task for a certain day
    void deleteAllTasks (); // delete all tasks for a day

    sf::Text getName (); // get the name of the day as a text object
    std::string getNameStr (); // FOR TESTING
    void draw(sf::RenderWindow& window, const int DAY_VALUE, const sf::Font FONT); // draw the day in the window (overloaded draw function)
    void drawAllTasks(sf::RenderWindow& window, const sf::Font FONT); // draw all tasks for the day (overloaded draw function)
    bool isMouseOver(sf::RenderWindow& window); // check if the mouse is over the day shape
};
#endif // DAY_H